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
 * @file        cube.cpp
 * @summary     8x8x8 Mono-color LED Cube
 * @version     1.3
 * @author      nitacku
 * @data        31 March 2014
 */

#include "ccube.h"

// Default Constructor
CCube::CCube() { }

// ===============================================================
//  Transition Functions
// ===============================================================


void CCube::TransitionShift(const CCube::Axis axis, const CCube::Polarity polarity, const uint8_t delay)
{
    for (uint8_t x = 0; x < 8; x++)
    {
        TranslateShift(axis, ((polarity == CCube::Polarity::POSITIVE) << 1) - 1);
        DelayMS(delay);
    }
}


void CCube::TransitionScroll(const CCube::Axis axis, const CCube::Polarity polarity, const uint8_t delay)
{
    for (uint8_t x = 0; x < 7; x++)
    {
        TranslateScroll(axis, ((polarity == CCube::Polarity::POSITIVE) << 1) - 1);
        DelayMS(delay);
    }
}


void CCube::TransitionPlane(const CCube::Axis axis, const CCube::Polarity polarity, const CCube::State state, const uint8_t delay)
{
    for (uint8_t x = 0; x < 8; x++)
    {
        uint8_t value = x + (((polarity == CCube::Polarity::POSITIVE) - 1) & (7 - x - x));

        SetPlane(axis, value, state);
        DelayMS(delay);
        SetPlane(axis, value, CCube::State::OFF);
    }
}


// ===============================================================
//  Translate Functions
// ===============================================================


// Scroll the outer sides of the cube around an axis by value
void CCube::TranslateScroll(const CCube::Axis axis, int8_t value)
{
    uint8_t dx, dy, dz;

    int8_t increment_x[4];
    int8_t increment_y[4];
    int8_t increment_z[4];

    uint8_t positive = (value > 0);
    uint8_t negative = (value < 0);

    switch (axis)
    {
    default:
    case CCube::Axis::X:
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

    case CCube::Axis::Y:
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

    case CCube::Axis::Z:
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

    for (uint8_t l = 0; l<value; l++)
    {
        uint8_t x = 0;
        uint8_t y = 0;
        uint8_t z = 0;

        for (uint8_t i = 0; i < 8; i++)
        {
            uint8_t prev_x;
            uint8_t prev_y;
            uint8_t prev_z;
            
            CCube::State start_state = GetVoxel(type_voxel(x, y, z));

            for (uint8_t j = 0; j < 4; j++)
            {
                for (uint8_t k = 0; k < 7; k++)
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
void CCube::TranslateShift(const CCube::Axis axis, const int8_t value)
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
    case CCube::Axis::X:
        for (z = 0; z < 8; z++)
        {
            for (y = 0; y < 8; y++)
            {
                cube[z][y] = (cube[z][y] >> 1) + (((value < 0) - 1) & ((cube[z][y] << 1) - (cube[z][y] >> 1)));
                //cube[z][y] = (value < 0) ? (cube[z][y] >> 1) : (cube[z][y] << 1);
            }
        }

        return TranslateShift(axis, value + n);

    case CCube::Axis::Y:
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

    case CCube::Axis::Z:
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

    SetPlane(axis, ((value > 0) - 1) & 0x7, CCube::State::OFF);
    return TranslateShift(axis, value + n); 
}


// ===============================================================
//  Draw Functions
// ===============================================================


void CCube::SetVoxel(const type_voxel &voxel, const CCube::State state)
{
    if (CoordinateInRange(voxel))
    {
        switch (state)
        {
        case CCube::State::OFF:
            cube[voxel.z][voxel.y] &= ~(1 << voxel.x);
            break;

        case CCube::State::ON:
            cube[voxel.z][voxel.y] |= (1 << voxel.x);
            break;

        case CCube::State::INV:
            cube[voxel.z][voxel.y] ^= (1 << voxel.x);
            break;
        }
    }
}


void CCube::SetLine(type_voxel v0, type_voxel v1, const CCube::State state)
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
void CCube::set_character(const CCube::Axis axis, const uint8_t index, const char character)
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

void CCube::SetPlane(const CCube::Axis axis, const uint8_t index, const CCube::State state)
{
    if (index < 8)
    {
        for (uint8_t i = 0; i < 8; i++)
        {
            switch (axis)
            {
            case CCube::Axis::X:
                for (uint8_t y = 0; y < 8; y++)
                {
                    switch (state)
                    {
                    case CCube::State::OFF:
                        cube[i][y] &= ~(1 << index);
                        break;

                    case CCube::State::ON:
                        cube[i][y] |= (1 << index);
                        break;

                    case CCube::State::INV:
                        cube[i][y] ^= (1 << index);
                        break;
                    }
                }

                break;

            case CCube::Axis::Y:
                switch (state)
                {
                case CCube::State::OFF:
                    cube[i][index] = 0x00;
                    break;

                case CCube::State::ON:
                    cube[i][index] = 0xFF;
                    break;

                case CCube::State::INV:
                    cube[i][index] ^= 0xFF;
                    break;
                }

                break;

            case CCube::Axis::Z:
                switch (state)
                {
                case CCube::State::OFF:
                    cube[index][i] = 0x00;
                    break;

                case CCube::State::ON:
                    cube[index][i] = 0xFF;
                    break;

                case CCube::State::INV:
                    cube[index][i] ^= 0xFF;
                    break;
                }

                break;
            }
        }
    }
}

/*
void CCube::SetCircle(const type_float_cd &fcd, float radius, const CCube::State state)
{
    
}
*/


void CCube::SetSphere(const type_float_cd &fcd, float radius, const CCube::State state)
{
    float radius2 = radius * radius;

    for (float k = 0; k < 8; k += 0.5)
    {
        float z0;
        z0 = (k - fcd.z);
        z0 *= z0;

        for (float j = 0; j < 8; j += 0.5)
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
                x0 = operand;                   // x can be viewed as int.
                ix = 0x1fbb67a8 + (ix >> 1);    // Initial guess.
                x0 = 0.5f*(x0 + operand/x0);    // Newton step.
                */

                SetVoxel(type_voxel(x0 + fcd.x, j, k), state);
                SetVoxel(type_voxel(fcd.x - x0, j, k), state);
            }
        }
    }
}


void CCube::SetCube(const uint8_t pattern)
{
    for (uint8_t z = 0; z < 8; z++)
    {
        for (uint8_t y = 0; y < 8; y++)
        {
            cube[z][y] = pattern;
        }
    }
}


void CCube::SetCuboid(type_voxel v0, type_voxel v1, const CCube::State state)
{
    CoordinateOrder(v0, v1);

    for (uint8_t x = v0.x; x < v1.x + 1; x++)
    {
        for (uint8_t y = v0.y; y < v1.y + 1; y++)
        {
            for (uint8_t z = v0.z; z < v1.z + 1; z++)
            {
                SetVoxel(type_voxel(x, y, z), state);
            }
        }
    }
}


void CCube::SetWireframe(const type_voxel &v0, const type_voxel &v1, const CCube::State state)
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
CCube::State CCube::GetVoxel(const type_voxel &voxel)
{
    if (CoordinateInRange(voxel))
    {
        if (cube[voxel.z][voxel.y] & (1 << voxel.x))
        {
            return CCube::State::ON;
        }
    }

    return CCube::State::OFF;
}


void CCube::Copy(CCube& buffer)
{
    memcpy_fast(buffer.cube, cube, 64);
}


void CCube::DelayMS(uint16_t x)
{
    for (; x > 0; x--)
    {
        for (uint16_t z = 0; z < DELAY_CONSTANT_C; z++)
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


// Makes sure v0 is always smaller than v1
void CCube::CoordinateOrder(type_voxel &v0, type_voxel &v1)
{
    max(v0.x, v1.x); // v1.x = t0.x ^ ((t0.x ^ t1.x) & -(t0.x < t1.x));
    min(v0.x, v1.x); // v0.x = t1.x ^ ((t0.x ^ t1.x) & -(t0.x < t1.x));

    max(v0.y, v1.y); // v1.y = t0.y ^ ((t0.y ^ t1.y) & -(t0.y < t1.y));
    min(v0.y, v1.y); // v0.y = t1.y ^ ((t0.y ^ t1.y) & -(t0.y < t1.y));

    max(v0.z, v1.z); // v1.z = t0.z ^ ((t0.z ^ t1.z) & -(t0.z < t1.z));
    min(v0.z, v1.z); // v0.z = t1.z ^ ((t0.z ^ t1.z) & -(t0.z < t1.z));
}


void* memcpy_fast(void* dst, const void* src, uint16_t num)
{
    asm volatile(
         "  movw r30, %[src]        \n\t"
         "  movw r26, %[dst]        \n\t"
         "  sbrs %A[num], 0         \n\t"
         "  rjmp Lcpyeven_%=        \n\t"
         "  rjmp Lcpyodd_%=         \n\t"
         "Lcpyloop_%=:              \n\t"
         "  ld __tmp_reg__, Z+      \n\t"
         "  st X+, __tmp_reg__      \n\t"
         "Lcpyodd_%=:               \n\t"
         "  ld __tmp_reg__, Z+      \n\t"
         "  st X+, __tmp_reg__      \n\t"
         "Lcpyeven_%=:              \n\t"
         "  subi %A[num], 2         \n\t"
         "  brcc Lcpyloop_%=        \n\t"
         "  sbci %B[num], 0         \n\t"
         "  brcc Lcpyloop_%=        \n\t"
         : [num] "+r" (num)
         : [src] "r" (src),
           [dst] "r" (dst)
         : "memory"
         );
    return dst;
}
