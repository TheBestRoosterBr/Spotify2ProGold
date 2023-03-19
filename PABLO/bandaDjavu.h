#ifndef DJJUNINHOPORTUGAL_H_INCLUDED
#define DJJUNINHOPORTUGAL_H_INCLUDED

#include "angra.h"

void createPlaylist(sf::RenderWindow &window)
{


    negocioDoLado negocio;

    sf::RectangleShape background(sf::Vector2f(WIDTH,HEIGHT));
    background.setFillColor(sf::Color(255,255,255,20));

    sf::RectangleShape quadradoDecima(sf::Vector2f(WIDTH - negocio.getSize().x,(HEIGHT - HEIGHT/6)/2));
    quadradoDecima.setFillColor(sf::Color(93,90,86));
    quadradoDecima.setPosition(negocio.getSize().x,0);

    //sf::RectangleShape foto(WIDTH/8,WIDTH/8);
    //foto.setPosition(quadradoDecima.getPosition() + Vector2f(WIDTH/20,WIDTH/20));

    sf::Font arial;
    arial.loadFromFile("fontes/arialBold.ttf");

    string name = "Minha playlist";

    sf::Text nome;
    nome.setFont(arial);
    nome.setCharacterSize(WIDTH/20);
    nome.setFillColor(sf::Color::White);
    nome.setPosition(quadradoDecima.getPosition() + sf::Vector2f(WIDTH/20,WIDTH/20));
    nome.setString(name);

    bool trocarNome = false;


    sf::Text nomenome;
    nomenome.setFont(arial);
    nomenome.setCharacterSize(WIDTH/50);
    nomenome.setFillColor(sf::Color::White);
    nomenome.setPosition(sf::Vector2f(nome.getPosition().x,nome.getPosition().y - nome.getGlobalBounds().height/2));
    nomenome.setString("nome:");

    sf::Text vamos;
    vamos.setFont(arial);
    vamos.setCharacterSize(WIDTH/50);
    vamos.setFillColor(sf::Color::White);
    vamos.setPosition(sf::Vector2f(negocio.getSize().x + vamos.getGlobalBounds().width/4,quadradoDecima.getGlobalBounds().height));
    vamos.setString("Vamos incrementar sua playlist");

    std::vector <string> musicas;


    Jogador jogador;
    Tocador tocador;

    PlayList playlist("SO AS MELHORES");
    playlist.load();


    tocador.setPlaylist(&playlist);
    jogador.setTocador(&tocador);

    jogador.tocador->init();
    jogador.tocador->update();
    jogador.tocador->play();


    bool trocou = false;


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

            if(trocarNome)
            {
                if (event.type == sf::Event::TextEntered)
                {
                    if (event.text.unicode == '\b' && name.size() > 0) // Handle backspace
                    {
                        name.pop_back();
                    }else if (event.text.unicode == sf::Keyboard::Enter) // Handle enter key
                    {
                        trocarNome = false;
                    }
                    else if (event.text.unicode < 128) // Handle input characters
                    {
                        name += static_cast<char>(event.text.unicode);
                    }
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

                    if(nome.getGlobalBounds().contains(mouse) && trocarNome == false)
                    {
                        trocarNome = true;
                        name = "";
                    }




                }
            }

        }

        jogador.negQficaGrande.update( (double) jogador.tocador->getMusicPosicion() / jogador.tocador->getMusicDuration());

        jogador.bAvancar.hover(mouse);
        jogador.bVoltar.hover(mouse);
        jogador.negQficaGrande.hover(mouse,window);
        window.clear();


        window.draw(background);
        window.draw(quadradoDecima);

        nome.setString(name);

        window.draw(nome);
        window.draw(vamos);
        if(trocarNome)
        {
            window.draw(nomenome);
        }

        negocio.show(window);
        jogador.show(window);
        window.display();
    }
}






#endif
