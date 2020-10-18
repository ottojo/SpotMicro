/**
 * @file TrajectoryRunner.cpp
 * @author jonas
 * @date 10/18/20
 * Description here TODO
 */

#include "TrajectoryRunner.hpp"
#include <thread>

void TrajectoryRunner::run(const TrajectoryRunner::TrajPtr &frontLeft, const TrajectoryRunner::TrajPtr &frontRight,
                           const TrajectoryRunner::TrajPtr &backLeft, const TrajectoryRunner::TrajPtr &backRight,
                           TrajectoryRunner::Duration duration, RobotHW &robot) {
    auto start = Clock::now();
    auto end = start + duration;
    constexpr auto delay = std::chrono::milliseconds(5);

    while (Clock::now() < end) {
        const auto stepStart = Clock::now();
        const auto expired = stepStart - start;
        const double progress = static_cast<double>(expired.count()) /
                                static_cast<double>(duration.count());
        fmt::print("Trajectory progress: {:.1f}% ({}ms)\n", progress * 100,
                   std::chrono::duration_cast<std::chrono::milliseconds>(expired).count());
        robot.setFrontLeftFoot(frontLeft->getPos(progress));
        robot.setFrontRightFoot(frontRight->getPos(progress));
        robot.setBackLeftFoot(backLeft->getPos(progress));
        robot.setBackRightFoot(backRight->getPos(progress));

        std::this_thread::sleep_until(stepStart + delay);
    }

    // Ensure end of trajectory always gets commanded
    robot.setFrontLeftFoot(frontLeft->getPos(1));
    robot.setFrontRightFoot(frontRight->getPos(1));
    robot.setBackLeftFoot(backLeft->getPos(1));
    robot.setBackRightFoot(backRight->getPos(1));
}
