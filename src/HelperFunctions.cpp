#include "HelperFunctions.h"
#include "GlobalValues.h"

HelperFunctions::HelperFunctions(void)
{
}

HelperFunctions::~HelperFunctions(void)
{
}

bool HelperFunctions::isPositionInSlice(const ofPoint& position)
{
	ofPoint diff = position - GlobalValues::PIZZA_CENTER_POINT;
	if(diff.length() > GlobalValues::PIZZA_RADIUS || diff.length() < GlobalValues::PIZZA_INNER_RADIUS)
		return false;

	float anglePt = ofRadToDeg(atan2(diff.y, diff.x));
	if (anglePt < 0) 
		anglePt += 360;

	float diffAngle = anglePt - GlobalValues::getInstance().getCurrentPizzaRotation();
	if (diffAngle > 180) 
		anglePt -= 360;
	if (diffAngle < -180) 
		anglePt += 360;

	return 
		anglePt >= GlobalValues::getInstance().getCurrentPizzaRotation() && 
		anglePt <= GlobalValues::getInstance().getCurrentPizzaRotation() + GlobalValues::SLICE_ANGLE;
}