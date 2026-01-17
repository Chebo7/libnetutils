#include "../../include/netutils/IPv6/Ipv6InterfaceAddress.hpp"
#include "../../include/netutils/Socket/SmartSocket.hpp"
#include "../../include/netutils/Utils/ThrowSystemError.hpp"

std::string NetUtils::IPv6::Ipv6InterfaceAddress(const std::string interface) {

  if (interface.empty()) {
    throw std::runtime_error(
        "Ipv6InterfaceAddress: The interface name is empty");
  }

  if (interface.size() >= IFNAMSIZ) {
    throw std::runtime_error("Ipv6InterfaceAddress: Interface name too large");
  }

  NetUtils::Socket::SmartSocket sock(AF_INET6, SOCK_DGRAM, 0);

  if (sock.getFd() == -1) {
    throw std::runtime_error("Ipv6InterfaceAddress: Error to create socket");
  }

  struct ifreq ifr;
  memset(&ifr, 0, sizeof(ifr));

  strncpy(ifr.ifr_ifrn.ifrn_name, interface.c_str(), IFNAMSIZ);
  ifr.ifr_ifrn.ifrn_name[IFNAMSIZ - 1] = '\0';

  if (ioctl(sock, SIOCGIFADDR, &ifr) == -1) {
    NetUtils::Utils::ThrowSystemError("Ipv6InterfaceAddress", errno);
  }

  struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)&ifr.ifr_ifru.ifru_addr;
  char ipAddrChar[INET6_ADDRSTRLEN];

  inet_ntop(AF_INET6, &addr6->sin6_addr, ipAddrChar, INET6_ADDRSTRLEN);

  return ipAddrChar;
}
