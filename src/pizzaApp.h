#pragma once
#include <map>
#include "ofMain.h"
#include "PizzaImage.h"
#include "Participant.h"
#include "ofxOsc.h"

class pizzaApp 
	: public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	void exit();
		
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

private:
	std::map<int, Participant*> participants;

	PizzaImage* pizzaBackground;
	PizzaImage* pizzaSlice;
	PizzaImage* pizzaFront;
	PizzaImage* pizzaCenter;

	ofTrueTypeFont highScoreFont;
	ofTrueTypeFont currentScoreFont;

	unsigned long long lastElapsedMillis;
	ofxOscReceiver receiver;
};
