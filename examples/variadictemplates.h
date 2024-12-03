#pragma once

#include <iostream>
#include <tuple>
#include <utility>

namespace
{
    // Pack expansion is either space or comma separated based on the context
    template<class... Ts> // Ts the type of the parameter pack
    inline auto Sum(Ts... args) // args is a parameter pack
    {
        // Space separated - Sum(T1, T2, T3) expands to (T1 + T2 + T3)
        return (args + ...); // Parameter unpack (Pack Expansion)
    }

    template<class... Ts>
    inline auto Sum1(Ts... args)
    {
        // Comma separated - Sum1(T1, T2, T3) expands to Sum(T1, T2, T3)
        return Sum(args...);
    }

    template<class... Ts>
    inline auto Sum2(Ts... args)
    {
        // Will expand the inner most pack first
        // Sum2(T1, T2) expands to Sum(Sum(T1, T2) + T1, Sum(T1, T2) + T2))
        return Sum(Sum(args...) + args...);
    }

    // Expanding two parameter packs at the same time
    template<class... Ts>
    class ParamPackT
    {
    public:
        template<class... Us>
        class ParamPackU
        {
        public:
            // Ts and Us must be the same length else the tuple of pairs is invalid because the pair needs two types for each unpack
            // ParamPackT<T1, T2>::ParamPackU<U1, U2>::Tuple will expand to std::tuple<std::pair<T1, U1>, std::pair<T2, U2>>
            using Tuple = std::tuple<std::pair<Ts, Us>...>;
        };
    };

    template<class... Ts>
    class VariadicClassInheritance final : public Ts... // Parameter expansion with inheritance. Note: Each type must be unique
    {
    public:
        using Ts::operator()...; // Parameter expansion with using, effectinly using the operator() for each type in Ts. Note: Each operator must be unique
    };

    // Guide for the type since C++17 (not needed in C++20)
    // This allows VariadicClassInheritance foo{1.0f, false} instead of VariadicClassInheritance<double_t, bool> foo{1.0f, false}
    // It works by defining a type after the -> for the type of Ts passed to the constructor
    //template<class... Ts>
    //VariadicClassInheritance(Ts...) -> VariadicClassInheritance<Ts...>;

    // Example callables to show how VariadicClassInheritance could be used
    class PrintAuto
    {
    public:
        void operator()(const auto value) const // auto as a function param is a C++20 feature
        {
            std::cout << "Auto " << value << "\n";
        }
    };

    class PrintDouble
    {
    public:
        void operator()(const double_t value) const
        {
            std::cout << "Double " << value << "\n";
        }
    };
}

namespace VariadicTemplates
{
    inline void Run()
    {
        std::cout << "START -  Variadic Templates\n";

        ParamPackT<bool, float_t>::ParamPackU<double_t, uint16_t>::Tuple tuple{};

        const VariadicClassInheritance valuePrinter{
            PrintAuto{},
            PrintDouble{},
            [](const bool value)
            {
                std::cout << "Bool " << value << "\n";
            }};

        valuePrinter(1.23f);
        valuePrinter(1.23);
        valuePrinter(true);
        valuePrinter(123);

        std::cout << Sum(1) << " == Sum(1)\n";
        std::cout << Sum(1, 2) << " == Sum(1, 2)\n";
        std::cout << Sum(1, 2, 3) << " == Sum(1, 2, 3)\n";

        std::cout << Sum1(1) << " == Sum1(1)\n";
        std::cout << Sum1(1, 2) << " == Sum1(1, 2)\n";
        std::cout << Sum1(1, 2, 3) << " == Sum1(1, 2, 3)\n";

        std::cout << Sum2(1) << " == Sum2(1)\n";
        std::cout << Sum2(1, 2) << " == Sum2(1, 2)\n";
        std::cout << Sum2(1, 2, 3) << " == Sum2(1, 2, 3)\n";

        std::cout << "END - Variadic Templates\n";
    }
}
