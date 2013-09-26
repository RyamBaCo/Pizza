#include "AnimationManager.h"

std::list<BaseAnimation*> AnimationManager::animations;

AnimationManager::AnimationManager()
{
}

AnimationManager::~AnimationManager()
{
}

BaseAnimation* AnimationManager::getAnimationAt(int index)
{
	int currentIndex = 0;

	for(auto iterator = animations.begin(); iterator != animations.end(); ++iterator)
	{
		if(currentIndex == index)
			return *iterator;
		++currentIndex;
	}

	return 0;
}

int AnimationManager::getAnimationCount()
{
	return animations.size();
}

void AnimationManager::addAnimation(BaseAnimation* animation)
{
	animations.push_back(animation);
}

void AnimationManager::update(int deltaTime)
{
	for(auto iterator = animations.begin(); iterator != animations.end();)
	{
		if((*iterator)->isReadyForDelete())
		{
			delete *iterator;
			iterator = animations.erase(iterator);
		}
		else
		{
			(*iterator)->update(deltaTime);
			++iterator;
		}
	}
}

void AnimationManager::draw()
{
	for(auto iterator = animations.begin(); iterator != animations.end(); ++iterator)
		(*iterator)->draw();
}

void AnimationManager::cleanUp()
{
	for(auto iterator = animations.begin(); iterator != animations.end(); ++iterator)
		delete *iterator;

	animations.clear();
}
