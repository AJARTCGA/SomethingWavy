#ifndef _VECTOR2_
#define _VECTOR2_

#include <math.h>
#include <iostream>

class Vec2
{
	/***** ATTRIBUTES *****/
protected:
	float mx, my;

	/***** CONSTRUCTOR / DECONSTRUCTOR *****/
public:

	// default constructor sets both x and y to 0
	Vec2() { mx = 0; my = 0; }

	// constructor with initial values as floats
	Vec2(float x, float y) { mx = x; my = y; }

	// constructor with initial values as ints
	Vec2(int x, int y) { mx = (float)x; my = (float)y; }

	// constructor with a scalar to be both x and y
	Vec2(float scalar) { mx = scalar; my = scalar; }

	// default deconstructor
	~Vec2() {};

	/***** GETTERS / SETTERS *****/

	float Vec2::getX() { return mx; }
	float Vec2::getY() { return my; }

	/***** OPERATOR OVERLOADS *****/

	// +=
	Vec2 & Vec2::operator+=(const Vec2 &rhs) {
		this->mx = this->mx + rhs.mx;
		this->my = this->my + rhs.my;
		return *this; 
	}

	// +
	const Vec2 Vec2::operator+(const Vec2 &rhs) {
		Vec2 result = *this;
		result += rhs;
		return result;
	}

	// -=
	Vec2 & Vec2::operator-=(const Vec2 &rhs) {
		this->mx = this->mx - rhs.mx;
		this->my = this->my - rhs.my;
		return *this;
	}

	// -
	const Vec2 Vec2::operator-(const Vec2 &rhs) {
		Vec2 result = *this;
		result -= rhs;
		return result;
	}

	// *=
	Vec2 & Vec2::operator*=(const float &rhs) {
		this->mx = this->mx * rhs;
		this->my = this->my * rhs;
		return *this;
	}

	// *
	const Vec2 Vec2::operator*(const float &rhs) {
		Vec2 result = *this;
		result *= rhs;
		return result;
	}

	// /=
	Vec2 & Vec2::operator/=(const float &rhs) {
		this->mx = this->mx / rhs;
		this->my = this->my / rhs;
		return *this;
	}

	// /
	const Vec2 Vec2::operator/(const float &rhs) {
		Vec2 result = *this;
		result /= rhs;
		return result;
	}

	/***** METHODS *****/

	// returns a new Vec2 that is a copy of the one calling the method
	Vec2 Vec2::copy() { return Vec2(mx, my); }

	// returns a new Vec2 that is the calling vector casted to ints
	Vec2 Vec2::toInt() { return Vec2((int)mx, (int)my); }

	// returns the magnitude of the vector
	float Vec2::magnitude() { return sqrtf( (mx*mx) + (my*my) ); }

	// returns a new Vec2 that is the calling vector normalized
	Vec2 Vec2::normalize() { return Vec2(*this / this->magnitude()); }
	
};

#endif