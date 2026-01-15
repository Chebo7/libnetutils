#pragma once
#include <format>
#include <ifaddrs.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <vector>

namespace NetUtils {
namespace IPv6 {
std::vector<std::string> Ipv6NetworkInterfaces();
}

} // namespace NetUtils