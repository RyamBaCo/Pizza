#pragma once
#include <string>
#include "ofMain.h"

class PizzaImage
{
public:
	PizzaImage(const std::string& imageFile);
	~PizzaImage();

	ofPoint getDrawPosition() const;

	void draw();
	void draw(float rotation);
	void draw(const ofPoint& position, float rotation = 0);

private:
	ofImage pizzaImage;
	ofPoint drawPosition;
};