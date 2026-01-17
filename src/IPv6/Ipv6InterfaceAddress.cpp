#include "../../include/netutils/IPv6/Ipv6InterfaceAddress.hpp"

std::string NetUtils::IPv6::Ipv6InterfaceAddress(const std::string interface) {

  if (interface.empty()) {
    throw std::runtime_error(
        "Ipv6InterfaceAddress: The interface name is empty");
  }

  if (interface.size() >= IFNAMSIZ) {
    throw std::runtime_error("Ipv6InterfaceAddress: Interface name too large");
  }

  struct ifaddrs *ifaddr, *ifa;

  if (getifaddrs(&ifaddr) == -1) {
    freeifaddrs(ifaddr);
    switch (errno) {
    case ENOMEM:
      throw std::runtime_error("Ipv6InterfaceAddress: Cannot allocate memory");

    case EFAULT:
      throw std::runtime_error("Ipv6InterfaceAddress: Bad address");

    case EAFNOSUPPORT:
      throw std::runtime_error(
          "Ipv6InterfaceAddress: Address family not supported by protocol");

    case EINTR:
      throw std::runtime_error("Ipv6InterfaceAddress: Interrupted system call");

    case ENFILE:
      throw std::runtime_error(
          "Ipv6InterfaceAddress: Too many open files in system");

    default:
      throw std::runtime_error(
          std::format("Ipv6InterfaceAddress: {}", std::to_string(errno)));
    }
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
    throw std::runtime_error("Ipv6InterfaceAddress: Interface not found");
  }

  if (ipv6Addr == nullptr) {
    freeifaddrs(ifaddr);
    throw std::runtime_error(
        "Ipv6InterfaceAddress: The interface has no address");
  }

  char ipStr[INET6_ADDRSTRLEN];
  inet_ntop(AF_INET6, &(ipv6Addr->sin6_addr), ipStr, INET6_ADDRSTRLEN);

  std::string address = ipStr;

  freeifaddrs(ifaddr);

  return address;
}
