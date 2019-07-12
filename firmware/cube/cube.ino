/*
 * Copyright (c) 2017 nitacku
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
 * @file        cube.ino
 * @summary     8x8x8 Mono-color LED Cube
 * @version     1.5
 * @author      nitacku
 * @data        19 February 2017
 */

#include <TimerOne.h>
#include <EEPROM.h>
#include "bitmap.h"
#include "ccube.h"
#include "voxel.h"

const uint16_t DELAY_CONSTANT = DELAY_CONSTANT_C;

// redefine typedef to reduce noise
typedef CCube::type_voxel type_voxel;

const uint8_t PWM_8[9] = {0x00, 0x01, 0x11, 0x49, 0x55, 0xAD, 0x77, 0xF7, 0xFF};
const uint16_t PWM_12[13] = {0x000, 0x001, 0x041, 0x111, 0x249, 0x4A5, 0x555, 0xB5A, 0xDB6, 0xEEE, 0xFBE, 0xFFE, 0xFFF};
const uint16_t TIMER = 2500; // set timer period to 2500 microseconds == 50Hz per layer

enum portb_pins_t : uint8_t
{
    PORTB_RCLK    = 0,
    PORTB_SRCLK   = 1,
    PORTB_OE      = 2,
    PORTB_SRCLR   = 3,
    PORTB_LAYER_6 = 4,
    PORTB_LAYER_7 = 5,
};

enum portc_pins_t : uint8_t
{
    PORTC_LAYER_0 = 0,
    PORTC_LAYER_1 = 1,
    PORTC_LAYER_2 = 2,
    PORTC_LAYER_3 = 3,
    PORTC_LAYER_4 = 4,
    PORTC_LAYER_5 = 5,
};

enum portd_pins_t : uint8_t
{
    PORTD_SERIAL_0 = 0,
    PORTD_SERIAL_1 = 1,
    PORTD_SERIAL_2 = 2,
    PORTD_SERIAL_3 = 3,
    PORTD_SERIAL_4 = 4,
    PORTD_SERIAL_5 = 5,
    PORTD_SERIAL_6 = 6,
    PORTD_SERIAL_7 = 7,
};

// Return integral value of Enumeration
template<typename T> constexpr auto getValue(const T e)
{
    //return static_cast<std::underlying_type<e>::type>(e);
    return static_cast<uint8_t>(e);
}

// Effect Functions
void EffectLightningBug(CCube& cube);
void EffectPulse(CCube& cube);
void EffectEdgeTraverse(CCube& cube);
void EffectFireworks(CCube& cube);
void EffectInvertedSphere(CCube& cube);
void EffectCharacterRotate(CCube& cube, const unsigned char string[]);
void EffectCubeRotate(CCube& cube);
void EfectSphereGhost(CCube& cube);
void EffectWedgeRotate(CCube& cube);
void EffectPlaneSeparation(CCube& cube);
void EffectMarquee(CCube& cube, const unsigned char string[], const uint8_t delay);
void EffectMagneticAttraction(CCube& cube, const CCube::Axis axis);
void EffectCubePulse(CCube& cube);
void EffectCubeCorners(CCube& cube);
void EffectWireframeBoxRotate(CCube& cube);
void EffectWireframeWedgeRotate(CCube& cube);
void EffectPlaneTwist(CCube& cube);
void EffectPlaneTraverse(CCube& cube);
void EffectScrambleSolve(CCube& cube);
void EffectRandomFiller(CCube& cube);
void EffectScrollingSine(CCube& cube);
void EffectTornado(CCube& cube);
void EffectChasingCubes(CCube& buffer, CCube& buffer_1);
void EffectPlotFunction(CCube& cube, uint8_t (*function_ptr)(const int8_t, const int8_t, float), const uint8_t iterations, const float step_size);

// Plot Functions
uint8_t FunctionWaves(const int8_t x, const int8_t y, const float step);
uint8_t FunctionBesinc(const int8_t x, const int8_t y, const float step);

// Utility Functions
void DelayMS(uint16_t x);
uint8_t CoordinateInRange(const type_voxel &voxel);
void CoordinateOrder(type_voxel &v0, type_voxel &v1);

// Register Functions
void UpdateDisplay(CCube& buffer);
void UpdateDisplay(const CCube& buffer0, const CCube& buffer1);

// Global Variables
CCube* g_cube;
float transfer_x = 0.0;
float transfer_y = 0.0;

void loop(void)
{
    unsigned char message_marquee[] = "\x80\x81\x82\x83\x84\x85\x86 presents: LED cube  Enjoy!   ";
    //unsigned char message_marquee[] = "\x8E\x8F\x90\x91\x92  "; // Intel
    unsigned char message_rotate[] = "\x87\x88\x89\x8A\x8B\x8C\x8D"; // LEDCUBE

    // Instantiate cube objects
    CCube cube; // linked to global
    CCube buffer;
    CCube buffer_1;

    g_cube = &cube; // Assign the global cube pointer

    while (true)
    {                                                                                       //Size (bytes)
        EffectMarquee(buffer, message_marquee, 225);                                        //! 442 + 1708
        EffectCharacterRotate(buffer, message_rotate);                                      //! 756
        EffectPlotFunction(buffer, FunctionBesinc, 12, 0.125);                              // 542 + 176
        cube.TransitionShift(CCube::Axis::Z, CCube::Polarity::NEGATIVE, 100);               // 18
        EffectPlotFunction(buffer, FunctionWaves, 25, 0.125);                               // 302
        cube.TransitionShift(CCube::Axis::Z, CCube::Polarity::POSITIVE, 100);               // 18
        EffectScrollingSine(cube);                                                          // 362
        EffectTornado(cube);                                                                // 390
        cube.TransitionShift(CCube::Axis::Z, CCube::Polarity::POSITIVE, 100);               // 18
        EffectPlaneTwist(buffer);                                                           // 618
        EffectScrambleSolve(cube);                                                          // 454
        EffectPlaneTraverse(buffer);                                                        // 284
        EffectMagneticAttraction(buffer, CCube::Axis::X);                                   // 440
        cube.TransitionScroll(CCube::Axis::Y, CCube::Polarity::POSITIVE, 100);              // 132
        EffectMagneticAttraction(buffer, CCube::Axis::Z);                                   // 14
        cube.TransitionScroll(CCube::Axis::X, CCube::Polarity::NEGATIVE, 100);              // 18
        EffectMagneticAttraction(buffer, CCube::Axis::Y);                                   // 14
        cube.TransitionScroll(CCube::Axis::Z, CCube::Polarity::NEGATIVE, 100);              // 18
        EffectPlaneSeparation(buffer);                                                      //! 1042
        cube.TransitionShift(CCube::Axis::Y, CCube::Polarity::POSITIVE, 100);               // 18
        EffectWedgeRotate(buffer);                                                          // 658
        cube.TransitionShift(CCube::Axis::Z, CCube::Polarity::NEGATIVE, 100);               // 18
        EffectCubePulse(buffer);                                                            // 304
        EffectCubeCorners(buffer);                                                          // 460
        cube.TransitionShift(CCube::Axis::Z, CCube::Polarity::NEGATIVE, 100);               // 18
        EffectEdgeTraverse(cube);                                                           //! 762
        //EffectCubeRotate(buffer);                                                         //! 1720
        EffectChasingCubes(buffer, buffer_1);                                               // 588
        cube.TransitionShift(CCube::Axis::Y, CCube::Polarity::NEGATIVE, 100);               // 18
        EffectPulse(cube);                                                                  // 370
        EffectRandomFiller(cube);                                                           // 306
        EffectInvertedSphere(cube);                                                         // 274
        EfectSphereGhost(buffer);                                                           //! 752
        EffectFireworks(buffer);                                                            //! 1640
    }
}

// ===============================================================
//  Effect Functions
// ===============================================================

void EffectLightningBug(CCube& cube)
{
    const uint8_t population = 5;
    uint8_t state[population];
    type_voxel voxel[population];

    Timer1.initialize(50);
    cube.SetCube(0x00);

    for (uint8_t i = 0; i < population; i++)
    {
        voxel[i] = type_voxel(rand() % 8, rand() % 8, rand() % 8);
        state[i] = i+1;//(1 + (rand() % 7));
    }

    for (uint16_t k = 0; k < 5000; k++)
    {
        for (uint8_t j = 0; j < 8; j++)
        {
            for (uint8_t i = 0; i < population; i++)
            {
                cube.SetVoxel(voxel[i], static_cast<CCube::State>((PWM_8[state[i]] >> j) & 0x01));
            }
        }
    }

    Timer1.initialize(TIMER);
}


void EffectPulse(CCube& cube)
{
    const uint8_t WBIT = 12; // Set to 8 for 8-bit PWM
    const uint16_t* PWM = PWM_12;
    
    uint8_t index;

    Timer1.initialize(50);

    for (uint8_t i = 0; i < 8; i++)
    {
        index = (i % 2) ? WBIT : 0;

        while (index < (WBIT + 1))
        {
            for (uint8_t k = 0; k < 255; k++)
            {
                for (uint8_t j = 0; j < WBIT; j++)
                {
                    if ((PWM[index] >> j) & 0x001)
                    {
                        cube.SetCube(0xFF);
                    }
                    else
                    {
                        cube.SetCube(0x00);
                    }
                }
            }

            index += (i % 2) ? -1 : 1;
        }
    }

    Timer1.initialize(TIMER);
}


void EffectEdgeTraverse(CCube& cube)
{
    uint8_t x0, y0, z0;

    for (uint8_t i = 0; i < 7; i++)
    {
        x0 = !!(i & 0x1) * 7;
        y0 = !!(i & 0x2) * 7;
        z0 = !!(i & 0x4) * 7;

        for (uint8_t z = 0; z < 2; z++)
        {
            CCube::State state;
            state = !z ? CCube::State::ON : CCube::State::OFF;

            for (uint8_t y = 0; y < 3; y++)
            {
                for (uint8_t x = 0; x < (7 + (y > 1)); x++)
                {
                    uint8_t dx, dy, dz;

                    dx = x0 ? 7-x : x;
                    dy = y0 ? 7-x : x;
                    dz = z0 ? 7-x : x;

                    switch (y)
                    {
                        case 0:
                        cube.SetVoxel(type_voxel(dx, y0, z0), state);
                        cube.SetVoxel(type_voxel(x0, dy, z0), state);
                        cube.SetVoxel(type_voxel(x0, y0, dz), state);
                        break;

                        case 1:
                        cube.SetVoxel(type_voxel(dx, y0, 7-z0), state);
                        cube.SetVoxel(type_voxel(x0, dy, 7-z0), state);
                        cube.SetVoxel(type_voxel(7-x0, y0, dz), state);
                        cube.SetVoxel(type_voxel(7-x0, dy, z0), state);
                        cube.SetVoxel(type_voxel(x0, 7-y0, dz), state);
                        cube.SetVoxel(type_voxel(dx, 7-y0, z0), state);
                        break;

                        case 2:
                        cube.SetVoxel(type_voxel(dx, 7-y0, 7-z0), state);
                        cube.SetVoxel(type_voxel(7-x0, dy, 7-z0), state);
                        cube.SetVoxel(type_voxel(7-x0, 7-y0, dz), state);
                        break;
                    }

                    DelayMS(150);
                }
            }
        }
    }
}


void EffectFireworks(CCube& cube)
{
    uint8_t x, y, z;
    const float force = 0.1;

    for (uint8_t i = 0; i < 8; i++)
    {
        x = rand()%4 + 2;
        y = rand()%4 + 2;
        z = 8-rand()%4;

        CCube::type_float_cd voxel[40];

        for (uint8_t j = 0; j < 40; j++)
        {
            float theta, phi, z0;

            z0 = 2*force*((float)rand()/(float)RAND_MAX)-force;
            theta = asin(z0/force);
            phi = 2*PI*((float)rand()/(float)RAND_MAX);

            voxel[j].x = force*cos(theta)*cos(phi);
            voxel[j].y = force*cos(theta)*sin(phi);
            voxel[j].z = z0 + 0.5*force;
        }

        cube.SetVoxel(type_voxel(x, y, 0), CCube::State::ON);

        for (uint8_t j = 0; j < z; j++)
        {
            UpdateDisplay(cube);
            DelayMS(100+(10*j*j));
            cube.TranslateShift(CCube::Axis::Z, 1);
        }

        DelayMS(100);

        for (uint8_t j = 8; j < 64; j++)
        {
            cube.SetCube(0x00);

            for (uint8_t k = 0; k < 40; k++)
            {
                cube.SetVoxel(type_voxel(x + j*voxel[k].x, y + j*voxel[k].y, z + j*voxel[k].z - j*j*0.005), CCube::State::ON);
            }

            UpdateDisplay(cube);
            DelayMS(60);
        }
    }
}


void EffectInvertedSphere(CCube& cube)
{
    float r;

    CCube::type_float_cd voxel = (CCube::type_float_cd){3.725, 3.725, 3.725};

    for (uint8_t x = 0; x < 3; x++)
    {
        r = 0.55;

        for (uint8_t z = 0; z < 1; z++)
        {
            for (uint8_t y = 0; y < 28; y++)
            {
                if (z > 0)
                {
                    r -= 0.275;

                    if (y < 14)
                    {
                        cube.SetSphere(voxel, r - 2.2, CCube::State::ON);
                    }

                    cube.SetSphere(voxel, r, CCube::State::OFF);
                }
                else
                {
                    r += 0.275;
                    cube.SetSphere(voxel, r, CCube::State::ON);

                    if (y > 4)
                    {
                        cube.SetSphere(voxel, r - 2.2, CCube::State::OFF);
                    }
                }
            }

            DelayMS(500);
        }
    }
}


void EffectCharacterRotate(CCube& cube, const unsigned char string[])
{
    uint8_t* bitmap;
    type_voxel voxel[128];
    uint8_t index, count;
    float angle;

    index = 0;

    while (string[index] != 0)
    {
        bitmap = get_bitmap(string[index]);
        count = 0;

        for (uint8_t x = 0; x < 8; x++)
        {
            for (uint8_t z = 0; z < 8; z++)
            {
                if ((*(bitmap + z) >> x) & 0x01)
                {
                    voxel[count].x = x-4;
                    voxel[count].y = 1;
                    voxel[count].z = 3-z;
                    count++;

                    voxel[count].x = x-4;
                    voxel[count].y = 0;
                    voxel[count].z = 3-z;
                    count++;
                }
            }
        }

        angle = 0;

        for (uint8_t z = 0; z < 60; z++)
        {
            cube.SetCube(0x0);

            for (uint8_t x = 0; x < count; x++)
            {
                cube.SetVoxel(voxel[x].Rotate(0, 0, angle) + 3.5, CCube::State::ON);
            }

            angle += PI/10;
            UpdateDisplay(cube);
            DelayMS(128 - count);
        }

        index++;
    }
}


void EffectCubeRotate(CCube& cube)
{
    float angle_x, angle_y, angle_z;

    type_voxel vertex_template[8] =
    {
        type_voxel(-3, 3, -4),
        type_voxel(3, 3, -4),
        type_voxel(3, -3, -4),
        type_voxel(-3, -3, -4),
        type_voxel(-3, 3, 2),
        type_voxel(3, 3, 2),
        type_voxel(3, -3, 2),
        type_voxel(-3, -3, 2)
    };

    angle_x = 0;
    angle_y = 0;
    angle_z = 0;

    for (uint32_t j = 0; j < 500; j++)
    {
        type_voxel voxel[8];

        for (uint8_t i = 0; i < 8; i++)
        {
            voxel[i] = vertex_template[i].Rotate(sin(angle_x), sin(angle_y), sin(angle_z));
        }

        for (uint8_t i = 0; i < 4; i++)
        {
            cube.SetLine(voxel[i] + 3, voxel[i+1-((i==3) << 2)] + 3, CCube::State::ON);
            cube.SetLine(voxel[i+4] + 3, voxel[i+5-((i==3) << 2)] + 3, CCube::State::ON);
            cube.SetLine(voxel[i] + 3, voxel[i+4] + 3, CCube::State::ON);
        }

        const float increment = PI/25.0;

        switch (j / 100)
        {
            default:
            case 0:
            angle_z += increment;
            break;

            case 1:
            angle_x += increment;
            break;

            case 2:
            angle_y += increment;
            break;

            case 3:
            angle_x += increment;
            angle_y += increment;
            break;

            case 4:
            angle_x += increment;
            angle_y += increment;
            angle_z += increment;
            break;
        }

        UpdateDisplay(cube);
        DelayMS(75);
        cube.SetCube(0x0);
    }
}


void EfectSphereGhost(CCube& cube)
{
    float step_r, step_x, step_y, step_z, pos_r, pos_x, pos_y, pos_z;

    pos_r = 0;
    pos_x = 3;
    pos_y = 3;
    pos_z = 3;

    step_x = PI/23;
    step_y = PI/19;
    step_z = PI/17;
    step_r = PI/23;

    for (uint8_t i = 255; i > 0; i--)
    {
        pos_r += step_r;
        pos_r -= PI * (pos_r > PI);
        pos_x += step_x;
        pos_y += step_y;
        pos_z += step_z;

        cube.SetCube(0x00);
        cube.SetSphere((CCube::type_float_cd) {0.5*(22-i)*(i<22) + 3.5 + 3*sin(pos_x), 3.5 + 3*sin(pos_y), 3.5 + 3*sin(pos_z)}, 1.5 + 3*sin(pos_r), CCube::State::ON);

        UpdateDisplay(cube);
        DelayMS(100);
    }
}


void EffectPlaneSeparation(CCube& cube)
{
    uint8_t end[8][8];
    uint8_t start[8][8];

    for (uint8_t side = 0; side < 6; side++)
    {
        for (uint8_t i = 0; i < 8; i++)
        {
            uint8_t array[8] = {0, 1, 2, 3, 4, 5, 6, 7};

            for (uint8_t j = 7; j > 0; j--)
            {
                uint8_t index = rand() % (j+1);
                uint8_t temp = array[j];
                array[j] = array[index];
                array[index] = temp;
            }

            for (uint8_t j = 0; j < 8; j++)
            {
                end[i][j] = array[j];
                start[array[j]][i] = j;
            }
        }

        for (uint8_t l = 0; l < 2; l++)
        {
            for (uint8_t i = 0; i < 8; i++)
            {
                cube.SetCube(0x00);

                for (uint8_t j = 0; j < 8; j++)
                {
                    for (uint8_t k = 0; k < 8; k++)
                    {
                        uint8_t x0, y0, z0, e;

                        if (l < 1)
                        {
                            if (side > 2)
                            {
                                e = (end[j][k]+7-i < 7) ? end[j][k]+7-i : 7;
                            }
                            else
                            {
                                e = (end[j][k]-7+i > 0) ? end[j][k]-7+i : 0;
                            }
                        }
                        else
                        {
                            if ((side > 1) && (side < 5))
                            {
                                e = (start[j][k]+i < 7) ? start[j][k]+i : 7;
                            }
                            else
                            {
                                e = (start[j][k]-i > 0) ? start[j][k]-i : 0;
                            }
                        }

                        switch ((side+l) % 3)
                        {
                            default:
                            case 0:
                                x0 = e;
                                y0 = j;
                                z0 = k;
                                break;

                            case 1:
                                x0 = j;
                                y0 = k;
                                z0 = e;
                                break;

                            case 2:
                                x0 = k;
                                y0 = e;
                                z0 = j;
                                break;
                        }

                        cube.SetVoxel(type_voxel(x0, y0, z0), CCube::State::ON);
                    }
                }

                UpdateDisplay(cube);
                DelayMS(100);
            }

            DelayMS(500);
        }
    }
}


void EffectMarquee(CCube& cube, const unsigned char string[], const uint8_t delay)
{
    uint8_t* bitmap;

    cube.SetCube(0x00);

    uint8_t i = 0;

    while (string[i] != 0)
    {
        bitmap = get_bitmap(string[i]);

        //for (x = 0; x < (8 + (string[i] > 127 )); x++)
        for (uint8_t x = 0; x < (8 - (string[i] > 141 )); x++)
        {
            for (uint8_t z = 0; z < 8 && x < 8; z++)
            {
                cube.SetVoxel(type_voxel(0, 7, 7-z), static_cast<CCube::State>((*(bitmap + z) >> (7-x)) & 0x01));
            }

            UpdateDisplay(cube);
            DelayMS(delay);
            cube.SetLine(type_voxel(7, 0, 0), type_voxel(7, 0, 7), CCube::State::OFF);
            cube.TranslateScroll(CCube::Axis::Z, -1);
        }

        i++;
    }
}


void EffectMagneticAttraction(CCube& cube, const CCube::Axis axis)
{
    uint8_t voxel[64];

    for (uint8_t k = 7; k > 0; k -= 7)
    {
        for (uint8_t i = 0; i < 64; i++)
        {
            voxel[i] = k;
        }

        uint8_t i;

        for (uint8_t j = 0; j < 72; j++)
        {
            if (j < 64)
            {
                while (voxel[i = rand() % 64] != k);

                voxel[i] += 1 - ((k > 0) << 1);
            }

            cube.SetCube(0x00);

            for (uint8_t i = 0; i < 64; i++)
            {
                uint8_t x0, y0, z0;

                switch (axis)
                {
                    default:
                    case CCube::Axis::X:
                    x0 = voxel[i];
                    y0 = i%8;
                    z0 = i/8;
                    break;

                    case CCube::Axis::Y:
                    x0 = i%8;
                    y0 = voxel[i];
                    z0 = i/8;
                    break;

                    case CCube::Axis::Z:
                    x0 = i%8;
                    y0 = i/8;
                    z0 = voxel[i];
                    break;
                }

                cube.SetVoxel(type_voxel(x0, y0, z0), CCube::State::ON);

                if (voxel[i] && (voxel[i] < 7))
                {
                    voxel[i] += 1 - ((k > 0) << 1);
                }
            }

            UpdateDisplay(cube);
            DelayMS(40);
        }
    }
}


void EffectCubePulse(CCube& cube)
{
    uint8_t pt = 0;

    for (uint8_t i = 0; i < 12; i++)
    {
        for (uint8_t j = 0; j < 3; j++)
        {
            cube.SetCube(0x00);
            cube.SetWireframe(type_voxel(pt, pt, pt), type_voxel(7-pt, 7-pt, 7-pt), CCube::State::ON);
            UpdateDisplay(cube);

            pt += ((i % 2) ? -1 : 1);

            DelayMS(100);
        }
    }
}


void EffectCubeCorners(CCube& cube)
{
    uint8_t x0, y0, z0, x1, y1, z1;
    int8_t dx, dy, dz;

    for (uint8_t i = 0; i < 8; i++)
    {
        x0 = !!(i & 0x1) * 7;
        y0 = !!(i & 0x2) * 7;
        z0 = !!(i & 0x4) * 7;

        dx = 1 - (!!(i & 0x1) << 1);
        dy = 1 - (!!(i & 0x2) << 1);
        dz = 1 - (!!(i & 0x4) << 1);

        x1 = 7-x0;
        y1 = 7-y0;
        z1 = 7-z0;

        for (uint8_t k = 0; k < 2; k++)
        {
            for (uint8_t j = 0; j < 6; j++)
            {
                x0 += dx;
                y0 += dy;
                z0 += dz;

                cube.SetCube(0x00);
                cube.SetWireframe(type_voxel(x0, y0, z0), type_voxel(x1, y1, z1), CCube::State::ON);
                UpdateDisplay(cube);
                DelayMS(100);
            }

            dx = -dx;
            dy = -dy;
            dz = -dz;
        }
    }
}


void EffectWedgeRotate(CCube& cube)
{
    uint8_t x0, y0, x1, y1;
    float delay, angle;
    type_voxel voxel[4];

    x0 = 0;
    y0 = 0;
    x1 = 0;
    y1 = 7;
    delay = 0;
    angle = 0;

    for (uint8_t k = 0; k < 14; k++)
    {
        for (uint8_t i = 0; i < 28; i++)
        {
            cube.SetCube(0x00);

            voxel[0] = type_voxel(x0, y0, 0);
            voxel[1] = type_voxel(7-x0, 7-y0, 0);
            voxel[2] = type_voxel(x1, y1, 7);
            voxel[3] = type_voxel(7-x1, 7-y1, 7);

            for (uint8_t j = 0; j < 4; j++)
            {
                for (uint8_t l = 1; l < 4; l++)
                {
                    if (l > j)
                    {
                        cube.SetLine(voxel[j], voxel[l], CCube::State::ON);
                    }
                }
            }

            UpdateDisplay(cube);

            angle += (PI / 56) + ((PI / 112) * sin(angle));
            delay = 36 + (50 * (1 + sin(angle)));
            DelayMS(delay);

            switch (i/7)
            {
                case 0:
                x0 += 1;
                y1 -= 1;
                break;

                case 1:
                y0 += 1;
                x1 += 1;
                break;

                case 2:
                x0 -= 1;
                y1 += 1;
                break;

                case 3:
                y0 -= 1;
                x1 -= 1;
                break;
            }
        }
    }
}


/*
void EffectPlaneTwist(CCube& cube)
{
    uint16_t angle, increment, twist;

    angle = 0;
    twist = 0;

    for (uint16_t i = 0; i < 1270; i++)
    {
        cube.SetCube(0x00);

        increment = 0;

        for (uint16_t j = 0; j < 8; j++)
        {
            float x = cos16(angle + increment)/6553;
            float y = sin16(angle + increment)/6553;

            if ((i-(8*j)) < (1270-(8*8)))
            {
                cube.SetLine(type_voxel(3 + x, 3 + y, j), type_voxel(3 - x, 3 - y, j), CCube::State::ON);
            }

            increment += twist;
        }

        twist = ((32768/10) * sin16(51*i))/32768;
        angle += 32768/30;
        UpdateDisplay(cube);
        DelayMS(35);
    }
}
*/

void EffectPlaneTwist(CCube& cube)
{
    float angle, increment, twist;

    angle = 0.0;
    twist = 0.0;

    for (uint16_t i = 0; i < 1270; i++)
    {
        cube.SetCube(0x00);

        increment = 0.0;

        for (uint16_t j = 0; j < 8; j++)
        {
            float x = 4.75*cos(angle + increment);
            float y = 4.75*sin(angle + increment);

            if ((i-(8*j)) < (1270-(8*8)))
            {
                cube.SetLine(type_voxel(4.0 + x, 4.0 + y, j), type_voxel(4.0 - x, 4.0 - y, j), CCube::State::ON);
            }

            increment += twist;
        }

        twist = (PI/10.0) * sin(i/200.0);
        angle += PI/30.0;
        UpdateDisplay(cube);
        DelayMS(35);
    }
}


void EffectPlaneTraverse(CCube& cube)
{
    for (uint8_t k = 0; k < 8; k++)
    {
        for (uint8_t i = 0; i < 3; i++)
        {
            for (uint8_t j = 0; j < 8; j++)
            {
                uint8_t TranslateShift, stationary;
                uint8_t shift0, shift1, shift2;

                if (k % 2)
                {
                    TranslateShift = j;
                    stationary = 7;
                }
                else
                {
                    TranslateShift = 7-j;
                    stationary = 0;
                }

                cube.SetCube(0x00);

                switch (static_cast<CCube::Axis>(i))
                {
                    default:
                    case CCube::Axis::X:
                    shift0 = TranslateShift;
                    shift1 = 7-stationary;
                    shift2 = 7-stationary;
                    break;

                    case CCube::Axis::Y:
                    shift0 = stationary;
                    shift1 = TranslateShift;
                    shift2 = 7-stationary;
                    break;

                    case CCube::Axis::Z:
                    shift0 = stationary;
                    shift1 = stationary;
                    shift2 = TranslateShift;
                    break;
                }

                cube.SetPlane(CCube::Axis::X, shift0, CCube::State::ON);
                cube.SetPlane(CCube::Axis::Y, shift1, CCube::State::ON);
                cube.SetPlane(CCube::Axis::Z, shift2, CCube::State::ON);

                UpdateDisplay(cube);
                DelayMS(50);
            }
        }
    }
}


void EffectScrambleSolve(CCube& cube)
{
    const uint8_t length = 50;
    uint8_t history[length];
    CCube::Axis prev_axis;
    uint8_t direction = 0;
    CCube::Axis axis = CCube::Axis::X;

    cube.SetCube(0x00);
    cube.SetPlane(CCube::Axis::X, 7, CCube::State::ON);
    cube.SetPlane(CCube::Axis::Y, 7, CCube::State::ON);

    for (uint8_t i = 0; i < length; i++)
    {
        prev_axis = axis;
        axis = static_cast<CCube::Axis>(rand() % 3);

        if (axis != prev_axis)
        {
            direction = rand() % 2;
        }

        history[i] = getValue(axis) | (direction << 2);
    }

    DelayMS(1250);

    for (uint8_t k = 0; k < 2; k++)
    {
        for (uint8_t i = 0; i < length; i++)
        {
            for (uint8_t j = 0; j < 5; j++)
            {
                if (k)
                {
                    cube.TranslateScroll(static_cast<CCube::Axis>(history[length-1-i] & 0x3), ((history[length-1-i] & 0x4) >> 1) - 1);
                }
                else
                {
                    cube.TranslateScroll(static_cast<CCube::Axis>(history[i] & 0x3), 1 - ((history[i] & 0x4) >> 1));
                }

                DelayMS(70);
            }
        }

        DelayMS(1250);
    }
}


// Set and clear exactly 512 voxels in a random order.
void EffectRandomFiller(CCube& cube)
{
    uint8_t lfsr[2];

    cube.SetCube(0x00);

    for (uint8_t i = 0; i < 2; i++)
    {
        lfsr[0] = rand() % 256;
        lfsr[1] = rand() % 256;

        for (uint8_t j = 0; j < 255; j++)
        {
            for (uint8_t k = 0; k < 2; k++)
            {
                // linear feedback shift register; taps == 8 6 5 4; period == 255
                lfsr[k] = (lfsr[k] >> 1) ^ (-(lfsr[k] & 1) & 0xB8);
                cube.SetVoxel(type_voxel((lfsr[k] / 4) % 8, (k << 2) + lfsr[k] % 4, lfsr[k] / 32), CCube::State::INV);

                DelayMS(5);
            }
        }
    }
}


void EffectScrollingSine(CCube& cube)
{
    float step = 0;

    for (uint8_t k = 0; k < 6; k++)
    {
        for (uint8_t i = 0; i < 64; i++)
        {
            step += PI / 14;
            cube.SetVoxel(type_voxel(1, 0, 4 + 3.5 * sin(step)), CCube::State::ON);
            DelayMS(50);
            cube.TranslateScroll(CCube::Axis::Z, -1);
            cube.SetLine(type_voxel(1, 0, 0), type_voxel(1, 0, 7), CCube::State::OFF);
        }
    }
}


void EffectTornado(CCube& cube)
{
    uint8_t x = 4;
    uint8_t y = 4;

    for (uint8_t j = 0; j < 250; j++)
    {
        cube.SetVoxel(type_voxel(x, y, 0), CCube::State::ON);
        cube.SetVoxel(type_voxel(x-1, y, 0), CCube::State::ON);
        cube.SetVoxel(type_voxel(x, y-1, 0), CCube::State::ON);
        cube.SetVoxel(type_voxel(x-1, y-1, 0), CCube::State::ON);

        DelayMS(125);
        cube.TranslateShift(CCube::Axis::Z, 1);

        x += ((rand() % 2) << 1) - 1;
        y += ((rand() % 2) << 1) - 1;

        if (x < 1) { x++; }
        if (x > 7) { x--; }
        if (y < 1) { y++; }
        if (y > 7) { y--; }
    }

}


void EffectChasingCubes(CCube& buffer_0, CCube& buffer_1)
{
    buffer_0.SetCube(0xFF);
    buffer_1.SetCube(0xFF);

    for (int8_t k = -4; k < 5; k+=8)
    {
        for (uint8_t j = 0; j < 3; j++)
        {
            buffer_0.TranslateShift(static_cast<CCube::Axis>(j), k);
            buffer_1.TranslateShift(static_cast<CCube::Axis>(j), k);
        }
    }

    for (uint8_t j = 0; j < 3; j++)
    {
        buffer_1.TranslateShift(static_cast<CCube::Axis>(j), -4);
    }

    uint8_t delay = 114;

    for (uint8_t l = 0; l < 8; l++)
    {
        for (int8_t k = -1; k < 2; k+=2)
        {
            for (uint8_t j = 0; j < 3; j++)
            {
                for (uint8_t i = 0; i < 4; i++)
                {
                    buffer_0.TranslateShift(static_cast<CCube::Axis>(j), k);
                    buffer_1.TranslateShift(static_cast<CCube::Axis>(j), -k);

                    UpdateDisplay(buffer_0, buffer_1);

                    delay = (l < 4) ? delay - 1 : delay + 1;
                    DelayMS(delay);
                }
            }
        }
    }

    DelayMS(450);

    for (uint8_t l = 0; l < 8; l++)
    {
        for (int8_t k = 1; k > -2; k-=2)
        {
            for (int8_t j = 2; j > -1; j--)
            {
                for (uint8_t i = 0; i < 4; i++)
                {
                    buffer_0.TranslateShift(static_cast<CCube::Axis>(j), -k);
                    buffer_1.TranslateShift(static_cast<CCube::Axis>(j), k);

                    UpdateDisplay(buffer_0, buffer_1);

                    delay = (l < 4) ? delay - 1 : delay + 1;
                    DelayMS(delay);
                }
            }
        }
    }

    DelayMS(400);
}


void EffectPlotFunction(CCube& cube, uint8_t (*function_ptr)(const int8_t, const int8_t, const float), const uint8_t iterations, const float step_size)
{
    float offset = 0.0;

    for (float step = 0; step<iterations*2*PI; step+=step_size)
    {
        cube.SetCube(0x00);

        for (uint8_t x = 0; x < 8; x++)
        {
            for (uint8_t y = 0; y < 8; y++)
            {
                cube.SetVoxel(type_voxel(x, y, function_ptr(x-3.5, y-3.5, step)), CCube::State::ON);
            }
        }

        UpdateDisplay(cube);

        transfer_x = sin(offset);
        transfer_y = cos(offset);
        offset += 0.005;
    }
}


// ===============================================================
//  Plot Functions
// ===============================================================


uint8_t FunctionWaves(const int8_t x, const int8_t y, const float step)
{
    return 4 + 2 * (sin(step + transfer_x * x) + sin(step + transfer_y * y));
}


uint8_t FunctionBesinc(const int8_t x, const int8_t y, const float step)
{
    return 4 + 3.25 * (cos(step + sqrt(x*x + y*y)));
}

// ===============================================================
//  Utility Functions
// ===============================================================

void DelayMS(uint16_t x)
{
    uint16_t z;

    for (; x > 0; x--)
    {
        for (z = 0; z < DELAY_CONSTANT; z++)
        {
            asm volatile("nop");
        }
    }
}

// ===============================================================
//  Register Functions
// ===============================================================

void UpdateDisplay(CCube& buffer)
{
    buffer.Copy((*g_cube));
}


void UpdateDisplay(const CCube& buffer0, const CCube& buffer1)
{
    for (uint8_t y = 0; y < 8; y++)
    {
        for (uint8_t z = 0; z < 8; z++)
        {
            (*g_cube).cube[z][y] = buffer0.cube[z][y] | buffer1.cube[z][y];
        }
    }
}


//ISR(TIMER1_COMPA_vect)
void TimerISR(void)
{
    static uint8_t current_layer = 0;
    const uint8_t sequence[8] = {0, 5, 2, 7, 4, 1, 6, 3};
    uint8_t layer = sequence[current_layer++ & 7];

    // Expand loop for maximum speed
    PORTC = 0x00; // Turn all layer selects off
    PORTB &= ~((0x1 << PORTB_LAYER_6) | (0x1 << PORTB_LAYER_7));
    PORTB &= ~(0x1 << PORTB_RCLK); // Write Register clock LOW

    PORTB &= ~(0x1 << PORTB_SRCLK); // Write Serial Register clock LOW
    PORTD = (*g_cube).cube[layer][7];
    PORTB |= (0x1 << PORTB_SRCLK); // Write Serial Register clock HIGH

    PORTB &= ~(0x1 << PORTB_SRCLK); // Write Serial Register clock LOW
    PORTD = (*g_cube).cube[layer][6];
    PORTB |= (0x1 << PORTB_SRCLK); // Write Serial Register clock HIGH

    PORTB &= ~(0x1 << PORTB_SRCLK); // Write Serial Register clock LOW
    PORTD = (*g_cube).cube[layer][5];
    PORTB |= (0x1 << PORTB_SRCLK); // Write Serial Register clock HIGH

    PORTB &= ~(0x1 << PORTB_SRCLK); // Write Serial Register clock LOW
    PORTD = (*g_cube).cube[layer][4];
    PORTB |= (0x1 << PORTB_SRCLK); // Write Serial Register clock HIGH

    PORTB &= ~(0x1 << PORTB_SRCLK); // Write Serial Register clock LOW
    PORTD = (*g_cube).cube[layer][3];
    PORTB |= (0x1 << PORTB_SRCLK); // Write Serial Register clock HIGH

    PORTB &= ~(0x1 << PORTB_SRCLK); // Write Serial Register clock LOW
    PORTD = (*g_cube).cube[layer][2];
    PORTB |= (0x1 << PORTB_SRCLK); // Write Serial Register clock HIGH

    PORTB &= ~(0x1 << PORTB_SRCLK); // Write Serial Register clock LOW
    PORTD = (*g_cube).cube[layer][1];
    PORTB |= (0x1 << PORTB_SRCLK); // Write Serial Register clock HIGH

    PORTB &= ~(0x1 << PORTB_SRCLK); // Write Serial Register clock LOW
    PORTD = (*g_cube).cube[layer][0];
    PORTB |= (0x1 << PORTB_SRCLK); // Write Serial Register clock HIGH

    // Latch register before next layer enable
    PORTB |= (0x1 << PORTB_RCLK); // Write Register clock HIGH

    if (layer < 6)
    {
        PORTC = (0x01 << layer); // Write layer select HIGH
    }
    else if (layer == 6)
    {
        PORTB |= (0x01 << PORTB_LAYER_6); // Write Pin 12 High
    }
    else
    {
        PORTB |= (0x01 << PORTB_LAYER_7); // Write Pin 13 High
    }
}


void InitializeRandom(void)
{
    uint8_t data;
    uint32_t r = 0;

    for (uint8_t i = 0; i < 4; i++)
    {
        data = EEPROM.read(i);
        r = ((r << (8 * i)) | data);
    }

    srand(r); // seed rand
    r = rand(); // generate new random value

    for (uint8_t i = 0; i < 4; i++)
    {
        EEPROM.write(i, (r >> (8 * (3 - i))) & 0xFF);
    }
}


void setup(void)
{
    DDRD = 0xFF;    // digital pins
    DDRB = 0xFF;    // digital pins
    DDRC = 0xFF;    // analog pins

    PORTC = 0x00;
    PORTB = 0x00;

    PORTB |= (0x1 << PORTB_SRCLR); // Active-Low Serial Register Clear
    PORTB &= ~(0x1 << PORTB_OE); // Active-Low Output Enable

    Timer1.initialize(TIMER); // set timer period to 50Hz per layer
    Timer1.attachInterrupt( TimerISR ); // attach ISR

    pinMode(2, INPUT);
    Serial.begin(9600);
}
