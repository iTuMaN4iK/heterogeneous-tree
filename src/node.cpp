#include "heterogeneous_tree/node.h"

using namespace itmn;

itmn::node::~node() { this->clear(); }

node::node(const node &_other) { *this = _other; }

node &node::operator=(const node &_other)
{
    clear();
    m_children = _other.m_children;
    m_clear_function = _other.m_clear_function;
    m_copy_function = _other.m_copy_function;
    m_copy_function(_other, *this);

    return *this;
}

node_ptr node::add_child(node_ptr _child)
{
    m_children.push_back(_child);
    return m_children.back();
}

std::vector<node_ptr> node::children() { return m_children; }

void node::clear()
{
    if (m_clear_function)
    {
        m_clear_function(*this);
    }
}
