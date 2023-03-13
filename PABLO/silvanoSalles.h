#ifndef SILVANOSALLES_H_INCLUDED
#define SILVANOSALLES_H_INCLUDED

void homePage(sf::RenderWindow &window)
{

    negocioDoLado negocio;
    sf::Texture logoTexture;
    logoTexture.loadFromFile("spotify-logo.png");

    sf::Sprite logoSprite;
    logoSprite.setTexture(logoTexture);
    logoSprite.setPosition(sf::Vector2f(50, 50));

    sf::RectangleShape background(sf::Vector2f(1920, 1080));
    background.setFillColor(sf::Color(255, 215, 0));
    window.draw(background);

    sf::Texture searchTexture;
    searchTexture.loadFromFile("search.png");

    sf::Sprite searchSprite;
    searchSprite.setTexture(searchTexture);
    searchSprite.setPosition(sf::Vector2f(1420, 50));

    sf::Texture buttonTexture;
    buttonTexture.loadFromFile("button.png");

    sf::Sprite buttonSprite;
    buttonSprite.setTexture(buttonTexture);
    buttonSprite.setPosition(sf::Vector2f(1750, 50));

    window.draw(searchSprite);
    window.draw(buttonSprite);


    sf::Font font;
    font.loadFromFile("fontes/arial.ttf");

    sf::Text searchText;
    searchText.setFont(font);
    searchText.setString("Search for artists, songs, or podcasts");
    searchText.setCharacterSize(24);
    searchText.setFillColor(sf::Color::Black);
    searchText.setPosition(sf::Vector2f(1150, 55));

    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setString("SIGN UP");
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setPosition(sf::Vector2f(1780, 65));

    window.draw(searchText);
    window.draw(buttonText);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.draw(background);
        window.draw(logoSprite);
        window.draw(searchSprite);
        window.draw(buttonSprite);
        window.draw(searchText);
        window.draw(buttonText);
        negocio.show(window);
        window.display();
    }
};

#endif // SILVANOSALLES_H_INCLUDED
