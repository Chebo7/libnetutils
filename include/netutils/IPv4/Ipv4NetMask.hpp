#pragma once
#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <format>
#include <linux/sockios.h>
#include <net/if.h>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

namespace NetUtils {
namespace IPv4 {
std::string Ipv4NetMask(const std::string interface);
}
} // namespace NetUtils