#include <gtest/gtest.h>
#include <list>
#include "huffman.h"
#include "histogram.hpp"

TEST(HuffmanCodes, ScenarioOne)
{
    //std::list<char> arr { 'a', 'b', 'c', 'd', 'e', 'f' }; 
    //std::list<int> freq { 5, 9, 12, 13, 16, 45 };
    std::list<std::pair<char, int>> data { {'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45} };

    HuffmanCodes(data);
/*
    ASSERT_EQ(huffman_code('a'), "1100" );
    ASSERT_EQ(huffman_code('b'), "1101" );
    ASSERT_EQ(huffman_code('c'), "100" );
    ASSERT_EQ(huffman_code('d'), "101" );
    ASSERT_EQ(huffman_code('e'), "111" );
    ASSERT_EQ(huffman_code('f'), "0");  
    */
}
