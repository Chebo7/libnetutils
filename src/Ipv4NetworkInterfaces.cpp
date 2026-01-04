#include "../include/netutils/Ipv4NetworkInterfaces.hpp"

std::vector<std::string> NetUtils::Ipv4NetworkInterfaces() {
  struct ifaddrs *ifaddr, *ifa;

  if (getifaddrs(&ifaddr) == -1) {
    throw "Unable to get network interfaces";
  }

  std::vector<std::string> interfaces;

  for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
    if (ifa->ifa_addr != nullptr && ifa->ifa_addr->sa_family == AF_INET) {
      interfaces.emplace_back(ifa->ifa_name);
    }
  }

  freeifaddrs(ifaddr);

  return interfaces;
}