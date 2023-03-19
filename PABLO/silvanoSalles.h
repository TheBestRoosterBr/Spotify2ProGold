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

            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left)
                {

                    if(jogador.bAvancar.hover(mouse)){
                            jogador.tocador->skip();
                            trocou = true;
                            if(jogador.isPlaying){
                                jogador.tocador->play();
                            }

                    }

                    if(jogador.bVoltar.hover(mouse)){


                        jogador.tocador->previous();
                        trocou = true;
                        if(jogador.isPlaying){
                                jogador.tocador->play();
                        }

                    }

                    if(jogador.pButton.hover(mouse)){

                        if(jogador.isPlaying){
                            jogador.tocador->pause();
                        }
                        else {
                            if(trocou){
                                jogador.tocador->play();
                                trocou = false;
                            }
                            else{
                                jogador.tocador->desPause();
                                trocou = false;
                            }

                        }
                        jogador.isPlaying = !jogador.isPlaying;


                    }



                }
            }

        }

        jogador.negQficaGrande.update(  (double) jogador.tocador->getMusicPosicion() / jogador.tocador->getMusicDuration());

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
