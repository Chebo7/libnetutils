#pragma once
#include <ifaddrs.h>
#include <string>
#include <sys/socket.h>
#include <vector>

namespace NetUtils {
namespace IPv4 {
std::vector<std::string> Ipv4NetworkInterfaces();
}
} // namespace NetUtils