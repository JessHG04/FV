#ifndef cuadrado_h
#define cuadrado_h

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class cuadradoD{
    public:
        Texture *tex2;
        cuadradoD();
        Sprite devolverSprite2();
    private:
        Sprite *sprite2;
};

#endif