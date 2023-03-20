#ifndef AMADOBATISTA_H_INCLUDED
#define AMADOBATISTA_H_INCLUDED

#include "angra.h"

void biblioteca(sf::RenderWindow &window) {

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

    std::vector <string> plists  = get_filenames("Playlists");

    for(int i = 0; i < plists.size(); i++){


    }
    int yScroll = HEIGHT/2;

    sf::View fixedView(sf::FloatRect(0, 0,WIDTH, HEIGHT));
    sf::View movingView(sf::FloatRect(0,0, WIDTH, HEIGHT));



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
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    if (event.mouseWheelScroll.delta < 0) {
                        yScroll += 100;
                        movingView.setCenter(WIDTH/2,yScroll);

                    } else if(event.mouseWheelScroll.delta > 0) {
                        yScroll -= 100;
                        if(yScroll < HEIGHT/2) {
                            yScroll = HEIGHT/2;

                        }
                        movingView.setCenter(WIDTH/2,yScroll);

                    }
                }
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
        window.setView(movingView);
        window.draw(background);









        window.setView(fixedView);
        negocio.show(window);
        jogador.show(window);

        window.display();
    }
}

#endif // AMADOBATISTA_H_INCLUDED
