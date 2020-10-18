/**
 * @file ServoController.hpp
 * @author jonas
 * @date 9/24/20
 * Description here TODO
 */

#ifndef SPOTMICROCPP_SERVOCONTROLLER_HPP
#define SPOTMICROCPP_SERVOCONTROLLER_HPP

#include <i2c/ServoHat.hpp>  // for ServoHat
#include <string>            // for allocator, string


class ServoController {
    public:

        explicit ServoController(const std::string &path = "/dev/i2c-1");

        void set(gsl::index index, unsigned int us);

    private:
        i2c::ServoHat servoHat;

};


#endif //SPOTMICROCPP_SERVOCONTROLLER_HPP
