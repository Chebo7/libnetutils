#include "../../include/netutils/Socket/SmartSocket.hpp"
#include <sys/socket.h>
#include <unistd.h>

NetUtils::Socket::SmartSocket::SmartSocket(int domain, int type, int protocol) {
  fd = socket(domain, type, protocol);
}

NetUtils::Socket::SmartSocket::~SmartSocket() { close(fd); }