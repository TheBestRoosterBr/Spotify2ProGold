#ifndef ASASMORENAS_H_INCLUDED
#define ASASMORENAS_H_INCLUDED

class negocioDoLado{

    int wid = WIDTH/5;
    int hei = HEIGHT;

    sf::RectangleShape background;

    sf::Text inicio;
    sf::Text buscar;
    sf::Text sua_bib;
    sf::Font arial;

    sf::Texture homTex;
    sf::Sprite homSpr;

    sf::Texture logoT;
    sf::Sprite logoSpr;
public:
    negocioDoLado(){



        background.setFillColor(sf::Color(0,0,0));
        background.setSize(sf::Vector2f(wid,hei));

        background.setPosition(0,0);

        int posX = wid/7;
        int posY = wid/5;

        logoT.loadFromFile("assets/logoPNG.png");
        logoSpr.setTexture(logoT);
        //logoSpr.setScale(0.75,0.75);
        logoSpr.setPosition(posX,posY - logoSpr.getGlobalBounds().height/2);
        float csize = wid/13;

        homTex.loadFromFile("assets/home.png");
        homSpr.setTexture(homTex);
        homSpr.setScale(0.75,0.7);
        homSpr.setPosition(posX - homSpr.getGlobalBounds().width/6 ,posY * 2);

        int tposx = posX * 1.2 + homSpr.getGlobalBounds().width;

        arial.loadFromFile("fontes/arialBold.ttf");
        inicio.setColor(sf::Color(255,255,255));
        inicio.setFont(arial);
        inicio.setCharacterSize(csize);
        inicio.setString("Início");
        inicio.setPosition(tposx,posY * 2);

        buscar.setColor(sf::Color(255,255,255));
        buscar.setFont(arial);
        buscar.setCharacterSize(csize);
        buscar.setString("Buscar");
        buscar.setPosition(tposx,posY * 3);


    }

    void show(sf::RenderWindow& window){
        window.draw(background);
        window.draw(logoSpr);
        window.draw(homSpr);
        window.draw(inicio);
        window.draw(buscar);


    }




};

#endif // ASASMORENAS_H_INCLUDED
