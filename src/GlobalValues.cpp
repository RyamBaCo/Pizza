#include "GlobalValues.h"
#include "AnimationManager.h"
#include "SpriteAnimation.h"

const ofPoint GlobalValues::PIZZA_CENTER_POINT = ofPoint(1024 / 2, 768 / 2);
const std::string GlobalValues::ANIMATION_FIRE = "fire_1_40";
const std::string GlobalValues::ANIMATION_GAIN_SLOT = "fx1_blue_topEffect";
const std::string GlobalValues::ANIMATION_INGREDIENTS_EXPLOSION = "fx3_fireBall";
const std::string GlobalValues::ANIMATION_INCREASE_SCORE = "fx5_fire_scissors";
const std::string GlobalValues::ANIMATION_NEW_HIGHSCORE = "fx6_eaterFire";
const std::string GlobalValues::ANIMATION_INGREDIENTS_SPAWN = "fx7_energyBall";
const std::string GlobalValues::ANIMATION_LOSE_SLOT = "fx10_blackExplosion";

GlobalValues::GlobalValues()
	:	currentScore(0),
		lastScore(0),
		highScore(0),
		rotatingClockwise(true),
		rotationForChange(ofRandom(GlobalValues::PIZZA_MIN_ANGLE_FOR_ROTATION_CHANGE, GlobalValues::PIZZA_MAX_ANGLE_FOR_ROTATION_CHANGE)),
		absoluteRotation(0),
		currentPizzaRotation(0)
{
	// TODO read all the mapping values from XML or JSON
	ingredientMap.insert(std::pair<IngredientType, IngredientValues>(CHEESE, IngredientValues("images/ingredients/cheese.png", "sounds/Cabasa.wav")));
	ingredientMap.insert(std::pair<IngredientType, IngredientValues>(EGG, IngredientValues("images/ingredients/egg.png", "sounds/Clap.wav")));
	ingredientMap.insert(std::pair<IngredientType, IngredientValues>(PAPRIKA, IngredientValues("images/ingredients/paprika.png", "sounds/Claves.wav")));
	ingredientMap.insert(std::pair<IngredientType, IngredientValues>(PINEAPPLE, IngredientValues("images/ingredients/pineapple.png", "sounds/Cowbell.wav")));
	ingredientMap.insert(std::pair<IngredientType, IngredientValues>(TOMATO, IngredientValues("images/ingredients/tomato.png", "sounds/Crash.wav")));
	ingredientMap.insert(std::pair<IngredientType, IngredientValues>(BACON, IngredientValues("images/ingredients/bacon.png", "sounds/Crash.wav")));
	ingredientMap.insert(std::pair<IngredientType, IngredientValues>(CORN, IngredientValues("images/ingredients/corn.png", "sounds/Crash.wav")));
	ingredientMap.insert(std::pair<IngredientType, IngredientValues>(MUSHROOM, IngredientValues("images/ingredients/mushroom.png", "sounds/Crash.wav")));
	ingredientMap.insert(std::pair<IngredientType, IngredientValues>(ONIONS, IngredientValues("images/ingredients/onions.png", "sounds/Crash.wav")));
	ingredientMap.insert(std::pair<IngredientType, IngredientValues>(SALAMI, IngredientValues("images/ingredients/salami.png", "sounds/Crash.wav")));

	std::map<std::string, int> numberOfFrames;
	numberOfFrames[GlobalValues::ANIMATION_FIRE] = 40;
	numberOfFrames[GlobalValues::ANIMATION_GAIN_SLOT] = 22;
	numberOfFrames[GlobalValues::ANIMATION_INGREDIENTS_EXPLOSION] = 20;
	numberOfFrames[GlobalValues::ANIMATION_INCREASE_SCORE] = 13;
	numberOfFrames[GlobalValues::ANIMATION_NEW_HIGHSCORE] = 20;
	numberOfFrames[GlobalValues::ANIMATION_INGREDIENTS_SPAWN] = 32;
	numberOfFrames[GlobalValues::ANIMATION_LOSE_SLOT] = 19;

	for(auto iterator = numberOfFrames.begin(); iterator != numberOfFrames.end(); ++iterator)
		for(int i = 0; i < (*iterator).second; ++i)
			animationImages[(*iterator).first].push_back(new PizzaImage("images/" + (*iterator).first + "/" + "s (" + ofToString(i + 1) + ").png", PizzaImage::CENTER));
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

std::vector<PizzaImage*> GlobalValues::getAnimationImages(std::string animationName)
{
	return animationImages[animationName];
}

void GlobalValues::initSliceAnimations()
{
	for(int i = 0; i < 10; ++i)
		AnimationManager::addAnimation(new SpriteAnimation(GlobalValues::ANIMATION_FIRE, GlobalValues::ANIMATION_FIRE_SPEED, GlobalValues::PIZZA_CENTER_POINT, 0, true));
}

bool GlobalValues::updatePizzaRotation(int deltaTime)
{
	// TODO implement rotation with rotationspeed and stuff
	float rotationChange = deltaTime * GlobalValues::PIZZA_BASE_ROTATION_SPEED / 1000.0f + GlobalValues::PIZZA_ROTATION_SPEED_PER_SCORE / 1000.0f * std::max(lastScore, currentScore);

	if(GlobalValues::PIZZA_MIN_ANGLE_FOR_ROTATION_CHANGE > 0)
	{
		absoluteRotation += rotationChange;

		if(absoluteRotation > rotationForChange)
		{
			rotatingClockwise = !rotatingClockwise;
			absoluteRotation = 0;
			rotationForChange = ofRandom(GlobalValues::PIZZA_MIN_ANGLE_FOR_ROTATION_CHANGE, GlobalValues::PIZZA_MAX_ANGLE_FOR_ROTATION_CHANGE);
		}
	}
	
	bool newRound = false;

	if(rotatingClockwise)
	{
		currentPizzaRotation += rotationChange;
		if(currentPizzaRotation > 360)
		{
			currentPizzaRotation -= 360;
			newRound = true;
		}
	}

	else
	{
		currentPizzaRotation -= rotationChange;
		if(currentPizzaRotation < 0)
		{
			currentPizzaRotation += 360;
			newRound = true;
		}
	}
	
	if(newRound)	
	{
		if(currentScore > highScore)
		{
			AnimationManager::addAnimation(new SpriteAnimation(GlobalValues::ANIMATION_NEW_HIGHSCORE, GlobalValues::ANIMATION_NEW_HIGHSCORE_SPEED, ofPoint(GlobalValues::PIZZA_CENTER_POINT.x, GlobalValues::PIZZA_CENTER_POINT.y - 140 + 148 / 2), 0));
			highScore = currentScore;
		}
		lastScore = currentScore;
		currentScore = 0;

		
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

	((SpriteAnimation*)AnimationManager::getAnimationAt(6))->setPosition(GlobalValues::PIZZA_CENTER_POINT + ofPoint(190 * cos(ofDegToRad(currentPizzaRotation + 12)), 190 * sin(ofDegToRad(currentPizzaRotation + 12))));
	((SpriteAnimation*)AnimationManager::getAnimationAt(6))->setRotation(currentPizzaRotation);
	((SpriteAnimation*)AnimationManager::getAnimationAt(7))->setPosition(GlobalValues::PIZZA_CENTER_POINT + ofPoint(250 * cos(ofDegToRad(currentPizzaRotation + 20)), 250 * sin(ofDegToRad(currentPizzaRotation + 20))));
	((SpriteAnimation*)AnimationManager::getAnimationAt(7))->setRotation(currentPizzaRotation);
	((SpriteAnimation*)AnimationManager::getAnimationAt(8))->setPosition(GlobalValues::PIZZA_CENTER_POINT + ofPoint(250 * cos(ofDegToRad(currentPizzaRotation + 10)), 250 * sin(ofDegToRad(currentPizzaRotation + 10))));
	((SpriteAnimation*)AnimationManager::getAnimationAt(8))->setRotation(currentPizzaRotation);
	((SpriteAnimation*)AnimationManager::getAnimationAt(9))->setPosition(GlobalValues::PIZZA_CENTER_POINT + ofPoint(110 * cos(ofDegToRad(currentPizzaRotation + 8)), 110 * sin(ofDegToRad(currentPizzaRotation + 8))));
	((SpriteAnimation*)AnimationManager::getAnimationAt(9))->setRotation(currentPizzaRotation);

	return false;
}

void GlobalValues::increaseCurrentScore()
{
	++currentScore;
	AnimationManager::addAnimation(new SpriteAnimation(GlobalValues::ANIMATION_INCREASE_SCORE, GlobalValues::ANIMATION_INCREASE_SCORE_SPEED, ofPoint(GlobalValues::PIZZA_CENTER_POINT.x - 15, GlobalValues::PIZZA_CENTER_POINT.y - 75 + 169 / 2), 0));
}

void GlobalValues::cleanUp()
{
	if(animationImages.size() <= 0)
		return;

	for(auto iterator = animationImages.begin(); iterator != animationImages.end(); ++iterator)
	{
		std::vector<PizzaImage*> imageVector = getAnimationImages((*iterator).first);
		for(int i = 0; i < imageVector.size(); ++i)
			delete imageVector[i];
	}

	animationImages.clear();
}
