#ifndef BIGLOVE_H_INCLUDED
#define BIGLOVE_H_INCLUDED

#include "angra.h"
#include "ListaString.h"

void seePlaylist(sf::RenderWindow &window,string playList)
{

    println(playList);
    Jogador jogador;

    tocador.pause();

    playlist.setNome(playList);
    playlist.load();


    jogador.setTocador(&tocador);


    jogador.tocador->init();
    jogador.tocador->update();
    jogador.tocador->open();
    //jogador.tocador->play();







    bool trocou = false;

    negocioDoLado negocio;

    sf::RectangleShape background(sf::Vector2f(WIDTH,HEIGHT * 3));
    background.setFillColor(sf::Color(255,255,255,20));

    int yScroll = HEIGHT/2;

    sf::View fixedView(sf::FloatRect(0, 0,WIDTH, HEIGHT));
    sf::View movingView(sf::FloatRect(0,0, WIDTH, HEIGHT));

    sf::RectangleShape quadradoDecima(sf::Vector2f(WIDTH - negocio.getSize().x,(HEIGHT - HEIGHT/6)/2.5));
    quadradoDecima.setFillColor(sf::Color(93,90,86));
    quadradoDecima.setPosition(negocio.getSize().x,0);

    //sf::RectangleShape foto(WIDTH/8,WIDTH/8);
    //foto.setPosition(quadradoDecima.getPosition() + Vector2f(WIDTH/20,WIDTH/20));

    PlayButton pButton;
    pButton.setSize(WIDTH/35);
    pButton.setFillColor(sf::Color(212,175,55));
    pButton.setPosition(sf::Vector2f(negocio.getSize().x * 1.25,quadradoDecima.getSize().y/2));




    sf::Font arial;
    arial.loadFromFile("fontes/arialBold.ttf");



    sf::Text nome;
    nome.setFont(arial);
    nome.setCharacterSize(WIDTH/20);
    nome.setFillColor(sf::Color::White);
    nome.setPosition(quadradoDecima.getPosition() + sf::Vector2f(WIDTH/20,WIDTH/20));
    nome.setString(playlist.getNome());



    sf::Text* musgas = new sf::Text[playlist._size()];
    sf::RectangleShape* recMusga = new sf::RectangleShape[ playlist._size()];

    int gap = WIDTH/25;

    for(int i = 0; i < playlist._size(); i++)
    {

        recMusga[i].setSize(sf::Vector2f(quadradoDecima.getSize().x,gap));
        recMusga[i].setPosition(sf::Vector2f(negocio.getSize().x, gap * i + quadradoDecima.getGlobalBounds().height * 1.2));
        recMusga[i].setFillColor(sf::Color(255,255,255,20));

        musgas[i].setFont(arial);
        musgas[i].setCharacterSize(WIDTH/75);
        musgas[i].setFillColor(sf::Color::White);

        std::string temp = playlist[i]->musica;



        musgas[i].setString(temp.c_str() + 8);

        musgas[i].setPosition(sf::Vector2f(
                                  recMusga[i].getPosition().x + WIDTH/100,
                                  recMusga[i].getPosition().y + musgas[i].getGlobalBounds().height
                              ));


    }



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


            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                {
                    if (event.mouseWheelScroll.delta < 0)
                    {
                        yScroll += 100;
                        movingView.setCenter(WIDTH/2,yScroll);

                    } else
                        if(event.mouseWheelScroll.delta > 0) {
                            yScroll -= 100;
                            if(yScroll < HEIGHT/2) {
                                yScroll = HEIGHT/2;
                            }
                            movingView.setCenter(WIDTH/2,yScroll);

                        }
                }
            }
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), movingView);

            for(int i = 0; i < playlist._size(); i++)
            {
                if(recMusga[i].getGlobalBounds().contains(mousePos))
                {

                    recMusga[i].setFillColor(sf::Color(255,255,255,40));
                } else {
                    recMusga[i].setFillColor(sf::Color(255,255,255,20));
                }

            }

            jogador.handleEvent(window,event,mouse,trocou);

        }

        jogador.negQficaGrande.update( (double) jogador.tocador->getMusicPosicion() / jogador.tocador->getMusicDuration());

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
        window.draw(quadradoDecima);

        window.draw(nome);

        for(int i = 0; i < playlist._size(); i++)
        {

            window.draw(recMusga[i]);
            window.draw(musgas[i]);
        }
        pButton.show(window,false);

        window.setView(fixedView);

        negocio.show(window);
        jogador.show(window);

        window.display();
    }
}



#endif // BIGLOVE_H_INCLUDED
