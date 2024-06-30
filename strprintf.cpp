#define _blackcap_name_strprintf_cpp_

#include <cstdio>
#include <cstring>
#include <memory>
#include "strprintf.hpp"

std::string strprintf(const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    std::string ret = vstrprintf(format, ap);
    va_end(ap);
    return ret;
}


std::string vstrprintf(const char *format, va_list ap)
{
    std::size_t bufsize = 128;
    va_list ap2;

    auto buf = std::unique_ptr<char[]>(new char[bufsize]);

    va_copy(ap2, ap);
    int status = std::vsnprintf(&buf[0], bufsize, format, ap2);
    va_end(ap2);
    if (status < 0) {
        buf[0] = '\0';  // mangled format, return empty string
    }

    if (status >= bufsize) {
        bufsize = status + 1;
        buf = std::unique_ptr<char[]>(new char[bufsize]);
        status = std::vsnprintf(&buf[0], bufsize, format, ap);
        if (status < 0 || status >= bufsize) {
            buf[0] = '\0';  // two strikes and yer out
        }
    }

    return std::string(&buf[0]);
}
