#include "../../include/netutils/IPv6/Ipv6NetworkInterfaces.hpp"

std::vector<std::string> NetUtils::IPv6::Ipv6NetworkInterfaces() {
  struct ifaddrs *ifaddr, *ifa;

  if (getifaddrs(&ifaddr) == -1) {
    freeifaddrs(ifaddr);
    switch (errno) {
    case ENOMEM:
      throw std::runtime_error("Ipv6NetworkInterfaces: Cannot allocate memory");

    case EFAULT:
      throw std::runtime_error("Ipv6NetworkInterfaces: Bad address");

    case EAFNOSUPPORT:
      throw std::runtime_error(
          "Ipv6NetworkInterfaces: Address family not supported by protocol");

    case EINTR:
      throw std::runtime_error(
          "Ipv6NetworkInterfaces: Interrupted system call");

    case ENFILE:
      throw std::runtime_error(
          "Ipv6NetworkInterfaces: Too many open files in system");

    default:
      throw std::runtime_error(
          std::format("Ipv6NetworkInterfaces: {}", std::to_string(errno)));
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
}