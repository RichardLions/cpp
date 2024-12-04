#pragma once

#include <iostream>
#include <string_view>

namespace
{
    // Inspired by: https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c
    template<typename T>
    constexpr auto TypeName()
    {
        std::string_view name{__FUNCSIG__};
        const std::string_view prefix{"auto __cdecl `anonymous-namespace'::type_name<"};
        const std::string_view suffix{">(void)"};
        name.remove_prefix(prefix.size() - 1);
        name.remove_suffix(suffix.size());
        return name;
    }

    inline int32_t lvalue() {}
    inline const int32_t const_lvalue() {}

    inline int32_t& lvalue_ref() {}
    inline const int32_t& const_lvalue_ref() {}

    inline int32_t&& rvalue_ref() {}
    inline const int32_t&& const_rvalue_ref() {}

    class Default
    {
    public:
        int lvalue() const {}
    };

    class NonDefault
    {
    public:
        NonDefault() = delete;
        int lvalue() const {}
    };

    template<typename T>
    T WhatIsTheType() {}
}

namespace Decltype
{
    inline void Run()
    {
        std::cout << "START - Decltype\n";

        int32_t lvalue_int{0};
        const int32_t const_lvalue_int{0};
        const int32_t& const_lvalue_int_ref{lvalue_int};

        // Decltype gives the declared type
        // You can get the type of a variable like so:
        std::cout << "decltype(lvalue_int) is " << TypeName<decltype(lvalue_int)>() << "\n";
        std::cout << "decltype((lvalue_int)) is " << TypeName<decltype((lvalue_int))>() << "\n";
        std::cout << "decltype(const_lvalue_int) is " << TypeName<decltype(const_lvalue_int)>() << "\n";
        std::cout << "decltype((const_lvalue_int)) is " << TypeName<decltype((const_lvalue_int))>() << "\n";
        std::cout << "decltype(static_cast<int&>(lvalue_int)) is " << TypeName<decltype(static_cast<int32_t&>(lvalue_int))>() << "\n";
        std::cout << "decltype(static_cast<int&&>(lvalue_int)) is " << TypeName<decltype(static_cast<int32_t&&>(lvalue_int))>() << "\n";
        std::cout << "decltype(static_cast<int>(lvalue_int)) is " << TypeName<decltype(static_cast<int32_t>(lvalue_int))>() << "\n";

        // You can get the type of a return like so:
        std::cout << "decltype(lvalue()) is " << TypeName<decltype(lvalue())>() << "\n";
        std::cout << "decltype(const_lvalue()) is " << TypeName<decltype(const_lvalue())>() << "\n";
        std::cout << "decltype(lvalue_ref()) is " << TypeName<decltype(lvalue_ref())>() << "\n";
        std::cout << "decltype(const_lvalue_ref()) is " << TypeName<decltype(const_lvalue_ref())>() << "\n";
        std::cout << "decltype(rvalue_ref()) is " << TypeName<decltype(rvalue_ref())>() << "\n";
        std::cout << "decltype(const_rvalue_ref()) is " << TypeName<decltype(const_rvalue_ref())>() << "\n";

        // If a type has no constructor you can use std::declval to get the return type like so:
        std::cout << "decltype(Default().lvalue()) is " << TypeName<decltype(Default().lvalue())>() << "\n"; // Has a constructor, so can be checked without std::declval
        std::cout << "decltype(std::declval<Default>().lvalue()) is " << TypeName<decltype(std::declval<Default>().lvalue())>() << "\n";
        //std::cout << "decltype(NonDefault().lvalue()) is " << TypeName<decltype(NonDefault().lvalue())>() << "\n"; ERROR has no default constructor
        std::cout << "decltype(std::declval<NonDefault>().lvalue()) is " << TypeName<decltype(std::declval<NonDefault>().lvalue())>() << "\n";

        // Auto drops const and references but these rule do not apply to pointers
        auto auto_int_lvalue{const_lvalue_int_ref};
        const auto auto_const_int_lvalue{const_lvalue_int_ref};
        const auto& auto_const_int_lvalue_ref{const_lvalue_int_ref};
        auto auto_const_int_lvalue_ptr{&const_lvalue_int_ref};
        // Can expresses additional qualifiers, however if the type cannot have the additional qualifiers a compile error will be thrown
        //auto* auto_const_int_lvalue_ptr{lvalue_int}; ERROR lvalue_int is not a pointer
        const auto auto_const_int_lvalue_ptr2{&const_lvalue_int_ref}; // NOTE: This becomes const int* const because it turns the entire auto type const
        const auto* auto_const_int_lvalue_ptr3{&const_lvalue_int_ref};
        const auto* const auto_const_int_lvalue_ptr4{&const_lvalue_int_ref};
        auto* auto_const_int_lvalue_ptr5{&const_lvalue_int_ref};
        auto auto_int_lvalue_ptr{&lvalue_int};
        std::cout << "decltype(auto_int_lvalue) is " << TypeName<decltype(auto_int_lvalue)>() << "\n";
        std::cout << "decltype(auto_const_int_lvalue) is " << TypeName<decltype(auto_const_int_lvalue)>() << "\n";
        std::cout << "decltype(auto_const_int_lvalue_ref) is " << TypeName<decltype(auto_const_int_lvalue_ref)>() << "\n";
        std::cout << "decltype(auto_const_int_lvalue_ptr) is " << TypeName<decltype(auto_const_int_lvalue_ptr)>() << "\n";
        std::cout << "decltype(auto_const_int_lvalue_ptr2) is " << TypeName<decltype(auto_const_int_lvalue_ptr2)>() << "\n";
        std::cout << "decltype(auto_const_int_lvalue_ptr3) is " << TypeName<decltype(auto_const_int_lvalue_ptr3)>() << "\n";
        std::cout << "decltype(auto_const_int_lvalue_ptr4) is " << TypeName<decltype(auto_const_int_lvalue_ptr4)>() << "\n";
        std::cout << "decltype(auto_const_int_lvalue_ptr5) is " << TypeName<decltype(auto_const_int_lvalue_ptr5)>() << "\n";
        std::cout << "decltype(auto_int_lvalue_ptr) is " << TypeName<decltype(auto_int_lvalue_ptr)>() << "\n";

        // Templates use the fully qualified type
        std::cout << "decltype(WhatIsTheType<decltype(lvalue_int)>()) is " << TypeName<decltype(WhatIsTheType<decltype(lvalue_int)>())>() << "\n";
        std::cout << "decltype(WhatIsTheType<decltype((lvalue_int))>()) is " << TypeName<decltype(WhatIsTheType<decltype((lvalue_int))>())>() << "\n";

        std::cout << "END - Decltype\n\n";

/*
        START - Decltype
        decltype(lvalue_int) is int
        decltype((lvalue_int)) is int&
        decltype(const_lvalue_int) is const int
        decltype((const_lvalue_int)) is const int&
        decltype(static_cast<int&>(lvalue_int)) is int&
        decltype(static_cast<int&&>(lvalue_int)) is int&&
        decltype(static_cast<int>(lvalue_int)) is int
        decltype(lvalue()) is int
        decltype(const_lvalue()) is int
        decltype(lvalue_ref()) is int&
        decltype(const_lvalue_ref()) is const int&
        decltype(rvalue_ref()) is int&&
        decltype(const_rvalue_ref()) is const int&&
        decltype(Default().lvalue()) is int
        decltype(std::declval<Default>().lvalue()) is int
        decltype(std::declval<NonDefault>().lvalue()) is int
        decltype(auto_int_lvalue) is int
        decltype(auto_const_int_lvalue) is const int
        decltype(auto_const_int_lvalue_ref) is const int&
        decltype(auto_const_int_lvalue_ptr) is const int*
        decltype(auto_const_int_lvalue_ptr2) is const int*const
        decltype(auto_const_int_lvalue_ptr3) is const int*
        decltype(auto_const_int_lvalue_ptr4) is const int*const
        decltype(auto_const_int_lvalue_ptr5) is const int*
        decltype(auto_int_lvalue_ptr) is int*
        decltype(WhatIsTheType<decltype(lvalue_int)>()) is int
        decltype(WhatIsTheType<decltype((lvalue_int))>()) is int&
        END - Decltype
*/
    }
}
