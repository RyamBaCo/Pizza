#pragma once
#include "ofMain.h"

class HelperFunctions
{
public:
	HelperFunctions();
	~HelperFunctions();

	static bool isPositionInSlice(const ofPoint& position);
};

