/**
 * @file Vector3d.hpp
 * @author jonas
 * @date 9/23/20
 * Description here TODO
 */
#include <fmt/format.h>

#ifndef SPOTMICROCPP_VECTOR3D_HPP
#define SPOTMICROCPP_VECTOR3D_HPP

struct Vector3d {
    double x;
    double y;
    double z;

    constexpr Vector3d operator-(const Vector3d &rhs) const {
        return Vector3d{x - rhs.x, y - rhs.y, z - rhs.z};
    }

    constexpr Vector3d operator+(const Vector3d &rhs) const {
        return Vector3d{x + rhs.x, y + rhs.y, z + rhs.z};
    }

    constexpr Vector3d operator*(double rhs) const {
        return Vector3d{rhs * x, rhs * y, rhs * z};
    }
};

constexpr Vector3d operator*(double lhs, const Vector3d &rhs) {
    return Vector3d{lhs * rhs.x, lhs * rhs.y, lhs * rhs.z};
}


template<>
struct fmt::formatter<Vector3d> {
    static constexpr auto parse(format_parse_context &ctx) {
        const auto *it = ctx.begin();
        const auto *end = ctx.end();
        if (it != end && *it != '}') {
            throw format_error("invalid format");
        }

        return it;
    }

    template<typename FormatContext>
    auto format(const Vector3d &p, FormatContext &ctx) {
        return format_to(
                ctx.out(),
                "({}, {}, {})", p.x, p.y, p.z);
    }
};

#endif //SPOTMICROCPP_VECTOR3D_HPP
