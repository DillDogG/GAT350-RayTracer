#pragma once

template<typename T>
constexpr T Lerp(const T& a, const T& b, float t)  {
	return (a * (1.0f - t)) + (b * t);
}