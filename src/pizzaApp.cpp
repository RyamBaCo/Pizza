#include "pizzaApp.h"
#include "AnimationManager.h"

void pizzaApp::setup()
{
	ofEnableAlphaBlending();
	ofSetWindowPosition(30, 100);

	pizzaBackground = new PizzaImage("images/pizzaEmpty.png");
	pizzaSlice = new PizzaImage("images/pizzaSlice.png");
	pizzaFront = new PizzaImage("images/pizzaFront.png");
	pizzaCenter = new PizzaImage("images/pizzaCenter.png");

	ofTrueTypeFont::setGlobalDpi(72);
	highScoreFont.loadFont("Arcade Book.ttf", 100, true, true);
	currentScoreFont.loadFont("Arcade Book.ttf", 60, true, true);

	lastElapsedMillis = ofGetElapsedTimeMillis();
}

void pizzaApp::exit()
{
	if(pizzaBackground != 0)
	{
		delete pizzaBackground;
		pizzaBackground = 0;
	}

	if(pizzaSlice != 0)
	{
		delete pizzaSlice;
		pizzaSlice = 0;
	}

	if(pizzaFront != 0)
	{
		delete pizzaFront;
		pizzaFront = 0;
	}

	if(pizzaCenter != 0)
	{
		delete pizzaCenter;
		pizzaCenter = 0;
	}

	for(auto iterator = participants.begin(); iterator != participants.end(); ++iterator)
		delete (*iterator).second;
	participants.clear();

	AnimationManager::cleanUp();
}

void pizzaApp::update()
{
	unsigned long long currentElapsedMillis = ofGetElapsedTimeMillis();
	int deltaTime = currentElapsedMillis - lastElapsedMillis;
	lastElapsedMillis = currentElapsedMillis;

	bool newRound = GlobalValues::getInstance().updatePizzaRotation(deltaTime);

	for(auto iterator = participants.begin(); iterator != participants.end(); ++iterator)
	{
		if(newRound)
			(*iterator).second->roundComplete();
		(*iterator).second->update();
	}

	AnimationManager::update(deltaTime);
}

void pizzaApp::draw()
{
	pizzaBackground->draw();
	pizzaSlice->draw(GlobalValues::getInstance().getCurrentPizzaRotation());
	pizzaFront->draw();
	pizzaCenter->draw();

	highScoreFont.drawString(ofToString(GlobalValues::getInstance().getHighScore()), ofGetWindowWidth() / 2 - 15, ofGetWindowHeight() / 2 - 10);
	currentScoreFont.drawString(ofToString(GlobalValues::getInstance().getCurrentScore()), ofGetWindowWidth() / 2 - 15, ofGetWindowHeight() / 2 + 50);

	for(auto iterator = participants.begin(); iterator != participants.end(); ++iterator)
		(*iterator).second->draw();

	AnimationManager::draw();
}

void pizzaApp::keyPressed(int key)
{
#if _DEBUG
	if(key == ' ')
	{
		static int id = 0;
		++id;
		Participant* newParticipant = new Participant();
		newParticipant->setPosition(ofPoint(ofRandom(GlobalValues::DEBUG_PARTICIPANT_RADIUS, ofGetWindowWidth() - GlobalValues::DEBUG_PARTICIPANT_RADIUS), GlobalValues::DEBUG_PARTICIPANT_RADIUS));
		participants.insert(std::pair<int, Participant*>(id, newParticipant));
	}
#endif
}

void pizzaApp::keyReleased(int key)
{
}

void pizzaApp::mouseMoved(int x, int y)
{
}

void pizzaApp::mouseDragged(int x, int y, int button)
{
#if _DEBUG
	for(auto iterator = participants.begin(); iterator != participants.end(); ++iterator)
	{
		Participant* participant = (*iterator).second;
		if(ofVec2f(participant->getPosition().x - x, participant->getPosition().y - y).length() < GlobalValues::DEBUG_PARTICIPANT_RADIUS * 2)
		{
			participant->setPosition(ofPoint(x, y));
			return;
		}
	}
#endif
}

void pizzaApp::mousePressed(int x, int y, int button)
{
}

void pizzaApp::mouseReleased(int x, int y, int button)
{
}

void pizzaApp::windowResized(int w, int h)
{
}

void pizzaApp::gotMessage(ofMessage msg)
{
}

void pizzaApp::dragEvent(ofDragInfo dragInfo)
{
}