/*
  ==============================================================================

    decimator.h
    Created: 31 Jul 2018 2:55:04pm
    Author:  Nick Tomassetti

	A decimation algorithim from musicdsp.org

  ==============================================================================
*/

#pragma once

class Decimator {
public:
	Decimator();
	~Decimator();

	float process(float input);
	void updateParameters(int bits, float rate);

private:
	int _bits;
	float _rate;
	long int m;// = 1 << (_bits - 1);
	float y = 0, cnt = 0;

};