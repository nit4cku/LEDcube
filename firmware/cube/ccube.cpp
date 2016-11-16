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
 * @file		cube.cpp
 * @summary		8x8x8 Mono-color LED Cube
 * @version		1.3
 * @author		nitacku
 * @data		31 March 2014
 */

#include "ccube.h"
#include "lib8tion.h"

// Default Constructor
CCube::CCube() { }

// ===============================================================
//  Transition Functions
// ===============================================================


void CCube::TransitionShift(const type_axis axis, const type_polarity polarity, const uint8_t delay)
{
	uint8_t x;

	for (x = 0; x < 8; x++)
	{
		TranslateShift(axis, ((polarity == POSITIVE) << 1) - 1);
		DelayMS(delay);
	}
}


void CCube::TransitionScroll(const type_axis axis, const type_polarity polarity, const uint8_t delay)
{
	uint8_t x;

	for (x = 0; x < 7; x++)
	{
		TranslateScroll(axis, ((polarity == POSITIVE) << 1) - 1);
		DelayMS(delay);
	}
}


void CCube::TransitionPlane(const type_axis axis, const type_polarity polarity, const uint8_t state, const uint8_t delay)
{
	uint8_t x;

	for (x = 0; x < 8; x++)
	{
		uint8_t value = x + (((polarity == POSITIVE) - 1) & (7 - x - x));

		SetPlane(axis, value, state);
		DelayMS(delay);
		SetPlane(axis, value, OFF);
	}
}


// ===============================================================
//  Translate Functions
// ===============================================================


// Scroll the outer sides of the cube around an axis by value
void CCube::TranslateScroll(const type_axis axis, int8_t value)
{
	uint8_t i, j, k, l, x, y, z, prev_x, prev_y, prev_z, dx, dy, dz, start_state;
	int8_t positive, negative;
	int8_t increment_x[4];
	int8_t increment_y[4];
	int8_t increment_z[4];

	positive = (value > 0);
	negative = (value < 0);

	switch (axis)
	{
	default:
	case AXIS_X:
		increment_x[0] = 0;
		increment_x[1] = 0;
		increment_x[2] = 0;
		increment_x[3] = 0;

		increment_y[0] = positive;
		increment_y[1] = negative;
		increment_y[2] = -positive;
		increment_y[3] = -negative;

		increment_z[0] = negative;
		increment_z[1] = positive;
		increment_z[2] = -negative;
		increment_z[3] = -positive;

		dx = 1;
		dy = 0;
		dz = 0;
		break;

	case AXIS_Y:
		increment_x[0] = positive;
		increment_x[1] = negative;
		increment_x[2] = -positive;
		increment_x[3] = -negative;

		increment_y[0] = 0;
		increment_y[1] = 0;
		increment_y[2] = 0;
		increment_y[3] = 0;

		increment_z[0] = negative;
		increment_z[1] = positive;
		increment_z[2] = -negative;
		increment_z[3] = -positive;

		dx = 0;
		dy = 1;
		dz = 0;
		break;

	case AXIS_Z:
		increment_x[0] = negative;
		increment_x[1] = positive;
		increment_x[2] = -negative;
		increment_x[3] = -positive;

		increment_y[0] = positive;
		increment_y[1] = negative;
		increment_y[2] = -positive;
		increment_y[3] = -negative;

		increment_z[0] = 0;
		increment_z[1] = 0;
		increment_z[2] = 0;
		increment_z[3] = 0;

		dx = 0;
		dy = 0;
		dz = 1;
		break;
	}

	value -= ((value >= 0) - 1) & (value << 1);

	for (l = 0; l<value; l++)
	{
		x = 0;
		y = 0;
		z = 0;

		for (i = 0; i < 8; i++)
		{
			start_state = GetVoxel(type_voxel(x, y, z));

			for (j = 0; j < 4; j++)
			{
				for (k = 0; k < 7; k++)
				{
					prev_x = x;
					prev_y = y;
					prev_z = z;

					x += increment_x[j];
					y += increment_y[j];
					z += increment_z[j];

					SetVoxel(type_voxel(prev_x, prev_y, prev_z), GetVoxel(type_voxel(x, y, z)));
				}
			}

			SetVoxel(type_voxel(prev_x, prev_y, prev_z), start_state);

			x += dx;
			y += dy;
			z += dz;
		}
	}
}


// Shift the entire contents of the cube along an axis by value
void CCube::TranslateShift(const type_axis axis, const int8_t value)
{
	uint8_t i, y, z;
	int8_t n;

	if (value == 0)
	{
		return;
	}
	
	i = (value < 0) ? 0 : 7;
	n = (value < 0) ? 1 : -1;
		
	switch (axis)
	{
	case AXIS_X:
		for (z = 0; z < 8; z++)
		{
			for (y = 0; y < 8; y++)
			{
				cube[z][y] = (cube[z][y] >> 1) + (((value < 0) - 1) & ((cube[z][y] << 1) - (cube[z][y] >> 1)));
				//cube[z][y] = (value < 0) ? (cube[z][y] >> 1) : (cube[z][y] << 1);
			}
		}

		return TranslateShift(axis, value + n);

	case AXIS_Y:
		y = 7;

		do
		{
			for (z = 0; z < 8; z++)
			{
				cube[z][i] = cube[z][i + n];
			}

			i += n;
		}
		while (--y);

		break;

	case AXIS_Z:
		z = 7;

		do
		{
			for (y = 0; y < 8; y++)
			{
				cube[i][y] = cube[i + n][y];
			}

			i += n;
		}
		while (--z);

		break;
	}

	SetPlane(axis, ((value > 0) - 1) & 0x7, OFF);
	return TranslateShift(axis, value + n);	
}


// ===============================================================
//  Draw Functions
// ===============================================================


void CCube::SetVoxel(const type_voxel &voxel, const type_state state)
{
	if (CoordinateInRange(voxel))
	{
		switch (state)
		{
		case OFF:
			cube[voxel.z][voxel.y] &= ~(1 << voxel.x);
			break;

		case ON:
			cube[voxel.z][voxel.y] |= (1 << voxel.x);
			break;

		case INV:
			cube[voxel.z][voxel.y] ^= (1 << voxel.x);
			break;
		}
	}
}


void CCube::SetLine(type_voxel v0, type_voxel v1, const type_state state)
{
	int8_t xd, yd, zd;
	int8_t ax, ay, az;
	int8_t sx, sy, sz;
	int8_t dx, dy, dz;

	dx = v1.x - v0.x;
	dy = v1.y - v0.y;
	dz = v1.z - v0.z;

	ax = abs(dx) << 1;
	ay = abs(dy) << 1;
	az = abs(dz) << 1;

	sx = (dx > 0) ? 1 : -1;
	sy = (dy > 0) ? 1 : -1;
	sz = (dz > 0) ? 1 : -1;

	SetVoxel(v0, state);

	if (ax >= max(ay, az)) /* x dominant */
	{
		yd = ay - (ax >> 1);
		zd = az - (ax >> 1);

		while (v0.x != v1.x)
		{
			if (yd > 0)
			{
				//v0.y += ((yd < 0) - 1) & sy;
				//yd -= ((yd < 0) - 1) & ax;
				
				v0.y += sy;
				yd -= ax;
			}

			if (zd > 0)
			{				
				v0.z += sz;
				zd -= ax;
			}

			v0.x += sx;
			yd += ay;
			zd += az;

			SetVoxel(v0, state);
		}
	}
	else if (ay >= max(ax, az)) /* y dominant */
	{
		xd = ax - (ay >> 1);
		zd = az - (ay >> 1);

		while (v0.y != v1.y)
		{
			if (xd > 0)
			{
				v0.x += sx;
				xd -= ay;
			}

			if (zd > 0)
			{
				v0.z += sz;
				zd -= ay;
			}

			v0.y += sy;
			xd += ax;
			zd += az;

			SetVoxel(v0, state);
		}
	}
	else if (az >= max(ax, ay)) /* z dominant */
	{
		xd = ax - (az >> 1);
		yd = ay - (az >> 1);

		while (v0.z != v1.z)
		{
			if (xd > 0)
			{
				v0.x += sx;
				xd -= az;
			}

			if (yd > 0)
			{
				v0.y += sy;
				yd -= az;
			}

			v0.z += sz;
			xd += ax;
			yd += ay;

			SetVoxel(v0, state);
		}
	}
}

/*
void CCube::set_character(const type_axis axis, const uint8_t index, const char character)
{
	uint8_t y, z;
	uint8_t* bitmap;

	bitmap = get_bitmap(character);

	for (y = 0; y < 8; y++)
	{
		for (z = 0; z < 8; z++)
		{
			SetVoxel(type_voxel(y, 7-index, 7-z), (*(bitmap + z) >> y) & 0x01);
		}
	}
}
*/

void CCube::SetPlane(const type_axis axis, const uint8_t index, const type_state state)
{
	uint8_t y, i;

	if (index < 8)
	{
		for (i = 0; i < 8; i++)
		{
			switch (axis)
			{
			case AXIS_X:
				for (y = 0; y < 8; y++)
				{
					switch (state)
					{
					case OFF:
						cube[i][y] &= ~(1 << index);
						break;

					case ON:
						cube[i][y] |= (1 << index);
						break;

					case INV:
						cube[i][y] ^= (1 << index);
						break;
					}
				}

				break;

			case AXIS_Y:
				switch (state)
				{
				case OFF:
					cube[i][index] = 0x00;
					break;

				case ON:
					cube[i][index] = 0xFF;
					break;

				case INV:
					cube[i][index] ^= 0xFF;
					break;
				}

				break;

			case AXIS_Z:
				switch (state)
				{
				case OFF:
					cube[index][i] = 0x00;
					break;

				case ON:
					cube[index][i] = 0xFF;
					break;

				case INV:
					cube[index][i] ^= 0xFF;
					break;
				}

				break;
			}
		}
	}
}


void CCube::SetSphere(const type_float_cd &fcd, float radius, const type_state state)
{
	float j, k;
	float radius2;

	radius2 = radius * radius;

	for (k = 0; k < 8; k += 0.5)
	{
		float z0;
		z0 = (k - fcd.z);
		z0 *= z0;

		for (j = 0; j < 8; j += 0.5)
		{
			float operand, y0;
			y0 = (j - fcd.y);
			y0 *= y0;
			operand = radius2 - y0 - z0;

			if (operand >= 0)
			{
				float x0;
				x0 = sqrt(operand);

				/*
				union {int ix; float x0;};
				x0 = operand;					// x can be viewed as int.
				ix = 0x1fbb67a8 + (ix >> 1);	// Initial guess.
				x0 = 0.5f*(x0 + operand/x0);	// Newton step.
				*/

				SetVoxel(type_voxel(x0 + fcd.x, j, k), state);
				SetVoxel(type_voxel(fcd.x - x0, j, k), state);
			}
		}
	}
}


void CCube::SetCube(const uint8_t pattern)
{
	uint8_t z;
	uint8_t y;

	for (z = 0; z < 8; z++)
	{
		for (y = 0; y < 8; y++)
		{
			cube[z][y] = pattern;
		}
	}
}


void CCube::SetCuboid(type_voxel v0, type_voxel v1, const type_state state)
{
	uint8_t x, y, z;

	CoordinateOrder(v0, v1);

	for (x = v0.x; x < v1.x + 1; x++)
	{
		for (y = v0.y; y < v1.y + 1; y++)
		{
			for (z = v0.z; z < v1.z + 1; z++)
			{
				SetVoxel(type_voxel(x, y, z), state);
			}
		}
	}
}


void CCube::SetWireframe(const type_voxel &v0, const type_voxel &v1, const type_state state)
{
	SetLine(type_voxel(v0.x, v0.y, v0.z), type_voxel(v1.x, v0.y, v0.z), state);
	SetLine(type_voxel(v1.x, v0.y, v0.z), type_voxel(v1.x, v1.y, v0.z), state);
	SetLine(type_voxel(v1.x, v1.y, v0.z), type_voxel(v0.x, v1.y, v0.z), state);
	SetLine(type_voxel(v0.x, v1.y, v0.z), type_voxel(v0.x, v0.y, v0.z), state);
	SetLine(type_voxel(v0.x, v0.y, v1.z), type_voxel(v1.x, v0.y, v1.z), state);
	SetLine(type_voxel(v1.x, v0.y, v1.z), type_voxel(v1.x, v1.y, v1.z), state);
	SetLine(type_voxel(v1.x, v1.y, v1.z), type_voxel(v0.x, v1.y, v1.z), state);
	SetLine(type_voxel(v0.x, v1.y, v1.z), type_voxel(v0.x, v0.y, v1.z), state);
	SetLine(type_voxel(v0.x, v0.y, v0.z), type_voxel(v0.x, v0.y, v1.z), state);
	SetLine(type_voxel(v1.x, v0.y, v0.z), type_voxel(v1.x, v0.y, v1.z), state);
	SetLine(type_voxel(v0.x, v1.y, v0.z), type_voxel(v0.x, v1.y, v1.z), state);
	SetLine(type_voxel(v1.x, v1.y, v0.z), type_voxel(v1.x, v1.y, v1.z), state);
}


// ===============================================================
//  Utility Functions
// ===============================================================


// Get the current status of a voxel
uint8_t CCube::GetVoxel(const type_voxel &voxel)
{
	if (CoordinateInRange(voxel))
	{
		if (cube[voxel.z][voxel.y] & (1 << voxel.x))
		{
			return ON;
		}
	}

	return OFF;
}


void CCube::Copy(CCube& buffer)
{
	memcpy8(buffer.cube, cube, 64);
}


void CCube::DelayMS(uint16_t x)
{
	uint16_t z;

	for (; x > 0; x--)
	{
		for (z = 0; z < DELAY_CONSTANT_C; z++)
		{
			asm volatile("nop");
		}
	}
}


// This function validates that the coordinates are inside the cube
uint8_t CCube::CoordinateInRange(const type_voxel &voxel)
{
	return ((voxel.x | voxel.y | voxel.z) < 8);
}


// Makes sure v0 is alwas smaller than v1
void CCube::CoordinateOrder(type_voxel &v0, type_voxel &v1)
{
	max(v0.x, v1.x); // v1.x = t0.x ^ ((t0.x ^ t1.x) & -(t0.x < t1.x));
	min(v0.x, v1.x); // v0.x = t1.x ^ ((t0.x ^ t1.x) & -(t0.x < t1.x));

	max(v0.y, v1.y); // v1.y = t0.y ^ ((t0.y ^ t1.y) & -(t0.y < t1.y));
	min(v0.y, v1.y); // v0.y = t1.y ^ ((t0.y ^ t1.y) & -(t0.y < t1.y));

	max(v0.z, v1.z); // v1.z = t0.z ^ ((t0.z ^ t1.z) & -(t0.z < t1.z));
	min(v0.z, v1.z); // v0.z = t1.z ^ ((t0.z ^ t1.z) & -(t0.z < t1.z));
}
