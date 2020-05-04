#pragma once
#include <SFML/Graphics.hpp>
#include "NPC.h"
#include <iostream>
#include <string>


class PersonajeNPC : public NPC{
    public:
     //Constructor
    PersonajeNPC(int cantidadX1Ene, int cantidadY1Ene , sf::Vector2i frm_actEne);
    //Destructor
    ~PersonajeNPC();
};