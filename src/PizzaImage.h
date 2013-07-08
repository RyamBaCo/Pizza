#pragma once
#include <string>
#include "ofMain.h"

// TODO refactor this class!
class PizzaImage
{
public:
	enum DrawDestination
	{
		LEFT_EDGE,
		CENTER
	};

	PizzaImage(const std::string& imageFile, const DrawDestination& drawDestination = LEFT_EDGE, const float drawRotation = 0);
	PizzaImage(const PizzaImage& pizzaImage);
	~PizzaImage();

	ofPoint getDrawPosition() const;
	float getDrawRotation() const;
	void setDrawRotation(const float drawRotation);

	void draw();
	void draw(float rotation);
	void draw(const ofPoint& position, float rotation = 0);

private:
	ofImage pizzaImage;
	ofPoint drawPosition;
	float drawRotation;
	DrawDestination drawDestination;
	std::string imageFile;
};