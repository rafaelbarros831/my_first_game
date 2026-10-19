#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class ControlNave {
public:

	float posiNaviX = 0.0f;
	float posiNaviY = 100.0f;

	void Movimento() {

		if (Keyboard::isKeyPressed(Keyboard::Key::D) && posiNaviX < 350.0f) posiNaviX += 0.08f;

		if (Keyboard::isKeyPressed(Keyboard::Key::A) && posiNaviX > -15.0f) posiNaviX -= 0.08f;

		if (Keyboard::isKeyPressed(Keyboard::Key::W) && posiNaviY > -45.0f) posiNaviY -= 0.08f;

		if (Keyboard::isKeyPressed(Keyboard::Key::S) && posiNaviY < 175.0f) posiNaviY += 0.08f;
	}

};