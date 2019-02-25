#include <gtest/gtest.h>
#include <list>
#include "huffman.hpp"
#include "histogram.hpp"

TEST(HuffmanCodes, CharacterEncoding)
{
    std::list<std::pair<char, int>> data { {'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45} };
    huffman<char> h(data);

    ASSERT_EQ(h.code('a'), "1100" );
    ASSERT_EQ(h.code('b'), "1101" );
    ASSERT_EQ(h.code('c'), "100" );
    ASSERT_EQ(h.code('d'), "101" );
    ASSERT_EQ(h.code('e'), "111" );
    ASSERT_EQ(h.code('f'), "0" );
}

TEST(HuffmanCodes, IntegerEncoding)
{
    std::list<std::pair<int, int>> data { {125, 5}, {23, 1}, {57, 12}, {45, 13}, {26, 16}, {78, 45} };
    huffman<int> h(data);

    ASSERT_EQ(h.code(125), "1001" );
    ASSERT_EQ(h.code(23), "1000" );
    ASSERT_EQ(h.code(57), "101" );
    ASSERT_EQ(h.code(45), "110" );
    ASSERT_EQ(h.code(26), "111" );
    ASSERT_EQ(h.code(78), "0" );
}