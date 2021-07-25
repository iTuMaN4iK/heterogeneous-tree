#include "heterogeneous_tree/node.h"
#include "heterogeneous_tree/visitor.h"

#include <gtest/gtest.h>

using namespace itmn;

TEST(testNode, createAndDisplay) {
    node_ptr nodeInt = make_node(1);
    node_ptr nodeDouble = make_node(2.5);
    node_ptr nodeString = make_node(std::string("Hello"));
}

TEST(testNode, copy) {
    node nodeInt{1};
    node copy = nodeInt;
}

TEST(testNode, add_child) {
    node_ptr nodeInt = make_node(8);
    auto bar = nodeInt->add_child(make_node(std::string("bar")));
    bar->add_child(make_node(2.015))->add_child(make_node(9));
    bar->add_child(make_node(2015));
    bar->add_child(make_node(std::string("2015")));
    auto bar2 = nodeInt->add_child(make_node(std::string("bar 2")));
    bar2->add_child(make_node(std::string("foo")));
    bar2->add_child(make_node(6.28318))->add_child(make_node(std::string("hello")));
    EXPECT_EQ(nodeInt->children().size(), 2);
    EXPECT_EQ(bar->children().size(), 3);
    EXPECT_EQ(bar2->children().size(), 2);
}

TEST(testNode, visit) {
    node_ptr node_int = make_node(8);
    auto str_bar = node_int->add_child(make_node(std::string("bar")));
    auto node_int2 = str_bar->add_child(make_node(2.015))->add_child(make_node(9));
    auto node_int3 = str_bar->add_child(make_node(2015));
    auto str_node = str_bar->add_child(make_node(std::string("2015")));
    auto bar2 = node_int->add_child(make_node(std::string("bar 2")));
    auto str_node2 = bar2->add_child(make_node(std::string("foo")));
    auto str_node3 = bar2->add_child(make_node(6.28318))->add_child(make_node(std::string("hello")));

    struct int_visitor : visitor::visitor_base<int> {
        void operator()(int &_value, int factor) {
            _value *= factor;
        }
    };

    struct expected_visitor_int : visitor::visitor_base<int> {
        void operator()(int _value, int _expected) {
            EXPECT_EQ(_value, _expected);
        }
    };

    node_int->visit_all(int_visitor{}, 2);
    expected_visitor_int ev{};
    node_int->visit(ev, 16);
    node_int2->visit(ev, 18);
    node_int3->visit(ev, 4030);

    struct str_visitor : visitor::visitor_base<std::string> {
        void operator()(std::string &_value) {
            _value.append("_ke");
        }
    };
    struct expected_visitor_str : visitor::visitor_base<std::string> {
        void operator()(const std::string &_value, const std::string &_expected) {
            EXPECT_EQ(_value, _expected);
        }
    };
    node_int->visit_all(str_visitor{});

    expected_visitor_str evs{};
    str_bar->visit(evs, std::string("bar_ke"));
    str_node->visit(evs, std::string("2015_ke"));
    bar2->visit(evs, std::string("bar 2_ke"));
    str_node2->visit(evs, std::string("foo_ke"));
    str_node3->visit(evs, std::string("hello_ke"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
