#include "../include/netutils/Ipv6InterfaceAddress.hpp"

std::string NetUtils::Ipv6InterfaceAddress(const std::string interface) {

  struct ifaddrs *ifaddr, *ifa;

  if (getifaddrs(&ifaddr) == -1) {
    throw std::runtime_error("Unable to get network interfaces");
  }

  struct sockaddr_in6 *ipv6Addr = nullptr;
  bool interfaceIsFound = false;

  for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
    if (ifa->ifa_addr != nullptr && ifa->ifa_addr->sa_family == AF_INET6 &&
        strcmp(ifa->ifa_name, interface.c_str()) == 0) {
      ipv6Addr = (struct sockaddr_in6 *)ifa->ifa_addr;
      interfaceIsFound = true;
    }
  }

  if (!interfaceIsFound) {
    freeifaddrs(ifaddr);
    throw std::runtime_error("Interface not found");
  }

  if (ipv6Addr == nullptr) {
    std::runtime_error("The interface has no address");
  }

  char ipStr[INET6_ADDRSTRLEN];
  inet_ntop(AF_INET6, &(ipv6Addr->sin6_addr), ipStr, INET6_ADDRSTRLEN);

  std::string address = ipStr;

  freeifaddrs(ifaddr);

  return address;
}
