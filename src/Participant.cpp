#include "Participant.h"
#include "HelperFunctions.h"

Participant::Participant()
	:	position(-1, -1),
		baseIngredient(0)
{
}

Participant::~Participant()
{
	if(hasIngredient())
	{
		delete baseIngredient;
		baseIngredient = 0;
	}

	removeIngredients();
}

void Participant::setPosition(const ofPoint& position)
{
	this->position = position;

	int distanceToCenter = ofVec2f(this->position.x - GlobalValues::PIZZA_CENTER_POINT.x, this->position.y - GlobalValues::PIZZA_CENTER_POINT.y).length();

	if(		distanceToCenter < GlobalValues::PIZZA_RADIUS
		&&	!hasIngredient())
		resetIngredients();
	else if(distanceToCenter > GlobalValues::PIZZA_RADIUS
		&&	hasIngredient())
		removeIngredients();

	// TODO refactor, position is stored twice
	if(hasIngredient())
		baseIngredient->setPosition(position);
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

	baseIngredient = new Ingredient(static_cast<GlobalValues::IngredientType>((int)ofRandom(0, 5)));
	ingredients.push_back(new Ingredient(baseIngredient->getType(), position));
}

void Participant::removeIngredients()
{
	for(auto iterator = ingredients.begin(); iterator != ingredients.end(); ++iterator)
		delete *iterator;
	ingredients.clear();
}

void Participant::update()
{
	// TODO put this in observer pattern or something
	for(auto iterator = ingredients.begin(); iterator != ingredients.end(); ++iterator)
		(*iterator)->update();
}

bool Participant::draw()
{
#if _DEBUG
	HelperFunctions::isPositionInSlice(position) ? ofSetColor(100, 100, 100) : ofSetColor(255, 0, 0);
	ofCircle(position, GlobalValues::DEBUG_PARTICIPANT_RADIUS);
	ofSetColor(255, 255, 255);
#endif

	if(hasIngredient())
		baseIngredient->draw();

	for(auto iterator = ingredients.begin(); iterator != ingredients.end(); ++iterator)
		(*iterator)->draw();

	return true;
}