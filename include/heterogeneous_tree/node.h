#pragma once

#include "visitor.h"

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

namespace itmn
{
    class node;

    using node_ptr = std::shared_ptr<node>;

    class node
    {
    public:
        node() = default;

        template<class T>
        explicit node(T _value)
        {
            m_clear_function = [](node &_c) { s_values<T>.erase(&_c); };
            m_copy_function = [](const node &_from, node &_to)
            { s_values<T>[&_to] = s_values<T>[&_from]; };
            s_values<T>[this] = std::move(_value);
        }

        ~node();

        node(const node &_other);

        node &operator=(const node &_other);

        node_ptr add_child(node_ptr _child);

        std::vector<node_ptr> children();

        template<class T, class... ARGS>
        void visit(T &&visitor, ARGS &&...args)
        {
            visit_impl(std::forward<T>(visitor),
                       typename std::decay_t<T>::types{},
                       std::forward<ARGS>(args)...);
        }

        template<class T, class... ARGS>
        void visit_all(T &&visitor, ARGS &&...args)
        {
            visit_impl(visitor, typename std::decay_t<T>::types{}, std::forward<ARGS>(args)...);
            for (auto children : m_children)
            {
                children->visit_all(visitor, std::forward<ARGS>(args)...);
            }
        }

    private:
        template<class T>
        static std::unordered_map<const node *, T> s_values;

        std::vector<node_ptr> m_children;
        std::function<void(node &)> m_clear_function;
        std::function<void(const node &, node &)> m_copy_function;

    private:
        void clear();

        template<class T, template<class...> class TLIST, class... TYPES, class... ARGS>
        void visit_impl(T &&visitor, TLIST<TYPES...>, ARGS &&...args)
        {
            (..., visit_impl_help<std::decay_t<T>, TYPES>(visitor, std::forward<ARGS>(args)...));
        }

        template<class T, class U, class... ARGS>
        void visit_impl_help(T &visitor, ARGS &&...args)
        {
            if (s_values<U>.find(this) != std::end(s_values<U>))
                visitor(s_values<U>[this], std::forward<ARGS>(args)...);
        }
    };

    template<class T>
    node_ptr make_node(T &&_value)
    {
        return std::make_shared<node>(std::forward<T>(_value));
    }

    template<class T>
    std::unordered_map<const node *, T> node::s_values;
}   // namespace itmn