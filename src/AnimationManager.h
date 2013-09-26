#pragma once
#include "BaseAnimation.h"
#include <list>

class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();

	static BaseAnimation* getAnimationAt(int index);
	static int getAnimationCount();

	static void addAnimation(BaseAnimation* animation);
	static void update(int deltaTime);
	static void draw();

	static void cleanUp();

private:
	static std::list<BaseAnimation*> animations;
};

