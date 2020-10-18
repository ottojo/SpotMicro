/**
 * @file LegPose.hpp
 * @author jonas
 * @date 9/18/20
 * Description here TODO
 */

#ifndef SPOTMICROCPP_LEGPOSE_HPP
#define SPOTMICROCPP_LEGPOSE_HPP

#include "Angle.hpp"     // for Angle
#include <fmt/format.h>  // for format_parse_context, format_error, formatter
#include <iosfwd>        // for ostream

struct LegPose {
    Angle abductionAngle{0};

    // Hip Angle: Positive == Lower leg points up (CCW rotation when viewed from outside)
    Angle hipAngle{0};

    /** @brief Angle of knee-servo, 0 == servo arm vertical (CCW rotation when viewed from outside) */
    Angle kneeAngle{0};
};

std::ostream &operator<<(std::ostream &os, const LegPose &pose);


template<>
struct fmt::formatter<LegPose> {
    static constexpr auto parse(const format_parse_context &ctx) {
        const auto *it = ctx.begin();
        const auto *end = ctx.end();
        if ((it != end) && (*it != '}')) {
            throw format_error("invalid format");
        }
        return it;
    }

    template<typename FormatContext>
    auto format(const LegPose &p, FormatContext &ctx) {
        return format_to(
                ctx.out(),
                "(abduction: {}, hip: {}, knee: {})",
                p.abductionAngle, p.hipAngle, p.kneeAngle);
    }
};

#endif //SPOTMICROCPP_LEGPOSE_HPP
