#ifndef BIGLOVE_H_INCLUDED
#define BIGLOVE_H_INCLUDED

#include "angra.h"

void seePlaylist(sf::RenderWindow &window,PlayList * playlist)
{
    Jogador jogador;
    Tocador tocador;

    playlist->load();



    tocador.setPlaylist(playlist);
    jogador.setTocador(&tocador);


    jogador.tocador->init();
    jogador.tocador->update();
    jogador.tocador->open();
    jogador.tocador->play();

    bool trocou = false;

    negocioDoLado negocio;

    sf::RectangleShape background(sf::Vector2f(WIDTH,HEIGHT * 3));
    background.setFillColor(sf::Color(255,255,255,20));

    int yScroll = HEIGHT/2;

    sf::View fixedView(sf::FloatRect(0, 0,WIDTH , HEIGHT));
    sf::View movingView(sf::FloatRect(0,0 , WIDTH, HEIGHT));

    sf::RectangleShape quadradoDecima(sf::Vector2f(WIDTH - negocio.getSize().x,(HEIGHT - HEIGHT/6)/2.5));
    quadradoDecima.setFillColor(sf::Color(93,90,86));
    quadradoDecima.setPosition(negocio.getSize().x,0);

    //sf::RectangleShape foto(WIDTH/8,WIDTH/8);
    //foto.setPosition(quadradoDecima.getPosition() + Vector2f(WIDTH/20,WIDTH/20));

    sf::Font arial;
    arial.loadFromFile("fontes/arialBold.ttf");



    sf::Text nome;
    nome.setFont(arial);
    nome.setCharacterSize(WIDTH/20);
    nome.setFillColor(sf::Color::White);
    nome.setPosition(quadradoDecima.getPosition() + sf::Vector2f(WIDTH/20,WIDTH/20));
    nome.setString(playlist->getNome());



    sf::Text* musgas = new sf::Text[playlist->_size()];
    sf::RectangleShape* recMusga = new sf::RectangleShape[ playlist->_size()];

    int gap = WIDTH/25;
    for(int i = 0; i < playlist->_size(); i++)
    {
        recMusga[i].setSize(sf::Vector2f(quadradoDecima.getSize().x,gap));
        recMusga[i].setPosition(sf::Vector2f(negocio.getSize().x, gap * i + quadradoDecima.getGlobalBounds().height * 1.2));
        recMusga[i].setFillColor(sf::Color(255,255,255,20));

        musgas[i].setFont(arial);
        musgas[i].setCharacterSize(WIDTH/75);
        musgas[i].setFillColor(sf::Color::White);

        std::string temp = playlist[0][i]->musica;

        musgas[i].setString(temp.c_str() + 8);

        musgas[i].setPosition(sf::Vector2f(
                                  recMusga[i].getPosition().x + WIDTH/100,
                                  recMusga[i].getPosition().y + musgas[i].getGlobalBounds().height
                              ));


    }



    while (window.isOpen())
    {
        sf::Event event;

        sf::Vector2f mouse;

        mouse.x = sf::Mouse::getPosition(window).x;
        mouse.y = sf::Mouse::getPosition(window).y;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                {
                    if (event.mouseWheelScroll.delta < 0)
                    {
                        yScroll += 100;
                        movingView.setCenter(WIDTH/2,yScroll);

                    }else if(event.mouseWheelScroll.delta > 0){
                        yScroll -= 100;
                        if(yScroll < HEIGHT/2){
                            yScroll = HEIGHT/2;
                        }
                        movingView.setCenter(WIDTH/2,yScroll);

                    }
                }
            }


            for(int i = 0; i < playlist->_size(); i++)
            {
                if(recMusga[i].getGlobalBounds().contains(mouse))
                {
                    recMusga[i].setFillColor(sf::Color(255,255,255,40));
                }
                else
                {
                    recMusga[i].setFillColor(sf::Color(255,255,255,20));
                }

            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {

                    if(jogador.bAvancar.hover(mouse))
                    {
                        jogador.tocador->skip();
                        trocou = true;
                        if(jogador.isPlaying)
                        {
                            jogador.tocador->play();
                        }

                    }

                    if(jogador.bVoltar.hover(mouse))
                    {


                        jogador.tocador->previous();
                        trocou = true;
                        if(jogador.isPlaying)
                        {
                            jogador.tocador->play();
                        }

                    }

                    if(jogador.pButton.hover(mouse))
                    {

                        if(jogador.isPlaying)
                        {
                            jogador.tocador->pause();
                        }
                        else
                        {
                            if(trocou)
                            {
                                jogador.tocador->play();
                                trocou = false;
                            }
                            else
                            {
                                jogador.tocador->desPause();
                                trocou = false;
                            }

                        }
                        jogador.isPlaying = !jogador.isPlaying;


                    }

                }
            }

        }

        jogador.negQficaGrande.update( (double) jogador.tocador->getMusicPosicion() / jogador.tocador->getMusicDuration());

        jogador.bAvancar.hover(mouse);
        jogador.bVoltar.hover(mouse);
        jogador.negQficaGrande.hover(mouse,window);

        window.clear();



        window.setView(movingView);

        window.draw(background);
        window.draw(quadradoDecima);

        window.draw(nome);

        for(int i = 0; i < playlist->_size(); i++)
        {
            window.draw(recMusga[i]);
            window.draw(musgas[i]);
        }


        window.setView(fixedView);
        negocio.show(window);
        jogador.show(window);

        window.display();
    }
}



#endif // BIGLOVE_H_INCLUDED
