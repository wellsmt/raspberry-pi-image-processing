#include <iostream>
#include <map>
#include <vector>

/**
 * @param buffer a std::vector<T>
 * @return std::map<T, size_t> counts of each unique entry in buffer
 */
template<class T>
std::map<T, size_t> histogram(const std::vector<T> buffer){
    std::map<T, size_t> hist;

    for(auto& value : buffer)
    {
        if(hist.find(value) == hist.end())
        {
            hist[value]=1;
        }
        else
        {
            hist[value]++;
        }
    }
    return hist;
}