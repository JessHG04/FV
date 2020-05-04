#pragma ONCE
#include <SFML/Graphics.hpp>
#include <iostream>

class Portal{
    public:
    Portal(int, int);
    ~Portal();
    sf::RectangleShape getCaja();
    void Update();
    void Draw(sf::RenderWindow &);
    
    private:
    sf::Sprite *sprite;
    sf::Texture text;
    sf::RectangleShape cajaColision;
};