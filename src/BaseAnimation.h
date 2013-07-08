#pragma once
#include "PizzaImage.h"

class BaseAnimation
{
public:
	BaseAnimation(const PizzaImage& pizzaImage);
	BaseAnimation();
	~BaseAnimation();

	bool isReadyForDelete() const;
	virtual void update(int deltaTime) = 0;
	virtual void draw() = 0;

protected:
	bool readyForDelete;
	PizzaImage* pizzaImage;
};

