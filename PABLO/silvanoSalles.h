#ifndef SILVANOSALLES_H_INCLUDED
#define SILVANOSALLES_H_INCLUDED

#include "angra.h"

void homePage(sf::RenderWindow &window) {

    negocioDoLado negocio;
    Jogador jogador;
    Tocador tocador;

    PlayList playlist("SO AS MELHORES");
    playlist.load();


    tocador.setPlaylist(&playlist);
    jogador.setTocador(&tocador);

    jogador.tocador->init();
    jogador.tocador->update();
    jogador.tocador->play();


    sf::RectangleShape background(sf::Vector2f(WIDTH,HEIGHT));
    background.setFillColor(sf::Color(255,255,255,20));

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

        window.clear();

        window.draw(background);
        negocio.show(window);
        jogador.show(window);

        window.display();
    }
}


#endif // SILVANOSALLES_H_INCLUDED
