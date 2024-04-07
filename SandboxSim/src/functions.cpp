#include "../headers/functions.h"	

float mappingFunc(int value) {
	float minIn{ 0.0f }, maxIn{ 200.0f }, minOut{ -1.0f }, maxOut{ 1.0f };
	float fraction = static_cast<float>(value - minIn) / (maxIn - minIn);
	float mappedValue = minOut + fraction * (maxOut - minOut);
	return mappedValue;
}