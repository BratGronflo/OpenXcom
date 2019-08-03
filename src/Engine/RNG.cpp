/*
 * Copyright 2010-2016 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "RNG.h"
#include <cmath>
#include <time.h>
#include <stdlib.h>
#ifndef UINT64_MAX
#define UINT64_MAX 0xffffffffffffffffULL
#endif

namespace OpenXcom
{
namespace RNG
{

/*  Written in 2014 by Sebastiano Vigna (vigna@acm.org)

To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.

See <http://creativecommons.org/publicdomain/zero/1.0/>. */

/* This is a good generator if you're short on memory, but otherwise we
   rather suggest to use a xorshift128+ (for maximum speed) or
   xorshift1024* (for speed and very long period) generator. */

static uint64_t nextImpl(uint64_t& state)
{
	state ^= state >> 12; // a
	state ^= state << 25; // b
	state ^= state >> 27; // c
	return state * 2685821657736338717ULL;
}

uint64_t x = time(0); /* The state must be seeded with a nonzero value. */
uint64_t x_seedless = time(0) ^ 0x2aafed63c68b2255; //apply some random number to reduce similarity with `x`.


uint64_t next()
{
	return nextImpl(x);
}

/**
 * Returns the current seed in use by the generator.
 * @return Current seed.
 */
uint64_t getSeed()
{
	return x;
}

/**
 * Changes the current seed in use by the generator.
 * @param n New seed.
 */
void setSeed(uint64_t n)
{
	x = n;
}

/**
 * Generates a random integer number within a certain range.
 * @param min Minimum number, inclusive.
 * @param max Maximum number, inclusive.
 * @return Generated number.
 */
int generate(int min, int max)
{
	uint64_t num = next();
	return (int)(num % (max - min + 1) + min);
}

/**
 * Generates a random decimal number within a certain range.
 * @param min Minimum number.
 * @param max Maximum number.
 * @return Generated number.
 */
double generate(double min, double max)
{
	double num = next();
	return (num / ((double)UINT64_MAX / (max - min)) + min);
}

/**
 * Generates a random integer number within a certain range.
 * Distinct from "generate" in that it doesn't touch the seed.
 * @param min Minimum number, inclusive.
 * @param max Maximum number, inclusive.
 * @return Generated number.
 */
int seedless(int min, int max)
{
	return (int)(nextImpl(x_seedless) % (max - min + 1) + min);
}


/**
 * Normal random variate generator
 * @param m mean
 * @param s standard deviation
 * @return normally distributed value.
 */
double boxMuller(double m, double s)
{
	double y1;
	static double y2;
	static int use_last = 0;

	if (use_last)				/* use value from previous call */
	{
		y1 = y2;
		use_last = 0;
	}
	else
	{
		double x1, x2, w;
		do {
			x1 = 2.0 * generate(0.0, 1.0) - 1.0;
			x2 = 2.0 * generate(0.0, 1.0) - 1.0;
			w = x1 * x1 + x2 * x2;
		} while ( w >= 1.0 );

		w = sqrt( (-2.0 * log( w ) ) / w );
		y1 = x1 * w;
		y2 = x2 * w;
		use_last = 1;
	}

	return( m + y1 * s );
}

/**
 * Generates a random percent chance of an event occurring,
 * and returns the result
 * @param value Value percentage (0-100%)
 * @return True if the chance succeeded.
 */
bool percent(int value)
{
	return (generate(0, 99) < value);
}

}

}
