#include "Array.hpp"

int main(void) {
    Array<int> test1(10);
    Array<int> test2;
    Array<int> test3;

    std::cout << "Testing 1: Copy & initializaiton" << std::endl;
    for (int i = 0; i < 10; i++)
        test1[i] = i;
    test2 = test1;
    test1[0] = 100;
    for (int i = 0; i < 10; i++) {
        std::cout << "test1: " << test1[i] <<
                    " test2: " << test2[i] <<
                    std::endl;
    }
    std::cout << std::endl;
   
    std::cout << "Testing 2: Error handling" << std::endl;
    try {
        std::cout << test2[11] << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    try {
        std::cout << test2[1] << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    try {
        std::cout << test3[0] << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    try {
        std::cout << test2[-1] << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    /*****************************************************************/
    std::cout << std::endl;
    std::cout << "Testing 3: Complex data types" << std::endl;
    
    Array<complexData> test4(5);

    for (int i = 0; i < 5; i++) {
        test4[i].a = i;
        test4[i].b = static_cast<char>(i + 70);
        test4[i].c = static_cast<float>(i) / 2;
    }
    for (int i = 0; i < 5; i++) {
        std::cout << "a: " << test4[i].a
                << " b: " << test4[i].b
                << " c: " << test4[i].c
                << std::endl;
    }
}