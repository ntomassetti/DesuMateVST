/*
  ==============================================================================

    decimator.cpp
    Created: 31 Jul 2018 2:55:04pm
	Author:  Nick Tomassetti

	A decimation algorithim from musicdsp.org

  ==============================================================================
*/

#include "decimator.h"

Decimator::Decimator() : _bits (16), _rate (1.0)
{
}

Decimator::~Decimator()
{
}

float Decimator::process(float input)
{
	m = 1 << (_bits - 1);
	cnt += _rate;
	if (cnt >= 1)
	{
		cnt -= 1;
		y = (long int)(input*m) / (float)m;
	}
	return y;
}

void Decimator::updateParameters(int bits, float rate)
{
	_bits = bits;
	_rate = rate;
}
