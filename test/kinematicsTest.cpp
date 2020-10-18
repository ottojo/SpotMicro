/**
 * @file kinematicsTest.cpp
 * @author jonas
 * @date 9/26/20
 * Description here TODO
 */

#include <gtest/gtest.h>
#include "../Kinematics.hpp"
#include "../MathUtil.hpp"

#include "angleCompare.hpp"
#include "../KinematicExceptions.hpp"

LegConfig frontLeftLeg{0.074, Servo{1500, 0}, Servo{1550, 635}, Servo{1650, -635}};

using namespace angle_literals;

TEST(LegInverseKinematics, AbductionAngle) {
    auto pose1 = Kinematics::legPoseFromFootPosition({0, 0.021, -0.1}, frontLeftLeg);
    EXPECT_PRED2(AlmostEqual, pose1.abductionAngle, 0.57236695430214479_deg);

    auto pose2 = Kinematics::legPoseFromFootPosition({0, 0.03, -0.1}, frontLeftLeg);
    EXPECT_PRED2(AlmostEqual, pose2.abductionAngle, 5.6550993165228878_deg);

    // Expect greater abduction angle when moving foot further outwards
    EXPECT_GT(pose2.abductionAngle.getDegs(), pose1.abductionAngle.getDegs());
}

TEST(LegInverseKinematics, AbductionAngle_negative) {
    auto pose1 = Kinematics::legPoseFromFootPosition({0, 0.021, -0.12}, frontLeftLeg);
    auto pose2 = Kinematics::legPoseFromFootPosition({0, 0.01, -0.12}, frontLeftLeg);
    EXPECT_LT(pose2.abductionAngle.getDegs(), 0);
    EXPECT_NEAR(pose2.abductionAngle.getDegs(), -4.79697470195548, TOLERANCE);
    EXPECT_GT(pose1.abductionAngle.getDegs(), pose2.abductionAngle.getDegs());
}

TEST(LegInverseKinematics, AbductionAngle_positiveZ) {
    auto pose1 = Kinematics::legPoseFromFootPosition({-0.055, frontLeftLeg.abductionOffset - 0.01, 0.02}, frontLeftLeg);
    EXPECT_PRED2(AlmostEqual, pose1.abductionAngle, 36.870_deg) << pose1;
}

TEST(LegInverseKinematics, HipAngle) {
    auto pos1 = Vector3d{-0.05, 0.02, -0.08};
    auto pose1 = Kinematics::legPoseFromFootPosition(pos1, frontLeftLeg);
    EXPECT_PRED2(AlmostEqual, pose1.abductionAngle, 0_deg);
    EXPECT_PRED2(AlmostEqual, pose1.hipAngle, -10.851_deg);

    // Lower foot by 1cm, expect higher hip angle
    auto pose2 = Kinematics::legPoseFromFootPosition({pos1.x, pos1.y, pos1.z - 0.03}, frontLeftLeg);
    EXPECT_LT(pose2.hipAngle.getDegs(), pose1.hipAngle.getDegs());
    EXPECT_GT(pose2.kneeAngle.getDegs(), pose1.kneeAngle.getDegs());
}

TEST(IK, xAxis) {
    // Moving foot directly behind joint, with leg plane vertical

    Vector3d invalidFront{0.01, frontLeftLeg.abductionOffset, 0};
    EXPECT_THROW(Kinematics::legPoseFromFootPosition(invalidFront, frontLeftLeg), UnreachableException)
                        << "Position in front of joint unreachable";

    Vector3d invalidTooFar{-0.5, frontLeftLeg.abductionOffset, 0};
    EXPECT_ANY_THROW(Kinematics::legPoseFromFootPosition(invalidTooFar, frontLeftLeg))
                        << "Position out of range for leg length";

    Vector3d near{-0.06, frontLeftLeg.abductionOffset, 0};
    auto pose = Kinematics::legPoseFromFootPosition(near, frontLeftLeg);
    EXPECT_PRED2(AlmostEqual, pose.abductionAngle, 0_deg);
    EXPECT_NEAR(pose.hipAngle.getDegs(), 45, 20);
    EXPECT_NEAR(pose.kneeAngle.getDegs(), -10, 5);
    EXPECT_LT(pose.kneeAngle.getDegs() - 90, pose.hipAngle.getDegs());
}

TEST(IK, positiveZ) {
    Vector3d pos{-0.055, frontLeftLeg.abductionOffset, 0.008};
    auto pose = Kinematics::legPoseFromFootPosition(pos, frontLeftLeg);
    EXPECT_NEAR(pose.abductionAngle.getRads(), 0, TOLERANCE);
    EXPECT_NEAR(pose.hipAngle.getDegs(), -45, 20) << "hip angle wrong!";
    EXPECT_NEAR(pose.kneeAngle.getDegs(), -10, 5) << "knee angle wrong!";
}

TEST(IK, negativeZ) {
    Vector3d pos{-0.05, frontLeftLeg.abductionOffset, -0.04};
    auto pose = Kinematics::legPoseFromFootPosition(pos, frontLeftLeg);
    EXPECT_PRED2(AlmostEqual, pose.abductionAngle, 0_deg);
    EXPECT_NEAR(pose.hipAngle.getDegs(), -10, 8);
    EXPECT_NEAR(pose.kneeAngle.getDegs(), 10, 10);

    EXPECT_EQ(pose.kneeAngle, 10.0_deg);
}

TEST(IK, largeNegativeZ) {
    // (positive hip angle)
    Vector3d pos{0, frontLeftLeg.abductionOffset, -0.09};
    auto pose = Kinematics::legPoseFromFootPosition(pos, frontLeftLeg);
    EXPECT_PRED2(AlmostEqual, pose.abductionAngle, 0_deg);
    EXPECT_NEAR(pose.hipAngle.getDegs(), 40, 5);
    EXPECT_NEAR(pose.kneeAngle.getDegs(), 60, 10);

    Vector3d lowerPos{pos.x, pos.y, -0.12};
    auto lowerPose = Kinematics::legPoseFromFootPosition(lowerPos, frontLeftLeg);
    EXPECT_GT(lowerPose.hipAngle.getDegs(), pose.hipAngle.getDegs());
    EXPECT_LT(lowerPose.kneeAngle.getDegs(), pose.kneeAngle.getDegs());
}
