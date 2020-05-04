#include "Juego.h"
#include <SFML/Graphics.hpp>
/******************************* HACE TODOS LOS COMANDOS A LA VEZ ************************************/
/* alias do="cmake -H. -Bbuild && cd build/ && make && mv GremoryHole .. && cd .. && ./GremoryHole"  */
/*            alias do="cd build/ && make && mv GremoryHole .. && cd .. && ./GremoryHole"            */
/*                                  Luego simplemente pones do                                       */
/*****************************************************************************************************/

Juego* Juego::juego = NULL;

// Creamos la unica instancia del juego
Juego* Juego::getInstancia(sf::Vector2u resolucion,sf::RenderWindow *window, int id) {
    if (juego == NULL) {
        juego = new Juego(resolucion, window, id);
    }
    return juego;
}


Juego::Juego(sf::Vector2u resolucion, sf::RenderWindow *window, int idPersonaje){
    //Creamos una ventana
    ventana = window;
    //Seleccion de personaje
    if(idPersonaje == 1){
        personajeSelec = 1;
        esGuerrera = true;
    }   

    if(idPersonaje == 2){
        personajeSelec = 2;
        esGuerrera = false;
    } 
    //Iniciamos el juego
    iniciar();
    //Camara
    vista.reset(sf::FloatRect(0, 0, resolucion.x, resolucion.y));
    vista.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
    sf::Vector2f pos_vista(resolucion.x / 2 , resolucion.y / 2);

    // ************************************ BUCLE DEL JUEGO *************************************************************************
    while(gameover != true){
        *crono1 = reloj1->getElapsedTime(); // Obtener tiempo transcurrido 
        *cronoInmortal = relojInmortal->getElapsedTime(); // Obtener tiempo transcurrido 
        //********************************************* DASH ************************************************* 
        *j1->crono_termina_dash = j1->termina_dash->getElapsedTime();
        *j1->crono_recarga_dash = j1->recarga_dash->getElapsedTime();

    
        if(j1->dash){
            if(j1->direccion == izq)
                j1->set_velocidad(sf::Vector2f(-j1->vel_desp*3,0));
            else
                j1->set_velocidad(sf::Vector2f(j1->vel_desp*3,0));
            if(j1->crono_termina_dash->asSeconds() > 0.5){
                detenerDash();
                j1->dash = false;
                j1->recarga_dash->restart();
            }                    
        }
        if(crono1->asSeconds() > 0.08){ // comparamos si el tiempo transcurrido es 1 fps (1 frame) si es asi ejecuttamos un instante
            while(ventana->pollEvent(*evento)){
                procesar_eventos();
            }
            //Pasar de Nivel
            if(portal != NULL){
                colisionPersPortal();
            }
            if(!cargar && level <= maxLevels){
                crearEnemigos();
                std::cout<< "Nivel: " << level << std::endl;
                mapa = new Map();
                mapa->mapMatrix(level);
                mapa->load("resources/Mapas/Tileset.png", sf::Vector2u(16,16), mapa->tilemap, mapa->widthMap, mapa->heightMap, mapa->numLayers);
                crearPortal();
                cargar = true;
            }
            j1->posInicial = j1->get_posicion();
            if(level > maxLevels){
                gameover = true;
            }

            if(p1){
               if(p1 != nullptr){
                    if(colisionProyecMapa(p1->dirColision)){
                        //p1->~Proyectil();
                        delete p1;        
                        p1 = 0;           
                    }
                }
                this->colisionProyectilEnemigos();
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
            //********************************************* GRAVEDAD *************************************************
            
            gestionGravedad();
            if((gravedad || j1->saltando) && !j1->dash){ // concicion no cae con el dash
                j1->vel_salto += 2.5f;
                
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

            if(j1->movimiento || j1->inmortal){
                j1->animar();
            }
             if(p1)
                p1->animar();

            j1->update();
            if(p1)
                p1->update();
            this->colisionesProtagonista();
            //UPDATES ENEMIGOS
            for(int x = 0; x < enemigos.size(); x++){
                if(enemigos[x] != NULL){ //otro if enemigos[x] -> muerto
                    if(x < 9){ //Hace todos los updates menos los de Lara porque tiene otros parámetros
                        enemigos[x]->Update(reloj1->getElapsedTime().asSeconds());
                    }
                }
            }
            
            if(larita1 != NULL && level == 1){
                if(larita1->Update(*ventana, j1, (83*16+100), (20*16))){ 
                    impacto();
                }
            }
            if(larita1 != NULL && level == 3){
                if(larita1->Update(*ventana, j1, (6*16+100), (12*16))){ 
                    impacto();
                }
            }
            if(larita2 != NULL && level == 3){
                if(larita2->Update(*ventana, j1, (111*16+100), (14*16))){ 
                    impacto();
                }
            }
            if(larita1 != NULL && level == 5){
                if(larita1->Update(*ventana, j1, (54*16+100), (16*16))){ 
                    impacto();
                }
            }
            if(larita2 != NULL && level == 5){
                if(larita2->Update(*ventana, j1, (79*16+100), (10*16))){ 
                    impacto();
                }
            }
            if(larita3 != NULL){
                if(larita3->Update(*ventana, j1, (83*16+100), (20*16))){ 
                    impacto();
                }
            }
            //BOSS PROYECTIL
            if(pBoss != NULL)
                pBoss->animar();
            if(bossFinal != NULL)
                bossFinal->updateBoss();
            if(pBoss != NULL)
                pBoss->update();
            if(bossFinal != NULL)
                bossLanza();
            if(bossFinal != NULL)
                bossTrueno();
            portal->Update();
            dibujar();
          
            if(cronoInmortal->asSeconds() > 2.5 && j1->inmortal){
                j1->inmortal = false;
                if(esGuerrera == false){
                    if(j1->direccion == izq){
                        j1->set_sprite(j1->txt_player,4,4,sf::Vector2i(0,2));
                    }
                        
                    if(j1->direccion == der){
                        j1->set_sprite(j1->txt_player,4,4,sf::Vector2i(0,3));
                    }
                }else{
                    if(j1->direccion == izq){
                        j1->set_sprite(j1->txt_player2,4,4,sf::Vector2i(0,2));
                    }
                        
                    if(j1->direccion == der){
                        j1->set_sprite(j1->txt_player2,4,4,sf::Vector2i(0,3));
                    }
                }
            }
            
            if(colisionPersTrampa(j1->dirColision)){
                if(!j1->inmortal){ 
                    relojInmortal->restart();
                    j1->inmortal = true;
                    j1->vida --;
                    if(j1->vida == 0)//*******************************************************RESTAMOS VIDA********************************
                        gameover = true;
                    if(esGuerrera == false){
                        if(j1->direccion == izq){
                            j1->set_sprite(j1->txt_herido,4,4,sf::Vector2i(0,2));
                        }
                        
                        if(j1->direccion == der){
                            j1->set_sprite(j1->txt_herido,4,4,sf::Vector2i(0,3));
                        }
                    }else{
                        if(j1->direccion == izq){
                            j1->set_sprite(j1->txt_herido2,4,4,sf::Vector2i(0,2));
                        }
                        
                        if(j1->direccion == der){
                            j1->set_sprite(j1->txt_herido2,4,4,sf::Vector2i(0,3));
                        }
                    }
                }
            }
            
            if(colisionPersMapa(j1->dirColision)){
                j1->saltando = false;
                j1->movimiento = false;
                j1->vel_salto = 0;
                j1->set_velocidad(sf::Vector2f(0,0));
                if(!j1->inmortal){
                    if(esGuerrera == false){
                        if(j1->direccion == izq){
                            j1->set_sprite(j1->txt_player,4,4,sf::Vector2i(0,2));
                        }
                            
                        if(j1->direccion == der){
                            j1->set_sprite(j1->txt_player,4,4,sf::Vector2i(0,3));
                        }
                    }else{
                        if(j1->direccion == izq){
                            j1->set_sprite(j1->txt_player2,4,4,sf::Vector2i(0,2));
                        }
                            
                        if(j1->direccion == der){
                            j1->set_sprite(j1->txt_player2,4,4,sf::Vector2i(0,3));
                        }
                    }
                }
            }
            this->muerteNPCs();
            reloj1->restart();
            //Camara - Extremo derecho, normal, extremo izquierdo
            if(j1->get_posicion().x >= (mapa->widthMap * 16 - resolucion.x /2)){
                pos_vista.x = mapa->widthMap * 16 - resolucion.x /2;
            }else if(j1->get_posicion().x > resolucion.x / 2){
                pos_vista.x = j1->get_posicion().x;
            }else{
                pos_vista.x = resolucion.x / 2;
            }
            for(int i = 0;  i < j1->vida; i++){
                interfaz->spr_vida[i]->setPosition(95 + i * 30 + pos_vista.x - resolucion.x /2,interfaz->spr_vida[i]->getPosition().y);
            }
            interfaz->spr_cara->setPosition(100 + pos_vista.x - resolucion.x /2,interfaz->spr_cara->getPosition().y);
            interfaz->nombre2.setPosition(100 + pos_vista.x - resolucion.x /2,interfaz->nombre2.getPosition().y);
            vista.setCenter(pos_vista);
        }
    }
    ventana->close();
}
//******************************************* FIN DEL BUCLE DEL JUEGO ************************************************************
void Juego::iniciar(){
    fps = 60;
    reloj1 = new sf::Clock();
    crono1 = new sf::Time();
    relojInmortal = new sf::Clock();
    cronoInmortal = new sf::Time();
    relojBoss = new sf::Clock();
    cronoBoss = new sf::Time();
    relojTrueno = new sf::Clock();
    cronoTrueno = new sf::Time();
    p1 = 0;
    
    if(esGuerrera){
        j1 = new Guerrera(4,4,sf::Vector2i(0,0));
        interfaz = new Interfaz(personajeSelec);
    }else{
        j1 = new Mago(4,4,sf::Vector2i(0,0));
        interfaz = new Interfaz(personajeSelec);
    } 
    //j1->set_posicion(sf::Vector2f(4*16,27*16));
    //j1->dirColision = abajo;
    //j1->direccion = quieto;
    j1->vel_salto = 0;
    
    evento = new sf::Event();
}

void Juego::dibujar(){
    ventana->clear();    
    ventana->setView(vista); //Camara
    ventana->draw(fondo);
    ventana->draw(*mapa);
    //ventana->draw(portal->getCaja());
    portal->Draw(*ventana);
    for(int x = 0; x < enemigos.size(); x++){
        if(enemigos[x] != NULL){
            enemigos[x]->Draw(*ventana);
        }
    }
    if(larita1 != NULL && larita1->dispara == true){
        larita1->getBala().Draw(*ventana);
    }
    if(larita2 != NULL && larita2->dispara == true){
        larita2->getBala().Draw(*ventana);
    }
    if(larita3 != NULL && larita3->dispara == true){
        larita3->getBala().Draw(*ventana);
    }
    //---------NPC-------------
    if(npc != NULL){
        ventana->draw(npc->getSpriteEne());
        ventana->draw(npc->cajaColisionesNPC);
    }
    //elijo la imagen dependiendo de la variable auxiliar (numero de monologo)
    if(npc != NULL){
        if(conversacionInicial.size()>0){
            for(int i = 0; i < conversacionInicial.size(); i++){
                if(variableAuxiliar==0){
                    ventana->draw(conversacionInicial[0]);
                }else if(variableAuxiliar==100){
                    ventana->draw(conversacionInicial[1]);
                }else if(variableAuxiliar==200){
                    ventana->draw(conversacionInicial[2]);
                }else if(variableAuxiliar==300){
                    ventana->draw(conversacionInicial[3]);
                }
            }
        }
    }
    //---------BOSS-------------
    if(bossFinal != NULL){
        ventana->draw(bossFinal->getSpriteBoss());
        ventana->draw(bossFinal->cajaColisionesBoss);
    }
   
    ventana->draw(j1->cajaColisiones);
    ventana->draw(j1->cajaColisiones2);
    
    ventana->draw(j1->get_sprite());
    if(p1)
        ventana->draw(p1->get_sprite());
    //Boss proyectil
    if(pBoss)
        ventana->draw(pBoss->get_sprite());

    //Boss trueno
    if(trueno != NULL){
        ventana->draw(trueno->getSpriteEne());
        ventana->draw(trueno->cajaColisionesNPC);
    }
    if(trueno2 != NULL){
        ventana->draw(trueno2->getSpriteEne());
        ventana->draw(trueno2->cajaColisionesNPC);
    }
    
    if(interfaz){
        ventana->draw(interfaz->nombre2);
        ventana->draw(*interfaz->spr_cara);
        for(int i = 0; i < j1->vida; i++){
            if(interfaz->spr_vida[i] != NULL)
                ventana->draw(*interfaz->spr_vida[i]);
        }
    }
    ventana->display();
}

/*void Juego::logica(){

}*/

void Juego::procesar_eventos(){
    if(!j1->dash){
        switch (evento->type)
        {
            case sf::Event::Closed:
                exit(1);
                //ventana->close();
                break;
            case sf::Event::KeyPressed:
                // si se pulsta la tecla izquierda
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                    exit(1);
                    //ventana->close();
                    break;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
                    level++;
                    cargar = false;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                    j1->direccion = izq;
                    j1->dirColision = izq;

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
                        if(j1->crono_recarga_dash->asSeconds() > 0.5){ 
                            j1->movimiento = true;
                            //j1->set_frameY(0); 
                            if(esGuerrera == false){
                                j1->set_sprite(j1->txt_dash_I,1,1,sf::Vector2i(0,0));
                            }else{
                                j1->set_sprite(j1->txt_dash_I2,1,1,sf::Vector2i(0,0));
                            }
                            j1->termina_dash->restart();
                            j1->dash = true;
                        }
                    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                            if(!j1->saltando){
                                j1->vel_salto = -30.0f;
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
                        if(j1->crono_recarga_dash->asSeconds() > 0.5){
                            j1->movimiento = true;
                            //j1->set_frameY(0);
                            if(esGuerrera == false){
                                j1->set_sprite(j1->txt_dash_D,1,1,sf::Vector2i(0,0));
                            }else{
                                j1->set_sprite(j1->txt_dash_D2,1,1,sf::Vector2i(0,0));
                            } 

                            j1->dash = true;
                            j1->termina_dash->restart();
                        }     
                    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                        if(!j1->saltando){
                            j1->vel_salto = -30.0f;
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
                        j1->vel_salto = -30.0f;
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
                    if(j1->crono_recarga_dash->asSeconds() > 0.5){
                        j1->movimiento = true;
                        j1->set_frameY(0); 
                        j1->dash = true;  // meter en todos los press z dash y quitar el desplazamiento
                        j1->termina_dash->restart();
                        

                        //Vemos a que lado esta mirando
                        if(j1->direccion == izq){
                            j1->dirColision = izq;
                            if(esGuerrera == false){
                                j1->set_sprite(j1->txt_dash_I,1,1,sf::Vector2i(0,0));
                            }else{
                                j1->set_sprite(j1->txt_dash_I2,1,1,sf::Vector2i(0,0));
                            }

                            
                            //j1->set_posicion(sf::Vector2f(j1->get_posicion().x - j1->vel_desp,(j1->get_posicion().y)));
                        }else{
                            j1->dirColision = der;
                            if(esGuerrera == false){
                                j1->set_sprite(j1->txt_dash_D,1,1,sf::Vector2i(0,0));
                            }else{
                                j1->set_sprite(j1->txt_dash_D2,1,1,sf::Vector2i(0,0));
                            }
                        }
                    }
                    
                }

//------------------------NPC INICIO---------------------------------------------------------------------------------------
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                //compruebo la posicion cerca del NPC - SI CAMBIAMOS LA POSICIÓN DEL NPC, REVISAR EL IF DEL RANGO
                if(npc != NULL){
                    std::cout << "Posicion X: " << npc->getPosicionEne().x - j1->get_posicion().x <<  std::endl;
                    std::cout << "Posicion Y: " << j1->get_posicion().y-npc->getPosicionEne().y << std::endl;
                    if(npc->getPosicionEne().x - j1->get_posicion().x >=30 && npc->getPosicionEne().x - j1->get_posicion().x<=60 && j1->get_posicion().y-npc->getPosicionEne().y <= 15 && j1->get_posicion().y-npc->getPosicionEne().y >= 5){
                        //aumento para que cambie a la siguiente imagen
                        variableAuxiliar+=100;
                    }
                }
            }
    //------------------------ATAQUE-------------------------------------------------------------------------------------------
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    if(!esGuerrera){
                        if(!p1){
                                p1 = new Proyectil(4,1,sf::Vector2i(0,0));
                                if(j1->direccion == der)
                                    p1->dirColision = derecha;
                                else
                                    p1->dirColision = izquierda;
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
                            j1->set_sprite(j1->txt_ataque_I,3,1,sf::Vector2i(0,0));
                        }else{
                            j1->dirColision = der;
                            j1->movimiento = true;
                            j1->set_frameY(0); 
                            j1->set_sprite(j1->txt_ataque_D,3,1,sf::Vector2i(0,0));
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
                        }
                            
                                
                        
                        else if(evento->key.code == (sf::Keyboard::Space)){
                            if(esGuerrera == false){
                                j1->movimiento = false;

                                if(j1->direccion == izq){
                                    j1->set_sprite(j1->txt_player,4,4,sf::Vector2i(0,2));
                                }else{
                                    j1->set_sprite(j1->txt_player,4,4,sf::Vector2i(0,3));
                                }
                                //j1->set_posicion(sf::Vector2f(j1->get_posicion().x, j1->get_posicion().y));
                            }else{
                                j1->movimiento = false;

                                if(j1->direccion == izq){
                                    j1->set_sprite(j1->txt_player,24,4,sf::Vector2i(0,2));
                                }else{
                                    j1->set_sprite(j1->txt_player2,4,4,sf::Vector2i(0,3));
                                }
                                
                            }
                            j1->set_posicion(sf::Vector2f(j1->get_posicion().x, j1->get_posicion().y));
                        }
                        break;
            
            default:
                    //j1->movimiento = false;
                    
            break;
        }
    }
}

void Juego::gestionGravedad(){
    int gid;
    sf::RectangleShape cajaMapa(sf::Vector2f(16, 16)); //Caja de colision de cada GID del mapa
    sf::RectangleShape box = j1->cajaColisiones; // sensor 1
    sf::RectangleShape box2 = j1->cajaColisiones2; // sensor 2
    //box2.setPosition(box.getPosition().x,box.getPosition().y + j1->tamFrame.y + 5);

    gravedad = true;

    for(unsigned int l = 0; l < 1; l++){
        for(unsigned int y = 0; y < mapa->heightMap; y++){
            for(unsigned int x = 0; x < mapa->widthMap; x++){
                gid = mapa->tilemap[l][y][x];

                cajaMapa.setPosition(sf::Vector2f(x*16, y*16));
                if(gid > 0)
                    if(cajaMapa.getGlobalBounds().intersects(j1->cajaColisiones2.getGlobalBounds())){ 
                        gravedad = false;
                    }

            }
        }
    }
}

bool Juego::colisionPersMapa(direcciones direccion){ //La colision del personaje con el mapa
    int gid;
    sf::RectangleShape cajaMapa(sf::Vector2f(16, 16)); //Caja de colision de cada GID del mapa
    bool colisionando = false;
    sf::RectangleShape box = j1->cajaColisiones;
    box.scale(1,1.05); //Se hace un pelín más grande
    for(unsigned int l = 0; l < 1; l++){
        for(unsigned int y = 0; y < mapa->heightMap; y++){
            for(unsigned int x = 0; x < mapa->widthMap; x++){
                gid = mapa->tilemap[l][y][x];
                cajaMapa.setPosition(sf::Vector2f(x*16, y*16));
            
                if(gid > 0 && direccion == 4 && !colisionando){ //Abajo
                    if(cajaMapa.getGlobalBounds().intersects(box.getGlobalBounds())){
                        if(cajaMapa.getGlobalBounds().intersects(j1->cajaColisiones.getGlobalBounds())){
                            j1->set_posicion(sf::Vector2f(j1->posInicial.x, j1->posInicial.y-1));
                            j1->dirColision = quieto;
                            colisionando = true;
                        }
                    }
                }
                if(gid > 0 && direccion == 1 && !colisionando){ //Arriba
                    if(cajaMapa.getGlobalBounds().intersects(j1->cajaColisiones.getGlobalBounds())){
                        j1->set_posicion(sf::Vector2f(j1->posInicial.x, j1->posInicial.y+1));
                        j1->dirColision = quieto;
                        if(j1->saltando)
                            j1->dirColision = abajo;
                        j1->vel_salto = 0;
                        colisionando = true;
                    }
                }
                if(gid > 0 && direccion == 2 && !colisionando){ //Izquierda
                    if(cajaMapa.getGlobalBounds().intersects(j1->cajaColisiones.getGlobalBounds())){
                        j1->set_posicion(sf::Vector2f(j1->posInicial.x+1, j1->posInicial.y));
                        j1->dirColision = quieto;
                        if(j1->saltando)
                            j1->dirColision = abajo;
                        colisionando = true;
                    }
                }
                if(gid > 0 && direccion == 3 && !colisionando){ //Derecha
                    if(cajaMapa.getGlobalBounds().intersects(j1->cajaColisiones.getGlobalBounds())){
                        j1->set_posicion(sf::Vector2f(j1->posInicial.x-1, j1->posInicial.y));
                        j1->dirColision = quieto;
                        if(j1->saltando)
                            j1->dirColision = abajo;
                        colisionando = true;
                    }
                }
            }
        }
    }
    return colisionando;
}

bool Juego::colisionProyecMapa(direccionProyectil direccion){ //La colision del proyectil con el mapa
    int gid;
    bool colisionando = false;
    sf::RectangleShape box(sf::Vector2f(16, 16));

    for(unsigned int l = 0; l < 1; l++){
        for(unsigned int y = 0; y < mapa->heightMap; y++){
            for(unsigned int x = 0; x < mapa->widthMap; x++){
                gid = mapa->tilemap[l][y][x];
                box.setPosition(sf::Vector2f(x*16, y*16));

                if(gid > 0 && direccion == 1 && !colisionando){ //Izquierda
                    if(box.getGlobalBounds().intersects(p1->get_sprite().getGlobalBounds())){
                        colisionando = true;
                    }
                }
                if(gid > 0 && direccion == 2 && !colisionando){ //Derecha
                    if(box.getGlobalBounds().intersects(p1->get_sprite().getGlobalBounds())){
                        colisionando = true;
                    }
                }                
            }
        }
    }
    return colisionando;
}

bool Juego::colisionPersTrampa(direcciones direccion){ //La colision del personaje con la trampa
    int gid;
    sf::RectangleShape box(sf::Vector2f(16, 16));
    bool colisionando = false;
    for(unsigned int l = 0; l < 1; l++){
        for(unsigned int y = 0; y < mapa->heightMap; y++){
            for(unsigned int x = 0; x < mapa->widthMap; x++){
                gid = mapa->tilemap[l][y][x]; // Es el id + 1
                box.setPosition(sf::Vector2f(x*16, y*16));

                if((gid == 144 || gid == 166 || gid == 168 || gid == 190 || gid == 213 || gid == 235 || gid == 237 || gid == 259) && direccion == 1 && !colisionando){ //Arriba
                    if(box.getGlobalBounds().intersects(j1->cajaColisiones.getGlobalBounds())){
                        colisionando = true;
                    }
                }

                if((gid == 144 || gid == 166 || gid == 168 || gid == 190 || gid == 213 || gid == 235 || gid == 237 || gid == 259)  && direccion == 2 && !colisionando){ //Izquierda
                    if(box.getGlobalBounds().intersects(j1->cajaColisiones.getGlobalBounds())){
                       colisionando = true;
                    }
                }

                if((gid == 144 || gid == 166 || gid == 168 || gid == 190 || gid == 213 || gid == 235 || gid == 237 || gid == 259)  && direccion == 3 && !colisionando){ //Derecha
                    if(box.getGlobalBounds().intersects(j1->cajaColisiones.getGlobalBounds())){
                        colisionando = true;
                    }
                }

                if((gid == 144 || gid == 166 || gid == 168 || gid == 190 || gid == 213 || gid == 235 || gid == 237 || gid == 259) && direccion == 4 && !colisionando){ //Abajo
                    if(box.getGlobalBounds().intersects(j1->cajaColisiones.getGlobalBounds())){
                        colisionando = true;
                    }
                }
                if(gid == 14 && !colisionando){
                    if(box.getGlobalBounds().intersects(j1->cajaColisiones.getGlobalBounds())){
                        j1->vida = 1;
                        colisionando = true;
                    }
                }
                
            }
        }
    }
    return colisionando;
}

void Juego::colisionPersPortal(){
    
    if(j1->cajaColisiones.getGlobalBounds().intersects(portal->getCaja().getGlobalBounds())){
        level++;
        cargar = false;
    }
}

void Juego::impacto(){
    if(!j1->inmortal){ 
        relojInmortal->restart();
        j1->inmortal = true;
        j1->vida --;
        if(j1->vida == 0)
            gameover = true;
        if(esGuerrera == false){
            if(j1->direccion == izq){
                j1->set_sprite(j1->txt_herido,4,4,sf::Vector2i(0,2));
            }
            
            if(j1->direccion == der){
                j1->set_sprite(j1->txt_herido,4,4,sf::Vector2i(0,3));
            }
        }else{
            if(j1->direccion == izq){
                j1->set_sprite(j1->txt_herido2,4,4,sf::Vector2i(0,2));
            }
            
            if(j1->direccion == der){
                j1->set_sprite(j1->txt_herido2,4,4,sf::Vector2i(0,3));
            }
        }
    }
}

void Juego::crearPortal(){
    delete portal;
    
    if(level == 1){
        portal = new Portal(145*16, 9*16);
        j1->set_posicion(sf::Vector2f(4*16,27*16));
        j1->dirColision = abajo;
        j1->vel_salto = 0;
        if(!textFondo.loadFromFile("resources/fondo1.jpg")){
    	    std::cout << "Error cargando imagen de fondo de la mazmorra 1" << std::endl;
	    }
    }
    if(level == 2){
        portal = new Portal(53*16, 32*16);
        j1->set_posicion(sf::Vector2f(5*16,33*16));

        j1->dirColision = abajo;
        j1->vel_salto = 0;
        if(!textFondo.loadFromFile("resources/boss1.jpg")){
    	    std::cout << "Error cargando imagen de fondo del boss 1" << std::endl;
	    }
    }
    if(level == 3){
        portal = new Portal(171*16, 25*16);
        j1->set_posicion(sf::Vector2f(3*16,27*16));
        j1->dirColision = abajo;
        j1->vel_salto = 0;
        if(!textFondo.loadFromFile("resources/fondo2.jpg")){
    	    std::cout << "Error cargando imagen de fondo de la mazmorra 2" << std::endl;
	    }
    }
    if(level == 4){
        portal = new Portal(53*16, 32*16);
        j1->set_posicion(sf::Vector2f(5*16,33*16));
        j1->dirColision = abajo;
        j1->vel_salto = 0;
        if(!textFondo.loadFromFile("resources/boss1.jpg")){
    	    std::cout << "Error cargando imagen de fondo del boss 2" << std::endl;
	    }
    }
    if(level == 5){
        portal = new Portal(170*16, 23*16);
        j1->set_posicion(sf::Vector2f(4*16,9*16));
        j1->dirColision = abajo;
        j1->vel_salto = 0;
        if(!textFondo.loadFromFile("resources/fondo3.png")){
    	    std::cout << "Error cargando imagen de fondo de la mazmorra 3" << std::endl;
	    }
    }
    if(level == 6){
        portal = new Portal(53*16, 32*16);
        j1->set_posicion(sf::Vector2f(5*16,33*16));
        j1->dirColision = abajo;
        j1->vel_salto = 0;
        if(!textFondo.loadFromFile("resources/boss1.png")){
    	    std::cout << "Error cargando imagen de fondo del boss 3" << std::endl;
	    }
    }
    fondo.setTexture(textFondo);
}

void Juego::crearEnemigos(){
    darkrai1 = NULL;
    darkrai2 = NULL;
    darkrai3 = NULL;
    mojoncito1 = NULL;
    mojoncito2 = NULL;
    mojoncito3 = NULL;
    kindercito1 = NULL;
    kindercito2 = NULL;
    kindercito3 = NULL;
    larita1 = NULL;
    larita2 = NULL;
    larita3 = NULL;
    npc = NULL;
    bossFinal = NULL;
    trueno = NULL;
    trueno2 = NULL;
    enemigos.clear();
    if(level == 1){
        darkrai1 = new Darkrai(125*16, 6*16, 25.0f, *j1->spr_player);
        mojoncito1 = new mojon(60*16, 38*16, 55*16, 68*16);
        kindercito1 = new KinderSorpresa(115*16, 150*16, 36*16, 40.0, *(j1->spr_player), *sp, 10);
        larita1 = new lara(83*16, 20*16);
        //NPC
        //inicializo NPC
        npc = new PersonajeNPC(4, 10, sf::Vector2i(0,0));
        npc -> cambiarPosicionEne(sf::Vector2f(290,310));
        npc->movimientoEne=false;
        npc->cambiarFrameYNPC(0);
        npc->setVelEne(sf::Vector2f(0.0, 0.0));
        npc->updateEne();

        //anyado todas las imagenes del monologo del NPC
        conver1.loadFromFile("resources/Sprites/conversacion/conver1.png");
        conversacionInicial.push_back(sf::Sprite(conver1));
        conver2.loadFromFile("resources/Sprites/conversacion/conver2.png");
        conversacionInicial.push_back(sf::Sprite(conver2));
        conver3.loadFromFile("resources/Sprites/conversacion/conver3.png");
        conversacionInicial.push_back(sf::Sprite(conver3));
        conver3.loadFromFile("resources/Sprites/conversacion/conver4.png");
        conversacionInicial.push_back(sf::Sprite(conver4));
        for(int i = 0; i < conversacionInicial.size(); i++){
            //conversacionInicial[i].setScale(1.5, 1.5);
            conversacionInicial[i].setPosition(sf::Vector2f(200,320));
        }
    }
    if(level == 2){  //Mojon hacerlo grandesico y más fuertote
        mojoncito1 = new mojon(43*16, 42*16, 4*16, 55*16);
        mojoncito1->getSprite().setScale(2.0, 2.0);
    }
    if(level == 3){
        darkrai1 = new Darkrai(51*16, 6*16, 25.0f, *j1->spr_player);
        darkrai2 = new Darkrai(172*16, 6*16, 25.0f, *j1->spr_player);
        mojoncito1 = new mojon(43*16, 29*16, 40*16, 48*16);
        mojoncito2 = new mojon(138*16, 26*16, 132*16, 146*16);
        kindercito1 = new KinderSorpresa(73*16, 99*16, 36*16, 40.0, *(j1->spr_player), *sp, 10);
        larita1 = new lara(6*16, 12*16);
        larita2 = new lara(111*16, 14*16);
    }
    if(level == 4){

    }
    if(level == 5){
        darkrai1 = new Darkrai(101*16, 12*16, 25.0f, *j1->spr_player);
        mojoncito1 = new mojon (9*16, 39*16, 4*16, 15*16);
        mojoncito2 = new mojon(69*16, 41*16, 65*16, 76*16);
        kindercito1 = new KinderSorpresa(85*16, 103*16, 34*16, 40.0, *(j1->spr_player), *sp, 10);
        larita1 = new lara(54*16, 16*16);
        larita2 = new lara (79*16, 10*16);
    }
    if(level == 6){
        //BOSS
        bossFinal = new PersonajeBoss(4, 10, sf::Vector2i(0,0));
        bossFinal -> cambiarPosicionBoss(sf::Vector2f(330,440));
        bossFinal->movimientoBoss=false;
        bossFinal->cambiarFrameYBoss(2);
        bossFinal->direccionBoss=izquierdaBoss;
        bossFinal->setVelBoss(sf::Vector2f(0.0, 0.0));
        bossFinal->updateBoss();    
        //inicializo rayo
        trueno = new Trueno(4, 2, sf::Vector2i(0,0));
        trueno -> cambiarPosicionEne(sf::Vector2f(200,300));
        trueno->movimientoEne=false;
        trueno->cambiarFrameYNPC(0);
        trueno->setVelEne(sf::Vector2f(0.0, 0.0));
        trueno->updateEne();

        trueno2 = new Trueno(4, 2, sf::Vector2i(0,0));
        trueno2 -> cambiarPosicionEne(sf::Vector2f(400,300));
        trueno2->movimientoEne=false;
        trueno2->cambiarFrameYNPC(0);
        trueno2->setVelEne(sf::Vector2f(0.0, 0.0));
        trueno2->updateEne();
    }
    enemigos.push_back(darkrai1);
    enemigos.push_back(darkrai2);
    enemigos.push_back(darkrai3);
    enemigos.push_back(mojoncito1);
    enemigos.push_back(mojoncito2);
    enemigos.push_back(mojoncito3);
    enemigos.push_back(kindercito1);
    enemigos.push_back(kindercito2);
    enemigos.push_back(kindercito3);
    enemigos.push_back(larita1);
    enemigos.push_back(larita2);
    enemigos.push_back(larita3);
}

void Juego::colisionesProtagonista(){ //REVISAR
    /*
    if(!muerteLara){
        if(larita1->Update(*ventana, j1, (83*16 + 100), (20*16))){
            impacto();
        }
    }
    if(!muerteDarkrai){
        if(darkrai1->colisionProtagonista(j1)){
            impacto();
        }
    }
    if(!muerteMojon){
        if(mojoncito1->colisionProtagonista(j1)){
            impacto();
        }
    }
    if(!muerteKinder){
        if(kindercito1->colisionProtagonista(j1)){
            impacto();
        }
    }
    */
}

void Juego::colisionProyectilEnemigos(){
    // Colision proyectil con mojon
    if(p1 != nullptr){
        if(!muerteMojon){
            if(mojoncito1->colisionProyectil(p1)){
                delete p1;        
                p1 = 0;
            }
        }
    }
    // Colision proyectil con lara
    if(p1 != nullptr){
        if(!muerteLara){
            if(larita1->colisionProyectil(p1)){
                delete p1;        
                p1 = 0;
            }
        }
    }
    // Colision proyectil con darkrai
    if(p1 != nullptr){
        if(!muerteDarkrai){
            if(darkrai1->colisionProyectil(p1)){
                delete p1;        
                p1 = 0;
            }
        }
    }
    // Colision proyectil con kinderSorpresa
    if(p1 != nullptr){
        if(!muerteKinder){
            if(kindercito1->colisionProyectil(p1)){
                delete p1;        
                p1 = 0;
            }
        }
    }
}

void Juego::muerteNPCs(){
    /*
    if(!muerteMojon){
        if(mojoncito1->morir()){
            delete mojoncito1;
            muerteMojon = true;
        }
    }
    if(!muerteDarkrai){
        if(darkrai1->morir()){
            delete darkrai1;
            muerteDarkrai = true;
        }
    }
    if(!muerteLara){
        if(larita1->morir()){
            delete larita1;
            muerteLara = true;
        }
    }
    if(!muerteKinder){
        if(kindercito1->morir()){
            delete kindercito1;
            muerteKinder = true;
        }
    }
    */
}

void Juego::detenerDash(){
    j1->movimiento = false;
    if(!j1->inmortal){
        if(esGuerrera == false){
            if(j1->direccion == izq){
                j1->set_sprite(j1->txt_player,4,4,sf::Vector2i(0,2));
            }
            
            if(j1->direccion == der){
                j1->set_sprite(j1->txt_player,4,4,sf::Vector2i(0,3));
            }
        }else{
            if(j1->direccion == izq){
                j1->set_sprite(j1->txt_player2,4,4,sf::Vector2i(0,2));
            }
            
            if(j1->direccion == der){
                j1->set_sprite(j1->txt_player2,4,4,sf::Vector2i(0,3));
            }
        }
    }else{
        if(esGuerrera == false){
            if(j1->direccion == izq){
                j1->set_sprite(j1->txt_herido,4,4,sf::Vector2i(0,2));
            }
            
            if(j1->direccion == der){
                j1->set_sprite(j1->txt_herido,4,4,sf::Vector2i(0,3));
            }
        }else{
            if(j1->direccion == izq){
                j1->set_sprite(j1->txt_herido2,4,4,sf::Vector2i(0,2));
            }
            
            if(j1->direccion == der){
                j1->set_sprite(j1->txt_herido2,4,4,sf::Vector2i(0,3));
            }
        }
    }
    j1->set_velocidad(sf::Vector2f(0,0));
    j1->set_posicion(sf::Vector2f(j1->get_posicion().x, j1->get_posicion().y));
}

//BOSS lanzamiento proyectil
void Juego::bossLanza(){

    *cronoBoss = relojBoss->getElapsedTime();
    int valor = rand() % 2; 
    //cada cierto tiempo el boss lanza un proyectil
    if(cronoBoss->asSeconds()>2.4){
            if(valor==0){
                pBoss = new Proyectil(4,1,sf::Vector2i(0,0));

                //si mira en direccion derecha, lanzara el proyectil hacia la izquierda
                if(bossFinal->direccionBoss == der)
                    pBoss->dirColision = derecha;
                else
                    pBoss->dirColision = izquierda;
                pBoss->posicionInicial = sf::Vector2f(pBoss->get_posicion().x,pBoss->get_posicion().y);
                
                //si mira en direccion izquierda, lanzara el proyectil hacia la izquierda
                if(bossFinal->direccionBoss == izq){

                    pBoss->set_posicion(sf::Vector2f(bossFinal->getPosicionBoss().x-20,bossFinal->getPosicionBoss().y));
                    pBoss->set_velocidad(sf::Vector2f(-pBoss->vel_desp,0));
                }
                else{
                    pBoss->set_posicion(sf::Vector2f(bossFinal->getPosicionBoss().x+20,bossFinal->getPosicionBoss().y));
                    pBoss->set_velocidad(sf::Vector2f(pBoss->vel_desp,0));
                }
            }else if(valor==1){
                //trueno->animarMuerteNPC();
            }
        //reinicio de reloj
        relojBoss->restart();
    }
}


//BOSS lanza trueno

//BOSS lanzamiento proyectil
void Juego::bossTrueno(){

    *cronoTrueno = relojTrueno->getElapsedTime();
    int valor = rand() % 2; 

    //cada cierto tiempo el boss lanza un proyectil
    if(cronoTrueno->asSeconds()>0.3){
        if(valor==0){
            trueno->animarNPC();
        }else if(valor==1){
            trueno2->animarMuerteNPC();
        }
            
        //reinicio de reloj
        relojTrueno->restart();
    }
}