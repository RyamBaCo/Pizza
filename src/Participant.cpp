#include "Participant.h"

Participant::Participant()
	:	position(-1, -1)
{
}

Participant::~Participant()
{
	removeIngredients();
}

void Participant::setPosition(const ofPoint& position)
{
	this->position = position;

	int distanceToCenter = ofVec2f(this->position.x - GlobalValues::PIZZA_CENTER_POINT.x, this->position.y - GlobalValues::PIZZA_CENTER_POINT.y).length();

	if(		distanceToCenter < GlobalValues::PIZZA_RADIUS
		&&	!hasIngredients())
		createIngredients();
	else if(distanceToCenter > GlobalValues::PIZZA_RADIUS
		&&	hasIngredients())
		removeIngredients();
}

ofPoint Participant::getPosition() const
{
	return position;
}

bool Participant::hasIngredients() const
{
	return ingredients.size() > 0;
}

void Participant::createIngredients()
{
	ingredients.push_back(new Ingredient(static_cast<GlobalValues::IngredientType>((int)ofRandom(0, 5))));
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
	ofCircle(position, GlobalValues::DEBUG_PARTICIPANT_RADIUS);
#endif

	for(auto iterator = ingredients.begin(); iterator != ingredients.end(); ++iterator)
		(*iterator)->draw(position);

	return true;
}