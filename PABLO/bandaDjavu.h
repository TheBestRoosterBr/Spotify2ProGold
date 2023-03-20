#ifndef DJJUNINHOPORTUGAL_H_INCLUDED
#define DJJUNINHOPORTUGAL_H_INCLUDED

#include "angra.h"
void atualizarPosicao(std::vector <string> musicas,sf::Text* musgas,sf::RectangleShape* recMusga,sf::Text* addMusga,
                      double x,double negociox,double gap,double y,sf::Font& font) {

    for(int i = 0; i < musicas.size(); i++) {

        recMusga[i].setSize(sf::Vector2f(x,gap));
        recMusga[i].setPosition(sf::Vector2f(negociox, gap * i + y * 1.2));
        recMusga[i].setFillColor(sf::Color(255,255,255,20));

        addMusga[i].setFont(font);
        addMusga[i].setCharacterSize(WIDTH/75);
        addMusga[i].setFillColor(sf::Color::White);
        addMusga[i].setString("Adicionar");
        addMusga[i].setPosition(sf::Vector2f(
                                    WIDTH - addMusga[i].getGlobalBounds().width * 1.5,
                                    recMusga[i].getPosition().y + addMusga[i].getGlobalBounds().height
                                ));
        musgas[i].setFont(font);
        musgas[i].setCharacterSize(WIDTH/75);
        musgas[i].setFillColor(sf::Color::White);
        musgas[i].setString(musicas[i]);
        musgas[i].setPosition(sf::Vector2f(
                                  recMusga[i].getPosition().x + WIDTH/100,
                                  recMusga[i].getPosition().y + addMusga[i].getGlobalBounds().height
                              ));

    }

}

void createPlaylist(sf::RenderWindow &window) {
    Jogador jogador;
    jogador.setTocador(&tocador);


    PlayList newPlaylist;


    bool trocou = false;


    negocioDoLado negocio;

    sf::RectangleShape background(sf::Vector2f(WIDTH,HEIGHT * 3));
    background.setFillColor(sf::Color(255,255,255,20));

    int yScroll = 0;

    sf::View fixedView(sf::FloatRect(0, 0,WIDTH, HEIGHT));
    sf::View movingView(sf::FloatRect(0,0, WIDTH, HEIGHT));

    sf::RectangleShape quadradoDecima(sf::Vector2f(WIDTH - negocio.getSize().x,(HEIGHT - HEIGHT/6)/2.5));
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
    vamos.setPosition(sf::Vector2f(negocio.getSize().x * 1.1,quadradoDecima.getGlobalBounds().height ));
    vamos.setString("Vamos incrementar sua playlist");

    FolderScanner scan;
    std::vector <string> musicas;
    std::vector <sf::Text> musgasAdds;
    std::vector <sf::Text> remover;

    if(argumentos == 1)
        scan.setPath("musicas");
    else
        scan.setPath(arq);

    scan.scan(musicas);

    sf::Text* musgas = new sf::Text[musicas.size()];
    sf::RectangleShape* recMusga = new sf::RectangleShape[musicas.size()];
    sf::Text* addMusga = new sf::Text[musicas.size()];

    int gap = WIDTH/25;
    for(int i = 0; i < musicas.size(); i++) {
        recMusga[i].setSize(sf::Vector2f(quadradoDecima.getSize().x,gap));
        recMusga[i].setPosition(sf::Vector2f(negocio.getSize().x, gap * i + quadradoDecima.getGlobalBounds().height * 1.2));
        recMusga[i].setFillColor(sf::Color(255,255,255,20));

        addMusga[i].setFont(arial);
        addMusga[i].setCharacterSize(WIDTH/75);
        addMusga[i].setFillColor(sf::Color::White);
        addMusga[i].setString("Adicionar");
        addMusga[i].setPosition(sf::Vector2f(
                                    WIDTH - addMusga[i].getGlobalBounds().width * 1.5,
                                    recMusga[i].getPosition().y + addMusga[i].getGlobalBounds().height
                                ));
        musgas[i].setFont(arial);
        musgas[i].setCharacterSize(WIDTH/75);
        musgas[i].setFillColor(sf::Color::White);
        musgas[i].setString(musicas[i]);
        musgas[i].setPosition(sf::Vector2f(
                                  recMusga[i].getPosition().x + WIDTH/100,
                                  recMusga[i].getPosition().y + addMusga[i].getGlobalBounds().height
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
            jogador.handleEvent(window,event,mouse,trocou);

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


            if(trocarNome) {
                if (event.type == sf::Event::TextEntered) {
#define L 13
                    println((int)event.text.unicode);
                    if (event.text.unicode == '\b' && name.size() > 0) { // Handle backspace
                        name.pop_back();
                        println(name);

                    } else if (event.text.unicode == L) { // Handle enter key
                        trocarNome = false;

                        newPlaylist.setNome(name);
                    } else if (event.text.unicode < 128) { // Handle input characters
                        name += static_cast<char>(event.text.unicode);
                    }
                }
#undef L
            }

            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), movingView);

            for(int i = 0; i < musicas.size(); i++) {
                if(recMusga[i].getGlobalBounds().contains(mousePos)) {
                    recMusga[i].setFillColor(sf::Color(255,255,255,40));
                } else {
                    recMusga[i].setFillColor(sf::Color(255,255,255,20));
                }

                if(addMusga[i].getGlobalBounds().contains(mousePos)) {
                    addMusga[i].setCharacterSize(WIDTH/70);
                } else {
                    addMusga[i].setCharacterSize(WIDTH/75);
                }
            }

            for(int i = 0; i < remover.size(); i++ ) {
                if(remover[i].getGlobalBounds().contains(mousePos)) {
                    remover[i].setCharacterSize(WIDTH/65);
                } else {
                    remover[i].setCharacterSize(WIDTH/75);
                }
            }


            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {

                    for(int i = 0; i < newPlaylist._size(); ++i)
                        println(newPlaylist[i]->musica);

                    for(int i = 0; i < remover.size(); i++) {
                        if(remover[i].getGlobalBounds().contains(mousePos)) {
                            newPlaylist.removerPosicao(i);
                            println("o erro ta na materia?");
                            newPlaylist.savePlaylist();

                            musgasAdds.erase(musgasAdds.begin()+i);
                            remover.erase(remover.begin() + i);


                            for(int i = 0; i < musgasAdds.size(); i++) {
                                double y =  quadradoDecima.getGlobalBounds().height * 1.2 + WIDTH/75 * i * 3;
                                musgasAdds[i].setPosition(sf::Vector2f(negocio.getSize().x,y));
                            }

                            double y =  quadradoDecima.getGlobalBounds().height * 1.2 + WIDTH/75 * musgasAdds.size() * 3;
                            atualizarPosicao(musicas,musgas,recMusga, addMusga,
                                             quadradoDecima.getSize().x,negocio.getSize().x,gap, y,arial);




                        }
                    }

                    for(int i = 0; i < musicas.size(); i++) {

                        if(addMusga[i].getGlobalBounds().contains(mousePos)) {

                            newPlaylist.push_back("musicas\\" + musicas[i]);
                            newPlaylist.savePlaylist();
                            sf::Text txt;
                            txt.setFont(arial);
                            txt.setCharacterSize(WIDTH/75);
                            txt.setFillColor(sf::Color::White);
                            txt.setString(musicas[i]);

                            double y =  quadradoDecima.getGlobalBounds().height * 1.2 + WIDTH/75 * musgasAdds.size() * 3;

                            txt.setPosition(sf::Vector2f(negocio.getSize().x,y));

                            musgasAdds.push_back(txt);

                            sf::Text remov;
                            remov.setFont(arial);
                            remov.setCharacterSize(WIDTH/75);
                            remov.setFillColor(sf::Color::White);
                            remov.setString("Remover");
                            remov.setPosition(sf::Vector2f(WIDTH - remov.getGlobalBounds().width * 1.25,y));

                            remover.push_back(remov);

                            println("sim eh o taualizafa");


                            atualizarPosicao(musicas,musgas,recMusga, addMusga,
                                             quadradoDecima.getSize().x,negocio.getSize().x,gap, y,arial);




                        }
                    }

                    if(nome.getGlobalBounds().contains(mouse) && trocarNome == false) {
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

        jogador.ltimer.update(sf::seconds(jogador.tocador->getMusicPosicion()));
        jogador.rtimer.update(sf::seconds(jogador.tocador->getMusicDuration()));

        if(jogador.tocador->music->getStatus() != sf::Music::Playing && jogador.tocador->music->getStatus() != sf::Music::Paused) {

            if(jogador.lButton.getValue()) {
                jogador.tocador->music->setPosition(sf::seconds(0));
                jogador.tocador->play();
            } else {
                jogador.tocador->skip(jogador.rButton.getValue());
                jogador.tocador->play();

            }

        }

        window.clear();

        window.setView(movingView);

        window.draw(background);
        window.draw(quadradoDecima);

        nome.setString(name);

        window.draw(nome);
        window.draw(vamos);


        if(trocarNome) {
            window.draw(nomenome);
        }
        for(int i = 0; i < musicas.size(); i++) {
            window.draw(recMusga[i]);
            window.draw(addMusga[i]);
            window.draw(musgas[i]);
        }
        for(auto i : musgasAdds) {
            window.draw(i);
        }
        for(auto i : remover) {
            window.draw(i);
        }

        window.setView(fixedView);
        negocio.show(window);
        jogador.show(window);

        window.display();
    }
}






#endif
