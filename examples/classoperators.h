#pragma once

#include <cstdarg>
#include <iostream>

namespace
{
    // Rule of 5 - If a destructor, copy-constructor, or copy-assignment operator is defined this
    // prevents the implicit definition of the move constructor and move assignment operator.
    // So if you define one, define them all(5).
    class Operators
    {
    public:
        Operators()
        {
            std::cout << "Operators()\n";
        }

        ~Operators()
        {
            std::cout << "~Operators()\n";
        }

        Operators(Operators&)
        {
            std::cout << "Operators(Operators&)\n";
        }

        Operators(const Operators&)
        {
            std::cout << "Operators(const Operators&)\n";
        }

        Operators(Operators&&)
        {
            std::cout << "Operators(Operators&&)\n";
        }

        Operators& operator=(const Operators&)
        {
            std::cout << "Operators& operator=(const Operators&)\n";
            return *this;
        }

        Operators& operator=(Operators&&)
        {
            std::cout << "Operators& operator=(Operators&&)\n";
            return *this;
        }
    };

    Operators PassByValue(Operators foo)
    {
        std::cout << "return\n";
        return foo;
    }

    Operators ConstPassByValue(const Operators foo)
    {
        std::cout << "return\n";
        return foo;
    }

    Operators PassByRef(Operators& foo)
    {
        std::cout << "return\n";
        return foo;
    }

    Operators ConstPassByRef(const Operators& foo)
    {
        std::cout << "return\n";
        return foo;
    }
}

namespace ClassOperators
{
    inline void Run()
    {
        std::cout << "START - ClassOperators\n";

        std::cout << "sizeof(Operators) " << sizeof(Operators) << "\n";
        std::cout << "sizeof(Operators&) " << sizeof(Operators&) << "\n";
        std::cout << "sizeof(Operators*) " << sizeof(Operators*) << "\n";

        std::cout << "\nConstructors:\n";
        {
            Operators a{};
            Operators b{a};
            const Operators c{std::move(a)};
            const Operators d{c};
            const Operators e{std::move(c)};
        }

        std::cout << "\nPassByValue:\n";
        {
            Operators a{};
            std::cout << "PassByValue(a)\n";
            PassByValue(a);
            std::cout << "PassByValue(std::move(a))\n";
            PassByValue(std::move(a));
            std::cout << "PassByValue(Operators{})\n";
            PassByValue(Operators{});
        }

        std::cout << "\nConstPassByValue:\n";
        {
            Operators a{};
            std::cout << "ConstPassByValue(a)\n";
            ConstPassByValue(a);
            std::cout << "ConstPassByValue(std::move(a))\n";
            ConstPassByValue(std::move(a));
            std::cout << "ConstPassByValue(Operators{})\n";
            ConstPassByValue(Operators{});
        }

        std::cout << "\nPassByRef:\n";
        {
            Operators a{};
            std::cout << "PassByRef(a)\n";
            PassByRef(a);
        }

        std::cout << "\nConstPassByRef:\n";
        {
            Operators a{};
            std::cout << "ConstPassByRef(a)\n";
            ConstPassByRef(a);
            std::cout << "ConstPassByRef(std::move(a))\n";
            ConstPassByRef(std::move(a));
            std::cout << "ConstPassByRef(Operators{})\n";
            ConstPassByRef(Operators{});
        }

        std::cout << "END - ClassOperators\n\n";

/*
        START - ClassOperators
        sizeof(Operators) 1
        sizeof(Operators&) 1
        sizeof(Operators*) 8

        Constructors:
        Operators()
        Operators(Operators&)
        Operators(Operators&&)
        Operators(const Operators&)
        Operators(const Operators&)
        ~Operators()
        ~Operators()
        ~Operators()
        ~Operators()
        ~Operators()

        PassByValue:
        Operators()
        PassByValue(a)
        Operators(Operators&)
        return
        Operators(Operators&&)
        ~Operators()
        ~Operators()
        PassByValue(std::move(a))
        Operators(Operators&&)
        return
        Operators(Operators&&)
        ~Operators()
        ~Operators()
        PassByValue(Operators{})
        Operators()
        return
        Operators(Operators&&)
        ~Operators()
        ~Operators()
        ~Operators()

        ConstPassByValue:
        Operators()
        ConstPassByValue(a)
        Operators(Operators&)
        return
        Operators(const Operators&)
        ~Operators()
        ~Operators()
        ConstPassByValue(std::move(a))
        Operators(Operators&&)
        return
        Operators(const Operators&)
        ~Operators()
        ~Operators()
        ConstPassByValue(Operators{})
        Operators()
        return
        Operators(const Operators&)
        ~Operators()
        ~Operators()
        ~Operators()

        PassByRef:
        Operators()
        PassByRef(a)
        return
        Operators(Operators&)
        ~Operators()
        ~Operators()

        ConstPassByRef:
        Operators()
        ConstPassByRef(a)
        return
        Operators(const Operators&)
        ~Operators()
        ConstPassByRef(std::move(a))
        return
        Operators(const Operators&)
        ~Operators()
        ConstPassByRef(Operators{})
        Operators()
        return
        Operators(const Operators&)
        ~Operators()
        ~Operators()
        ~Operators()
        END - ClassOperators
*/
    }
}
