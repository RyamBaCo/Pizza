#include "FadeOutAnimation.h"


FadeOutAnimation::FadeOutAnimation(const PizzaImage& pizzaImage, const int fadeOutSpeed)
	:	BaseAnimation(pizzaImage),
		fadeOutSpeed(fadeOutSpeed),
		currentTransparency(255),
		passedTime(0)
{
}

FadeOutAnimation::~FadeOutAnimation()
{
}

void FadeOutAnimation::update(int deltaTime)
{
	passedTime += deltaTime;

	if(passedTime >= fadeOutSpeed)
	{
		passedTime = fadeOutSpeed;
		readyForDelete = true;
	}

	currentTransparency = 255 - (float)passedTime / fadeOutSpeed * 255;
}

void FadeOutAnimation::draw()
{
	ofSetColor(255, 255, 255, currentTransparency);
	pizzaImage->draw();
	ofSetColor(255, 255, 255, 255);
}
