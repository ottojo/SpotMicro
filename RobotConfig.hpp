/**
 * @file Config.hpp
 * @author jonas
 * @date 10/18/20
 * Description here TODO
 */

#ifndef SPOTMICROCPP_ROBOTCONFIG_HPP
#define SPOTMICROCPP_ROBOTCONFIG_HPP

#include "LegConfig.hpp"

struct RobotConfig {
    LegConfig frontLeft;
    LegConfig frontRight;
    LegConfig backLeft;
    LegConfig backRight;
};

#endif //SPOTMICROCPP_ROBOTCONFIG_HPP
