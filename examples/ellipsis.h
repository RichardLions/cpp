#pragma once

#include <cstdarg>
#include <iostream>

namespace
{
    inline int32_t Max(const int32_t count, ...) // Can also be written as Max(const int32_t count...) As long as ... is the last arg
    {
        int32_t max{0};

        va_list ints{}; // Holds variadic function args from ...(Ellipsis)
        va_start(ints, count); // Enable access to variadic function args
        for(int32_t i{0}; i != count; ++i)
        {
            const int32_t next{va_arg(ints, int32_t)}; // Get the next arg. If the type is not a int32_t, the behaviour in undefined
            if(next > max)
                max = next;
        }
        va_end(ints); // Ends traversal of the variadic function arguments

        return max;
    }
}

namespace Ellipsis
{
    inline void Run()
    {
        std::cout << "START -  Ellipsis\n";

        // Can accept no additional args
        Max(0);
        // The first arg has to be correct, compiler does not know the number of args
        Max(0, 1, 2, 3);
        // Will accept any types
        Max(6, 9.0, false, "str", 1, 8.4f, 'd');

        // Example
        std::cout << Max(5, 0, 4, -1, 8, 4) << " == Max(5, 0, 4, -1, 8, 4)\n";

        std::cout << "END - Ellipsis\n";
    }
}
