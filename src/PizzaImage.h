#pragma once
#include <string>
#include "ofMain.h"

class PizzaImage
{
public:
	PizzaImage(const std::string& imageFile);
	~PizzaImage();

	void draw();
	void draw(float rotation);

private:
	ofImage pizzaImage;
	ofPoint drawPosition;
};
