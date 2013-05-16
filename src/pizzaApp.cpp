#include "pizzaApp.h"

void pizzaApp::setup()
{
	ofSetWindowPosition(30, 100);

	pizzaBackground = new PizzaImage("images/pizzaEmpty.png");
	pizzaSlice = new PizzaImage("images/pizzaSlice.png");
	pizzaFront = new PizzaImage("images/pizzaFront.png");
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

	for(auto iterator = participants.begin(); iterator != participants.end(); ++iterator)
		delete (*iterator).second;
	participants.clear();
}

void pizzaApp::update()
{
	GlobalValues::getInstance().update();

	for(auto iterator = participants.begin(); iterator != participants.end(); ++iterator)
		(*iterator).second->update();
}

void pizzaApp::draw()
{
	ofEnableAlphaBlending();
	pizzaBackground->draw();
	pizzaSlice->draw(GlobalValues::getInstance().getCurrentPizzaRotation());
	pizzaFront->draw();

	for(auto iterator = participants.begin(); iterator != participants.end(); ++iterator)
		(*iterator).second->draw();

	ofDisableAlphaBlending();
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
		if(ofVec2f(participant->getPosition().x - x, participant->getPosition().y - y).length() < GlobalValues::DEBUG_PARTICIPANT_RADIUS)
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