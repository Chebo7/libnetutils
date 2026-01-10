#pragma once
#include <ifaddrs.h>
#include <string>
#include <sys/socket.h>
#include <vector>

namespace NetUtils {
std::vector<std::string> Ipv6NetworkInterfaces();
}