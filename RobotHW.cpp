/**
 * @file RobotHW.cpp
 * @author jonas
 * @date 10/18/20
 * Description here TODO
 */

#include "RobotHW.hpp"
#include "Kinematics.hpp"
#include "expect.hpp"

void RobotHW::setFrontLeftFoot(Vector3d pos) {
    setLeg(pos, config.frontLeft, 0);
}

void RobotHW::setFrontRightFoot(Vector3d pos) {
    setLeg(pos, config.frontRight, 3);
}

void RobotHW::setBackLeftFoot(Vector3d pos) {
    setLeg(pos, config.backLeft, 6);

}

void RobotHW::setBackRightFoot(Vector3d pos) {
    setLeg(pos, config.backRight, 9);

}

void RobotHW::setLeg(Vector3d pos, LegConfig c, gsl::index firstServo) {
    auto pose = Kinematics::legPoseFromFootPosition(pos, c);
    ExpectM(std::abs(pose.abductionAngle.getDegs()) < 30, "|Abduction angle| < 10°");
    ExpectM(pose.kneeAngle.getDegs() > -90, "Knee angle > -40°");
    ExpectM(pose.kneeAngle.getDegs() < 45, "Knee angle < 45°");
    ExpectM(std::abs(pose.hipAngle.getDegs()) < 80, "|HipAngle| < 80°");
    servoController.set(firstServo, c.abductionServo.getValue(pose.abductionAngle));
    servoController.set(firstServo + 1, c.hipServo.getValue(pose.hipAngle));
    servoController.set(firstServo + 2, c.kneeServo.getValue(pose.kneeAngle));
}
