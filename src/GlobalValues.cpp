#include "GlobalValues.h"
#include "AnimationManager.h"
#include "SpriteAnimation.h"

const ofPoint GlobalValues::PIZZA_CENTER_POINT = ofPoint(1024 / 2, 768 / 2);

GlobalValues::GlobalValues()
	:	currentScore(0),
		highScore(0)
{
	currentPizzaRotation = 0;

	// TODO read all the mapping values from XML or JSON
	ingredientMap.insert(std::pair<IngredientType, IngredientValues>(CHEESE, IngredientValues("images/ingredients/cheese.png", "sounds/Cabasa.wav")));
	ingredientMap.insert(std::pair<IngredientType, IngredientValues>(EGG, IngredientValues("images/ingredients/egg.png", "sounds/Clap.wav")));
	ingredientMap.insert(std::pair<IngredientType, IngredientValues>(PAPRIKA, IngredientValues("images/ingredients/paprika.png", "sounds/Claves.wav")));
	ingredientMap.insert(std::pair<IngredientType, IngredientValues>(PINEAPPLE, IngredientValues("images/ingredients/pineapple.png", "sounds/Cowbell.wav")));
	ingredientMap.insert(std::pair<IngredientType, IngredientValues>(TOMATO, IngredientValues("images/ingredients/tomato.png", "sounds/Crash.wav")));
}

GlobalValues& GlobalValues::getInstance()
{
	static GlobalValues instance;
	return instance;
}

GlobalValues::IngredientValues GlobalValues::getValuesForIngredient(const IngredientType& type)
{
	return ingredientMap[type];
}

int GlobalValues::getCurrentPizzaRotation() const
{
	return currentPizzaRotation;
}

int GlobalValues::getHighScore() const
{
	return highScore;
}

int GlobalValues::getCurrentScore() const
{
	return currentScore;
}

void GlobalValues::initSliceAnimations()
{
	for(int i = 0; i < 6; ++i)
		AnimationManager::addAnimation(new SpriteAnimation("fire_1_40", 40, GlobalValues::ANIMATION_FIRE_SPEED, GlobalValues::PIZZA_CENTER_POINT, 0, true));
}

bool GlobalValues::updatePizzaRotation(int deltaTime)
{
	// TODO implement rotation with rotationspeed and stuff
	currentPizzaRotation += deltaTime * 0.1f;
	if(currentPizzaRotation > 360)
	{
		if(currentScore > highScore)
		{
			AnimationManager::addAnimation(new SpriteAnimation("fx6_eaterFire", 20, GlobalValues::ANIMATION_NEW_HIGHSCORE_SPEED, ofPoint(ofGetScreenWidth() / 2 - 410 + 168 / 2, ofGetWindowHeight() / 2 - 140 + 148 / 2), 0));
			highScore = currentScore;
		}
		currentScore = 0;

		currentPizzaRotation -= 360;
		return true;
	}

	for(int i = 0; i < 3; ++i)
	{
		int currentDistance = 140 + 170 * i / 3.0f;
		((SpriteAnimation*)AnimationManager::getAnimationAt(i))->setPosition(GlobalValues::PIZZA_CENTER_POINT + ofPoint(currentDistance * cos(ofDegToRad(currentPizzaRotation)), currentDistance * sin(ofDegToRad(currentPizzaRotation))));
		((SpriteAnimation*)AnimationManager::getAnimationAt(i))->setRotation(currentPizzaRotation);
	}

	for(int i = 3; i < 6; ++i)
	{
		int currentDistance = 140 + 150 * (i - 3) / 3.0f;
		float currentRotation = currentPizzaRotation + 20 + 15 * (i - 3) / 3.0f;
		((SpriteAnimation*)AnimationManager::getAnimationAt(i))->setPosition(GlobalValues::PIZZA_CENTER_POINT + ofPoint(currentDistance * cos(ofDegToRad(currentRotation)), currentDistance * sin(ofDegToRad(currentRotation))));
		((SpriteAnimation*)AnimationManager::getAnimationAt(i))->setRotation(currentPizzaRotation);
	}

	return false;
}

void GlobalValues::increaseCurrentScore()
{
	++currentScore;
	AnimationManager::addAnimation(new SpriteAnimation("fx5_fire_scissors", 13, GlobalValues::ANIMATION_INCREASE_SCORE_SPEED, ofPoint(ofGetScreenWidth() / 2 - 410 + 133 / 2, ofGetWindowHeight() / 2 - 75 + 169 / 2), 0));
}
