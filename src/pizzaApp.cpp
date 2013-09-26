#include "pizzaApp.h"
#include "AnimationManager.h"

void pizzaApp::setup()
{
	receiver.setup(10000);

	ofEnableAlphaBlending();
	ofSetWindowPosition(30, 100);
	ofBackground(0, 0, 0);

	pizzaBackground = new PizzaImage("images/pizzaEmpty.png");
	pizzaSlice = new PizzaImage("images/pizzaSlice.png");
	pizzaFront = new PizzaImage("images/pizzaFront.png");
	pizzaCenter = new PizzaImage("images/pizzaCenter.png");
	image1 = new PizzaImage("images/1.png");
	image2 = new PizzaImage("images/2.png");
	image3 = new PizzaImage("images/3.png");
	imageGo = new PizzaImage("images/go.png");

	ofTrueTypeFont::setGlobalDpi(72);
	highScoreFont.loadFont("Arcade Book.ttf", 90, true, true);
	currentScoreFont.loadFont("Arcade Book.ttf", 50, true, true);
	GlobalValues::getInstance().initSliceAnimations();

	backSound.loadSound("sounds/00-back.wav");
	backSound.setLoop(true);
	backSound.play();

	lastElapsedMillis = ofGetElapsedTimeMillis();
	playersInGameLastRound = false;
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

	if(image1 != 0)
	{
		delete image1;
		image1 = 0;
	}

	if(image2 != 0)
	{
		delete image2;
		image2 = 0;
	}

	if(image3 != 0)
	{
		delete image3;
		image3 = 0;
	}

	if(imageGo != 0)
	{
		delete imageGo;
		imageGo = 0;
	}

	for(auto iterator = participants.begin(); iterator != participants.end(); ++iterator)
		delete (*iterator).second;
	participants.clear();

	AnimationManager::cleanUp();
	GlobalValues::getInstance().cleanUp();

	backSound.unloadSound();
}

void pizzaApp::update()
{
	unsigned long long currentElapsedMillis = ofGetElapsedTimeMillis();
	int deltaTime = currentElapsedMillis - lastElapsedMillis;
	lastElapsedMillis = currentElapsedMillis;

	while(receiver.hasWaitingMessages())
	{
		ofxOscMessage message;
		receiver.getNextMessage(&message);
		std::vector<int> idsFound;
		if (message.getNumArgs() > 1)
		{
			for (int i = 0; i < message.getNumArgs(); i += 5)
			{
				int id = message.getArgAsInt32(i);
				idsFound.push_back(id);

				Participant* participant;
				if  (participants.find(id) == participants.end())
					participants[id] = new Participant();

				participants[id]->setPosition(
					ofPoint(message.getArgAsFloat(i + 1) * ofGetWindowSize().x, 
					message.getArgAsFloat(i + 2) * ofGetWindowSize().y)
					);
			}
		}

		// reset old inputs that are no longer visible
		vector<int> idsToDelete;
		for (auto it = participants.begin(); it != participants.end(); ++it)
			// check if id is not in ids add to delete list
			if (std::find(idsFound.begin(), idsFound.end(), it->first) == idsFound.end())
				idsToDelete.push_back(it->first);

		for (vector<int>::iterator it = idsToDelete.begin(); it != idsToDelete.end(); ++it)
			participants.erase(participants.find(*it));
	}

	if(!GlobalValues::getInstance().isGameStopped())
	{
		GlobalValues::getInstance().updatePizzaRotation(deltaTime);
		for(auto iterator = participants.begin(); iterator != participants.end(); ++iterator)
			(*iterator).second->update();
	}
	
	AnimationManager::update(deltaTime);

	bool playersInGame = false;
	for(auto iterator = participants.begin(); iterator != participants.end(); ++iterator)
		if((*iterator).second->hasIngredient())
			playersInGame = true;

	if(!playersInGame)
	{
		GlobalValues::getInstance().resetCurrentScore();
		GlobalValues::getInstance().startGame();
		timeForCountdown = 0;
	}

	if(playersInGame && !playersInGameLastRound)
		GlobalValues::getInstance().stopGame();

	playersInGameLastRound = playersInGame;

	if(GlobalValues::getInstance().isGameStopped())// && AnimationManager::getAnimationCount() <= 10)
	{
		timeForCountdown += deltaTime;
		if(timeForCountdown >= 4000)
		{
			GlobalValues::getInstance().resetCurrentScore();
			GlobalValues::getInstance().startGame();
			timeForCountdown = 0;
		}
	}
}

void pizzaApp::draw()
{
	pizzaBackground->draw();
//	pizzaSlice->draw(GlobalValues::getInstance().getCurrentPizzaRotation());
	pizzaFront->draw();
	pizzaCenter->draw();

	int highScore = GlobalValues::getInstance().getHighScore();
	int currentScore = GlobalValues::getInstance().getCurrentScore();
	highScoreFont.drawString(ofToString(highScore), GlobalValues::PIZZA_CENTER_POINT.x - (highScore >= 10 ? 35 : 15), GlobalValues::PIZZA_CENTER_POINT.y - 10);
	currentScoreFont.drawString(ofToString(currentScore), GlobalValues::PIZZA_CENTER_POINT.x - (currentScore >= 10 ? 25 : 15), GlobalValues::PIZZA_CENTER_POINT.y + 40);

	for(auto iterator = participants.begin(); iterator != participants.end(); ++iterator)
		(*iterator).second->draw();

	if(timeForCountdown > 3000)
		imageGo->draw();
	else if(timeForCountdown > 2000)
		image3->draw();
	else if(timeForCountdown > 1000)
		image2->draw();
	else if(timeForCountdown > 0)
		image1->draw();

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