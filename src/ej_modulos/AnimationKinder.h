#pragma once
#include <SFML/Graphics.hpp>

class AnimationKinder {
    private:

        sf::IntRect *coordenadasRect;  // Coordenadas de recorte de la textura
        float tiempoTotal = 0.0;      // Tiempo total de la animación
        float tiempoCambio;            // Tiempo de visualización del sprite
        float tiempoTotalAtq = 0.0; // Para el tiempo de ataque
        int indice = 0;       // Indice para la zona de recortes
        std::vector<sf::IntRect> coordEstatico; // Recortes del personaje estatico
        std::vector<sf::IntRect> coordAtaque; // Recortes del personaje atacando
        std::vector<sf::IntRect> coordMovimiento; // Recortes del personaje atacando
        std::vector<sf::IntRect> *coordActual; // Accion actual
        int ejecuta = 2;      // Animacion a ejecutar: 1->Movimiento, 2->Estatico


    public:

        AnimationKinder(sf::Texture*, float);
        ~AnimationKinder();
        void UpdateMovement(float ,int );
        bool UpdateAttack(float );
        sf::IntRect getCoordenadasRect();
        sf::Vector2f getOrigin();
        int getIndice();
};