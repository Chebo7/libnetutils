#include "../../include/netutils/IPv6/Ipv6NetworkInterfaces.hpp"
#include "../../include/netutils/Utils/ThrowSystemError.hpp"

std::vector<std::string> NetUtils::IPv6::Ipv6NetworkInterfaces() {
  struct ifaddrs *ifaddr, *ifa;

  if (getifaddrs(&ifaddr) == -1) {
    freeifaddrs(ifaddr);
    NetUtils::Utils::ThrowSystemError("Ipv6NetworkInterfaces", errno);
  }

  std::vector<std::string> interfaces;

  for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
    if (ifa->ifa_addr != nullptr && ifa->ifa_addr->sa_family == AF_INET6) {
      interfaces.emplace_back(ifa->ifa_name);
    }
  }

  freeifaddrs(ifaddr);

  return interfaces;
}
