#include "../../include/netutils/IPv4/Ipv4NetworkInterfaces.hpp"
#include "../../include/netutils/Utils/ThrowSystemError.hpp"

std::vector<std::string> NetUtils::IPv4::Ipv4NetworkInterfaces() {
  struct ifaddrs *ifaddr, *ifa;

  if (getifaddrs(&ifaddr) == -1) {
    freeifaddrs(ifaddr);
    NetUtils::Utils::ThrowSystemError("Ipv4NetworkInterfaces", errno);
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
