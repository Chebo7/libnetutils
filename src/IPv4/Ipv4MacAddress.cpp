#include "../../include/netutils/IPv4/Ipv4MacAddress.hpp"

std::string NetUtils::IPv4::Ipv4MacAddress(const std::string interface) {

  if (interface.empty()) {
    throw std::runtime_error("Ipv4MacAddress: The interface name is empty");
  }

  if (interface.size() >= IFNAMSIZ) {
    throw std::runtime_error("Ipv4MacAddress: Interface name too large");
  }

  int sock = socket(AF_INET, SOCK_DGRAM, 0);

  if (sock == -1) {
    throw std::runtime_error("Ipv4MacAddress: Error to create socket");
  }

  struct ifreq ifr;
  memset(&ifr, 0, sizeof(ifr));

  strncpy(ifr.ifr_ifrn.ifrn_name, interface.c_str(), IFNAMSIZ);
  ifr.ifr_ifrn.ifrn_name[IFNAMSIZ - 1] = '\0';

  if (ioctl(sock, SIOCGIFHWADDR, &ifr) == -1) {
    switch (errno) {
    case EBADF:
      throw std::runtime_error("Ipv4IndexInterface: Bad file descriptor");

    case EFAULT:
      throw std::runtime_error("Ipv4IndexInterface: Bad address");

    case EINVAL:
      throw std::runtime_error("Ipv4IndexInterface: Invalid argument");

    case ENODEV:
      throw std::runtime_error("Ipv4IndexInterface: No such device");

    case ENOTTY:
      throw std::runtime_error(
          "Ipv4IndexInterface: Inappropriate ioctl for device");

    case ENXIO:
      throw std::runtime_error("Ipv4IndexInterface: No such device or address");

    default:
      throw std::runtime_error("Ipv4IndexInterface: " + std::to_string(errno));
    }
  }

  close(sock);

  unsigned char *mac =
      reinterpret_cast<unsigned char *>(ifr.ifr_ifru.ifru_hwaddr.sa_data);

  return std::string(std::format("{:02X}:{:02X}:{:02X}:{:02X}:{:02X}:{:02X}",
                                 mac[0], mac[1], mac[2], mac[3], mac[4],
                                 mac[5]));
}