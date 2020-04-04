#include "Menu.h"


Menu::Menu(float width, float height){
    if(!font.loadFromFile("arial.ttf")){
    }

    menu[0].setFont(font);
    menu[0].setColor(sf::Color::Blue);
    menu[0].setString("Guerrera");
    menu[0].setPosition(sf::Vector2f(width/2,height/(2+1)*1));
    menu[1].setFont(font);
    menu[1].setColor(sf::Color::Blue);
    menu[1].setString("Mago");
    menu[1].setPosition(sf::Vector2f(width/2,height/(2+1)*2));

    seleccionado = 0;
}

void Menu :: dibujar(sf::RenderWindow &window){
    for(int i = 0; i < 2; i++){
        window.draw(menu[i]);
    }
}
void Menu::moveUp(){
    if(seleccionado - 1 >= 0){
        menu[seleccionado].setColor(sf::Color::White);
        seleccionado --;
        menu[seleccionado].setColor(sf::Color::Blue);
    }
}

void Menu::moveDown(){
    if(seleccionado + 1 < 2){
        menu[seleccionado].setColor(sf::Color::White);
        seleccionado ++;
        menu[seleccionado].setColor(sf::Color::Blue);
    }
}
Menu::~Menu(){

}