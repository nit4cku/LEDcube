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
 * @file		bitmap.h
 * @summary		8x8x8 Mono-color LED Cube
 * @version		1.3
 * @author		nitacku
 * @data		31 March 2014
 */

#include <avr/pgmspace.h>

const static uint8_t __[8] PROGMEM =
{
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000
};

const static uint8_t _EXCLAIMATION[8] PROGMEM =
{
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00000000,
	0b00011000,
	0b00011000
};

const static uint8_t _QUOTE[8] PROGMEM =
{
	0b01100110,
	0b01100110,
	0b01100110,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000
};

const static uint8_t _POUND[8] PROGMEM =
{
	0b00100100,
	0b00100100,
	0b01111110,
	0b00100100,
	0b00100100,
	0b01111110,
	0b00100100,
	0b00100100
};

const static uint8_t _DOLLAR[8] PROGMEM =
{
	0b00011000,
	0b00111110,
	0b01011000,
	0b00111100,
	0b00011010,
	0b00011010,
	0b01111100,
	0b00011000
};

const static uint8_t _PERCENT[8] PROGMEM =
{
	0b00110010,
	0b01010010,
	0b01100100,
	0b00001000,
	0b00010000,
	0b00100110,
	0b01001010,
	0b01001100
};

const static uint8_t _AMPERSAND[8] PROGMEM =
{
	0b00100000,
	0b01010000,
	0b01010000,
	0b00100000,
	0b01010010,
	0b01001010,
	0b01000100,
	0b00111010
};

const static uint8_t _APOSTROPHE[8] PROGMEM =
{
	0b00011000,
	0b00011000,
	0b00110000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000
};

const static uint8_t _LPARENTHESIS[8] PROGMEM =
{
	0b00011000,
	0b00110000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b00110000,
	0b00011000
};

const static uint8_t _RPARENTHESIS[8] PROGMEM =
{
	0b00011000,
	0b00001100,
	0b00000110,
	0b00000110,
	0b00000110,
	0b00000110,
	0b00001100,
	0b00011000
};

const static uint8_t _STAR[8] PROGMEM =
{
	0b00000000,
	0b00010000,
	0b01010100,
	0b00111000,
	0b00111000,
	0b01010100,
	0b00010000,
	0b00000000
};

const static uint8_t _PLUS[8] PROGMEM =
{
	0b00000000,
	0b00011000,
	0b00011000,
	0b01111110,
	0b01111110,
	0b00011000,
	0b00011000,
	0b00000000
};

const static uint8_t _COMMA[8] PROGMEM =
{
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00011000,
	0b00011000,
	0b00110000
};

const static uint8_t _MINUS[8] PROGMEM =
{
	0b00000000,
	0b00000000,
	0b00000000,
	0b01111110,
	0b01111110,
	0b00000000,
	0b00000000,
	0b00000000
};

const static uint8_t _PERIOD[8] PROGMEM =
{
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00011000,
	0b00011000
};

const static uint8_t _FORWARDSLASH[8] PROGMEM =
{
	0b00000010,
	0b00000110,
	0b00001100,
	0b00011000,
	0b00110000,
	0b01100000,
	0b11000000,
	0b10000000
};

const static uint8_t _0[8] PROGMEM =
{
	0b01111110,
	0b01111110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01111110,
	0b01111110
};

const static uint8_t _1[8] PROGMEM =
{
	0b00011000,
	0b00111000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b01111110,
	0b01111110
};

const static uint8_t _2[8] PROGMEM =
{
	0b01111110,
	0b01111110,
	0b00000110,
	0b01111110,
	0b01111110,
	0b01100000,
	0b01111110,
	0b01111110
};

const static uint8_t _3[8] PROGMEM =
{
	0b01111110,
	0b01111110,
	0b00000110,
	0b01111110,
	0b01111110,
	0b00000110,
	0b01111110,
	0b01111110
};

const static uint8_t _4[8] PROGMEM =
{
	0b01100110,
	0b01100110,
	0b01100110,
	0b01111110,
	0b01111110,
	0b00000110,
	0b00000110,
	0b00000110
};

const static uint8_t _5[8] PROGMEM =
{
	0b01111110,
	0b01111110,
	0b01100000,
	0b01111110,
	0b01111110,
	0b00000110,
	0b01111110,
	0b01111110
};

const static uint8_t _6[8] PROGMEM =
{
	0b01111110,
	0b01111110,
	0b01100000,
	0b01111110,
	0b01111110,
	0b01100110,
	0b01111110,
	0b01111110
};

const static uint8_t _7[8] PROGMEM =
{
	0b01111110,
	0b01111110,
	0b00000110,
	0b00001100,
	0b00011000,
	0b00110000,
	0b01100000,
	0b01100000
};

const static uint8_t _8[8] PROGMEM =
{
	0b01111110,
	0b01111110,
	0b01100110,
	0b01111110,
	0b01111110,
	0b01100110,
	0b01111110,
	0b01111110
};

const static uint8_t _9[8] PROGMEM =
{
	0b01111110,
	0b01111110,
	0b01100110,
	0b01111110,
	0b01111110,
	0b00000110,
	0b01111110,
	0b01111110
};

const static uint8_t _COLON[8] PROGMEM =
{
	0b00000000,
	0b00000000,
	0b00011000,
	0b00011000,
	0b00000000,
	0b00011000,
	0b00011000,
	0b00000000
};

const static uint8_t _SEMICOLON[8] PROGMEM =
{
	0b00000000,
	0b00000000,
	0b00011000,
	0b00011000,
	0b00000000,
	0b00011000,
	0b00011000,
	0b00110000
};

const static uint8_t _LESS[8] PROGMEM =
{
	0b00000000,
	0b00110000,
	0b00011100,
	0b00000110,
	0b00000110,
	0b00011100,
	0b00110000,
	0b00000000
};

const static uint8_t _EQUAL[8] PROGMEM =
{
	0b00000000,
	0b01111110,
	0b01111110,
	0b00000000,
	0b00000000,
	0b01111110,
	0b01111110,
	0b00000000
};

const static uint8_t _GREATER[8] PROGMEM =
{
	0b00000000,
	0b00001100,
	0b00111000,
	0b01100000,
	0b01100000,
	0b00111000,
	0b00001100,
	0b00000000
};

const static uint8_t _QUESTION[8] PROGMEM =
{
	0b00111100,
	0b01111110,
	0b01100110,
	0b00001100,
	0b00011000,
	0b00000000,
	0b00011000,
	0b00011000
};

const static uint8_t _AT[8] PROGMEM =
{
	0b00111100,
	0b01000010,
	0b10011010,
	0b10101010,
	0b10101010,
	0b10011110,
	0b01000000,
	0b00111100
};

const static uint8_t _A[8] PROGMEM =
{
	0b00111100,
	0b01111110,
	0b01100110,
	0b01100110,
	0b01111110,
	0b01111110,
	0b01100110,
	0b01100110
};

const static uint8_t _B[8] PROGMEM =
{
	0b01111100,
	0b01111110,
	0b01100110,
	0b01111100,
	0b01111110,
	0b01100110,
	0b01111110,
	0b01111100
};

const static uint8_t _C[8] PROGMEM =
{
	0b00111110,
	0b01111110,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01111110,
	0b00111110
};

const static uint8_t _D[8] PROGMEM =
{
	0b01111100,
	0b01111110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01111110,
	0b01111100
};

const static uint8_t _E[8] PROGMEM =
{
	0b01111110,
	0b01111110,
	0b01100000,
	0b01111110,
	0b01111110,
	0b01100000,
	0b01111110,
	0b01111110
};

const static uint8_t _F[8] PROGMEM =
{
	0b01111110,
	0b01111110,
	0b01100000,
	0b01111110,
	0b01111110,
	0b01100000,
	0b01100000,
	0b01100000
};

const static uint8_t _G[8] PROGMEM =
{
	0b00111110,
	0b01111110,
	0b01100000,
	0b01101110,
	0b01101110,
	0b01100110,
	0b01111110,
	0b00111110
};

const static uint8_t _H[8] PROGMEM =
{
	0b01100110,
	0b01100110,
	0b01100110,
	0b01111110,
	0b01111110,
	0b01100110,
	0b01100110,
	0b01100110
};

const static uint8_t _I[8] PROGMEM =
{
	0b01111110,
	0b01111110,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b01111110,
	0b01111110
};

const static uint8_t _J[8] PROGMEM =
{
	0b00111110,
	0b00111110,
	0b00000110,
	0b00000110,
	0b00000110,
	0b01100110,
	0b01111110,
	0b00111110
};

const static uint8_t _K[8] PROGMEM =
{
	0b01100110,
	0b01100110,
	0b01101100,
	0b01110000,
	0b01111000,
	0b01101100,
	0b01100110,
	0b01100110
};

const static uint8_t _L[8] PROGMEM =
{
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01111110,
	0b01111110
};

const static uint8_t _M[8] PROGMEM =
{
	0b01100110,
	0b01111110,
	0b01111110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01100110
};

const static uint8_t _N[8] PROGMEM =
{
	0b00111100,
	0b01111110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01100110
};

const static uint8_t _O[8] PROGMEM =
{
	0b00111100,
	0b01111110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01111110,
	0b00111100
};

const static uint8_t _P[8] PROGMEM =
{
	0b01111100,
	0b01111110,
	0b01100110,
	0b01100110,
	0b01111110,
	0b01111100,
	0b01100000,
	0b01100000
};

const static uint8_t _Q[8] PROGMEM =
{
	0b00111100,
	0b01111110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01111110,
	0b00111100,
	0b00000110
};

const static uint8_t _R[8] PROGMEM =
{
	0b01111100,
	0b01111110,
	0b01100110,
	0b01100110,
	0b01111110,
	0b01111100,
	0b01100110,
	0b01100110
};

const static uint8_t _S[8] PROGMEM =
{
	0b00111110,
	0b01111110,
	0b01100000,
	0b01111100,
	0b00111110,
	0b00000110,
	0b01111110,
	0b01111100
};

const static uint8_t _T[8] PROGMEM =
{
	0b01111110,
	0b01111110,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000
};

const static uint8_t _U[8] PROGMEM =
{
	0b01100110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01111110,
	0b00111100
};

const static uint8_t _V[8] PROGMEM =
{
	0b01100110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b00110110,
	0b00011110,
	0b00001110,
	0b00000110
};

const static uint8_t _W[8] PROGMEM =
{
	0b01100110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01111110,
	0b01111110,
	0b01100110
};

const static uint8_t _X[8] PROGMEM =
{
	0b01100110,
	0b01100110,
	0b00111100,
	0b00011000,
	0b00111100,
	0b01100110,
	0b01100110,
	0b01100110
};


const static uint8_t _Y[8] PROGMEM =
{
	0b01100110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b00111100,
	0b00011000,
	0b00011000,
	0b00011000
};

const static uint8_t _Z[8] PROGMEM =
{
	0b01111110,
	0b01111110,
	0b00001100,
	0b00011000,
	0b00110000,
	0b01100000,
	0b01111110,
	0b01111110
};

const static uint8_t _LBRACKET[8] PROGMEM =
{
	0b00111000,
	0b00111000,
	0b00100000,
	0b00100000,
	0b00100000,
	0b00100000,
	0b00111000,
	0b00111000
};

const static uint8_t _BACKSLASH[8] PROGMEM =
{
	0b10000000,
	0b11000000,
	0b01100000,
	0b00110000,
	0b00011000,
	0b00001100,
	0b00000110,
	0b00000010
};

const static uint8_t _RBRACKET[8] PROGMEM =
{
	0b00011100,
	0b00011100,
	0b00000100,
	0b00000100,
	0b00000100,
	0b00000100,
	0b00011100,
	0b00011100
};

const static uint8_t _CARRET[8] PROGMEM =
{
	0b00011000,
	0b00111100,
	0b01100110,
	0b01000010,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000
};

const static uint8_t _UNDERSCORE[8] PROGMEM =
{
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b11111110,
	0b11111110
};

const static uint8_t _TICK[8] PROGMEM =
{
	0b01100000,
	0b01110000,
	0b00111000,
	0b00011000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000
};

const static uint8_t _a[8] PROGMEM =
{
	0b00000000,
	0b00000000,
	0b00111100,
	0b00000110,
	0b00111110,
	0b01100110,
	0b01100110,
	0b00111110
};

const static uint8_t _b[8] PROGMEM =
{
	0b01100000,
	0b01100000,
	0b01100000,
	0b01111100,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01111100
};

const static uint8_t _c[8] PROGMEM =
{
	0b00000000,
	0b00000000,
	0b00111110,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b00111110
};

const static uint8_t _d[8] PROGMEM =
{
	0b00000110,
	0b00000110,
	0b00000110,
	0b00111110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b00111110
};

const static uint8_t _e[8] PROGMEM =
{
	0b00000000,
	0b00000000,
	0b00111100,
	0b01100110,
	0b01100110,
	0b01111110,
	0b01100000,
	0b00111110
};

const static uint8_t _f[8] PROGMEM =
{
	0b00000000,
	0b00111100,
	0b01100110,
	0b01100000,
	0b01111100,
	0b01100000,
	0b01100000,
	0b01100000
};

const static uint8_t _g[8] PROGMEM =
{
	0b00000000,
	0b00111100,
	0b01100110,
	0b01100110,
	0b00111110,
	0b00000110,
	0b01100110,
	0b00111100
};

const static uint8_t _h[8] PROGMEM =
{
	0b01100000,
	0b01100000,
	0b01100000,
	0b01111100,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01100110
};

const static uint8_t _i[8] PROGMEM =
{
	0b00000000,
	0b00011000,
	0b00011000,
	0b00000000,
	0b00111000,
	0b00011000,
	0b00011000,
	0b00111100
};

const static uint8_t _j[8] PROGMEM =
{
	0b00000000,
	0b00001100,
	0b00001100,
	0b00000000,
	0b00001100,
	0b00001100,
	0b00001100,
	0b00111000
};

const static uint8_t _k[8] PROGMEM =
{
	0b01100000,
	0b01100000,
	0b01100110,
	0b01101100,
	0b01110000,
	0b01111000,
	0b01101100,
	0b01100110
};

const static uint8_t _l[8] PROGMEM =
{
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b00111000
};

const static uint8_t _m[8] PROGMEM =
{
	0b00000000,
	0b00000000,
	0b01100110,
	0b01111110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01100110
};

const static uint8_t _n[8] PROGMEM =
{
	0b00000000,
	0b00000000,
	0b00111100,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01100110
};

const static uint8_t _o[8] PROGMEM =
{
	0b00000000,
	0b00000000,
	0b00111100,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b00111100
};

const static uint8_t _p[8] PROGMEM =
{
	0b00000000,
	0b00000000,
	0b01111100,
	0b01100110,
	0b01100110,
	0b01111100,
	0b01100000,
	0b01100000
};

const static uint8_t _q[8] PROGMEM =
{
	0b00000000,
	0b00000000,
	0b00111110,
	0b01100110,
	0b01100110,
	0b00111110,
	0b00000110,
	0b00000110
};

const static uint8_t _r[8] PROGMEM =
{
	0b00000000,
	0b00000000,
	0b00111100,
	0b01100110,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000
};

const static uint8_t _s[8] PROGMEM =
{
	0b00000000,
	0b00000000,
	0b00111110,
	0b01110000,
	0b00111100,
	0b00000110,
	0b00000110,
	0b01111100
};

const static uint8_t _t[8] PROGMEM =
{
	0b00000000,
	0b00000000,
	0b00110000,
	0b01111110,
	0b00110000,
	0b00110000,
	0b00110000,
	0b00011110
};

const static uint8_t _u[8] PROGMEM =
{
	0b00000000,
	0b00000000,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01100110,
	0b00111100
};

const static uint8_t _v[8] PROGMEM =
{
	0b00000000,
	0b00000000,
	0b01100110,
	0b01100110,
	0b00110110,
	0b00011110,
	0b00001110,
	0b00000110
};

const static uint8_t _w[8] PROGMEM =
{
	0b00000000,
	0b00000000,
	0b01100110,
	0b01100110,
	0b01100110,
	0b01111110,
	0b01111110,
	0b01100110
};

const static uint8_t _x[8] PROGMEM =
{
	0b00000000,
	0b00000000,
	0b01100110,
	0b00111100,
	0b00011000,
	0b00111100,
	0b01100110,
	0b01100110,
};


const static uint8_t _y[8] PROGMEM =
{
	0b00000000,
	0b00000000,
	0b01100110,
	0b01100110,
	0b01100110,
	0b00111110,
	0b00000110,
	0b01111100
};

const static uint8_t _z[8] PROGMEM =
{
	0b00000000,
	0b00000000,
	0b01111110,
	0b00000110,
	0b00001100,
	0b00011000,
	0b01110000,
	0b01111110
};

const static uint8_t _LBRACE[8] PROGMEM =
{
	0b00001110,
	0b00011100,
	0b00011000,
	0b01111000,
	0b01111000,
	0b00011000,
	0b00011100,
	0b00001110
};

const static uint8_t _PIPE[8] PROGMEM =
{
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000
};

const static uint8_t _RBRACE[8] PROGMEM =
{
	0b01110000,
	0b00111000,
	0b00011000,
	0b00011110,
	0b00011110,
	0b00011000,
	0b00111000,
	0b01110000
};

const static uint8_t _TILDE[8] PROGMEM =
{
	0b01100000,
	0b11110010,
	0b10111010,
	0b10011110,
	0b00001100,
	0b00000000,
	0b00000000,
	0b00000000
};

const static uint8_t __n[8] PROGMEM =
{
	0b00000000,
	0b01111111,
	0b01111111,
	0b01100011,
	0b01100011,
	0b01100011,
	0b01100011,
	0b01100011
};

const static uint8_t __i[8] PROGMEM =
{
	0b00000000,
	0b01000011,
	0b00100011,
	0b00010011,
	0b00000011,
	0b00000011,
	0b01111111,
	0b01111111
};

const static uint8_t __t[8] PROGMEM =
{
	0b00000000,
	0b01100000,
	0b01100000,
	0b01111111,
	0b01100000,
	0b01100000,
	0b01111111,
	0b01111111
};

const static uint8_t __a[8] PROGMEM =
{
	0b00000000,
	0b01111111,
	0b01111111,
	0b00001011,
	0b00010011,
	0b00100011,
	0b01111111,
	0b01111111
};

const static uint8_t __c[8] PROGMEM =
{
	0b00000000,
	0b01111111,
	0b01111111,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01111111,
	0b01111111
};

const static uint8_t __k[8] PROGMEM =
{
	0b00000000,
	0b01100001,
	0b01100010,
	0b01100100,
	0b01101000,
	0b01110000,
	0b01111111,
	0b01111111
};

const static uint8_t __u[8] PROGMEM =
{
	0b00000000,
	0b01100011,
	0b01100011,
	0b01100011,
	0b01100011,
	0b01100011,
	0b01111111,
	0b01111111
};

const static uint8_t __L[8] PROGMEM =
{
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11111111,
	0b11111111
};

const static uint8_t __E[8] PROGMEM =
{
	0b11111111,
	0b11111111,
	0b11000000,
	0b11111100,
	0b11111100,
	0b11000000,
	0b11111111,
	0b11111111
};

const static uint8_t __D[8] PROGMEM =
{
	0b11111110,
	0b11111111,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11111111,
	0b11111110
};

const static uint8_t __C[8] PROGMEM =
{
	0b01111110,
	0b11111111,
	0b11000011,
	0b11000000,
	0b11000000,
	0b11000011,
	0b11111111,
	0b01111110
};

const static uint8_t __U[8] PROGMEM =
{
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11000011,
	0b11111111,
	0b01111110
};

const static uint8_t __B[8] PROGMEM =
{
	0b11111110,
	0b11111111,
	0b11000011,
	0b11111110,
	0b11000011,
	0b11000011,
	0b11111111,
	0b11111110
};

const static uint8_t* const bitmapTable[] PROGMEM =
{
	__, _EXCLAIMATION, _QUOTE, _POUND, _DOLLAR, _PERCENT,
	_AMPERSAND, _APOSTROPHE, _LPARENTHESIS, _RPARENTHESIS,
	_STAR, _PLUS, _COMMA, _MINUS, _PERIOD, _FORWARDSLASH,
	_0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
	_COLON, _SEMICOLON, _LESS, _EQUAL, _GREATER, _QUESTION, _AT,
	_A, _B, _C, _D, _E, _F, _G, _H, _I, _J, _K, _L, _M,
	_N, _O, _P, _Q, _R, _S, _T, _U, _V, _W, _X, _Y, _Z,
	_LBRACKET, _BACKSLASH, _RBRACKET, _CARRET, _UNDERSCORE, _TICK,
	_a, _b, _c, _d, _e, _f, _g, _h, _i, _j, _k, _l, _m,
	_n, _o, _p, _q, _r, _s, _t, _u, _v, _w, _x, _y, _z,
	_LBRACE, _PIPE, _RBRACE, _TILDE, __
};

const static uint8_t* const customBitmapTable[] PROGMEM =
{
	__n, __i, __t, __a, __c, __k, __u,
	__L, __E, __D, __C, __U, __B, __E
};


uint8_t* get_bitmap(unsigned char character)
{
	static uint8_t bitmap[8];

	if ((character < 32) || (character > 141))
	{
		character = 32;
	}
	
	if (character < 128)
	{
		memcpy_P(bitmap, (uint8_t*)pgm_read_word(&bitmapTable[character - 32]), 8);
	}
	else
	{
		memcpy_P(bitmap, (uint8_t*)pgm_read_word(&customBitmapTable[character - 128]), 8);
	}

	return &bitmap[0];
}

