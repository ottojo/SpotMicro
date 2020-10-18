/**
 * @file RobotHW.hpp
 * @author jonas
 * @date 10/18/20
 * Description here TODO
 */

#ifndef SPOTMICROCPP_ROBOTHW_HPP
#define SPOTMICROCPP_ROBOTHW_HPP


#include "Vector3d.hpp"
#include "ServoController.hpp"
#include "RobotConfig.hpp"

class RobotHW {
    public:
        RobotHW(RobotConfig c, ServoController &s) :
                servoController{s},
                config{c} {}

        void setFrontLeftFoot(Vector3d pos);

        void setFrontRightFoot(Vector3d pos);

        void setBackLeftFoot(Vector3d pos);

        void setBackRightFoot(Vector3d pos);

    private:
        void setLeg(Vector3d pos, LegConfig c, gsl::index firstServo);

        ServoController &servoController;
        RobotConfig config;
};


#endif //SPOTMICROCPP_ROBOTHW_HPP
