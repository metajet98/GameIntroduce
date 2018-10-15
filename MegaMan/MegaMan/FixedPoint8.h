#pragma once
#include <cstdio>

class FixedPoint8 {
private:
	int m_value;

public:
	inline FixedPoint8() {
		m_value = 0;
	};
	inline FixedPoint8(int a_integer, int a_fraction) {
		m_value = a_integer * 256 + a_fraction;
	};
	inline FixedPoint8(int a_value) {
		m_value = a_value * 256;
	};
	inline operator int() {
		return m_value / 256;
	};

	// operator +
	inline FixedPoint8 operator+(const FixedPoint8& a_fixedPoint8) {
		FixedPoint8 fixedPoint8;
		fixedPoint8.m_value = m_value + a_fixedPoint8.m_value;
		return fixedPoint8;
	};
	inline FixedPoint8 operator+(const int& a_int) {
		FixedPoint8 fixedPoint8;
		fixedPoint8.m_value = m_value + (a_int * 256);
		return fixedPoint8;
	};
	inline void operator+=(const FixedPoint8& a_fixedPoint8) {
		m_value += a_fixedPoint8.m_value;
	};
	inline void operator+=(const int& a_int) {
		m_value += (a_int * 256);
	};

	// operator -
	inline FixedPoint8 operator-() {
		FixedPoint8 fixedPoint8;
		fixedPoint8.m_value = -m_value;
		return fixedPoint8;
	};
	inline FixedPoint8 operator-(const FixedPoint8& a_fixedPoint8) {
		FixedPoint8 fixedPoint8;
		fixedPoint8.m_value = m_value - a_fixedPoint8.m_value;
		return fixedPoint8;
	};
	inline FixedPoint8 operator-(const int& a_int) {
		FixedPoint8 fixedPoint8;
		fixedPoint8.m_value = m_value - (a_int * 256);
		return fixedPoint8;
	};
	inline void operator-=(const FixedPoint8& a_fixedPoint8) {
		m_value -= a_fixedPoint8.m_value;
	};
	inline void operator-=(const int& a_int) {
		m_value -= (a_int * 256);
	};

	// operator =
	inline void operator=(const FixedPoint8& a_fixedPoint8) {
		m_value = a_fixedPoint8.m_value;
	};
	inline void operator=(const int& a_int) {
		m_value = a_int * 256;
	};

	// operator ==
	inline bool operator==(const FixedPoint8& a_fixedPoint8) {
		return m_value == a_fixedPoint8.m_value;
	};
	inline bool operator==(const int& a_int) {
		return (m_value / 256) == a_int;
	};

	// operator !=
	inline bool operator!=(const FixedPoint8& a_fixedPoint8) {
		return m_value != a_fixedPoint8.m_value;
	};
	inline bool operator!=(const int& a_int) {
		return (m_value / 256) != a_int;
	};

	// operator <
	inline bool operator<(const FixedPoint8& a_fixedPoint8) {
		return m_value < a_fixedPoint8.m_value;
	};
	inline bool operator<(const int& a_int) {
		return (m_value / 256) < a_int;
	};

	// operator >
	inline bool operator>(const FixedPoint8& a_fixedPoint8) {
		return m_value > a_fixedPoint8.m_value;
	};
	inline bool operator>(const int& a_int) {
		return (m_value / 256) > a_int;
	};

	// debug
	inline void print() {
		std::printf("%d,%d (%d)", m_value / 256, m_value & 0x00FF, m_value);
	};
	inline int get() {
		return m_value;
	};
};
