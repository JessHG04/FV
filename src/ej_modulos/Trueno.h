#pragma once
#include <SFML/Graphics.hpp>
#include "PoderTrueno.h"
#include <iostream>
#include <string>


class Trueno : public PoderTrueno{
    public:
     //Constructor
    Trueno(int cantidadX1Ene, int cantidadY1Ene , sf::Vector2i frm_actEne);
    //Destructor
    ~Trueno();
};