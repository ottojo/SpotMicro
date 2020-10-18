/**
 * @file VectorXZ.hpp
 * @author jonas
 * @date 9/23/20
 * Description here TODO
 */
#include <fmt/format.h>

#ifndef SPOTMICROCPP_VECTORXZ_HPP
#define SPOTMICROCPP_VECTORXZ_HPP
struct VectorXZ {
    double x;
    double z;
};


template<>
struct fmt::formatter<VectorXZ> {
    static constexpr auto parse(format_parse_context &ctx) {
        const auto *it = ctx.begin();
        const auto *end = ctx.end();
        if (it != end && *it != '}') {
            throw format_error("invalid format");
        }

        return it;
    }

    template<typename FormatContext>
    auto format(const VectorXZ &p, FormatContext &ctx) {
        return format_to(
                ctx.out(),
                "(x={}, z={})", p.x, p.z);
    }
};

#endif //SPOTMICROCPP_VECTORXZ_HPP
