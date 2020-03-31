#include "Map.h"

Map::Map(){
    widthMap = 0;
    heightMap = 0;
    numLayers = 0;
    widthTile = 0;
    heightTile = 0;
}

void Map::mapMatrix(){

    tinyxml2::XMLDocument doc;

    doc.LoadFile("resources/Mapas/Mazmorra1.tmx");
    //Dimensiones del mapa y tiles
    tinyxml2::XMLElement *map = doc.FirstChildElement("map");

    map->QueryIntAttribute("width", &widthMap);
    map->QueryIntAttribute("height", &heightMap);
    map->QueryIntAttribute("tilewidth", &widthTile);
    map->QueryIntAttribute("tileheight", &heightTile);

    //Carga de tileset y background
    tinyxml2::XMLElement *img = map->FirstChildElement("tileset")->FirstChildElement("image");
    const char *filename = img->Attribute("source");

    /*tinyxml2::XMLElement* imgBackground = map->FirstChildElement("imagelayer")->FirstChildElement("image");
    const char* filenameback=imgBackground->Attribute("source");*/

    //Numero de capas 
    tinyxml2::XMLElement *layer = map->FirstChildElement("layer");
    while(layer){
        numLayers++;
        layer = layer->NextSiblingElement("layer");
    }

    //Reserva de memoria de los GIDs de las capas
    tilemap = new int **[numLayers];
    for(unsigned int l = 0; l < numLayers; l++){
        tilemap[l] = new int *[heightMap]; 
    }
    for(unsigned int l = 0; l < numLayers; l++){
        for(unsigned int y = 0; y < heightMap; y++){
            tilemap[l][y] = new int[widthMap];
        }
    }

    this->data = map->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");

    //Asignacion de cada gids a la matriz de 3x3 (layer-height-width)

    for(unsigned int l = 0; l < numLayers; l++){
        std::cout << "L vale: " << l << std::endl;
        if(l==1){
            //this->data = map->NextSiblingElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
            this->data = map->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile")
        }
        for(unsigned int y = 0; y < heightMap; y++) {
            for(unsigned int x = 0; x < widthMap; x++){
                data->QueryIntAttribute("gid", &tilemap[l][y][x]);
                //Pasamos al siguiente tile
                this->data = data->NextSiblingElement("tile");
            }
        }
        //this->data = map->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
    }
    //std::cout << "He acabao con la matriz" << std::endl;

    //Segun las diapositivas de teoria
    
    //tinyxml2::XMLElement *data [0] = map->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
    /*this->data = map->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
    for(unsigned l = 0; l < numLayers; l++){
        for(unsigned y = 0; y < heightMap; y++){
            for(unsigned x = 0; x < widthMap; x++){
                data->QueryIntAtribute("gid", &tilemap[l][y][x]);
                //Paso al siguiente
                this->data = data->NextSiblingElement("tile");
            }
        }
    }
    */

}

bool Map::load(const std::string& path, sf::Vector2u tileSize, int*** level, unsigned int witdh, unsigned int heigth, int numLayer){
       //std::cout << "Layers: " << numLayer << std::endl;
       //std::cout << "Height: " << heigth << std::endl;
       //std::cout << "Width: " << witdh << std::endl;
       if(!tile.loadFromFile(path)){
           return false;
       }
       vertex.setPrimitiveType(sf::Quads);
       vertex.resize(widthMap * heightMap * 4); //Se multiplica por 4 bc el tiled es de 16x16

       for(unsigned int l = 0; l < numLayers; l++){
           for(unsigned int y = 0; y < heightMap; y++){
               for(unsigned int x = 0; x < widthMap; x++){
                   int gid = level[l][y][x];
                   if(gid > 0){
                       gid-=1;
                   }
                   int u; 
                   int v;

                   if(gid!=0){
                       //Posicion del tileset para partirlo
                       u = gid % (tile.getSize().x / tileSize.x); 
                       v = gid / (tile.getSize().x / tileSize.x);
                       //Puntero para apuntar al quad actual
                       sf::Vertex *quad = &vertex[(x+y*widthMap)* 4]; 

                       //Definicion de las esquinas del quad
                       quad[0].position = sf::Vector2f(x * tileSize.x, y * tileSize.y);
                       quad[1].position = sf::Vector2f((x+1) * tileSize.x, y * tileSize.y);
                       quad[2].position = sf::Vector2f((x+1) * tileSize.x, (y+1) * tileSize.y);
                       quad[3].position = sf::Vector2f(x * tileSize.x, (y+1) * tileSize.y);

                       //Definicion de las texturas de las coordenadas
                       quad[0].texCoords = sf::Vector2f(u*tileSize.x, v*tileSize.y);
                       quad[1].texCoords = sf::Vector2f((u+1)*tileSize.x, v*tileSize.y);
                       quad[2].texCoords = sf::Vector2f((u+1)*tileSize.x, (v+1)*tileSize.y);
                       quad[3].texCoords = sf::Vector2f(u*tileSize.x,(v+1)*tileSize.y);
                   }
               }
           }
       }
    return true;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    states.texture = &tile;
    target.draw(vertex,states);
}

Map::~Map(){

}