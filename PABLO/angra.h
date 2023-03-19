#ifndef ANGRA_H_INCLUDED
#define ANGRA_H_INCLUDED


class PlayButton{
    sf::CircleShape circle;
    sf::CircleShape triangle;
    sf::RectangleShape recs[2];

public:
    PlayButton(){

        int recHei = HEIGHT/7;

        circle.setFillColor(sf::Color(255,255,255));
        circle.setRadius(recHei/5);
        circle.setPosition(WIDTH/2 - circle.getRadius(),HEIGHT - recHei + circle.getRadius());

        triangle.setPointCount(3);
        triangle.setRadius(circle.getRadius()/2);
        triangle.setRotation(90);

        triangle.setPosition
        (
            WIDTH/2 + triangle.getGlobalBounds().width/1.5,
            HEIGHT - recHei + circle.getRadius() + triangle.getGlobalBounds().height/2
        );

        triangle.setFillColor(sf::Color(0,0,0));


        int recSize = circle.getRadius()/2;

        for(int i  = 0; i < 2; i++){
            recs[i].setSize(sf::Vector2f(recSize/2,recSize * 2));
            recs[i].setFillColor(sf::Color(0,0,0));
            recs[i].setPosition(
                WIDTH/2 + recSize * i - recSize/1.5,
                HEIGHT - recHei + circle.getRadius() + recSize
            );

        }

    }

    bool hover(sf::Vector2f mousePos) {
        return circle.getGlobalBounds().contains(mousePos);
    }

    void show(sf::RenderWindow& window, bool isPlaying){
        window.draw(circle);
        if(isPlaying){
            window.draw(recs[0]);
            window.draw(recs[1]);
        }else{
            window.draw(triangle);
        }

    }
};

class BotaoAvancar{
    sf::CircleShape avancar;
    sf::RectangleShape quadAv;

public:

    BotaoAvancar(){
        int recHei = HEIGHT/7;
        avancar.setPointCount(3);
        avancar.setRotation(90);
        avancar.setRadius(recHei/8);
        avancar.setFillColor(sf::Color(150,150,150));
        avancar.setPosition(sf::Vector2f(
            WIDTH/2 + avancar.getRadius()*6,
            HEIGHT - recHei + recHei/5 + avancar.getGlobalBounds().height/2
        ));

        quadAv.setSize(sf::Vector2f(avancar.getRadius()/2,avancar.getRadius()*2));
        quadAv.setFillColor(sf::Color(150,150,150));
        quadAv.setPosition(
            WIDTH/2 + avancar.getRadius()*6,
            HEIGHT - recHei + recHei/5 + avancar.getGlobalBounds().height/2
        );
    }

    bool hover(sf::Vector2f mousePos) {
        if(avancar.getGlobalBounds().contains(mousePos) || quadAv.getGlobalBounds().contains(mousePos)){
            avancar.setFillColor(sf::Color(255,255,255));
            quadAv.setFillColor(sf::Color(255,255,255));

            return true;
        }else{
            avancar.setFillColor(sf::Color(150,150,150));
            quadAv.setFillColor(sf::Color(150,150,150));

            return false;

        }

    }
    void show(sf::RenderWindow& window){
        window.draw(avancar);
        window.draw(quadAv);

    }

};

class BotaoVoltar{
    sf::CircleShape voltar;
    sf::RectangleShape quadAv;

public:

    BotaoVoltar(){
        int recHei = HEIGHT/7;
        voltar.setPointCount(3);
        voltar.setRotation(90 + 180);
        voltar.setRadius(recHei/8);
        voltar.setFillColor(sf::Color(150,150,150));
        voltar.setPosition(sf::Vector2f(
            WIDTH/2 - voltar.getRadius()*6,
            HEIGHT - recHei + recHei/2.5  + voltar.getGlobalBounds().height/2
        ));

        quadAv.setSize(sf::Vector2f(voltar.getRadius()/2,voltar.getRadius()*2));
        quadAv.setFillColor(sf::Color(150,150,150));
        quadAv.setPosition(
            WIDTH/2 - voltar.getRadius()*6.5,
            HEIGHT - recHei + recHei/5 + voltar.getGlobalBounds().height/2
        );
    }

    bool hover(sf::Vector2f mousePos) {
        if(voltar.getGlobalBounds().contains(mousePos) || quadAv.getGlobalBounds().contains(mousePos)){
            voltar.setFillColor(sf::Color(255,255,255));
            quadAv.setFillColor(sf::Color(255,255,255));
            return true;
        }else{
            voltar.setFillColor(sf::Color(150,150,150));
            quadAv.setFillColor(sf::Color(150,150,150));
            return false;

        }

    }
    void show(sf::RenderWindow& window){
        window.draw(voltar);
        window.draw(quadAv);

    }

};

class ONegocioQueFicaGrande{

    int wid = WIDTH/3;
    int hei = wid/80;
    sf::RectangleShape barra;
    sf::RectangleShape barraGold;
    sf::CircleShape bola;

public:
    ONegocioQueFicaGrande(){
        barra.setSize(sf::Vector2f(wid,hei));
        barra.setFillColor(sf::Color(150,150,150));
        barra.setPosition(sf::Vector2f(WIDTH/2 - wid/2,HEIGHT - hei*6));

        barraGold.setPosition(barra.getPosition());
        barraGold.setFillColor(sf::Color::White);
        barraGold.setSize(sf::Vector2f(0, hei));

        bola.setRadius(hei * 2);
        bola.setFillColor(sf::Color::White);

    }


    void hover(sf::Vector2f mouse, sf::RenderWindow& window){

        if(barra.getGlobalBounds().contains(mouse)){
            barraGold.setFillColor(sf::Color(212,175,55));


        }else{
             barraGold.setFillColor(sf::Color::White);

        }

    }

    void show(sf::RenderWindow& window){
        window.draw(barra);
        window.draw(barraGold);

    }

    void update(double porcentagem){
        barraGold.setSize(sf::Vector2f(barra.getSize().x * porcentagem, hei));
        bola.setPosition(sf::Vector2f(WIDTH/2 - wid/2,HEIGHT - hei*6));
    }

};
class Jogador{
public:


    bool isPlaying = true;

    //Tocador tocador;


//desenhos:
    int recWid = WIDTH;
    int recHei = HEIGHT/7;

    sf::RectangleShape back;

    PlayButton pButton;
    BotaoAvancar bAvancar;
    BotaoVoltar bVoltar;
    sf::CircleShape voltar;
    sf::RectangleShape quadVol;

    ONegocioQueFicaGrande negQficaGrande;
    Tocador * tocador;



    Jogador(){

        back.setSize(sf::Vector2f(recWid,recHei));
        back.setPosition(0,HEIGHT - recHei);
        back.setFillColor(sf::Color(50,50,50));

    }

    void setTocador(Tocador * p){
        this->tocador = p;
    }

    void show(sf::RenderWindow& window){
        window.draw(back);
        pButton.show(window,isPlaying);
        bAvancar.show(window);
        bVoltar.show(window);
        negQficaGrande.show(window);
    }


};

#endif // ANGRA_H_INCLUDED
