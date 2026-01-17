#include "../../include/netutils/IPv4/Ipv4IndexInterface.hpp"
#include "../../include/netutils/Socket/SmartSocket.hpp"
#include "../../include/netutils/Utils/ThrowSystemError.hpp"

int NetUtils::IPv4::Ipv4IndexInterface(std::string interface) {

  if (interface.empty()) {
    throw std::runtime_error("Ipv4IndexInterface: The interface name is empty");
  }

  if (interface.size() >= IFNAMSIZ) {
    throw std::runtime_error("Ipv4IndexInterface: Interface name too large");
  }

  NetUtils::Socket::SmartSocket sock(AF_INET, SOCK_DGRAM, 0);

  if (sock == -1) {
    throw std::runtime_error("Ipv4IndexInterface: Error to create socket");
  }

  struct ifreq ifr;
  memset(&ifr, 0, sizeof(ifr));

  strncpy(ifr.ifr_ifrn.ifrn_name, interface.c_str(), IFNAMSIZ);

  if (ioctl(sock, SIOCGIFINDEX, &ifr) == -1) {
    NetUtils::Utils::ThrowSystemError("Ipv4IndexInterface", errno);
  }

  return ifr.ifr_ifru.ifru_ivalue;
}