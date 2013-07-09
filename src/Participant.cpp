#include "Participant.h"
#include "HelperFunctions.h"
#include "AnimationManager.h"
#include "FadeOutAnimation.h"
#include "SpriteAnimation.h"

Participant::Participant()
	:	position(-1, -1),
		baseIngredient(0),
		hud(new ParticipantHUD()),
		punished(false),
		punishedInRound(false)
{
}

Participant::~Participant()
{
	if(hasIngredient())
	{
		delete baseIngredient;
		baseIngredient = 0;
	}

	if(hud != 0)
	{
		delete hud;
		hud = 0;
	}

	for(auto iterator = ingredients.begin(); iterator != ingredients.end(); ++iterator)
		delete *iterator;
	ingredients.clear();
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

		if(	freeSlots > 0 &&
			(	ingredients.empty() ||
				(position - ingredients.back()->getPosition()).length() >= GlobalValues::INGREDIENT_DROP_RANGE))
		{
			dropIngredient();
			--freeSlots;
		}
	}

	if(lastPoints.size() > 0)
	{
		ofPoint averageDirection(0, 0);
		for(auto iterator = lastPoints.begin(); iterator != lastPoints.end(); ++iterator)
			averageDirection += *iterator;
		averageDirection /= lastPoints.size();
		frontDirection = (position - averageDirection).normalize();
	}
	
	lastPoints.push_back(position);
	if(lastPoints.size() > GlobalValues::MAX_POINTS_FOR_DIRECTION)
		lastPoints.pop_front();
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
	dropIngredient();

	freeSlots = GlobalValues::START_FREE_SLOTS;
	availableSlots = GlobalValues::START_FREE_SLOTS;
}

void Participant::dropIngredient()
{
	AnimationManager::addAnimation(new SpriteAnimation(GlobalValues::ANIMATION_INGREDIENTS_SPAWN, GlobalValues::ANIMATION_INGREDIENTS_SPAWN_SPEED, position - ofPoint(45 - 80 / 2, 40 - 67 / 2), 0));
	baseIngredient->setRotation(ofRandom(0, 360));
	ingredients.push_back(new Ingredient(baseIngredient->getType()));
	ingredients.back()->setPosition(position);
	ingredients.back()->setRotation(baseIngredient->getRotation());
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

void Participant::roundComplete()
{
	if(!hasIngredient())
		return;

	if(!punishedInRound)
	{
		++availableSlots;
		if(availableSlots > GlobalValues::MAX_FREE_SLOTS)
			availableSlots = GlobalValues::MAX_FREE_SLOTS;
		else
			for(int i = 0; i < availableSlots; ++i)
			{
				ofPoint frontVector(frontDirection * 80);
				ofPoint hudVector = hud->getHUDPosition(i) + ofPoint(0, 70);
				float originalAngle = atan2(frontDirection.y, frontDirection.x);
				float angle = originalAngle + 3.14159f / 2;
				ofPoint finalPosition = position - 
					(frontVector + ofPoint(hudVector.x * cos(angle) - hudVector.y * sin(angle), hudVector.x * sin(angle) + hudVector.y * cos(angle)))
					+ 160 * ofPoint(cos(atan2(frontDirection.y, frontDirection.x)), sin(atan2(frontDirection.y, frontDirection.x)));

				AnimationManager::addAnimation(new SpriteAnimation(GlobalValues::ANIMATION_GAIN_SLOT, GlobalValues::ANIMATION_GAIN_SLOT_SPEED, finalPosition, ofRadToDeg(angle)));
			}
	}

	freeSlots = availableSlots;
	punishedInRound = false;
}

void Participant::update()
{
	if(!punished && HelperFunctions::isPositionInSlice(position))
	{
		punished = true;

		--availableSlots;
		if(availableSlots < GlobalValues::MIN_FREE_SLOTS)
			availableSlots = GlobalValues::MIN_FREE_SLOTS;
		else
			for(int i = availableSlots; i < 6; ++i)
			{
				ofPoint frontVector(frontDirection * 80);
				ofPoint hudVector = hud->getHUDPosition(i);
				float originalAngle = atan2(frontDirection.y, frontDirection.x);
				float angle = originalAngle + 3.14159f / 2;
				ofPoint finalPosition = position - 
					(frontVector + ofPoint(hudVector.x * cos(angle) - hudVector.y * sin(angle), hudVector.x * sin(angle) + hudVector.y * cos(angle)))
					+ 160 * ofPoint(cos(atan2(frontDirection.y, frontDirection.x)), sin(atan2(frontDirection.y, frontDirection.x)));

				AnimationManager::addAnimation(new SpriteAnimation(GlobalValues::ANIMATION_LOSE_SLOT, GlobalValues::ANIMATION_LOSE_SLOT_SPEED, finalPosition, ofRadToDeg(angle)));
			}
		if(availableSlots > freeSlots)
			freeSlots = availableSlots;

		punishedInRound = true;
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
	HelperFunctions::isPositionInSlice(position) ? ofSetColor(100, 100, 100) : ofSetColor(255, 0, 0);
	ofCircle(position, GlobalValues::DEBUG_PARTICIPANT_RADIUS);
	ofCircle(position + frontDirection * GlobalValues::DEBUG_PARTICIPANT_DIRECTION_RADIUS, GlobalValues::DEBUG_PARTICIPANT_DIRECTION_RADIUS);
	ofSetColor(255, 255, 255);
#endif

	if(hasIngredient())
	{
		baseIngredient->draw();
		hud->draw(position + frontDirection * GlobalValues::HUD_DISTANCE, ofRadToDeg(atan2(frontDirection.y, frontDirection.x)) + 90, freeSlots, availableSlots);
	}

	for(auto iterator = ingredients.begin(); iterator != ingredients.end(); ++iterator)
		(*iterator)->draw();

	return true;
}
