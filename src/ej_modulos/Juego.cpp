#include "Juego.h"
#include <SFML/Graphics.hpp>




Juego::Juego(sf::Vector2u resolucion){
    //Creamos una ventana
    ventana = new sf::RenderWindow(sf::VideoMode(resolucion.x,resolucion.y), "Gremory Hole");
    //Iniciamos el juego
    iniciar();

    // ************************************ BUCLE DEL JUEGO *************************************************************************
    while(gameover != true){
        *crono1 = reloj1->getElapsedTime(); // Obtener tiempo transcurrido 
        j1->posInicial = j1->get_posicion();
        if(crono1->asSeconds() > 0.08){ // comparamos si el tiempo transcurrido es 1 fps (1 frame) si es asi ejecuttamos un instante
            while(ventana->pollEvent(*evento)){
                procesar_eventos();
            }

             if(p1){
                if(p1->eliminar == 20){
                    delete p1;        
                    p1 = 0;           
                }else
                {
                    p1->eliminar ++;
                }
            }
                //CUANDO SE REALICE LA COLISION SE ELIMINARA EL PROYECTIL-------------------------------------------
              //  if(COLISION)  {
                   // delete p1;
                   // p1 = 0; 
               // }
            //Si es mago nunca se para
             //if(instanceof<Mago>(j1))
                //j1->movimiento = true;
            // Si sigue saltando la gravedad le sigue afectando

            if(j1->saltando){
                j1->vel_salto += 2.0f;
                
               if(j1->vel_salto > 0){
                    j1->dirColision = abajo;
                }else{
                    j1->dirColision = arriba;
                }
                
                if(!j1->movimiento)
                    j1->set_velocidad(sf::Vector2f(0,j1->vel_salto));
                else if(j1->direccion == izq)
                    j1->set_velocidad(sf::Vector2f(-j1->vel_desp,j1->vel_salto));
                else if(j1->direccion == der)
                    j1->set_velocidad(sf::Vector2f(j1->vel_desp,j1->vel_salto));
            } 
            //********************************************* GRAVEDAD *************************************************
            /*else if(j1->dirColision == abajo){
                j1->vel_salto += 2.0f;
                j1->dirColision = abajo;
                
                if(!j1->movimiento)
                    j1->set_velocidad(sf::Vector2f(0,j1->vel_salto));
                else if(j1->direccion == izq)
                    j1->set_velocidad(sf::Vector2f(-j1->vel_desp,j1->vel_salto));
                else if(j1->direccion == der)
                    j1->set_velocidad(sf::Vector2f(j1->vel_desp,j1->vel_salto));
            }*/
            //********************************************************************************************************
            if(j1->movimiento){
                j1->animar();
            }
             if(p1)
                p1->animar();

            j1->update();
            if(p1)
                p1->update();
            dibujar();
            //Si sigue saltando y llega a la posicion de donde salto se para
            //EN EL JUEGO CAMBIAR ESTA CONDICION POR LA COLISION CON EL MAPA PORQUE PUEDE SER QUE SE SUBA A UNA PLATAFORMA Y NO VUELVA A LA POSICION INICIAL
            if(colisionPersMapa(j1->dirColision)){
                j1->saltando = false;
                j1->movimiento = false;
                j1->vel_salto = 0;
                j1->set_velocidad(sf::Vector2f(0,0));
                 if(j1->direccion == izq){
                        j1->set_sprite(j1->archivo,1,4,4,sf::Vector2i(0,2));
                    }
                    
                    if(j1->direccion == der){
                        j1->set_sprite(j1->archivo,1,4,4,sf::Vector2i(0,3));
                    }
            }
            reloj1->restart();
        }
    }
}
//******************************************* FIN DEL BUCLE DEL JUEGO ************************************************************
void Juego::iniciar(){
    fps = 60;
    reloj1 = new sf::Clock();
    crono1 = new sf::Time();
    mapa = new Map();
    mapa->mapMatrix();
    mapa->load("resources/Mapas/Tileset.png", sf::Vector2u(16,16), mapa->tilemap, mapa->widthMap, mapa->heightMap, mapa->numLayers);
    if(esGuerrera)
        j1 = new Guerrera(4,4,sf::Vector2i(0,0));
    else
        j1 = new Mago(4,4,sf::Vector2i(0,0));
    j1->set_posicion(sf::Vector2f(47,21*16));
    j1->dirColision = abajo;
    //j1->direccion = quieto;
    j1->vel_salto = 0;
    evento = new sf::Event();
}

void Juego::dibujar(){
    ventana->clear();
    ventana->draw(j1->get_sprite());
    ventana->draw(*mapa);
    if(p1)
        ventana->draw(p1->get_sprite());
    ventana->display();
}

/*void Juego::logica(){

}*/

void Juego::procesar_eventos(){
            
                    
    

    switch (evento->type)
    {
        case sf::Event::Closed:
            exit(1);
            break;
        case sf::Event::KeyPressed:
            // si se pulsta la tecla izquierda
            
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                 j1->direccion = izq;
                 j1->dirColision = izq;

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
                    j1->movimiento = true;
                    //j1->set_frameY(0); 
                    j1->set_sprite(j1->archivo,2,1,1,sf::Vector2i(0,0));
                    j1->set_velocidad(sf::Vector2f(-j1->vel_desp*5,0));
                        
                }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                        if(!j1->saltando){
                            j1->vel_salto = -20.0f;
                            j1->saltando = true;
                            j1->dirColision = arriba;
                            if (j1->movimiento != true)
                                j1->posInicial = sf::Vector2f(j1->get_posicion().x, j1->get_posicion().y);
                            //j1->movimiento = true;
                            j1->set_velocidad(sf::Vector2f(0,j1->vel_salto));     
                        }
                }else{
                    j1->movimiento = true;
                    //j1->direccion = izq;
                    j1->set_frameY(2); 
                    j1->set_velocidad(sf::Vector2f(-j1->vel_desp,0));
                    //j1->set_posicion(sf::Vector2f(j1->get_posicion().x - j1->vel_desp,(j1->get_posicion().y)));
                }
                    
                }
            
            // si se pulsa la tecla derecha
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                j1->direccion = der;
                j1->dirColision = der;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
                    j1->movimiento = true;
                    //j1->set_frameY(0); 
                    j1->set_sprite(j1->archivo, 4,1,1,sf::Vector2i(0,0));
                    j1->set_velocidad(sf::Vector2f(j1->vel_desp*5,0));
                        
                }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                    if(!j1->saltando){
                        j1->vel_salto = -20.0f;
                        j1->saltando = true;
                        j1->dirColision = der;
                        if (j1->movimiento != true)
                            j1->posInicial = sf::Vector2f(j1->get_posicion().x, j1->get_posicion().y);
                        //j1->movimiento = true;
                        j1->set_velocidad(sf::Vector2f(0,j1->vel_salto));     
                    }
                }else{
                    j1->movimiento = true;
                    //j1->direccion = izq;
                    j1->set_frameY(3); 
                    j1->set_velocidad(sf::Vector2f(j1->vel_desp,0));
                    //j1->set_posicion(sf::Vector2f(j1->get_posicion().x - j1->vel_desp,(j1->get_posicion().y)));
                }
                
                
            }

//--------------------------SALTO----------------------------------------------------------------------------------------
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                if(!j1->saltando){
                    j1->vel_salto = -20.0f;
                    j1->saltando = true;
                    j1->dirColision = arriba;
                    if (j1->movimiento != true)
                        j1->posInicial = sf::Vector2f(j1->get_posicion().x, j1->get_posicion().y);
                    //j1->movimiento = true;
                    j1->set_velocidad(sf::Vector2f(0,j1->vel_salto));     
                }
            }
                

//--------------------------DASH-----------------------------------------------------------------------------------------
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
                j1->movimiento = true;
                j1->set_frameY(0); 
                

                //Vemos a que lado esta mirando
                if(j1->direccion == izq){
                    j1->dirColision = izq;
                    j1->set_sprite(j1->archivo,2,1,1,sf::Vector2i(0,0));
                    j1->set_velocidad(sf::Vector2f(-j1->vel_desp*5,0));
                    //j1->set_posicion(sf::Vector2f(j1->get_posicion().x - j1->vel_desp,(j1->get_posicion().y)));
                }else{
                    j1->dirColision = der;
                    j1->set_sprite(j1->archivo,4,1,1,sf::Vector2i(0,0));
                    j1->set_velocidad(sf::Vector2f(j1->vel_desp*5,0));
                }
            }
//------------------------ATAQUE-------------------------------------------------------------------------------------------
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                if(!esGuerrera){
                    if(!p1){
                            p1 = new Proyectil(4,1,sf::Vector2i(0,0));
                            
                            p1->posicionInicial = sf::Vector2f(p1->get_posicion().x,p1->get_posicion().y);
                            
                            if(j1->direccion == izq){
                                p1->set_posicion(sf::Vector2f(j1->get_posicion().x-20,j1->get_posicion().y));
                                p1->set_velocidad(sf::Vector2f(-p1->vel_desp,0));
                            }
                            else{
                                p1->set_posicion(sf::Vector2f(j1->get_posicion().x+20,j1->get_posicion().y));
                                p1->set_velocidad(sf::Vector2f(p1->vel_desp,0));
                            }
                        
                    }
                }
                else{
                    if(j1->direccion == izq){
                        j1->dirColision = izq;
                        j1->movimiento = true;
                        j1->set_frameY(0); 
                        j1->set_sprite(j1->archivo,6,3,1,sf::Vector2i(0,0));
                    }else{
                        j1->dirColision = der;
                        j1->movimiento = true;
                        j1->set_frameY(0); 
                        j1->set_sprite(j1->archivo,7,3,1,sf::Vector2i(0,0));
                    }
                //j1->set_frameY(0);
                }
            }
            break;


                /**** TECLAS SIN PULSAR ****/

            case sf::Event::KeyReleased: // si se suelta la tecla
                // si se despulsta la tecla izquierda
                if(evento->key.code == (sf::Keyboard::Left)){
                    j1->movimiento = false;
                    j1->set_frameX(0);
                    j1->direccion = izq;
                    j1->set_velocidad(sf::Vector2f(0,0));
                    //j1->set_posicion(sf::Vector2f(j1->get_posicion().x - kVel,(j1->get_posicion().y)));
                }
                // si se despulsa la tecla derecha
                else if(evento->key.code == (sf::Keyboard::Right)){
                    j1->movimiento = false;
                    j1->set_frameX(0);
                    j1->direccion = der;
                    j1->set_velocidad(sf::Vector2f(0,0));
                
                    //j1->set_posicion(sf::Vector2f(j1->get_posicion().x + kVel,(j1->get_posicion().y)));
                }else if(evento->key.code == (sf::Keyboard::Z)){
                    j1->movimiento = false;
                    if(j1->direccion == izq){
                        j1->set_sprite(j1->archivo,1,4,4,sf::Vector2i(0,2));
                    }
                    
                    if(j1->direccion == der){
                        j1->set_sprite(j1->archivo,1,4,4,sf::Vector2i(0,3));
                    }

                    j1->set_velocidad(sf::Vector2f(0,0));
                    j1->set_posicion(sf::Vector2f(j1->get_posicion().x, j1->get_posicion().y));
                }else if(evento->key.code == (sf::Keyboard::Space)){
                    if(esGuerrera){
                        j1->movimiento = false;

                        if(j1->direccion == izq){
                            j1->set_sprite(j1->archivo,1,4,4,sf::Vector2i(0,2));
                        }else{
                            j1->set_sprite(j1->archivo,1,4,4,sf::Vector2i(0,3));
                        }
                        j1->set_posicion(sf::Vector2f(j1->get_posicion().x, j1->get_posicion().y));
                    }
               
                }
                break;
        
        default:
                 //j1->movimiento = false;
                 
        break;

    }
}

bool Juego::colisionPersMapa(direcciones direccion){ //La colision del personaje con el mapa
    int gid;
    sf::RectangleShape box2(sf::Vector2f(j1->tamFrame.x-20, j1->tamFrame.y-20));
    box2.setPosition(j1->get_posicion().x, j1->get_posicion().y+10);
    box2.setFillColor(sf::Color::Red);
    bool colisionando = false;
    for(unsigned int l = 0; l < mapa->numLayers; l++){
        for(unsigned int y = 0; y < mapa->heightMap; y++){
            for(unsigned int x = 0; x < mapa->widthMap; x++){
                gid = mapa->tilemap[l][y][x];
                sf::RectangleShape box(sf::Vector2f(16, 16));
                box.setPosition(sf::Vector2f(x*16, y*16));
                if(gid > 0 && direccion == 1 && !colisionando){ //Arriba
                    if(box.getGlobalBounds().intersects(box2.getGlobalBounds())){
                        j1->set_posicion(sf::Vector2f(j1->posInicial.x, j1->posInicial.y+1));
                        j1->dirColision = quieto;
                        if(j1->saltando)
                            j1->dirColision = abajo;
                        j1->vel_salto = 0;
                        colisionando = true;
                    }
                }
                if(gid > 0 && direccion == 2 && !colisionando){ //Izquierda
                    if(box.getGlobalBounds().intersects(box2.getGlobalBounds())){
                        j1->set_posicion(sf::Vector2f(j1->posInicial.x+1, j1->posInicial.y));
                        j1->dirColision = quieto;
                        if(j1->saltando)
                            j1->dirColision = abajo;
                        colisionando = true;
                    }
                }
                if(gid > 0 && direccion == 3 && !colisionando){ //Derecha
                    if(box.getGlobalBounds().intersects(box2.getGlobalBounds())){
                        j1->set_posicion(sf::Vector2f(j1->posInicial.x-1, j1->posInicial.y));
                        j1->dirColision = quieto;
                        if(j1->saltando)
                            j1->dirColision = abajo;
                        colisionando = true;
                    }
                }
                
                if(direccion != quieto  && !colisionando){
                    j1->saltando = true;  // EL FALLO ESTA AQUIIIIII
                    j1->dirColision = abajo;    
                }

                if(gid > 0 && direccion == 4 && !colisionando){ //Abajo
                    if(box.getGlobalBounds().intersects(box2.getGlobalBounds())){
                        j1->set_posicion(sf::Vector2f(j1->posInicial.x, j1->posInicial.y-1));
                        j1->dirColision = quieto;
                        colisionando = true;
                        j1->saltando = false;
                    }
                }
                
            }
        }
    }
    return colisionando;
}

