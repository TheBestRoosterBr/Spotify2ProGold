#ifndef ANGRA_H_INCLUDED
#define ANGRA_H_INCLUDED


class PlayButton {
    sf::CircleShape circle;
    sf::CircleShape triangle;
    sf::RectangleShape recs[2];

  public:
    PlayButton() {

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

        for(int i  = 0; i < 2; i++) {
            recs[i].setSize(sf::Vector2f(recSize/2,recSize * 2));
            recs[i].setFillColor(sf::Color(0,0,0));
            recs[i].setPosition(
                WIDTH/2 + recSize * i - recSize/1.5,
                HEIGHT - recHei + circle.getRadius() + recSize
            );

        }

    }

    void setPosition(sf::Vector2f position) {

        circle.setPosition(sf::Vector2f(
            position.x - circle.getRadius(),
            position.y + circle.getRadius()
        ));

        triangle.setPosition(sf::Vector2f(
            position.x + triangle.getGlobalBounds().width/1.5,
            position.y + circle.getRadius() + triangle.getGlobalBounds().height/2
        ));

        recs[0].setPosition(sf::Vector2f(
            position.x - (circle.getRadius()/2)/1.5,
            position.y + circle.getRadius() + circle.getRadius()/2
        ));
        recs[1].setPosition(sf::Vector2f(
            position.x + (circle.getRadius()/2)/2,
            position.y + circle.getRadius() + circle.getRadius()/2
        ));
    }

    void setSize(float radius) {
        circle.setRadius(radius);
        triangle.setRadius(circle.getRadius()/2);
        int recSize = circle.getRadius()/2;
        recs[0].setSize(sf::Vector2f(recSize/2,recSize * 2));
        recs[1].setSize(sf::Vector2f(recSize/2,recSize * 2));

    }
    void setFillColor(sf::Color color) {
        circle.setFillColor(color);

    }

    bool hover(sf::Vector2f mousePos) {
        return circle.getGlobalBounds().contains(mousePos);
    }

    void show(sf::RenderWindow& window, bool isPlaying) {
        window.draw(circle);
        if(isPlaying) {
            window.draw(recs[0]);
            window.draw(recs[1]);
        } else {
            window.draw(triangle);
        }

    }
};

class BotaoAvancar {
    sf::CircleShape avancar;
    sf::RectangleShape quadAv;

  public:

    BotaoAvancar() {
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
        if(avancar.getGlobalBounds().contains(mousePos) || quadAv.getGlobalBounds().contains(mousePos)) {
            avancar.setFillColor(sf::Color(255,255,255));
            quadAv.setFillColor(sf::Color(255,255,255));

            return true;
        } else {
            avancar.setFillColor(sf::Color(150,150,150));
            quadAv.setFillColor(sf::Color(150,150,150));

            return false;

        }

    }
    void show(sf::RenderWindow& window) {
        window.draw(avancar);
        window.draw(quadAv);

    }

};

class BotaoVoltar {
    sf::CircleShape voltar;
    sf::RectangleShape quadAv;

  public:

    BotaoVoltar() {
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
        if(voltar.getGlobalBounds().contains(mousePos) || quadAv.getGlobalBounds().contains(mousePos)) {
            voltar.setFillColor(sf::Color(255,255,255));
            quadAv.setFillColor(sf::Color(255,255,255));
            return true;
        } else {
            voltar.setFillColor(sf::Color(150,150,150));
            quadAv.setFillColor(sf::Color(150,150,150));
            return false;

        }

    }
    void show(sf::RenderWindow& window) {
        window.draw(voltar);
        window.draw(quadAv);

    }

};

class ONegocioQueFicaGrande {

    int wid = WIDTH/3;
    int hei = wid/80;
    sf::RectangleShape barra;
    sf::RectangleShape barraGold;
    sf::CircleShape bola;

  public:
    ONegocioQueFicaGrande() {
        barra.setSize(sf::Vector2f(wid,hei));
        barra.setFillColor(sf::Color(150,150,150));
        barra.setPosition(sf::Vector2f(WIDTH/2 - wid/2,HEIGHT - hei*6));

        barraGold.setPosition(barra.getPosition());
        barraGold.setFillColor(sf::Color::White);
        barraGold.setSize(sf::Vector2f(0, hei));

        bola.setRadius(hei * 2);
        bola.setFillColor(sf::Color::White);

    }


    bool hover(sf::Vector2f mouse, sf::RenderWindow& window) {

        if(barra.getGlobalBounds().contains(mouse)) {
            barraGold.setFillColor(sf::Color(212,175,55));

            return true;

        } else {
            barraGold.setFillColor(sf::Color::White);
            return false;
        }

    }

    sf::Vector2f getSize() {
        return barra.getSize();
    }


    sf::Vector2f getPosition() {
        return barra.getPosition();
    }

    void show(sf::RenderWindow& window) {
        window.draw(barra);
        window.draw(barraGold);

    }

    void update(double porcentagem) {
        barraGold.setSize(sf::Vector2f(barra.getSize().x * porcentagem, hei));
        bola.setPosition(sf::Vector2f(WIDTH/2 - wid/2,HEIGHT - hei*6));
    }

};

class randomButton {
    sf::Texture randomT;
    sf::Sprite randomSpr;
    bool value;
  public:
    randomButton() {
        randomT.loadFromFile("assets/random.png");
        randomSpr.setTexture(randomT);
        randomSpr.setPosition(sf::Vector2f((WIDTH/6)*2.3, (HEIGHT/24)*21.4));
        value = false;
    }
    void show(sf::RenderWindow& window) {
        window.draw(randomSpr);
    }

    bool hover(const sf::Vector2f & mouse) {
        return randomSpr.getGlobalBounds().contains(mouse);
    }

    bool getValue() {
        return value;
    }

    void setValue(bool value) {
        this->value = value;
        if(value) {
            sf::Color c(212, 175, 55);
            randomSpr.setColor(c);
        } else {
            randomSpr.setColor(sf::Color::White);
        }
    }

};

class loopButton {
    sf::Texture loopT;
    sf::Sprite loopSpr;
    bool value;

  public:



    loopButton() {
        loopT.loadFromFile("assets/loop.png");
        loopSpr.setTexture(loopT);
        loopSpr.setPosition(sf::Vector2f((WIDTH/6)*3.56, (HEIGHT/24)*21.5));
        value = false;
    }
    void show(sf::RenderWindow& window) {
        window.draw(loopSpr);
    }

    bool hover(const sf::Vector2f & mouse) {
        return loopSpr.getGlobalBounds().contains(mouse);
    }

    bool getValue() {
        return value;
    }

    void setValue(bool value) {
        println("TROCOU");
        this->value = value;
        if(value) {
            sf::Color c(212, 175, 55);
            loopSpr.setColor(c);
        } else {
            loopSpr.setColor(sf::Color::White);
        }
    }



};

class Timer{

    sf::Font font;
    sf::Text text;

    string ajudarFormato(int value){
        string m;
        if( value >= 10){
            m = std::to_string(value);
        }
        else{
            m = "0" + std::to_string(value);
        }

        return m;

    }

public:
    Timer(sf::Font font){
        this->font = font;
        text.setFont(this->font);
    }

    Timer(){
        text.setString("99:99");
    }

    void setFont(sf::Font & font){
        text.setFont(font);
    }

    void setPosition(float x, float y){
        text.setPosition(x, y);
    }

    void setPosition(sf::Vector2f pos){
        text.setPosition(pos);
    }

    void setCharacterSize(unsigned int size){
        text.setCharacterSize(size);
    }

    float getWidth(){
        return text.getGlobalBounds().width;
    }
    float getHeight(){
        return text.getGlobalBounds().width;
    }


    void update(const sf::Time & time){

        string texto;
        int minutes = (int)time.asSeconds() / 60;
        int seconds = (int)time.asSeconds() % 60;
        texto = ajudarFormato(minutes) + ":" + ajudarFormato(seconds);
        text.setString(texto);

    }

    void show(sf::RenderWindow & window){
        window.draw(text);
    }

};

class Jogador {
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
    Timer ltimer;
    Timer rtimer;

    sf::CircleShape voltar;
    sf::RectangleShape quadVol;

    randomButton rButton;
    loopButton lButton;

    ONegocioQueFicaGrande negQficaGrande;
    Tocador * tocador;

    sf::Font f;

    Jogador() {

        back.setSize(sf::Vector2f(recWid,recHei));
        back.setPosition(0,HEIGHT - recHei);
        back.setFillColor(sf::Color(50,50,50));

        f.loadFromFile("fontes/arial.ttf");
        ltimer.setFont(f);
        rtimer.setFont(f);
        ltimer.setCharacterSize(HEIGHT / 80);
        rtimer.setCharacterSize(HEIGHT / 80);

        ltimer.setPosition(negQficaGrande.getPosition().x - ltimer.getWidth() * 1.4, negQficaGrande.getPosition().y - 3);
        rtimer.setPosition(negQficaGrande.getPosition().x + negQficaGrande.getSize().x + ltimer.getWidth() * 0.4, negQficaGrande.getPosition().y - 3);

    }

    void setTocador(Tocador * p) {
        this->tocador = p;
    }

    void show(sf::RenderWindow& window) {
        window.draw(back);
        pButton.show(window,isPlaying);
        bAvancar.show(window);
        bVoltar.show(window);
        negQficaGrande.show(window);
        rButton.show(window);
        lButton.show(window);
        ltimer.show(window);
        rtimer.show(window);
    }

    void handleEvent(sf::RenderWindow& window,sf::Event event,const sf::Vector2f& mouse,bool& trocou) {
        if (event.type == sf::Event::MouseButtonPressed) {

            if (event.mouseButton.button == sf::Mouse::Left) {

                if(this->lButton.hover(mouse)) {
                    this->lButton.setValue(!this->lButton.getValue());
                }

                if(this->rButton.hover(mouse)) {
                    this->rButton.setValue(!this->rButton.getValue());
                }

                if(this->bAvancar.hover(mouse)) {
                    this->tocador->skip(this->rButton.getValue());
                    trocou = true;
                    if(this->isPlaying) {
                        this->tocador->play();
                    }

                }

                if(this->bVoltar.hover(mouse)) {

                    this->tocador->previous();
                    trocou = true;
                    if(this->isPlaying) {
                        this->tocador->play();
                    }

                }

                if(this->pButton.hover(mouse)) {

                    if(this->isPlaying) {
                        this->tocador->pause();
                    } else {
                        if(trocou) {
                            this->tocador->play();
                            trocou = false;
                        } else {
                            this->tocador->desPause();
                            trocou = false;
                        }

                    }
                    this->isPlaying = !this->isPlaying;


                }




                if(this->negQficaGrande.hover(mouse, window)) {

                    ONegocioQueFicaGrande & neg = this->negQficaGrande;

                    float barraSize = neg.getSize().x;

                    float posicao = neg.getPosition().x;

                    float porcem = (mouse.x - posicao) / barraSize;
                    println(porcem);

                    this->tocador->setPosition(sf::seconds(this->tocador->getMusicDuration() * porcem));
                    this->tocador->music->pause();
                    this->tocador->music->play();

                    if(this->tocador->music->getStatus() != sf::Music::Playing) {
                        this->tocador->music->play();
                    }
                    //this->tocador->music->setPosition(sf::seconds(150));


                }
            }
        }
    }


};


#endif // ANGRA_H_INCLUDED
