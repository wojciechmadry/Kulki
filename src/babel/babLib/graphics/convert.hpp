// Copyright [2021] <Wojtek>"
#ifndef BABLIB_GRAPHICS_CONVERT_HPP_
#define BABLIB_GRAPHICS_CONVERT_HPP_

#include "rgb.hpp"
#include "cmyk.hpp"

namespace babel::GRAPHICS{
    using byte = uint8_t;

    inline constexpr cmyk RGB_TO_CMYK(const rgb &_rgb) noexcept
    {
        auto rp = static_cast<double>(_rgb.R()) / 255.0;
        auto gp = static_cast<double>(_rgb.G()) / 255.0;
        auto bp = static_cast<double>(_rgb.B()) / 255.0;
        double k = 1.0 - babel::ALGO::MATH::max(babel::ALGO::MATH::max(rp, gp), bp);
        double o_m_k = 1.0 - k;
        double c = ( ( 1.0 - rp - k ) / o_m_k ) * 100.0;
        double m = ( ( 1.0 - gp - k ) / o_m_k ) * 100.0;
        double y = ( ( 1.0 - bp - k ) / o_m_k ) * 100.0;
        k *= 100.0;
        return cmyk(static_cast<byte>(c), static_cast<byte>(m), static_cast<byte>(y), static_cast<byte>(k));
    }

    inline constexpr rgb CMYK_TO_RGB(const cmyk &_cmyk) noexcept
    {
        auto c = static_cast<double>(_cmyk.C()) / 100.0;
        auto m = static_cast<double>(_cmyk.M()) / 100.0;
        auto y = static_cast<double>(_cmyk.Y()) / 100.0;
        auto k = static_cast<double>(_cmyk.K()) / 100.0;
        byte r = static_cast<byte>(255 * ( 1.0 - c ) * ( 1.0 - k ));
        byte g = static_cast<byte>(255 * ( 1.0 - m ) * ( 1.0 - k ));
        byte b = static_cast<byte>(255 * ( 1.0 - y ) * ( 1.0 - k ));
        return rgb(r, g, b);
    }

}  // namespace babel::GRAPHICS
#endif  // BABLIB_GRAPHICS_CONVERT_HPP_
