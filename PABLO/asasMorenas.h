#ifndef ASASMORENAS_H_INCLUDED
#define ASASMORENAS_H_INCLUDED

class negocioDoLado{

    int wid = WIDTH/6;
    int hei = HEIGHT;

    sf::RectangleShape background;

    sf::CircleShape pontosEmCima[3];


    sf::Text inicio;
    sf::Text buscar;
    sf::Text sua_bib;

    sf::Font arial;

public:
    negocioDoLado(){

        std::cout << "parabens, sabe mt\n";
        ///Proxima biblioteca vai ser angra

        background.setFillColor(sf::Color(0,0,0));
        background.setSize(sf::Vector2f(wid,hei));

        background.setPosition(0,0);

        for(int i = 0; i < 3; i++){


            pontosEmCima[i].setFillColor(sf::Color(255,255,255));
            pontosEmCima[i].setRadius(wid/75);
            pontosEmCima[i].setPosition(wid/10 + (wid/20 * i),wid/10);

        }

        inicio.setColor(sf::Color(255,255,255));


        //inicio.setFont()

    }

    void show(sf::RenderWindow& window){
        window.draw(background);
        for(int i = 0; i < 3; i++)
            window.draw(pontosEmCima[i]);




    }




};

#endif // ASASMORENAS_H_INCLUDED
