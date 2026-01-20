#include "../../include/netutils/IPv6/Ipv6NetMask.hpp"
#include "../../include/netutils/Utils/ThrowSystemError.hpp"

std::string NetUtils::IPv6::Ipv6NetMask(std::string interface) {
  if (interface.empty()) {
    throw std::runtime_error("Ipv6NetMask: The interface name is empty");
  }

  if (interface.size() >= IFNAMSIZ) {
    throw std::runtime_error("Ipv6NetMask: Interface name too large");
  }

  struct ifaddrs *ifaddr, *ifa;

  if (getifaddrs(&ifaddr) == -1) {
    NetUtils::Utils::ThrowSystemError("Ipv6NetMask", errno);
  }

  struct sockaddr_in6 *ipv6Mask = nullptr;
  bool interfaceIsFound = false;

  for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
    if (ifa->ifa_addr != nullptr && ifa->ifa_addr->sa_family == AF_INET6 &&
        ifa->ifa_netmask != nullptr &&
        strcmp(ifa->ifa_name, interface.c_str()) == 0) {
      ipv6Mask = reinterpret_cast<struct sockaddr_in6 *>(ifa->ifa_netmask);
      interfaceIsFound = true;

      break;
    }
  }

  if (!interfaceIsFound) {
    freeifaddrs(ifaddr);
    throw std::runtime_error("Ipv6NetMask: Interface not found");
  }

  if (ipv6Mask == nullptr) {
    freeifaddrs(ifaddr);
    throw std::runtime_error("Ipv6NetMask: The interface has no address");
  }

  char netMaskChar[INET6_ADDRSTRLEN];
  inet_ntop(AF_INET6, &(ipv6Mask->sin6_addr), netMaskChar, INET6_ADDRSTRLEN);

  freeifaddrs(ifaddr);
  return netMaskChar;
}