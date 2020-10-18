/**
 * @file Config.hpp
 * @author jonas
 * @date 9/18/20
 * Description here TODO
 */

#ifndef SPOTMICROCPP_LEGCONFIG_HPP
#define SPOTMICROCPP_LEGCONFIG_HPP

#include <fmt/core.h>
#include <fmt/format.h>
#include "Servo.hpp"

struct LegConfig {
    constexpr LegConfig(double wireLength, Servo abduction, Servo hip, Servo knee) noexcept :
            wireLength{wireLength},
            abductionServo{abduction},
            hipServo{hip},
            kneeServo{knee} {};

    double abductionOffset = 0.02;
    double upperLegLength = 0.075;
    double lowerLegLength = 0.07;
    double servoArmLength = 0.014;
    double wireLength;
    double lowerLegLeverLength = 0.015;
    Servo abductionServo;
    Servo hipServo;
    Servo kneeServo;
};

template<>
struct fmt::formatter<LegConfig> {
    static constexpr auto parse(format_parse_context &ctx) {
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && *it != '}')
            throw format_error("invalid format");

        return it;
    }

    template<typename FormatContext>
    auto format(const LegConfig &p, FormatContext &ctx) {
        return format_to(
                ctx.out(),
                "abductionOffset: {}, "
                "upperLegLength: {}, "
                "lowerLegLength: {}, "
                "servoArmLength: {}, "
                "wireLength: {}, "
                "lowerLegLeverLength: {}, ",
                p.abductionOffset,
                p.upperLegLength,
                p.lowerLegLength,
                p.servoArmLength,
                p.wireLength,
                p.lowerLegLeverLength
        );
    }
};

#endif //SPOTMICROCPP_LEGCONFIG_HPP
