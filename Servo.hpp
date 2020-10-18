/**
 * @file Servo.hpp
 * @author jonas
 * @date 9/23/20
 * Description here TODO
 */

#ifndef SPOTMICROCPP_SERVO_HPP
#define SPOTMICROCPP_SERVO_HPP


#include "Angle.hpp"
#include <gsl/gsl>


class Servo {
    public:
        explicit constexpr Servo(int mid = 1500, double scale = DEFAULT_SCALE) noexcept: mid(mid), scale(scale) {}

        [[nodiscard]] constexpr int getValue(Angle a) const {
            Expects(-M_PI_2 <= a.getRads());
            Expects(a.getRads() <= M_PI_2);
            return gsl::narrow_cast<int>(scale * a.getRads()) + mid;
        }

        static constexpr double DEFAULT_SCALE = 635;

    private:
        int mid;

        double scale; // µs/rad
};


#endif //SPOTMICROCPP_SERVO_HPP
