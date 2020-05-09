#include "Menu.h"

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("darkforest.ttf"))
	{
		// handle error
	}

	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Yellow);
	menu[0].setString("Empezar partida");
	menu[0].setPosition(sf::Vector2f(width -20, height / (MAX_NUMBER_OF_ITEMS + 2) * 2));
	menu[0].setCharacterSize(35);

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("Salir");
	menu[1].setPosition(sf::Vector2f(width + 50, height / (MAX_NUMBER_OF_ITEMS + 5) * 4));
	menu[1].setCharacterSize(30);

	selectedItemIndex = 0;
}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		menu[selectedItemIndex].setCharacterSize(30);
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(sf::Color::Yellow);
		menu[selectedItemIndex].setCharacterSize(35);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		menu[selectedItemIndex].setCharacterSize(30);
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(sf::Color::Yellow);
		menu[selectedItemIndex].setCharacterSize(35);
	}
}
