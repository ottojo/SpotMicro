/**
 * @file TrajectoryRunner.hpp
 * @author jonas
 * @date 10/18/20
 * Description here TODO
 */

#ifndef SPOTMICROCPP_TRAJECTORYRUNNER_HPP
#define SPOTMICROCPP_TRAJECTORYRUNNER_HPP


#include <chrono>
#include <memory>
#include "FootTrajectory.hpp"
#include "RobotHW.hpp"

class TrajectoryRunner {
    public:
        using TrajPtr = std::shared_ptr<const FootTrajectory>;
        using Clock = std::chrono::system_clock;
        using Duration = Clock ::duration;

        static void run(const TrajPtr& frontLeft, const TrajPtr& frontRight, const TrajPtr& backLeft, const TrajPtr& backRight, Duration duration,
                        RobotHW &robot);
};


#endif //SPOTMICROCPP_TRAJECTORYRUNNER_HPP
