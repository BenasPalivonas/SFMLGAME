#include "Menu.h"

Menu::Menu(float width, float height)
{
	font.loadFromFile("BIGJOHN.otf");
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(width / 2, height / 3));
	menu[0].setCharacterSize(100);
	
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Exit");
	menu[1].setPosition(sf::Vector2f(width / 2, height / 3 *2));
	menu[1].setCharacterSize(100);
	selectedItemIndex = 0;



}
void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < 2; i++) {
		window.draw(menu[i]);
	}
}
void Menu::MoveUp() {
	if (selectedItemIndex == 1 ) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}
void Menu::MoveDown() {
	if (selectedItemIndex == 0) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}

}
	int Menu::selectedItemIndexReturn() {
		return selectedItemIndex;
	}

