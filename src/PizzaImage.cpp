#include "PizzaImage.h"

PizzaImage::PizzaImage(const std::string& imageFile)
{
	pizzaImage.loadImage(imageFile);
	// by default draw to center
	drawPosition = ofPoint(
		(ofGetWindowWidth() - pizzaImage.getWidth()) / 2,
		(ofGetWindowHeight() - pizzaImage.getHeight()) / 2);
}

PizzaImage::~PizzaImage()
{
}

void PizzaImage::draw()
{
	pizzaImage.draw(drawPosition);
}

void PizzaImage::draw(float rotation)
{
	ofPushMatrix();
		ofTranslate(drawPosition.x + pizzaImage.width / 2, drawPosition.y + pizzaImage.height / 2, 0);
		ofRotate(rotation, 0, 0, 1);
		ofTranslate(-(drawPosition.x + pizzaImage.width / 2), -(drawPosition.y + pizzaImage.height / 2), 0);
		draw();
	ofPopMatrix();
}
