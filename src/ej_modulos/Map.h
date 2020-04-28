#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "tinyxml2.h"

//Generacion de un unico mapa
//Drawable y transformable heredados de SFML

class Map : public sf::Drawable, public sf::Transformable{
    
    private:
        static Map *map;
        sf::VertexArray vertex;
        sf::Texture tile;
        
    public:
        Map();
        virtual ~Map();
        void mapMatrix(int); //Guardar datos del mapa
        bool load(const std::string& path, sf::Vector2u tileSize, int*** level, unsigned int witdh, unsigned int heigth, int numLayer);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        tinyxml2::XMLElement *data;
        int ***tilemap;
        int **gidMatrix;
        int widthMap;
        int heightMap;
        int numLayers;
        int widthTile;
        int heightTile;
};
