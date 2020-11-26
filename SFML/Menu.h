#pragma once
#include "SFML/Graphics.hpp"

class Menu
{
private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[3];
public:
	Menu(float width, float height);
	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int selectedItemIndexReturn();
	
};

