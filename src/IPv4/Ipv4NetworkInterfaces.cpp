#include "../../include/netutils/IPv4/Ipv4NetworkInterfaces.hpp"
#include <cerrno>
#include <format>
#include <stdexcept>
#include <string>

std::vector<std::string> NetUtils::IPv4::Ipv4NetworkInterfaces() {
  struct ifaddrs *ifaddr, *ifa;

  if (getifaddrs(&ifaddr) == -1) {
    freeifaddrs(ifaddr);
    switch (errno) {
    case ENOMEM:
      throw std::runtime_error("Ipv4NetworkInterfaces: Cannot allocate memory");

    case EFAULT:
      throw std::runtime_error("Ipv4NetworkInterfaces: Bad address");

    case EAFNOSUPPORT:
      throw std::runtime_error(
          "Ipv4NetworkInterfaces: Address family not supported by protocol");

    case EINTR:
      throw std::runtime_error(
          "Ipv4NetworkInterfaces: Interrupted system call");

    case ENFILE:
      throw std::runtime_error(
          "Ipv4NetworkInterfaces: Too many open files in system");

    default:
      throw std::runtime_error(
          std::format("Ipv4NetworkInterfaces: {}", std::to_string(errno)));
    }
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
