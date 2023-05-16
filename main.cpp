#include <iostream>
#include "vector.hpp"

namespace test
{

void test_vec()
{
    // vec
    container::Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    
    std::cout << "Print vec: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    // vec1
    container::Vector<int> vec1 = vec;
    vec1.push_back(5);

    std::cout << "Print vec1: ";
    for (size_t i = 0; i < vec1.size(); ++i) {
        std::cout << vec1[i] << " ";
    }
    std::cout << std::endl;

    //vec2
    const container::Vector<int> vec2 = vec1;
    std::cout << "Print const vec2: ";
    for (size_t i = 0; i < vec2.size(); ++i) {
        std::cout << vec2[i] << " ";
    }
    std::cout << std::endl;

    vec1.clear();
    std::cout << "Print const vec2: ";
    for (size_t i = 0; i < vec1.size(); ++i) {
        std::cout << vec1[i] << " ";
    }
    std::cout << std::endl;
    
    // vec3
    container::Vector<int> vec3;
    vec3 = std::move(vec);

    std::cout << "Print vec3: ";
    for (size_t i = 0; i < vec3.size(); ++i) {
        std::cout << vec3[i] << " ";
    }
    std::cout << std::endl;

    try {
        vec.pop_back();
        vec.pop_back();
        vec.pop_back();
        vec.pop_back();
        vec.pop_back();
    } catch (const std::exception& ex) {
        std::cout << "Exception caught: " << ex.what() << std::endl;
    }
}

}

int main() {

    test::test_vec();

    return 0;
}