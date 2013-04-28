#include "pizzaApp.h"

void pizzaApp::setup()
{
	pizzaBackground.loadImage("images/pizzaEmpty.png");
	pizzaSlice.loadImage("images/pizzaSlice.png");
	pizzaFront.loadImage("images/pizzaFront.png");
}

void pizzaApp::update()
{
}

void pizzaApp::draw()
{
	ofEnableAlphaBlending();
	pizzaBackground.draw(0, 0);

	ofPushMatrix();
		ofTranslate(pizzaSlice.width / 2, pizzaSlice.height / 2, 0);
		ofRotate(ofGetFrameNum() * .1, 0, 0, 1);
		ofTranslate(-pizzaSlice.width / 2, -pizzaSlice.height / 2, 0);
		pizzaSlice.draw(0, 0);
	ofPopMatrix();

	pizzaFront.draw(0, 0);
	ofDisableAlphaBlending();
}

void pizzaApp::keyPressed(int key)
{
}

void pizzaApp::keyReleased(int key)
{
}

void pizzaApp::mouseMoved(int x, int y)
{
}

void pizzaApp::mouseDragged(int x, int y, int button)
{
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