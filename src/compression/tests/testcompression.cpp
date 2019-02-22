#include <gtest/gtest.h>
#include "huffman.h"
#include "histogram.h"

TEST(Histogram, ScenarioOnce)
{
    std::vector<int> values { 1, 1, 2, 3, 5 };
    std::map<int, int> hist = histogram(values);

    //TODO: for each hist item chek freq

    ASSERT_TRUE(false);
}

TEST(HuffmanCodes, ScenarioOne)
{
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' }; 
    int freq[] = { 5, 9, 12, 13, 16, 45 }; 
  
    int size = sizeof(arr) / sizeof(arr[0]); 
  
    HuffmanCodes(arr, freq, size);
    ASSERT_TRUE(false);  
}
