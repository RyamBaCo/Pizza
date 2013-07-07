#include "PizzaImage.h"

PizzaImage::PizzaImage(const std::string& imageFile, const DrawDestination& drawDestination)
	:	drawDestination(drawDestination)
{
	pizzaImage.loadImage(imageFile);
	// by default draw to center
	drawPosition = ofPoint(
		(ofGetWindowWidth() - pizzaImage.width) / 2,
		(ofGetWindowHeight() - pizzaImage.height) / 2);
}

PizzaImage::~PizzaImage()
{
}

ofPoint PizzaImage::getDrawPosition() const
{
	return drawPosition;
}

void PizzaImage::draw()
{
	pizzaImage.draw(drawPosition);
}

void PizzaImage::draw(const ofPoint& position, float rotation /* = 0 */)
{
	drawPosition = position;
	if(drawDestination == CENTER)
		drawPosition -= ofPoint(pizzaImage.getWidth() / 2, pizzaImage.getHeight() / 2);

	draw(rotation);
}

void PizzaImage::draw(float rotation)
{
	// by default we rotate around the image's center
	ofPushMatrix();
		ofTranslate(drawPosition.x + pizzaImage.width / 2, drawPosition.y + pizzaImage.height / 2, 0);
		ofRotate(rotation, 0, 0, 1);
		ofTranslate(-(drawPosition.x + pizzaImage.width / 2), -(drawPosition.y + pizzaImage.height / 2), 0);
		draw();
	ofPopMatrix();
}
