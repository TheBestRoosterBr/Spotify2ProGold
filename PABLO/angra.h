#ifndef ANGRA_H_INCLUDED
#define ANGRA_H_INCLUDED
/*************************
parte de cebolinha:




*/


struct playButton{
    sf::CircleShape circle;
    sf::CircleShape triangle;
    sf::RectangleShape recs[2];

    void init(){

        circle.setFillColor(sf::Color(255,255,255));
        circle.setRadius(recHei/4);
        circle.setPosition(WIDTH/2 - recHei/8,HEIGHT - recHei * 3/2);

        triangle.setPointCount(3);
        triangle.setRadius(circle.getRadius()/2);
        triangle.setPosition(WIDTH/2 - triangle.getRadius(),HEIGHT - recHei/2);

        int recSize = circle.getRadius()/2;
        for(int i  = 0; i < 2; i++){
            recs[i].setSize(recSize/4,recSize);
            recs[i].setFillColor(sf::Color color(255,255,255));
            recs[i].setPosition(WIDTH/2 + (recSize * 4 * i) - recSize * 2,HEIGHT - recHei/2);

        }

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



class jogador{


    bool isPlaying;




//desenhos:
    int recWid = WIDTH;
    int recHei = HEIGHT/7;

    sf::RectangleShape back;
    playButton pButton;





public:

    jogador(){

        pButton.init();


    }
    void show(sf::RenderWindow& window){
        window.draw(back);
        pButton.show(window,isPlaying);
    }


};

#endif // ANGRA_H_INCLUDED
