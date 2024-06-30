#ifndef _blackcap_name_strprintf_hpp_
#define _blackcap_name_strprintf_hpp_

#include <cstdarg>
#include <string>

#ifdef _blackcap_name_strprintf_cpp_
#define _extern_
#else
#define _extern_ extern
#endif

_extern_ std::string strprintf(const char *, ...);
_extern_ std::string vstrprintf(const char *, va_list);

#undef _extern_
#endif
