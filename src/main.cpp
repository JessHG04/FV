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

	if (!fondo.loadFromFile("menufondo.png"))
	{
    std::cout << "Error cargando imagen de fondo de menú" << std::endl;
	}

	sf::Sprite fondito;
	fondito.setTexture(fondo);
	fondito.setScale(1.4,1.4);

	if (!font.loadFromFile("darkforest.ttf"))
	{
		std::cout << "Error cargando la fuente del menu" << std::endl;
	}

	sf::Music musicaMenu;
	
	if (!musicaMenu.openFromFile("menucancion.ogg"))
	{
		std::cout << "Error cargando sonido de fondo de menú" << std::endl;
	}

	musicaMenu.play();
	musicaMenu.setPlayingOffset(sf::seconds(2));
	musicaMenu.setVolume(25);

	//TITULO DEL JUEGO
	sf::Text text;
	text.setFont(font);
	text.setString("GREMORY HOLE");
	text.setColor(sf::Color::White);
	text.setCharacterSize(120);
	text.setPosition(sf::Vector2f(130, 200 / 10));

	//Empresa
	sf::Text empresa;
	empresa.setFont(font);
	empresa.setString(" © Doubtful Machine");
	empresa.setColor(sf::Color::White);
	empresa.setCharacterSize(20);
	empresa.setPosition(sf::Vector2f(10, 600));
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
		window->draw(empresa);
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
