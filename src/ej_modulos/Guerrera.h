#pragma once
#include <SFML/Graphics.hpp>
#include "Jugador.h"
#include <iostream>
#include <string>


class Guerrera : public Jugador{
    public:
     //Constructor
    Guerrera(int cantidadX1, int cantidadY1 , sf::Vector2i frm_act);
    //Destructor
    ~Guerrera();
    
};