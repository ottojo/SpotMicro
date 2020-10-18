#include <utility>

/**
 * @file KinematicExceptions.hpp
 * @author jonas
 * @date 9/26/20
 * Description here TODO
 */

#ifndef SPOTMICROCPP_KINEMATICEXCEPTIONS_HPP
#define SPOTMICROCPP_KINEMATICEXCEPTIONS_HPP

class KinematicsException : public std::exception {
        std::string message;
    public:
        explicit KinematicsException(const std::string &message) : message{message} {};

        [[nodiscard]] const char *what() const noexcept override {
            return message.c_str();
        }
};

class UnreachableException : public KinematicsException {
    public:
        explicit UnreachableException(const std::string &message) :
                KinematicsException(message) {};
};

#endif //SPOTMICROCPP_KINEMATICEXCEPTIONS_HPP
