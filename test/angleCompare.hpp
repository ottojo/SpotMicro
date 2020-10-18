/**
 * @file angleCompare.hpp
 * @author jonas
 * @date 9/26/20
 * Description here TODO
 */

#ifndef SPOTMICROCPP_ANGLECOMPARE_HPP
#define SPOTMICROCPP_ANGLECOMPARE_HPP

#include "../Angle.hpp"

constexpr double TOLERANCE = 0.0001;

bool AlmostEqual(Angle a, Angle b) {
    return std::abs((a - b).getRads()) < TOLERANCE;
}

#endif //SPOTMICROCPP_ANGLECOMPARE_HPP
