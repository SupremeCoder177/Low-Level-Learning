#include <vector>
#include <iostream>
#include <unordered_map>
#include <string>

int main(){

    std::vector<int> values = {1, 2, 3, 4, 5};

    /* In simple words, an iterator, iterates over all elements in a collection */

    //the most common example of such a thing is
    for(int i = 0; i < values.size(); i++) std::cout << values[i] << std::endl;

    // or like this
    for(int i : values) std::cout << i << std::endl;

    // but why this words?

    // the long version is
    for(std::vector<int>::iterator it = values.begin(); it != values.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    // now this is unecessary for vectors because you can access elements via their indexes

    // iterators are helpful for data structures like graphs or trees where you cannot access elements by their index
    std::unordered_map<std::string, int> map;
    map["Hello"] = 1;
    map["C++"] = 2;

    // so in this example you cannot access the elements inside the map using indices
    // so you use an iterator

    using mapIterator = std::unordered_map<std::string, int>;
    for(mapIterator::const_iterator it = map.begin(); it != map.end(); it++){
        auto& key = it->first;
        auto& value = it->second;

        std::cout << key << " " << value << std::endl;
    }

    // or you can also do something like this
    for(auto [key, value] : map)
    {
        std::cout << key << " " << value << std::endl;
    }

    return 0;
} 