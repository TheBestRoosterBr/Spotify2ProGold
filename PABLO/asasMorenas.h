#ifndef ASASMORENAS_H_INCLUDED
#define ASASMORENAS_H_INCLUDED

class negocioDoLado{

    int wid = WIDTH/8;
    int hei = HEIGHT;

    sf::RectangleShape background;

    sf::Text inicio;
    sf::Text buscar;
    sf::Text sua_bib;
    sf::Font arial;

    sf::Texture homTex;
    sf::Sprite homSpr;

    sf::Texture lupT;
    sf::Sprite lupSpr;

    sf::Texture bibT;

    sf::Sprite bibSpr;

    sf::Texture logoT;
    sf::Sprite logoSpr;
public:
    negocioDoLado(){



        background.setFillColor(sf::Color(0,0,0));
        background.setSize(sf::Vector2f(wid * 1.2,hei));

        background.setPosition(0,0);

        int posX = wid/7;


        logoT.loadFromFile("assets/logoPNG.png");
        logoSpr.setTexture(logoT);

        logoSpr.setPosition(posX,logoSpr.getGlobalBounds().height/2);
        float csize = wid/10;
        int posY = logoSpr.getGlobalBounds().height/2 + wid/5;

        homTex.loadFromFile("assets/home.png");
        homSpr.setTexture(homTex);
        homSpr.setScale(0.75,0.75);
        homSpr.setPosition(posX - homSpr.getGlobalBounds().width/6 ,posY * 2);

        int sprX = posX - homSpr.getGlobalBounds().width/6;
        int tposx = posX * 1.2 + homSpr.getGlobalBounds().width;

        arial.loadFromFile("fontes/arialBold.ttf");
        inicio.setColor(sf::Color::White);
        inicio.setFont(arial);
        inicio.setCharacterSize(csize);
        inicio.setString("Início");
        inicio.setPosition(tposx,posY * 2);

        lupT.loadFromFile("assets/lupa.png");
        lupSpr.setTexture(lupT);

        lupSpr.setPosition(sprX ,posY * 3);

        buscar.setColor(sf::Color(255,255,255));
        buscar.setFont(arial);
        buscar.setCharacterSize(csize);
        buscar.setString("Buscar");
        buscar.setPosition(tposx,posY * 3);

        bibT.loadFromFile("assets/bib.png");
        bibSpr.setTexture(bibT);
        bibSpr.setPosition(sprX,posY * 4);

        sua_bib.setColor(sf::Color(255,255,255));
        sua_bib.setFont(arial);
        sua_bib.setCharacterSize(csize);
        sua_bib.setString("Sua Biblioteca");
        sua_bib.setPosition(tposx,posY * 4);


    }

    void show(sf::RenderWindow& window){
        window.draw(background);
        window.draw(logoSpr);
        window.draw(homSpr);
        window.draw(inicio);
        window.draw(buscar);
        window.draw(lupSpr);
        window.draw(bibSpr);
        window.draw(sua_bib);

    }




};

#endif // ASASMORENAS_H_INCLUDED
