/**
 * @file LegPose.cpp
 * @author jonas
 * @date 9/26/20
 * Description here TODO
 */
#include "LegPose.hpp"

std::ostream &operator<<(std::ostream &os, const LegPose &pose) {
    os << fmt::format("{}", pose);
    return os;
}
