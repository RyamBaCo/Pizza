#pragma once
#include "ofMain.h"
#include "PizzaImage.h"
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

	static const int PIZZA_BASE_ROTATION_SPEED = 20;
	static const int PIZZA_ROTATION_SPEED_PER_SCORE = 50;
	// when set to zero no rotation changes
	static const int PIZZA_MIN_ANGLE_FOR_ROTATION_CHANGE = 200;
	static const int PIZZA_MAX_ANGLE_FOR_ROTATION_CHANGE = 600;

	static const ofPoint PIZZA_CENTER_POINT;
	static const int PIZZA_RADIUS = 260;
	static const int PIZZA_INNER_RADIUS = 90;
	static const int SLICE_ANGLE = 45;
	static const int MAX_POINTS_FOR_DIRECTION = 15;
	static const int MIN_DISTANCE_FOR_DIRECTION = 3;
	static const int INGREDIENT_DROP_RANGE = 200;
	static const int HUD_DISTANCE = 50;
	static const int MIN_FREE_SLOTS = 2;
	static const int START_FREE_SLOTS = 3;
	static const int MAX_FREE_SLOTS = 6;

	static const std::string ANIMATION_FIRE;
	static const std::string ANIMATION_GAIN_SLOT;
	static const std::string ANIMATION_INGREDIENTS_EXPLOSION;
	static const std::string ANIMATION_INCREASE_SCORE;
	static const std::string ANIMATION_NEW_HIGHSCORE;
	static const std::string ANIMATION_INGREDIENTS_SPAWN;
	static const std::string ANIMATION_LOSE_SLOT;

	static const int ANIMATION_INGREDIENTS_FADEOUT_SPEED = 500;
	static const int ANIMATION_INGREDIENTS_EXPLOSION_SPEED = 50;
	static const int ANIMATION_INGREDIENTS_SPAWN_SPEED = 50;
	static const int ANIMATION_INCREASE_SCORE_SPEED = 50;
	static const int ANIMATION_NEW_HIGHSCORE_SPEED = 50;
	static const int ANIMATION_LOSE_SLOT_SPEED = 50;
	static const int ANIMATION_GAIN_SLOT_SPEED = 70;
	static const int ANIMATION_FIRE_SPEED = 50;

	#pragma region IngredientTypes

	enum IngredientType
	{
		CHEESE = 0,
		EGG,
		PAPRIKA,
		PINEAPPLE,
		TOMATO,
		BACON,
		CORN,
		MUSHROOM,
		ONIONS,
		SALAMI,
		LAST
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
	void cleanUp();

	IngredientValues getValuesForIngredient(const IngredientType& type);
	std::vector<PizzaImage*> getAnimationImages(std::string animationName);
	int getCurrentPizzaRotation() const;
	int getHighScore() const;
	int getCurrentScore() const;
	void increaseCurrentScore();
	void initSliceAnimations();

	// returns true if a new round has been started
	bool updatePizzaRotation(int deltaTime);

private:
	GlobalValues();
	GlobalValues(GlobalValues const&);
	void operator=(GlobalValues const&);

private:
	std::map<IngredientType, IngredientValues> ingredientMap;
	std::map<std::string, std::vector<PizzaImage*> > animationImages;
	float currentPizzaRotation;
	float absoluteRotation;
	float rotationForChange;
	bool rotatingClockwise;
	int currentScore;
	int lastScore;
	int highScore;
};