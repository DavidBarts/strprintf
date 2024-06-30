Introduction
============

I've been playing around with C++ and I find this useful, so here it is
for future reference.

There's still a lot of C++ compilers in the wild that do not support
C++20 or better yet, in which `std::format` is a thing, and the standard
C++ system of using operators and manipulators to produce formatted
output is all three of: strange, clumsy, and verbose.

Description
===========

This is simply a wrapper around `std::vsnprintf` which allocates the
storage needed storage to contain its result. It does this in one or two
phases, depending on how long the result string is. First, it tries to
write into a reasonably-sized buffer that should be sufficiently large
in the vast majority of cases. If that fails, it allocates a buffer sure
to be large enough and invokes `std::vsnprintf` again. Therefore, in
most cases a "preflight" call is not made.

The returned string is returned as type `std::string`. This does result
in an extra copy, but I felt the simplification of storage management
was worth it. This allows uses like:

    std::cerr << strprintf("%s: unable to open %s: %s\n", myname, file_name, strerror(errno));

If a `char *` were returned, it would take three statements (assignment,
print, free) to accomplish the above without leaking memory.

Note that while `strprintf` *returns* a standard C++ string, it does not
*accept* such strings as input. It's still `snprintf` under the hood,
and being a C function, `snprintf` knows nothing about C++ classes.

A `vstrprintf` variant is also provided, so that you can easily get this
functionality inside a varadic function.

Compatibility
=============

This should work with C++11 or greater.

Using
=====

This is just one source file and one header file, no Makefiles or
anything. Simple enough that you can just add it to the source tree of a
program.
