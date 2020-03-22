#pragma once
#include <SFML/Graphics.hpp>


class Menu{
    public:

        Menu(float width, float height);
        ~Menu();

        void dibujar(sf::RenderWindow &window);
        void moveUp();
        void moveDown();

    private:
        int seleccionado;
        sf::Font font;
        sf::Text menu[2];


};