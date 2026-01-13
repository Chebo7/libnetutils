#include "../../include/netutils/IPv4/Ipv4IndexInterface.hpp"
#include "../../include/netutils/Socket/SmartSocket.hpp"

int NetUtils::IPv4::Ipv4IndexInterface(std::string interface) {

  if (interface.empty()) {
    throw std::runtime_error("Ipv4IndexInterface: The interface name is empty");
  }

  if (interface.size() >= IFNAMSIZ) {
    throw std::runtime_error("Ipv4IndexInterface: Interface name too large");
  }

  NetUtils::Socket::SmartSocket sock(AF_INET, SOCK_DGRAM, 0);

  if (sock == -1) {
    throw std::runtime_error("Ipv4IndexInterface: Error to create socket");
  }

  struct ifreq ifr;
  memset(&ifr, 0, sizeof(ifr));

  strncpy(ifr.ifr_ifrn.ifrn_name, interface.c_str(), IFNAMSIZ);

  if (ioctl(sock, SIOCGIFINDEX, &ifr) == -1) {
    switch (errno) {
    case EBADF:
      throw std::runtime_error("Ipv4IndexInterface: Bad file descriptor");

    case EFAULT:
      throw std::runtime_error("Ipv4IndexInterface: Bad address");

    case EINVAL:
      throw std::runtime_error("Ipv4IndexInterface: Invalid argument");

    case EIO:
      throw std::runtime_error("Ipv4IndexInterface: I/O error");

    case ENODEV:
      throw std::runtime_error("Ipv4IndexInterface: No such device");

    case ENOTTY:
      throw std::runtime_error(
          "Ipv4IndexInterface: Inappropriate ioctl for device");

    case ENXIO:
      throw std::runtime_error("Ipv4IndexInterface: No such device or address");

    case EAGAIN:
      throw std::runtime_error("Ipv4IndexInterface: Resource temporarily "
                               "unavailable/No STREAM resources");

    case ENOSR:
      throw std::runtime_error("Ipv4IndexInterface: Resource temporarily "
                               "unavailable/No STREAM resources");

    case EINTR:
      throw std::runtime_error("Ipv4IndexInterface: Interrupted system call");

    case ETIME:
      throw std::runtime_error("Ipv4IndexInterface: Timer expired");

    default:
      throw std::runtime_error("Ipv4IndexInterface: " + std::to_string(errno));
    }
  }

  return ifr.ifr_ifru.ifru_ivalue;
}