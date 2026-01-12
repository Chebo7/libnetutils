#include "../../include/netutils/IPv4/Ipv4IndexInterface.hpp"
#include "../../include/netutils/Socket/SmartSocket.hpp"

int NetUtils::IPv4::Ipv4IndexInterface(std::string interface) {
  NetUtils::Socket::SmartSocket sock(AF_INET, SOCK_DGRAM, 0);

  if (sock == -1) {
    throw std::runtime_error("Error to create socket");
  }

  struct ifreq ifr;
  memset(&ifr, 0, sizeof(ifr));

  strncpy(ifr.ifr_ifrn.ifrn_name, interface.c_str(), IFNAMSIZ);

  if (ioctl(sock, SIOCGIFINDEX, &ifr)) {
    throw std::runtime_error("Error to get index");
  }

  return ifr.ifr_ifru.ifru_ivalue;
}