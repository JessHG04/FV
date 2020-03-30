#include "Juego.h"
#include <SFML/Graphics.hpp>




Juego::Juego(sf::Vector2u resolucion){
    //Creamos una ventana
    ventana = new sf::RenderWindow(sf::VideoMode(resolucion.x,resolucion.y), "Gremory Hole");
    //Iniciamos el juego
    iniciar();
    //Camara
    vista.reset(sf::FloatRect(0, 0, resolucion.x, resolucion.y));
    vista.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
    sf::Vector2f pos_vista(resolucion.x / 2 , resolucion.y / 2);


    //----------------------------------------BUCLE DEL JUEGO------------------------------------------------------------------------------
    while(gameover != true){
        *crono1 = reloj1->getElapsedTime(); // Obtener tiempo transcurrido 

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
                if(!j1->movimiento)
                    j1->set_velocidad(sf::Vector2f(0,j1->vel_salto));
                else if(j1->direccion == izq)
                    j1->set_velocidad(sf::Vector2f(-j1->vel_desp,j1->vel_salto));
                else if(j1->direccion == der)
                    j1->set_velocidad(sf::Vector2f(j1->vel_desp,j1->vel_salto));
            }

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
            if(j1->saltando && j1->posInicial.y == j1->get_posicion().y){
                j1->saltando = false;
                j1->movimiento = false;
                j1->vel_salto = -20.0f;
                j1->set_velocidad(sf::Vector2f(0,0));
                 if(j1->direccion == izq){
                        j1->set_sprite(j1->archivo,1,4,4,sf::Vector2i(0,2));
                    }
                    
                    if(j1->direccion == der){
                        j1->set_sprite(j1->archivo,1,4,4,sf::Vector2i(0,3));
                    }
            }
            reloj1->restart();
            //Camara
            if(j1->get_posicion().x >= 2390){
                pos_vista.x = 2390;
            }else if(j1->get_posicion().x > resolucion.x / 2){
                pos_vista.x = j1->get_posicion().x;
            }else{
                pos_vista.x = resolucion.x / 2;
            }            
            vista.setCenter(pos_vista);
        }
    }
}

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
    j1->set_posicion(sf::Vector2f(300,300));
    evento = new sf::Event();
}

void Juego::dibujar(){
    ventana->clear();
    ventana->setView(vista); //Camara
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

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
                    j1->movimiento = true;
                    //j1->set_frameY(0); 
                    j1->set_sprite(j1->archivo,2,1,1,sf::Vector2i(0,0));
                    j1->set_velocidad(sf::Vector2f(-j1->vel_desp*5,0));
                        
                }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                        if(!j1->saltando){
                            j1->saltando = true;
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

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
                    j1->movimiento = true;
                    //j1->set_frameY(0); 
                    j1->set_sprite(j1->archivo, 4,1,1,sf::Vector2i(0,0));
                    j1->set_velocidad(sf::Vector2f(j1->vel_desp*5,0));
                        
                }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                    if(!j1->saltando){
                        j1->saltando = true;
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
                    j1->saltando = true;
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
                    j1->set_sprite(j1->archivo,2,1,1,sf::Vector2i(0,0));
                    j1->set_velocidad(sf::Vector2f(-j1->vel_desp*5,0));
                    //j1->set_posicion(sf::Vector2f(j1->get_posicion().x - j1->vel_desp,(j1->get_posicion().y)));
                }else{
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
                        j1->movimiento = true;
                        j1->set_frameY(0); 
                        j1->set_sprite(j1->archivo,6,3,1,sf::Vector2i(0,0));
                    }else{
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
