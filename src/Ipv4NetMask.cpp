#include "../include/netutils/Ipv4NetMask.hpp"

std::string NetUtils::Ipv4NetMask(const std::string interface) {
  int sock = socket(AF_INET, SOCK_DGRAM, 0);

  if (sock == -1) {
    throw std::runtime_error("Error to create socket");
  }

  struct ifreq ifr;
  memset(&ifr, 0, sizeof(ifr));

  strncpy(ifr.ifr_ifrn.ifrn_name, interface.c_str(), IFNAMSIZ);
  ifr.ifr_ifrn.ifrn_name[IFNAMSIZ - 1] = '\0';

  if (ioctl(sock, SIOCGIFNETMASK, &ifr) == -1) {
    close(sock);
    throw std::runtime_error("Error to get netmask");
  }

  close(sock);

  struct sockaddr_in *sckddr =
      reinterpret_cast<struct sockaddr_in *>(&ifr.ifr_ifru.ifru_netmask);

  char netMask[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &sckddr->sin_addr, netMask, INET_ADDRSTRLEN);
  return std::string(netMask);
}