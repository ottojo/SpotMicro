/**
 * @file ServoController.cpp
 * @author jonas
 * @date 9/24/20
 * Description here TODO
 */

#include "ServoController.hpp"
#include <i2c/Bus.hpp>   // for Bus
#include <memory>        // for make_shared, shared_ptr

ServoController::ServoController(const std::string &path) : servoHat{std::make_shared<i2c::Bus>(path)} {}

void ServoController::set(gsl::index index, unsigned int us) {
    servoHat.setServo(index, us);
}
