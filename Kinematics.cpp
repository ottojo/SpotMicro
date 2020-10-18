/**
 * @file Kinematics.cpp
 * @author jonas
 * @date 9/18/20
 * Description here TODO
 */

#include "Kinematics.hpp"
#include "Angle.hpp"                // for Angle
#include "KinematicExceptions.hpp"  // for UnreachableException
#include "MathUtil.hpp"             // for cosineLawAngle, squareAngle
#include <cmath>                    // for atan2, sqrt, M_PI, M_PI_2
#include <fmt/format.h>             // for format, print
#include <stdexcept>                // for invalid_argument

struct HipKneeAngles {
    Angle hipAngle;
    Angle kneeAngle;
};


static HipKneeAngles calcInLegPlane(double x, double z, const LegConfig &config) {

    const auto l = sqrt(x * x + z * z);

    // Angle between vector to foot and upper leg
    const auto innerHipAngle = math::cosineLawAngle(config.upperLegLength, l, config.lowerLegLength);

    // Angle -x axis to foot vector
    const auto footAngle = Angle{atan2(z, -x)};

    // -x -> footVector -> upper leg
    const auto hipAngle = footAngle + innerHipAngle;

    // Angle between upper and lower leg
    const auto innerKneeAngle = math::cosineLawAngle(config.lowerLegLength, config.upperLegLength, l);

    // Apply viereck
    const auto beta = Angle{M_PI} - innerKneeAngle;
    try {
        const auto alpha = math::squareAngle(config.upperLegLength, config.lowerLegLeverLength, config.wireLength,
                                             config.servoArmLength, beta);
        const auto kneeServoAngle = (hipAngle + alpha) - Angle{M_PI_2};
        return HipKneeAngles{.hipAngle=hipAngle, .kneeAngle=kneeServoAngle};
    } catch (std::invalid_argument &e) {
        throw UnreachableException(
                fmt::format("Error in computing knee servo angle for config {}, x={}, z={}, beta={}",
                            config, x, z, beta));
    }

}


LegPose Kinematics::legPoseFromFootPosition(const Vector3d &footPos, const LegConfig &config) {
    fmt::print("Solving leg pose for {}\n", footPos);
    // Solve abduction angle in YZ plane

    // Distance of foot to origin in YZ plane
    const auto footDistanceYZSquare = footPos.y * footPos.y + footPos.z * footPos.z;

    // foot Z coordinate in leg plane
    const auto lzSquared = footDistanceYZSquare - config.abductionOffset * config.abductionOffset;
    if (lzSquared < 0) {
        throw UnreachableException{"Distance to foot smaller than abduction offset."};
    }
    const auto legPlaneZ = sqrt(lzSquared) *
                           (footPos.z > 0 ? 1 : -1);

    // Angle between abduction axis and foot vector, positive = foot above hip in leg plane
    const auto phi = Angle{atan2(legPlaneZ, config.abductionOffset)};

    // Angle between robot y axis and foot vector
    const auto hfa = Angle{atan2(footPos.z, footPos.y)};

    // Abduction angle, positive = tilt upwards
    const auto abductionAngle = hfa - phi;

    auto planeResults = calcInLegPlane(footPos.x, legPlaneZ, config);

    return LegPose{.abductionAngle=abductionAngle, .hipAngle=planeResults.hipAngle, .kneeAngle=planeResults.kneeAngle};
}
