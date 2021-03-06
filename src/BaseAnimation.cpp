#include "BaseAnimation.h"


BaseAnimation::BaseAnimation(const PizzaImage& pizzaImage)
	:	pizzaImage(new PizzaImage(pizzaImage)),
		readyForDelete(false)
{
}

BaseAnimation::BaseAnimation()
	:	pizzaImage(0),
		readyForDelete(false)
{
}

BaseAnimation::~BaseAnimation()
{
	if(pizzaImage != 0)
	{
		delete pizzaImage;
		pizzaImage = 0;
	}
}

bool BaseAnimation::isReadyForDelete() const
{
	return readyForDelete;
}