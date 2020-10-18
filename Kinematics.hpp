/**
 * @file Kinematics.hpp
 * @author jonas
 * @date 9/18/20
 * Description here TODO
 */

#ifndef SPOTMICROCPP_KINEMATICS_HPP
#define SPOTMICROCPP_KINEMATICS_HPP


#include "Vector3d.hpp"
#include "VectorXZ.hpp"
#include "LegPose.hpp"
#include "LegConfig.hpp"

class Kinematics {
    public:
        static LegPose legPoseFromFootPosition(const Vector3d &footPos, const LegConfig &config);
};


#endif //SPOTMICROCPP_KINEMATICS_HPP
