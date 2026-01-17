#include "../../include/netutils/IPv4/Ipv4InterfaceAddress.hpp"
#include "../../include/netutils/Socket/SmartSocket.hpp"
#include "../../include/netutils/Utils/ThrowSystemError.hpp"

std::string NetUtils::IPv4::Ipv4InterfaceAddress(const std::string interface) {

  if (interface.empty()) {
    throw std::runtime_error(
        "Ipv4InterfaceAddress: The interface name is empty");
  }

  if (interface.size() >= IFNAMSIZ) {
    throw std::runtime_error("Ipv4InterfaceAddress: Interface name too large");
  }

  NetUtils::Socket::SmartSocket sock(AF_INET, SOCK_DGRAM, 0);

  if (sock.getFd() == -1) {
    throw std::runtime_error("Ipv4InterfaceAddress: Error to create socket");
  }

  struct ifreq ifr;
  memset(&ifr, 0, sizeof(ifr));

  strncpy(ifr.ifr_ifrn.ifrn_name, interface.c_str(), IFNAMSIZ);
  ifr.ifr_ifrn.ifrn_name[IFNAMSIZ - 1] = '\0';

  if (ioctl(sock, SIOCGIFADDR, &ifr) == -1) {
    NetUtils::Utils::ThrowSystemError("Ipv4InterfaceAddress", errno);
  }

  struct sockaddr_in *addr = (struct sockaddr_in *)&ifr.ifr_ifru.ifru_addr;
  char ipAddrChar[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &addr->sin_addr, ipAddrChar, INET_ADDRSTRLEN);

  return ipAddrChar;
}
