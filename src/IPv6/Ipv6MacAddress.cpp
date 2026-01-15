#include "../../include/netutils/IPv6/Ipv6MacAddress.hpp"
#include "../../include/netutils/Socket/SmartSocket.hpp"

std::string NetUtils::IPv6::Ipv6MacAddress(const std::string interface) {

  if (interface.empty()) {
    throw std::runtime_error("Ipv6MacAddress: The interface name is empty");
  }

  if (interface.size() >= IFNAMSIZ) {
    throw std::runtime_error("Ipv6MacAddress: Interface name too large");
  }

  NetUtils::Socket::SmartSocket sock(AF_INET6, SOCK_DGRAM, 0);

  if (sock == -1) {
    throw std::runtime_error("Ipv6MacAddress: Error to create socket");
  }

  struct ifreq ifr;
  memset(&ifr, 0, sizeof(ifr));

  strncpy(ifr.ifr_ifrn.ifrn_name, interface.c_str(), IFNAMSIZ);
  ifr.ifr_ifrn.ifrn_name[IFNAMSIZ - 1] = '\0';

  if (ioctl(sock, SIOCGIFHWADDR, &ifr) == -1) {
    switch (errno) {
    case EBADF:
      throw std::runtime_error("Ipv6MacAddress: Bad file descriptor");

    case EFAULT:
      throw std::runtime_error("Ipv6MacAddress: Bad address");

    case EINVAL:
      throw std::runtime_error("Ipv6MacAddress: Invalid argument");

    case ENODEV:
      throw std::runtime_error("Ipv6MacAddress: No such device");

    case ENOTTY:
      throw std::runtime_error(
          "Ipv6MacAddress: Inappropriate ioctl for device");

    case ENXIO:
      throw std::runtime_error("Ipv6MacAddress: No such device or address");

    default:
      throw std::runtime_error("Ipv6MacAddress: " + std::to_string(errno));
    }
  }

  unsigned char *mac =
      reinterpret_cast<unsigned char *>(ifr.ifr_ifru.ifru_hwaddr.sa_data);

  return std::string(std::format("{:02X}:{:02X}:{:02X}:{:02X}:{:02X}:{:02X}",
                                 mac[0], mac[1], mac[2], mac[3], mac[4],
                                 mac[5]));
}