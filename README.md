# Custom Vector Container - README

This C++ container class aims to provide a simplified implementation of a dynamic array similar to the `std::vector` in the C++ Standard Library. It offers various functionalities for managing and manipulating a dynamic array.

## Features

- Dynamic resizing for efficient memory management.
- Insertion and removal of elements at specific positions.
- Random access to elements using index-based notation.
- Custom iterators for traversing the elements.
- Comparison operators for easy comparisons with other vectors.
- ...

## Getting Started

To start using the Custom Vector Container in your C++ projects, follow these steps:

1. Clone or download the repository to your local machine.
2. Include the `"vector.hpp"` header in your source files.
3. Create an instance of the `container::vector` class for your data type.
4. Use the available member functions to manage and manipulate the vector.

## Usage Example

```cpp
#include "vector.hpp"
#include <iostream>

int main() {
    container::vector<int> myVector;
    myVector.push_back(10);
    myVector.push_back(20);
    
    for (const auto& value : myVector) {
        std::cout << value << " ";
    }
    
    return 0;
}