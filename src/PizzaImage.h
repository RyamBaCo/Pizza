#pragma once
#include <string>
#include "ofMain.h"

class PizzaImage
{
public:
	enum DrawDestination
	{
		LEFT_EDGE,
		CENTER
	};

	PizzaImage(const std::string& imageFile, const DrawDestination& drawDestination = LEFT_EDGE);
	~PizzaImage();

	ofPoint getDrawPosition() const;

	void draw();
	void draw(float rotation);
	void draw(const ofPoint& position, float rotation = 0);

private:
	ofImage pizzaImage;
	ofPoint drawPosition;
	DrawDestination drawDestination;
};