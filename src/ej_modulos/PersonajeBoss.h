#pragma once
#include <SFML/Graphics.hpp>
#include "Boss.h"
#include <iostream>
#include <string>


class PersonajeBoss : public Boss{
    public:
     //Constructor
    PersonajeBoss(int cantidadX1Boss, int cantidadY1Boss , sf::Vector2i frm_actBoss);
    //Destructor
    ~PersonajeBoss();
};