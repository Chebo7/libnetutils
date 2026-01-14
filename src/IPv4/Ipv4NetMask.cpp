#include "../../include/netutils/IPv4/Ipv4NetMask.hpp"
#include "../../include/netutils/Socket/SmartSocket.hpp"

std::string NetUtils::IPv4::Ipv4NetMask(const std::string interface) {

  if (interface.empty()) {
    throw std::runtime_error("Ipv4NetMask: The interface name is empty");
  }

  if (interface.size() >= IFNAMSIZ) {
    throw std::runtime_error("Ipv4NetMask: Interface name too large");
  }

  NetUtils::Socket::SmartSocket sock(AF_INET, SOCK_DGRAM, 0);

  if (sock == -1) {
    throw std::runtime_error("Ipv4NetMask: Error to create socket");
  }

  struct ifreq ifr;
  memset(&ifr, 0, sizeof(ifr));

  strncpy(ifr.ifr_ifrn.ifrn_name, interface.c_str(), IFNAMSIZ);
  ifr.ifr_ifrn.ifrn_name[IFNAMSIZ - 1] = '\0';

  if (ioctl(sock, SIOCGIFNETMASK, &ifr) == -1) {
    switch (errno) {
    case ENODEV:
      throw std::runtime_error("Ipv4NetMask: No such device");

    case EBADF:
      throw std::runtime_error("Ipv4NetMask: Bad file descriptor");

    case EFAULT:
      throw std::runtime_error("Ipv4NetMask: Bad address");

    case ENXIO:
      throw std::runtime_error("Ipv4IndexInterface: No such device or address");

    default:
      throw std::runtime_error(
          std::format("Ipv4NetMask: {}", std::to_string(errno)));
    }
  }

  struct sockaddr_in *sckddr =
      reinterpret_cast<struct sockaddr_in *>(&ifr.ifr_ifru.ifru_netmask);

  char netMask[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &sckddr->sin_addr, netMask, INET_ADDRSTRLEN);
  return std::string(netMask);
}