/**
 * @file expect.cpp
 * @author jonas
 * @date 9/24/20
 * Description here TODO
 */
#include "expect.hpp"
#include <iostream>   // for operator<<, basic_ostream, basic_ostream::opera...
#include <stdexcept>  // for invalid_argument

void expect(bool e, const std::string &message, int line, const std::string &file) {
    if (!e) {
        std::cout << "Expect \"" << message << "\" failed at " << file << ":" << line << std::endl;
        throw std::invalid_argument("Expect failed");
    }
}
