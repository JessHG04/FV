#ifndef cuadrado_I
#define cuadrado_I

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class cuadradoI{
    public:
        Texture *tex2;
        cuadradoI();
        Sprite devolverSprite2();
    private:
        Sprite *sprite2;
};

#endif