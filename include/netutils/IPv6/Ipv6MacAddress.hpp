#pragma once
#include <cstring>
#include <format>
#include <ifaddrs.h>
#include <net/if.h>
#include <stdexcept>
#include <string>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

namespace NetUtils {
namespace IPv6 {
std::string Ipv6MacAddress(const std::string interface);
}
} // namespace NetUtils