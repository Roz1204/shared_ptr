#include <iostream>
#include "shared_ptr.hpp"

int main() {
    shared_ptr<int> ptr1(new int(10));
    shared_ptr<int> ptr2 = ptr1; // Copy construction

    std::cout << "Count after copy construction: " << ptr1.get_count() << std::endl;

    {
        shared_ptr<int> ptr3(new int(20));
        shared_ptr<int> ptr4;
        ptr4 = ptr3; // Copy assignment

        std::cout << "Count inside inner scope: " << ptr3.get_count() << std::endl;
    }

    std::cout << "Count after inner scope: " << ptr2.get_count() << std::endl;

    return 0;
}
