#include "KinderSorpresa.h"

KinderSorpresa::KinderSorpresa(int pos1, int pos2, int posy, float speed, sf::Sprite &_pj1, sf::Sprite &_pj2, int vidas) : Enemigo(vidas) {
    this->speed = speed;

    // Asignamos los personajes que tiene que perseguir...
    if (&_pj1) {
        personaje1 = &_pj1;
    } else {
        personaje1 = NULL;
    }
    if (&_pj2) {
        personaje2 = &_pj2;
    } else {
        personaje2 = NULL;
    }

    // Establecemos el rango de movilidad...
    rangoMovimiento[0] = pos1;
    rangoMovimiento[1] = pos2;

    // Cargamos textura...
    textura.loadFromFile("resources/Sprites/Kinder Sorpresa/KinderSorpresa.png");
    textura.setSmooth(true);

    // Creamos sprite y animacion...
    body = new Sprite(textura);
    body->setPosition((pos1+pos2)/2, posy);
    animacion = new AnimationKinder(&textura, 0.5);
    body->setTextureRect(animacion->getCoordenadasRect());
    body->setOrigin(animacion->getOrigin());

    // Establecemos los limites colisionables...
    boundingSet[0].setSize(sf::Vector2f(64, 102));
    boundingSet[1].setSize(sf::Vector2f(61, 111));
    boundingSet[2].setSize(sf::Vector2f(107, 72));
    boundingSet[3].setSize(sf::Vector2f(113, 59));
    boundingSet[4].setSize(sf::Vector2f(134, 60));
    boundingSet[5].setSize(sf::Vector2f(64, 72));
    boundingSet[6].setSize(sf::Vector2f(63, 68));
    boundingSet[7].setSize(sf::Vector2f(95, 112));
    boundingSet[8].setSize(sf::Vector2f(92, 110));
    boundingSet[9].setSize(sf::Vector2f(53, 107));
    boundingSet[10].setSize(sf::Vector2f(50, 107));
    boundingSet[11].setSize(sf::Vector2f(93, 65));
    for (int i=0; i<12; i++) {
        boundingSet[i].setOrigin(boundingSet[i].getSize().x/2, boundingSet[i].getSize().y);
        boundingSet[i].setFillColor(sf::Color(150,50,20,80));
    }
    ajustes[0] = 12.0;
    ajustes[1] = 10.5;
    ajustes[2] = -11.5;
    ajustes[3] = -11.5;
    ajustes[4] = -22.0;
    ajustes[5] = 16;
    ajustes[6] = 15.5;
    ajustes[7] = 37.5;
    ajustes[8] = 37;
    ajustes[9] = 18.5;
    ajustes[10] = 16;
    ajustes[11] = 6.5;

    // La caja inicial...
    boundingBox = &boundingSet[0];
    boundingBox->setPosition(body->getPosition().x-ajustes[0], body->getPosition().y-17);
}


KinderSorpresa::~KinderSorpresa() {
    boundingBox = NULL;
    delete animacion;
    animacion = NULL;
    personaje1 = NULL;
    personaje2 = NULL;
    delete body;
    body = NULL;
    rangoMovimiento[0] = 0;
    rangoMovimiento[1] = 0;
}


void KinderSorpresa::Update(float deltaTime) {
    if(restartear == true){
        impactado.restart();
        restartear = false;
    }
    this->impactoProyectil();
    if(golpeado == false){
        sf::Vector2f _distancia1(0.0, 0.0);
        sf::Vector2f _distancia2(0.0, 0.0);
        sf::Vector2f _distancia;
        sf::Sprite *_pj = NULL;
        int indice = animacion->getIndice();
        float _desplazamiento = ajustes[indice];

        // Comprobamos el personaje que esta mas cerca...
        if (personaje1) {
            _distancia1.x = abs(body->getPosition().x)-abs(personaje1->getPosition().x);
            _distancia1.y = abs(abs(body->getPosition().y)-abs(personaje1->getPosition().y));
        }
        if (personaje2) {
            _distancia2.x = abs(body->getPosition().x)-abs(personaje2->getPosition().x);
            _distancia2.y = abs(abs(body->getPosition().y)-abs(personaje2->getPosition().y));
        }

        // Asignamos fuera la distancia para que siempre se oriente al personaje
        if (personaje2 != NULL) {
            bool _rango1 = this->estaEnRango(personaje1),
                _rango2 = this->estaEnRango(personaje2);

            if (_rango1  &&  !_rango2) {
                _pj = personaje1;
                _distancia = _distancia1;
            } else if (!_rango1  &&  _rango2) {
                _pj = personaje2;
                _distancia = _distancia2;
            } else if (!_rango1  &&  !_rango2) {
                _distancia = (abs(_distancia1.x) > abs(_distancia2.x)) ? _distancia2 : _distancia1;
            } else {
                if (abs(_distancia1.x) > abs(_distancia2.x)) {
                    _pj = personaje2;
                    _distancia = _distancia2;
                } else {
                    _pj = personaje1;
                    _distancia = _distancia1;
                }
            } 
        } else {
            _distancia = _distancia1;
            if (this->estaEnRango(personaje1))
                _pj = personaje1;
        }

        // Orientamos personaje...
        if (_distancia.x < 0.0) {
            miraIzquierda = false;
            if (!estaAtacando)
                body->setScale(-1, 1);
            _desplazamiento = -_desplazamiento;
        } else {
            miraIzquierda = true;
            if (!estaAtacando)
                body->setScale(1, 1);
        }
        _distancia.x = abs(_distancia.x);

        // Calculamos parametros de accion del NPC
        ejecuta = 2;
        if (_pj != NULL  &&  !estaAtacando) {

            // Si kinder esta dentro del rango de ataque...
            if (_distancia.x > body->getTextureRect().width/3) {
                if (body->getPosition().x >= rangoMovimiento[0]  &&  body->getPosition().x <= rangoMovimiento[1]) {
                    ejecuta = 1;
                    if (miraIzquierda) {
                        body->move(-speed*deltaTime, 0);
                    } else {
                        body->move(speed*deltaTime, 0);
                    }
                } else if (body->getPosition().x < rangoMovimiento[0]) {
                    body->setPosition(rangoMovimiento[0], body->getPosition().y);
                } else if (body->getPosition().x > rangoMovimiento[1]) {
                    body->setPosition(rangoMovimiento[1], body->getPosition().y);
                }
            } else if (relojAtaque.getElapsedTime().asSeconds() > 1.5f) {
                estaAtacando = true;
            }
        }

        // Actualizamos animacion...
        if (estaAtacando) {
            if (animacion->UpdateAttack(deltaTime)) {
                estaAtacando = false;
                relojAtaque.restart();
            }
        } else {
            animacion->UpdateMovement(deltaTime, ejecuta);
        }
        body->setTextureRect(animacion->getCoordenadasRect());

        // Posicionamos y setteamos bounding...
        if (ejecuta == 1  &&  indice == 1) {
            indice = 11;
        }
        boundingBox = &boundingSet[indice];
        boundingBox->setPosition(body->getPosition().x-_desplazamiento, body->getPosition().y-17);

        _pj = NULL;
    }
}


bool KinderSorpresa::estaEnRango(sf::Sprite *p) {
    bool _devuelve = false;
    float _altura = body->getTextureRect().height;
    float _pos_personaje = p->getPosition().y;

    if (_pos_personaje >= (body->getPosition().y-_altura+40)) {
        if (p->getPosition().x >= rangoMovimiento[0]  &&  p->getPosition().x <= rangoMovimiento[1]) {
            _devuelve = true;
        }
    }
    
    return _devuelve;
}

bool KinderSorpresa::colisionProyectil(Proyectil *p1){
        bool x = false;
        if(p1->get_sprite().getGlobalBounds().intersects(boundingBox->getGlobalBounds()) && golpeado == false){
            x = true;
            golpeado = true;
            restartear = true;           
        }
        return x;
    }

void KinderSorpresa::impactoProyectil(){
    float sgs = impactado.getElapsedTime().asSeconds();
    if(golpeado == true){
        if(contando % 2 == 0){
            body->setColor(sf::Color::Red);
            contando++;
        }
        else{
            this->hacerTransparente();
            contando++;
        }
        if(sgs >= 1){
            body->setColor(sf::Color(255, 255, 255));
            golpeado = false;
        }
    }
}


void KinderSorpresa::recibeGolpe() {
    if (!esGolpeado) {
        esGolpeado = true;
        this->perderVida();
    }
}


void KinderSorpresa::Draw(RenderWindow &window) {
    if (esGolpeado) {
        esGolpeado = false;
    } else {
        window.draw(*body);
    }
}

void KinderSorpresa::hacerTransparente(){
    body->setColor(Color::Transparent);
}

sf::RectangleShape KinderSorpresa::getBoundingBox() {
    return *boundingBox;
}