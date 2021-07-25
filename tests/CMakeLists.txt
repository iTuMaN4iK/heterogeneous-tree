add_executable(test.node test_node.cpp)
target_link_libraries(test.node heterogeneous_tree GTest::gtest)
add_test(NAME test.node
        COMMAND test.node)
