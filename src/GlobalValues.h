#pragma once
#include "ofMain.h"
#include <map>
#include <string>

class GlobalValues
{
public:

#if _DEBUG
	static const int DEBUG_PARTICIPANT_RADIUS = 20;
#endif

	static const ofPoint PIZZA_CENTER_POINT;
	static const int PIZZA_RADIUS = 350;
	static const int SLICE_ANGLE = 45;

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
		std::string soundDestination;

		IngredientValues()
		{
		}

		IngredientValues(const std::string& graphicDestination, const std::string& soundDestination)
			:	graphicDestination(graphicDestination),
				soundDestination(soundDestination)
		{
		}
	};

	#pragma endregion IngredientTypes

	static GlobalValues& getInstance();

	IngredientValues getValuesForIngredient(const IngredientType& type);
	int getCurrentPizzaRotation() const;

	void update();

private:
	GlobalValues();
	GlobalValues(GlobalValues const&);
	void operator=(GlobalValues const&);

private:
	std::map<IngredientType, IngredientValues> ingredientMap;
	int currentPizzaRotation;
};