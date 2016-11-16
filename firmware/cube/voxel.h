/*
 * Copyright (c) 2014 nitacku
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * Copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, Copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * @file		voxel.h
 * @summary		8x8x8 Mono-color LED Cube
 * @version		1.4
 * @author		nitacku
 * @data		10 October 2015
 */

#ifndef _VOXEL_H_
#define _VOXEL_H_

#include "Arduino.h"
#include "lib8tion.h"

template <class T>
class CVoxel
{
	public:

	T x;
	T y;
	T z;

	CVoxel(void);
	CVoxel(const T x, const T y, const T z);

	CVoxel& operator=(const T value);
	CVoxel& operator+=(const T value);
	CVoxel& operator-=(const T value);
	CVoxel& operator*=(const T value);
	CVoxel& operator/=(const T value);
	CVoxel& operator%=(const T value);

	CVoxel& operator=(const CVoxel<T>& voxel);
	CVoxel& operator+=(const CVoxel<T>& voxel);
	CVoxel& operator-=(const CVoxel<T>& voxel);
	CVoxel& operator*=(const CVoxel<T>& voxel);
	CVoxel& operator/=(const CVoxel<T>& voxel);
	CVoxel& operator%=(const CVoxel<T>& voxel);

	const CVoxel& operator++(void);
	const CVoxel& operator--(void);
	const CVoxel operator++(const int);
	const CVoxel operator--(const int);

	const CVoxel operator+(const T value) const;
	const CVoxel operator-(const T value) const;
	const CVoxel operator*(const T value) const;
	const CVoxel operator/(const T value) const;
	const CVoxel operator%(const T value) const;

	const CVoxel operator+(const CVoxel<T>& voxel) const;
	const CVoxel operator-(const CVoxel<T>& voxel) const;
	const CVoxel operator*(const CVoxel<T>& voxel) const;
	const CVoxel operator/(const CVoxel<T>& voxel) const;
	const CVoxel operator%(const CVoxel<T>& voxel) const;

	bool operator==(const CVoxel<T>& voxel) const;
	bool operator!=(const CVoxel<T>& voxel) const;

	const CVoxel Rotate(const float angle_x, const float angle_y, const float angle_z);
};


template <class T>
inline CVoxel<T> operator+(const T value, CVoxel<T> voxel)
{
	return voxel += value;
}


template <class T>
inline CVoxel<T> operator*(const T value, const CVoxel<T>& voxel)
{
	return voxel *= value;
}


// Constructor
template <class T>
CVoxel<T>::CVoxel(void) { }


// Constructor
template <class T>
CVoxel<T>::CVoxel(const T _x, const T _y, const T _z) : x(_x), y(_y), z(_z) { }


template <class T>
CVoxel<T>& CVoxel<T>::operator=(const T value)
{
	x = value;
	y = value;
	z = value;

	return *this;
}


template <class T>
CVoxel<T>& CVoxel<T>::operator+=(const T value)
{
	x += value;
	y += value;
	z += value;

	return *this;
}


template <class T>
CVoxel<T>& CVoxel<T>::operator-=(const T value)
{
	x -= value;
	y -= value;
	z -= value;

	return *this;
}


template <class T>
CVoxel<T>& CVoxel<T>::operator*=(const T value)
{
	x *= value;
	y *= value;
	z *= value;

	return *this;
}


template <class T>
CVoxel<T>& CVoxel<T>::operator/=(const T value)
{
	x /= value;
	y /= value;
	z /= value;

	return *this;
}


template <class T>
CVoxel<T>& CVoxel<T>::operator%=(const T value)
{
	x %= value;
	y %= value;
	z %= value;

	return *this;
}


template <class T>
CVoxel<T>& CVoxel<T>::operator=(const CVoxel<T>& voxel)
{
	//if (this != &voxel) // check for self-assigment
	{
		x = voxel.x;
		y = voxel.y;
		z = voxel.z;
	}

	return *this;
}


template <class T>
CVoxel<T>& CVoxel<T>::operator+=(const CVoxel<T>& voxel)
{
	x += voxel.x;
	y += voxel.y;
	z += voxel.z;

	return *this;
}


template <class T>
CVoxel<T>& CVoxel<T>::operator-=(const CVoxel<T>& voxel)
{
	x -= voxel.x;
	y -= voxel.y;
	z -= voxel.z;

	return *this;
}


template <class T>
CVoxel<T>& CVoxel<T>::operator*=(const CVoxel<T>& voxel)
{
	x *= voxel.x;
	y *= voxel.y;
	z *= voxel.z;

	return *this;
}


template <class T>
CVoxel<T>& CVoxel<T>::operator/=(const CVoxel<T>& voxel)
{
	x /= voxel.x;
	y /= voxel.y;
	z /= voxel.z;

	return *this;
}


template <class T>
CVoxel<T>& CVoxel<T>::operator%=(const CVoxel<T>& voxel)
{
	x %= voxel.x;
	y %= voxel.y;
	z %= voxel.z;

	return *this;
}

// Prefix
template <class T>
const CVoxel<T>& CVoxel<T>::operator++(void)
{
	x++;
	y++;
	z++;

	return *this;
}

// Prefix
template <class T>
const CVoxel<T>& CVoxel<T>::operator--(void)
{
	x--;
	y--;
	z--;

	return *this;
}

// Postfix
template <class T>
const CVoxel<T> CVoxel<T>::operator++(const int)
{
	CVoxel voxel(*this);
	++(*this);
	return voxel;
}

// Postfix
template <class T>
const CVoxel<T> CVoxel<T>::operator--(const int)
{
	CVoxel voxel(*this);
	--(*this);
	return voxel;
}


template <class T>
const CVoxel<T> CVoxel<T>::operator+(const T value) const
{
	return CVoxel(*this) += value;
}


template <class T>
const CVoxel<T> CVoxel<T>::operator-(const T value) const
{
	return CVoxel(*this) -= value;
}


template <class T>
const CVoxel<T> CVoxel<T>::operator*(const T value) const
{
	return CVoxel(*this) *= value;
}


template <class T>
const CVoxel<T> CVoxel<T>::operator/(const T value) const
{
	return CVoxel(*this) /= value;
}


template <class T>
const CVoxel<T> CVoxel<T>::operator%(const T value) const
{
	return CVoxel(*this) %= value;
}


template <class T>
const CVoxel<T> CVoxel<T>::operator+(const CVoxel<T>& voxel) const
{
	return CVoxel(*this) += voxel;
}


template <class T>
const CVoxel<T> CVoxel<T>::operator-(const CVoxel<T>& voxel) const
{
	return CVoxel(*this) -= voxel;
}


template <class T>
const CVoxel<T> CVoxel<T>::operator*(const CVoxel<T>& voxel) const
{
	return CVoxel(*this) *= voxel;
}


template <class T>
const CVoxel<T> CVoxel<T>::operator/(const CVoxel<T>& voxel) const
{
	return CVoxel(*this) /= voxel;
}


template <class T>
const CVoxel<T> CVoxel<T>::operator%(const CVoxel<T>& voxel) const
{
	return CVoxel(*this) %= voxel;
}


template <class T>
bool CVoxel<T>::operator==(const CVoxel<T>& voxel) const
{
	return ((voxel.x == x) && (voxel.y == y) && (voxel.z == z));
}


template <class T>
bool CVoxel<T>::operator!=(const CVoxel<T>& voxel) const
{
	return !(*this == voxel);
}

/*
// Rotate
template <class T>
const CVoxel<T> CVoxel<T>::Rotate(const uint16_t angle_x, const uint16_t angle_y, const uint16_t angle_z)
{
	int32_t xy, xz, yz, yx, zx, zy, _x, _y, _z;

	_x = x;
	_y = y;
	_z = z;

	// Rotation around the X axis
	xy = (_y*cos16(angle_x) - _z*sin16(angle_x)) / 16384;
	xz = (_y*sin16(angle_x) + _z*cos16(angle_x)) / 16384;

	// Rotation around the Y axis
	yz = (xz*cos16(angle_y) - _x*sin16(angle_y)) / 16384;
	yx = (xz*sin16(angle_y) + _x*cos16(angle_y)) / 16384;

	// Rotation around the Z axis
	zx = (yx*cos16(angle_z) - xy*sin16(angle_z)) / 16384;
	zy = (yx*sin16(angle_z) + xy*cos16(angle_z)) / 16384;

	return CVoxel(zx, zy, yz);
}
*/

// Rotate
template <class T>
const CVoxel<T> CVoxel<T>::Rotate(const float angle_x, const float angle_y, const float angle_z)
{
	float xy, xz, yz, yx, zx, zy;

	typedef union
	{
		uint8_t u;
		int8_t s;
	} u_to_s;

	u_to_s _x;
	u_to_s _y;
	u_to_s _z;

	_x.u = x;
	_y.u = y;
	_z.u = z;

	// Rotation around the X axis
	xy = cos(angle_x)*((float)_y.s + 0.5) - sin(angle_x)*((float)_z.s + 0.5);
	xz = sin(angle_x)*((float)_y.s + 0.5) + cos(angle_x)*((float)_z.s + 0.5);

	// Rotation around the Y axis
	yz = cos(angle_y)*xz - sin(angle_y)*((float)_x.s + 0.5);
	yx = sin(angle_y)*xz + cos(angle_y)*((float)_x.s + 0.5);

	// Rotation around the Z axis
	zx = cos(angle_z)*yx - sin(angle_z)*xy;
	zy = sin(angle_z)*yx + cos(angle_z)*xy;

	zx += 0.5;
	zy += 0.5;
	yz += 0.5;

	return CVoxel(zx, zy, yz);
}

#endif
