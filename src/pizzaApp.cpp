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
}

void pizzaApp::update()
{
}

void pizzaApp::draw()
{
	ofEnableAlphaBlending();
	pizzaBackground->draw();
	pizzaSlice->draw(ofGetFrameNum());
	pizzaFront->draw();
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