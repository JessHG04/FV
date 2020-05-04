#pragma once
#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 3

class MenuSeleccionPersonaje{
    public:
        MenuSeleccionPersonaje(float width, float height);
        ~MenuSeleccionPersonaje();

        void draw(sf::RenderWindow &window);
        void MoveUp();
        void MoveDown();
        void MoveRight();
        void MoveLeft();
        int GetPressedItem() { return selectedItemIndex; }

    private:
        int selectedItemIndex;
        sf::Font font;
        sf::Text menu[MAX_NUMBER_OF_ITEMS];
};
