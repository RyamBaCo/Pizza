#include "PizzaImage.h"

PizzaImage::PizzaImage(const std::string& imageFile, const DrawDestination& drawDestination, const float drawRotation)
	:	imageFile(imageFile),
		drawDestination(drawDestination),
		drawRotation(drawRotation)
{
	pizzaImage.loadImage(imageFile);
	// by default draw to center
	drawPosition = ofPoint(
		(ofGetWindowWidth() - pizzaImage.width) / 2,
		(ofGetWindowHeight() - pizzaImage.height) / 2);
}

PizzaImage::PizzaImage(const PizzaImage& other)
{
	imageFile = other.imageFile;
	pizzaImage.loadImage(imageFile);
	drawPosition = other.drawPosition;
	drawRotation = other.drawRotation;
	drawDestination = other.drawDestination;
}

PizzaImage::~PizzaImage()
{
}

ofPoint PizzaImage::getDrawPosition() const
{
	return drawPosition;
}

float PizzaImage::getDrawRotation() const
{
	return drawRotation;
}

void PizzaImage::setDrawRotation(const float drawRotation)
{
	this->drawRotation = drawRotation;
}

void PizzaImage::draw()
{
	draw(drawRotation);
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
		pizzaImage.draw(drawPosition);
	ofPopMatrix();
}
