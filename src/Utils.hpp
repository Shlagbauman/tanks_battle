#pragma once
#include <SFML/System/Vector2.hpp>

constexpr float deg2rad(float deg) noexcept { return deg * 3.1415926f / 180.f; }

template <typename T>
constexpr T clamp(T v, T min, T max) noexcept {
    return (v < min) ? min : (v > max) ? max : v;
}