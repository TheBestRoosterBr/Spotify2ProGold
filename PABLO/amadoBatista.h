#ifndef AMADOBATISTA_H_INCLUDED
#define AMADOBATISTA_H_INCLUDED

#include "angra.h"

void homePage(sf::RenderWindow &window) {

    negocioDoLado negocio;
    Jogador jogador;

    jogador.setTocador(&tocador);

    jogador.tocador->init();
    jogador.tocador->update();
    jogador.tocador->play();


    sf::RectangleShape background(sf::Vector2f(WIDTH,HEIGHT));
    background.setFillColor(sf::Color(255,255,255,20));

    std::vector <sf::RectangleShape> quadros;
    std::vector <PlayButton> butoes;





    bool trocou = false;


    while (window.isOpen()) {
        sf::Event event;

        sf::Vector2f mouse;

        mouse.x = sf::Mouse::getPosition(window).x;
        mouse.y = sf::Mouse::getPosition(window).y;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            negocio.handleEvents(window,event,mouse);
            jogador.handleEvent(window,event,mouse,trocou);

        }

        jogador.negQficaGrande.update((double)jogador.tocador->getMusicPosicion() / jogador.tocador->getMusicDuration());

        jogador.bAvancar.hover(mouse);
        jogador.bVoltar.hover(mouse);
        jogador.negQficaGrande.hover(mouse,window);


        jogador.ltimer.update(sf::seconds(jogador.tocador->getMusicPosicion()));
        jogador.rtimer.update(sf::seconds(jogador.tocador->getMusicDuration()));

        if(jogador.tocador->music->getStatus() != sf::Music::Playing && jogador.tocador->music->getStatus() != sf::Music::Paused){

            if(jogador.lButton.getValue()){
                jogador.tocador->music->setPosition(sf::seconds(0));
                jogador.tocador->play();
            }
            else{
                jogador.tocador->skip(jogador.rButton.getValue());
                jogador.tocador->play();

            }

        }


        window.clear();

        window.draw(background);
        negocio.show(window);
        jogador.show(window);

        window.display();
    }
}

#endif // AMADOBATISTA_H_INCLUDED
