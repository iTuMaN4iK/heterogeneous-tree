# Heterogeneous Tree

A library for storing various types in a tree-like format with arbitrary descendants.

## Install
+ Copy from the most recent release into your include directory, and you are set.
+ You could check out the repository as a git submodule, for example. With CMake, you can use add_subdirectory and the heterogeneous_tree target when linking. If not using a submodule, you must ensure that the copied files are located inside the same tree directory than your current project, to prevent an error with CMake and add_subdirectory.

And then in the source code:

```
#include <heterogeneous_tree/node.h>

```

To build the tests, checkout the repository and use CMake. Only with installed gtest:

```
mkdir build
cd build
cmake -DBUILD_TESTS ..
make
GTEST_COLOR=1 CTEST_OUTPUT_ON_FAILURE=1 make test
```

## Usage

+ Make a node and add children:

```
    node_ptr header = make_node(8);
    auto childOne = header->add_child(make_node(std::string("bar")));
    childOne->add_child(make_node(2.015))->add_child(make_node(9));
    childOne->add_child(make_node(2015));
    childOne->add_child(make_node(std::string("2015")));
    auto childTwo = header->add_child(make_node(std::string("bar 2")));
    childTwo->add_child(make_node(std::string("foo")));
    childTwo->add_child(make_node(6.28318))->add_child(make_node(std::string("hello")));
```
+ Interaction with the data contained in the tree occurs through the visit method. For this you need to create your visitor inherited from visitor_base specifying the data types with which you want to interact
```
    struct print_visitor : visitor_base<int, double, std::string> {
        template<class T>
        void operator()(T &_in, std::ostream &os) {
            os << _in << "\n";
        }
    };
```

## [Example](https://github.com/iTuMaN4iK/heterogeneous-tree-example)
