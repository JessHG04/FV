#include "MenuSeleccionPersonaje.h"

MenuSeleccionPersonaje::MenuSeleccionPersonaje(float width, float height){
	if (!font.loadFromFile("darkforest.ttf"))
	{
        //ERROR
	}

	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Yellow);
	menu[0].setString("Mercedes");
	menu[0].setPosition(sf::Vector2f(width - 170, 270));
	menu[0].setCharacterSize(35);

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("Eugyn");
	menu[1].setPosition(sf::Vector2f(width + 200, 270));
	menu[1].setCharacterSize(30);

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::White);
	menu[2].setString("Volver");
	menu[2].setPosition(sf::Vector2f(width + 50, 600));
	menu[2].setCharacterSize(20);

	selectedItemIndex = 0;
}


MenuSeleccionPersonaje::~MenuSeleccionPersonaje(){
}

void MenuSeleccionPersonaje::draw(sf::RenderWindow &window){
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void MenuSeleccionPersonaje::MoveUp()
{
	if (selectedItemIndex == 1){
		menu[selectedItemIndex].setColor(sf::Color::White);
		menu[selectedItemIndex].setCharacterSize(30);
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(sf::Color::Yellow);
		menu[selectedItemIndex].setCharacterSize(35);
	}
}

void MenuSeleccionPersonaje::MoveDown()
{
	if (selectedItemIndex == 0){
		menu[selectedItemIndex].setColor(sf::Color::White);
		menu[selectedItemIndex].setCharacterSize(30);
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(sf::Color::Yellow);
		menu[selectedItemIndex].setCharacterSize(35);
	}
}

void MenuSeleccionPersonaje::MoveRight(){
	menu[selectedItemIndex].setColor(sf::Color::White);
	menu[selectedItemIndex].setCharacterSize(30);
	selectedItemIndex = 2;
	menu[selectedItemIndex].setColor(sf::Color::Yellow);
	menu[selectedItemIndex].setCharacterSize(25);
}

void MenuSeleccionPersonaje::MoveLeft(){
	menu[selectedItemIndex].setColor(sf::Color::White);
	menu[selectedItemIndex].setCharacterSize(20);
	selectedItemIndex = 0;
	menu[selectedItemIndex].setColor(sf::Color::Yellow);
	menu[selectedItemIndex].setCharacterSize(35);
}
