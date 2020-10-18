
#include "LegConfig.hpp"
#include "RobotConfig.hpp"
#include "RobotHW.hpp"
#include "StraightTrajectory.hpp"
#include "TrajectoryRunner.hpp"
#include <fmt/core.h>

const RobotConfig spotMicro{
        .frontLeft=LegConfig{0.074, Servo{1500, 0}, Servo{1550, 635}, Servo{1650, -635}},
        .frontRight=LegConfig{0.07748, Servo{1500, 0}, Servo{1550, -635}, Servo{1650, 635}},

        .backLeft=LegConfig{0.07748, Servo{1500, 0}, Servo{1550, 635}, Servo{1650, -635}},
        .backRight=LegConfig{0.07748, Servo{1500, 0}, Servo{1550, -635}, Servo{1650, 635}},
};

int main() {
    ServoController servoController;
    RobotHW robot(spotMicro, servoController);

    auto down = -0.1;
    auto up = -0.08;
    auto front = 0.0;
    auto back = -0.04;

    auto frontBackTraj = std::make_shared<StraightTrajectory>(Vector3d{front, 0, down}, Vector3d{back, 0, down});
    auto upTraj = std::make_shared<StraightTrajectory>(Vector3d{back, 0, down}, Vector3d{back, 0, up});
    auto backFrontTraj = std::make_shared<StraightTrajectory>(Vector3d{back, 0, up}, Vector3d{front, 0, up});
    auto downTraj = std::make_shared<StraightTrajectory>(Vector3d{front, 0, up}, Vector3d{front, 0, down});

    auto t1 = std::chrono::milliseconds(100);
    auto t2 = std::chrono::milliseconds(200);

    while (true) {
        TrajectoryRunner::run(frontBackTraj, backFrontTraj, backFrontTraj, frontBackTraj, t2, robot);
        TrajectoryRunner::run(upTraj, downTraj, downTraj, upTraj, t1, robot);

        TrajectoryRunner::run(backFrontTraj, frontBackTraj, frontBackTraj, backFrontTraj, t2, robot);
        TrajectoryRunner::run(downTraj, upTraj, upTraj, downTraj, t1, robot);
    }
}
