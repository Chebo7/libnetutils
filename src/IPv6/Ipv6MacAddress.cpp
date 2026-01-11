#include "../../include/netutils/IPv6/Ipv6MacAddress.hpp"

std::string NetUtils::IPv6::Ipv6MacAddress(const std::string interface) {
  int sock = socket(AF_INET6, SOCK_DGRAM, 0);

  if (sock == -1) {
    throw std::runtime_error("Error to create socket");
  }

  struct ifreq ifr;
  memset(&ifr, 0, sizeof(ifr));

  strncpy(ifr.ifr_ifrn.ifrn_name, interface.c_str(), IFNAMSIZ);
  ifr.ifr_ifrn.ifrn_name[IFNAMSIZ - 1] = '\0';

  if (ioctl(sock, SIOCGIFHWADDR, &ifr) == -1) {
    close(sock);
    throw std::runtime_error("Error to get mac address");
  }

  close(sock);

  unsigned char *mac =
      reinterpret_cast<unsigned char *>(ifr.ifr_ifru.ifru_hwaddr.sa_data);

  return std::string(std::format("{:02X}:{:02X}:{:02X}:{:02X}:{:02X}:{:02X}",
                                 mac[0], mac[1], mac[2], mac[3], mac[4],
                                 mac[5]));
}