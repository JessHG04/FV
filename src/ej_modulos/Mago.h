#pragma once
#include <SFML/Graphics.hpp>
#include "Jugador.h"
#include <iostream>
#include <string>


class Mago : public Jugador{
    public:
     //Constructor
    Mago(int cantidadX1, int cantidadY1 , sf::Vector2i frm_act);
    //Destructor
    ~Mago();
};



