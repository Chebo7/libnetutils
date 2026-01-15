#pragma once
#include <cerrno>
#include <format>
#include <ifaddrs.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <vector>

namespace NetUtils {
namespace IPv4 {
std::vector<std::string> Ipv4NetworkInterfaces();
}
} // namespace NetUtils