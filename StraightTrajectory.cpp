/**
 * @file StraightTrajectory.cpp
 * @author jonas
 * @date 10/18/20
 * Description here TODO
 */

#include "StraightTrajectory.hpp"
#include "MathUtil.hpp"

Vector3d StraightTrajectory::getPos(double progress) const {
    return start + math::easeInOutSine(progress) * direction;
}
