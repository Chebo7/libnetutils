#include <cerrno>
#include <format>
#include <map>
#include <stdexcept>
#include <string>

namespace NetUtils {
namespace Utils {
void ThrowSystemError(std::string const functionName, const int er);
}
} // namespace NetUtils