#include "../include/netutils/Ipv4InterfaceAddress.hpp"

std::string NetUtils::Ipv4InterfaceAddress(const std::string interface) {

  struct ifaddrs *ifaddr, *ifa;

  if (getifaddrs(&ifaddr) == -1) {
    throw std::runtime_error("Unable to get network interfaces");
  }

  struct sockaddr_in *ipv4Addr = nullptr;
  bool interfaceIsFound = false;

  for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
    if (ifa->ifa_addr != nullptr && ifa->ifa_addr->sa_family == AF_INET &&
        strcmp(ifa->ifa_name, interface.c_str()) == 0) {
      ipv4Addr = (struct sockaddr_in *)ifa->ifa_addr;
      interfaceIsFound = true;
    }
  }

  if (!interfaceIsFound) {
    freeifaddrs(ifaddr);
    throw std::runtime_error("Interface not found");
  }

  if (ipv4Addr == nullptr) {
    std::runtime_error("The interface has no address");
  }

  char ipStr[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &(ipv4Addr->sin_addr), ipStr, INET_ADDRSTRLEN);

  std::string address = ipStr;

  freeifaddrs(ifaddr);

  return address;
}
