#pragma once
#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <ifaddrs.h>
#include <net/if.h>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>

namespace NetUtils {
namespace IPv4 {
std::string Ipv4InterfaceAddress(const std::string interface);
}
} // namespace NetUtils