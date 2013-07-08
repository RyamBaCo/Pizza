#pragma once
#include "BaseAnimation.h"

class FadeOutAnimation : public BaseAnimation
{
public:
	FadeOutAnimation(const PizzaImage& pizzaImage, int fadeOutSpeed);
	~FadeOutAnimation();

	void update(int deltaTime);
	void draw();

private:
	int currentTransparency;
	int fadeOutSpeed;
	int passedTime;
};

