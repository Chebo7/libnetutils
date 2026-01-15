#include "../../include/netutils/IPv4/Ipv4InterfaceAddress.hpp"

std::string NetUtils::IPv4::Ipv4InterfaceAddress(const std::string interface) {

  if (interface.empty()) {
    throw std::runtime_error(
        "Ipv4InterfaceAddress: The interface name is empty");
  }

  if (interface.size() >= IFNAMSIZ) {
    throw std::runtime_error("Ipv4InterfaceAddress: Interface name too large");
  }

  struct ifaddrs *ifaddr, *ifa;

  if (getifaddrs(&ifaddr) == -1) {
    freeifaddrs(ifaddr);
    switch (errno) {
    case ENOMEM:
      throw std::runtime_error("Ipv4InterfaceAddress: Cannot allocate memory");

    case EFAULT:
      throw std::runtime_error("Ipv4InterfaceAddress: Bad address");

    case EAFNOSUPPORT:
      throw std::runtime_error(
          "Ipv4InterfaceAddress: Address family not supported by protocol");

    case EINTR:
      throw std::runtime_error("Ipv4InterfaceAddress: Interrupted system call");

    case ENFILE:
      throw std::runtime_error(
          "Ipv4InterfaceAddress: Too many open files in system");

    default:
      throw std::runtime_error(
          std::format("Ipv4InterfaceAddress: {}", std::to_string(errno)));
    }
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
    throw std::runtime_error("Ipv4InterfaceAddress: Interface not found");
  }

  if (ipv4Addr == nullptr) {
    freeifaddrs(ifaddr);
    std::runtime_error("Ipv4InterfaceAddress: The interface has no address");
  }

  char ipStr[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &(ipv4Addr->sin_addr), ipStr, INET_ADDRSTRLEN);

  std::string address = ipStr;

  freeifaddrs(ifaddr);

  return address;
}
