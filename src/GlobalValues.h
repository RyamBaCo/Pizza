#pragma once
#include "ofMain.h"
#include <map>
#include <string>

// TODO move pizza rotation stuff into pizza rotator class or something
class GlobalValues
{
public:

#if _DEBUG
	static const int DEBUG_PARTICIPANT_RADIUS = 20;
	static const int DEBUG_PARTICIPANT_DIRECTION_RADIUS = 5;
#endif

	static const ofPoint PIZZA_CENTER_POINT;
	static const int PIZZA_RADIUS = 280;
	static const int PIZZA_INNER_RADIUS = 130;
	static const int SLICE_ANGLE = 45;
	static const int MAX_POINTS_FOR_DIRECTION = 50;
	static const int INGREDIENT_DROP_RANGE = 200;
	static const int HUD_DISTANCE = 50;
	static const int MIN_FREE_SLOTS = 2;
	static const int START_FREE_SLOTS = 3;
	static const int MAX_FREE_SLOTS = 6;

	static const int ANIMATION_INGREDIENTS_FADEOUT_SPEED = 500;
	static const int ANIMATION_INGREDIENTS_EXPLOSION_SPEED = 50;
	static const int ANIMATION_INGREDIENTS_SPAWN_SPEED = 50;
	static const int ANIMATION_INCREASE_SCORE_SPEED = 50;
	static const int ANIMATION_NEW_HIGHSCORE_SPEED = 50;
	static const int ANIMATION_LOSE_SLOT_SPEED = 50;
	static const int ANIMATION_GAIN_SLOT_SPEED = 100;

	#pragma region IngredientTypes

	enum IngredientType
	{
		CHEESE,
		EGG,
		PAPRIKA,
		PINEAPPLE,
		TOMATO
	};

	struct IngredientValues
	{
		std::string graphicDestination;
		ofSoundPlayer ingredientSound;

		IngredientValues()
		{
		}

		IngredientValues(const std::string& graphicDestination, const std::string& soundDestination)
			:	graphicDestination(graphicDestination)
		{
			ingredientSound.loadSound(soundDestination);
			ingredientSound.setMultiPlay(true);
		}

		void playSound()
		{
			ingredientSound.play();
		}
	};

	#pragma endregion IngredientTypes

	static GlobalValues& getInstance();

	IngredientValues getValuesForIngredient(const IngredientType& type);
	int getCurrentPizzaRotation() const;
	int getHighScore() const;
	int getCurrentScore() const;
	void increaseCurrentScore();

	// returns true if a new round has been started
	bool updatePizzaRotation(int deltaTime);

private:
	GlobalValues();
	GlobalValues(GlobalValues const&);
	void operator=(GlobalValues const&);

private:
	std::map<IngredientType, IngredientValues> ingredientMap;
	int currentPizzaRotation;
	int currentScore;
	int highScore;
};