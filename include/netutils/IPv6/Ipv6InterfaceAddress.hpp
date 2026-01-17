#pragma once
#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <format>
#include <ifaddrs.h>
#include <linux/sockios.h>
#include <net/if.h>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>

namespace NetUtils {
namespace IPv6 {
std::string Ipv6InterfaceAddress(const std::string interface);
}
} // namespace NetUtils