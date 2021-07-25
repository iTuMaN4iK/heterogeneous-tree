#pragma once

namespace itmn
{
    namespace visitor
    {
        template<class...>
        struct type_list
        {
        };

        template<class... TYPES>
        struct visitor_base
        {
            using types = type_list<TYPES...>;
        };
    }   // namespace visitor
}   // namespace itmn
