#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "include/config.h"
#include "ej_modulos/Menu.h"
#include "ej_modulos/MenuSeleccionPersonaje.h"
#include "ej_modulos/Juego.h"
#include "ej_modulos/Jugador.h"

int main() {
	sf::RenderWindow *window;
	window = new sf::RenderWindow(sf::VideoMode(960,640),"Gremory Hole");

	Menu menu(400, 700);
	MenuSeleccionPersonaje menu2(400, 700);

	sf::Font font;
	sf::Texture fondo;
	sf::Texture fondo2;

	if (!fondo.loadFromFile("menufondo.png")){
    	std::cout << "Error cargando imagen de fondo de menú" << std::endl;
	}

	if (!fondo2.loadFromFile("resources/controles.png")){
    	std::cout << "Error cargando imagen de fondo de menú" << std::endl;
	}

	sf::Sprite fondito;
	sf::Sprite fondito2;
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
	musicaMenu.setVolume(35);

	//TITULO DEL JUEGO
	sf::Text text;
	text.setFont(font);

	//Empresa
	sf::Text empresa;
	empresa.setFont(font);
	empresa.setString("Doubtful Machine");
	empresa.setColor(sf::Color::White);
	empresa.setCharacterSize(20);
	empresa.setPosition(sf::Vector2f(10, 600));

	//Descripcion personajes
	sf::Text desMercedes;
	sf::Text desEugyn;

	//Mercedes
	desMercedes.setFont(font);
	desMercedes.setString("Clase guerrera de Bardomur: \n\n- Vidas x 5 \n\n- Menos velocidad \n\n- Ataque a melé");
	desMercedes.setColor(sf::Color::White);
	desMercedes.setCharacterSize(20);
	desMercedes.setPosition(sf::Vector2f(200, 330));

	//Eugyn
	desEugyn.setFont(font);
	desEugyn.setString("Clase mago del clan oscuro: \n\n- Vidas x 3 \n\n- Mas velocidad \n\n- Ataque a distancia");
	desEugyn.setColor(sf::Color::White);
	desEugyn.setCharacterSize(20);
	desEugyn.setPosition(sf::Vector2f(550, 330));

	//Imagenes personajes
	sf::Texture mercedeTexture;
	sf::Texture eugynTexture;

	if(!mercedeTexture.loadFromFile("resources/Sprites/Merche/100.png")){
        //ERROR
	}

	if(!eugynTexture.loadFromFile("resources/Sprites/Eugyn/100.png")){
        //ERROR
	}

	sf::Sprite mercede(mercedeTexture);
	sf::Sprite eugyn(eugynTexture);
	mercede.setPosition(200, 150);
	eugyn.setPosition(550 ,150);
	mercede.setScale(3, 3);
	eugyn.setScale(3, 3);

	//Controles textos
	sf::Text mover;
	sf::Text saltar;
	sf::Text atacar;
	sf::Text dash;
	sf::Text mutear;
	sf::Text desmutear;
	sf::Text hablar;
	sf::Text volver;

	dash.setFont(font);
	mover.setFont(font);
	saltar.setFont(font);
	hablar.setFont(font);
	mutear.setFont(font);
	desmutear.setFont(font);
	atacar.setFont(font);
	volver.setFont(font);

	dash.setString("Dash");
	mover.setString("Moverse");
	saltar.setString("Saltar");
	hablar.setString("Interactuar");
	mutear.setString("Desactivar musica");
	desmutear.setString("Activar musica");
	atacar.setString("Atacar");
	volver.setString("Volver");

	dash.setColor(sf::Color::White);
	mover.setColor(sf::Color::White);
	saltar.setColor(sf::Color::White);
	hablar.setColor(sf::Color::White);
	mutear.setColor(sf::Color::White);
	desmutear.setColor(sf::Color::White);
	atacar.setColor(sf::Color::White);
	volver.setColor(sf::Color::Yellow);

	dash.setCharacterSize(20);
	mover.setCharacterSize(20);
	saltar.setCharacterSize(20);
	hablar.setCharacterSize(20);
	mutear.setCharacterSize(20);
	desmutear.setCharacterSize(20);
	atacar.setCharacterSize(20);
	volver.setCharacterSize(20);

	dash.setPosition(470, 315);
	mover.setPosition(250, 160);
	saltar.setPosition(180, 315);
	hablar.setPosition(730, 315);
	mutear.setPosition(180, 490);
	desmutear.setPosition(470, 490);
	atacar.setPosition(730, 160);
	volver.setPosition(800, 600);


	bool entra = false; //Empieza el juego
	bool seleccion = false; //Menu personaje seleccion
	int idPersonaje = 0; //Id del personaje que selecciono para asi saber que personaje creo al empezar el juego
	bool controles = false;
	bool reiniciar = false;
	Juego *juego = NULL;
	
	while (window->isOpen()){
		reiniciar = false;
		sf::Event event;

		while (window->pollEvent(event)){
			switch (event.type){
			case sf::Event::KeyReleased:
				switch (event.key.code){
					case sf::Keyboard::Up:
						menu.MoveUp();

						if(seleccion == true && controles == false){
							menu2.MoveLeft();
						}

						break;

					case sf::Keyboard::Left:
						if(seleccion == true && controles == false){
							menu2.MoveUp();
						}

						break;

					case sf::Keyboard::Down:
						menu.MoveDown();

						if(seleccion == true && controles == false){
							menu2.MoveRight();
						}

						break;
					
					case sf::Keyboard::Right:
						if(seleccion == true && controles == false){
							menu2.MoveDown();
						}

						break;

				case sf::Keyboard::Return:
					if(seleccion == true && controles == false){
						switch (menu2.GetPressedItem()){
							case 0:
								std::cout << "Mercedes" << std::endl;
								idPersonaje = 1;
								break;

							case 1:
								std::cout << "Eugyn" << std::endl;
								idPersonaje = 2;
								break;

							case 2:
								seleccion = false;
								break;
						}
					}else if(controles == false && seleccion == false){
						switch (menu.GetPressedItem()){
							case 0:
								std::cout << "Jugar ha sido seleccionado" << std::endl;
								//entra = true;
								seleccion = true;
								break;

							case 1:
								window->close();

							case 2:
								std::cout << "Controles" << std::endl;
								controles = true;
								break;
						}
					}else{
						controles = false;
						seleccion = false;
					}

					break;
				}

				break;

			case sf::Event::Closed:
				window->close();

				break;

			}
		}

		if(seleccion == false && controles == false){
			window->clear();
			text.setString("GREMORY HOLE");
			text.setColor(sf::Color::White);
			text.setCharacterSize(120);
			text.setPosition(sf::Vector2f(130, 200 / 10));

			window->clear();
			window->draw(fondito);
			window->draw(text);
			window->draw(empresa);
			menu.draw(*window);
			window->display();
		}

		if(controles == true){
			window->clear();

			text.setString("Controles");
			text.setCharacterSize(75);
			fondito2.setTexture(fondo2);
			fondito2.setScale(1, 1);
			window->draw(fondito);
			window->draw(fondito2);
			window->draw(text);
			window->draw(mover);
			window->draw(hablar);
			window->draw(saltar);
			window->draw(desmutear);
			window->draw(dash);
			window->draw(mutear);
			window->draw(atacar);
			window->draw(volver);
			window->display();
		}

		if(seleccion == true && controles == false){
			window->clear();

			text.setString("Elige a tu personaje");
			text.setCharacterSize(75);
			window->draw(fondito);
			window->draw(text);
			text.setPosition(sf::Vector2f(150, 200 / 10));
			window->draw(mercede);
			window->draw(eugyn);
			window->draw(desEugyn);
			window->draw(desMercedes);
			menu2.draw(*window);
			window->display();

			//Guerrera seleccionada
			if(idPersonaje == 1){
				musicaMenu.pause();
				juego = Juego::getInstancia(sf::Vector2u(960, 640), window, 1);
				reiniciar = true;
			}

			//Mago seleccionado
			if(idPersonaje == 2){
				musicaMenu.pause();
				juego = Juego::getInstancia(sf::Vector2u(960, 640), window, 2);
				reiniciar = true;
			}
			
			if(reiniciar){
				/*
				musicaMenu.play();
				//delete juego;
				//juego = NULL;
				entra = false;
				seleccion = false;
				idPersonaje = 0;
				*/
				window->close();
			}
			
		}
	}
	return 0;
}
