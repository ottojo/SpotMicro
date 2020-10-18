/**
 * @file Angle.hpp
 * @author jonas
 * @date 9/18/20
 * Description here TODO
 */

#ifndef SPOTMICROCPP_ANGLE_HPP
#define SPOTMICROCPP_ANGLE_HPP

#include <fmt/format.h>    // for format, format_parse_context, format_error
#include <cmath>           // for isnan, M_PI
#include <gsl/gsl_assert>  // for Expects
#include <gsl/gsl_util>    // for narrow_cast
#include <ostream>         // for ostream
#include <string>          // for operator<<

class Angle {
    double rads;
public:
    explicit constexpr Angle(double r) : rads{r} {
        Expects(!std::isnan(r));
    };

    static constexpr Angle fromDegs(double degs) {
        return Angle{degs * 2 * M_PI / 360};
    }

    [[nodiscard]]constexpr double getRads() const {
        return rads;
    }

    [[nodiscard]] constexpr double getDegs() const {
        return rads * 360 * 0.5 / M_PI;
    }

    constexpr Angle operator+(const Angle &rhs) const {
        return Angle{rads + rhs.rads};
    }

    constexpr Angle operator-() const {
        return Angle{-rads};
    }

    constexpr Angle operator-(const Angle &rhs) const {
        return Angle{rads - rhs.rads};
    }

    constexpr bool operator==(const Angle &rhs) const {
        return rads == rhs.rads;
    }

    friend std::ostream &operator<<(std::ostream &os, const Angle &angle) {
        os << fmt::format("{:d}", angle);
        return os;
    }

};

namespace angle_literals {
    constexpr Angle operator ""_deg(long double d) {
        return Angle::fromDegs(gsl::narrow_cast<double>(d));

    }

    constexpr Angle operator ""_deg(unsigned long long d) {
        return Angle::fromDegs(gsl::narrow_cast<double>(d));
    }

    constexpr Angle operator ""_rad(long double r) {
        return Angle{gsl::narrow_cast<double>(r)};

    }

    constexpr Angle operator ""_rad(unsigned long long r) {
        return Angle{gsl::narrow_cast<double>(r)};

    }
}


template<>
struct fmt::formatter<Angle> {

    bool asDegrees = true;

    constexpr auto parse(format_parse_context &ctx) {
        auto it = ctx.begin(), end = ctx.end();

        if (it != end and (*it == 'd' or *it == 'r')) {
            asDegrees = *it == 'd';
            ++it;
        }

        if (it != end && *it != '}') {
            throw format_error("invalid format");
        }

        return it;
    }

    template<typename FormatContext>
    auto format(const Angle &p, FormatContext &ctx) {
        if (asDegrees) {
            return format_to(ctx.out(), "{:.3f}°", p.getDegs());
        } else {
            return format_to(ctx.out(), "{:.3f}rad", p.getRads());
        }
    }
};


#endif //SPOTMICROCPP_ANGLE_HPP
