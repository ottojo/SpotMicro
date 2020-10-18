/**
 * @file MathUtil.hpp
 * @author jonas
 * @date 9/23/20
 * Description here TODO
 */

#ifndef SPOTMICROCPP_MATHUTIL_HPP
#define SPOTMICROCPP_MATHUTIL_HPP

#include "Angle.hpp"

#include "expect.hpp"
#include <gsl/gsl>

namespace math {
    /**
     * Calculate angle in triangle when the length of all sides is known
     * @param a Side a length
     * @param b Side b length
     * @param opposingLength Side c length (the angle opposite of this side is returned)
     * @return Angle opposite of side c in radians
     */
    static Angle cosineLawAngle(double a, double b, double opposingLength) {
        ExpectM(a + b > opposingLength, "Valid triangle");
        ExpectM(a + opposingLength > b, "Valid triangle");
        ExpectM(b + opposingLength > a, "Valid triangle");
        ExpectM(a != 0, "Side a != 0");
        ExpectM(b != 0, "Side b != 0");
        ExpectM(opposingLength != 0, "Side c != 0");
        ExpectM(!std::isnan(a), "a != nan");
        ExpectM(!std::isnan(b), "b != nan");
        ExpectM(!std::isnan(opposingLength), "c != nan");
        const double arg = (a * a + b * b - opposingLength * opposingLength) / (2 * a * b);
        ExpectM(std::abs(arg) < 1, "acos argument has to be between -1 and 1");
        auto result = Angle{acos(arg)};
        Ensures(result.getRads() >= 0);
        return result;
    }

    /**
     * Calculate length of side in triangle when both other sides and the opposing angle are known
     * @param a Side a length
     * @param b Side b length
     * @param gamma Angle opposite of side c
     * @return Side c length
     */
    static double cosineLawSide(double a, double b, Angle gamma) {
        return sqrt(a * a + b * b - 2 * a * b * cos(gamma.getRads()));
    }


    /**
     * _______c________
     * \                 \ b
     * d\                   \
     *   \alpha_____a____beta__\
     * @return alpha
     */
    static Angle squareAngle(double a, double b, double c, double d, Angle beta) {
        const auto e = cosineLawSide(a, b, beta);
        const auto alpha1 = cosineLawAngle(e, a, b);
        const auto alpha2 = cosineLawAngle(d, e, c);
        return alpha1 + alpha2;
    }

    /**
     * https://easings.net/#easeInOutSine
     * @param x between 0 and 1
     * @return between 0 and 1
     */
    static double easeInOutSine(double x) {
        return -(cos(M_PI * x) - 1) / 2;
    }

}  // namespace math
#endif //SPOTMICROCPP_MATHUTIL_HPP
