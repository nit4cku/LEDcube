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
 * @file		cube.h
 * @summary		8x8x8 Mono-color LED Cube
 * @version		1.3
 * @author		nitacku
 * @data		31 March 2014
 */

#ifndef _CUBE_H_
#define _CUBE_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "voxel.h"

const uint16_t DELAY_CONSTANT_C = 1750;

class CCube
{
	public:

	enum state_t : uint8_t
	{
		OFF,
		ON,
		INV,
	} STATE;

	enum polarity_t : uint8_t
	{
		POSITIVE,
		NEGATIVE,
	} POLARITY;

	enum axis_t : uint8_t
	{
		AXIS_X,
		AXIS_Y,
		AXIS_Z,
	} AXIS;

	typedef struct FCdStruct
	{
		float x;
		float y;
		float z;
	} FCd;

	typedef struct VCdStruct
	{
		uint8_t x;
		uint8_t y;
		uint8_t z;
	} VCd;

	//#define type_voxel(x, y, z) (VCd){x, y, z}
	//typedef VCd			type_voxel;
	typedef CVoxel<uint8_t>	type_voxel;
	typedef FCd				type_float_cd;
	typedef uint8_t			type_axis;
	typedef uint8_t			type_state;
	typedef uint8_t			type_polarity;
	typedef uint8_t			type_cube[8][8];

	type_cube cube;

	public:
	// Defualt constructor
	CCube(void);

	// Transition Functions
	void TransitionShift(const type_axis axis, const type_polarity polarity, const uint8_t delay);
	void TransitionScroll(const type_axis axis, const type_polarity polarity, const uint8_t delay);
	void TransitionPlane(const type_axis axis, const type_polarity polarity, const uint8_t state, const uint8_t delay);

	// Translate Functions
	void TranslateScroll(const type_axis axis, int8_t value);
	void TranslateShift(const type_axis axis, const int8_t value);

	// Draw Functions
	void SetVoxel(const type_voxel &voxel, const type_state state);
	void SetLine(type_voxel v0, type_voxel v1, const type_state state);
	void SetPlane(const type_axis axis, const uint8_t index, const type_state state);
	//void set_character(const type_axis axis, const uint8_t index, const char character);
	void SetCube(const uint8_t pattern);
	void SetWireframeBox(const type_voxel &v0, const type_voxel &v1, const type_state state);
	void SetSphere(const type_float_cd &fcd, float radius, const type_state state);
	void SetCuboid(type_voxel v0, type_voxel v1, const type_state state);
	void SetWireframe(const type_voxel &v0, const type_voxel &v1, const type_state state);

	// Utility Functions
	uint8_t GetVoxel(const type_voxel &voxel);
	void Copy(CCube& buffer);

	private:
	void DelayMS(uint16_t x);
	uint8_t CoordinateInRange(const type_voxel &voxel);
	void CoordinateOrder(type_voxel &v0, type_voxel &v1);
};

#endif
