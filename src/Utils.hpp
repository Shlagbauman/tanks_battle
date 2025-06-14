#pragma once
#include <SFML/System/Vector2.hpp>

/// Утилита перевода между градусами и радианами (пример для Doxygen)
constexpr float deg2rad(float deg) noexcept { return deg * 3.1415926f / 180.f; }

/// Ограничивает значение v диапазоном [min, max]
template <typename T>
constexpr T clamp(T v, T min, T max) noexcept {
    return (v < min) ? min : (v > max) ? max : v;
}