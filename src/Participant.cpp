#include "Participant.h"
#include "HelperFunctions.h"
#include "AnimationManager.h"
#include "FadeOutAnimation.h"
#include "SpriteAnimation.h"
#include "GlobalValues.h"
#include <limits>

Participant::Participant()
	:	position(-1, -1),
		baseIngredient(0),
		punished(false),
		lastIngredientPosition(ofPoint(INT_MAX, INT_MAX))
{
	burntSound.loadSound("sounds/11-last.wav");
	burntSound.setMultiPlay(true);
}

Participant::~Participant()
{
	if(hasIngredient())
	{
		delete baseIngredient;
		baseIngredient = 0;
	}

	for(auto iterator = ingredients.begin(); iterator != ingredients.end(); ++iterator)
		delete *iterator;

	ingredients.clear();
	burntSound.unloadSound();
}

void Participant::setPosition(const ofPoint& position)
{
	this->position = position;

	int distanceToCenter = ofVec2f(this->position.x - GlobalValues::PIZZA_CENTER_POINT.x, this->position.y - GlobalValues::PIZZA_CENTER_POINT.y).length();

	if(		distanceToCenter < GlobalValues::PIZZA_RADIUS
		&&	distanceToCenter > GlobalValues::PIZZA_INNER_RADIUS
		&&	!hasIngredient())
		resetIngredients();
	else if((	distanceToCenter > GlobalValues::PIZZA_RADIUS
			||	distanceToCenter < GlobalValues::PIZZA_INNER_RADIUS)
		&&	hasIngredient())
		removeIngredients();

	if(hasIngredient())
	{
		// TODO refactor, position is stored twice
		baseIngredient->setPosition(position);

		if(	!GlobalValues::getInstance().isGameStopped() &&
			!punished &&
			(position - lastIngredientPosition).length() >= GlobalValues::INGREDIENT_DROP_RANGE)
			dropIngredient();
	}
}

ofPoint Participant::getPosition() const
{
	return position;
}

bool Participant::hasIngredient() const
{
	return baseIngredient != 0;
}

void Participant::resetIngredients()
{
	if(hasIngredient())
	{
		delete baseIngredient;
		baseIngredient = 0;
	}

	baseIngredient = new Ingredient(static_cast<GlobalValues::IngredientType>((int)ofRandom(0, GlobalValues::IngredientType::LAST - 1)));
	dropIngredient();
}

void Participant::dropIngredient()
{
	AnimationManager::addAnimation(new SpriteAnimation(GlobalValues::ANIMATION_INGREDIENTS_SPAWN, GlobalValues::ANIMATION_INGREDIENTS_SPAWN_SPEED, position - ofPoint(45 - 80 / 2, 40 - 67 / 2), 0));
	baseIngredient->setRotation(ofRandom(0, 360));
	ingredients.push_back(new Ingredient(baseIngredient->getType()));
	ingredients.back()->setPosition(position);
	ingredients.back()->setRotation(baseIngredient->getRotation());
	lastIngredientPosition = position;
}

void Participant::removeIngredients()
{
	if(hasIngredient())
	{
		delete baseIngredient;
		baseIngredient = 0;
	}

	for(auto iterator = ingredients.begin(); iterator != ingredients.end(); ++iterator)
		(*iterator)->setReadyForDelete(true);
}

void Participant::update()
{
	if(!punished && HelperFunctions::isPositionInSlice(position))
	{
		punished = true;
		burntSound.play();
		GlobalValues::getInstance().updateHighScore();
	}

	if(punished && !HelperFunctions::isPositionInSlice(position))
		punished = false;

	// TODO put this in observer pattern or something
	for(auto iterator = ingredients.begin(); iterator != ingredients.end();)
	{
		if((*iterator)->isReadyForDelete())
		{
			AnimationManager::addAnimation(new FadeOutAnimation(*((*iterator)->getPizzaImage()), GlobalValues::ANIMATION_INGREDIENTS_FADEOUT_SPEED));
			AnimationManager::addAnimation(new SpriteAnimation(GlobalValues::ANIMATION_INGREDIENTS_EXPLOSION, GlobalValues::ANIMATION_INGREDIENTS_EXPLOSION_SPEED, (*iterator)->getPosition(), 0));

			delete *iterator;
			iterator = ingredients.erase(iterator);
		}
		else
		{
			(*iterator)->update();
			 ++iterator;
		}
	}
}

bool Participant::draw()
{
#if _DEBUG
	if(!hasIngredient())
	{
		ofSetColor(255, 0, 0);
		ofCircle(position, GlobalValues::DEBUG_PARTICIPANT_RADIUS);
		ofSetColor(255, 255, 255);
	}
#endif

	if(hasIngredient())
	{
		ofColor ingredientColor = GlobalValues::getInstance().getValuesForIngredient(baseIngredient->getType()).ingredientColor;
		ingredientColor.a = 150;
		ofSetColor(ingredientColor);
		ofCircle(position, GlobalValues::HUD_RADIUS);
		ofSetColor(255, 255, 255);
		baseIngredient->draw();
	}

	for(auto iterator = ingredients.begin(); iterator != ingredients.end(); ++iterator)
		(*iterator)->draw();

	return true;
}
