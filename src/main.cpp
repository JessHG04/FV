#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "include/config.h"
#include "ej_modulos/Menu.h"
#include "ej_modulos/Juego.h"
#include "ej_modulos/Jugador.h"

int main() {
	sf::RenderWindow *window;
	window = new sf::RenderWindow(sf::VideoMode(960,640),"Gremory Hole");

	Menu menu(400, 700);
	sf::Font font;
	sf::Texture fondo;

	if (!fondo.loadFromFile("menufondo.jpg"))
	{
		// handle error
	}

	sf::Sprite fondito;
	fondito.setTexture(fondo);

	if (!font.loadFromFile("arial.ttf"))
	{
		// handle error
	}

	sf::Music musicaMenu;
	
	if (!musicaMenu.openFromFile("menucancion.ogg"))
	{
		// handle error
	}

	musicaMenu.play();
	musicaMenu.setPlayingOffset(sf::seconds(2));
	musicaMenu.setVolume(25);

	//TITULO DEL JUEGO
	sf::Text text;
	text.setFont(font);
	text.setString("GREMORY HOLE");
	text.setColor(sf::Color::Blue);
	text.setCharacterSize(45);
	text.setPosition(sf::Vector2f(300 / 6, 200 / 10));
	bool entra = false;

	while (window->isOpen()){
		sf::Event event;

		while (window->pollEvent(event)){
			switch (event.type){
			case sf::Event::KeyReleased:
				switch (event.key.code){
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem()){
					case 0:
						std::cout << "Jugar ha sido seleccionado" << std::endl;
						entra = true;
						break;
					case 1:
						window->close();
						break;
					}

					break;
				}

				break;

			case sf::Event::Closed:
				window->close();

				break;

			}
		}

		window->clear();
		window->draw(fondito);
		window->draw(text);
		menu.draw(*window);
		window->display();

		if(entra == true){
			window->clear();
			Juego *juego = new Juego(sf::Vector2u(960,640), window);
		}
			
	}

	//Juego *juego = new Juego(sf::Vector2u(960,640));

 return 0;
}
