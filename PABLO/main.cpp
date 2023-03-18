#include "SFML/Graphics.hpp"

#include <iostream>
#include <vector>
#include <filesystem>
#include <cstring>
#include <windows.h>
#include <dirent.h>

#define println(x) std::cout << x << std::endl
#define WIDTH 1280
#define HEIGHT 720

#include "CustomMusic.h"
#include "FolderScanner.h"
#include "asasMorenas.h"
#include "silvanoSalles.h"
#include "ListaString.h"



void normal(PlayList * musicas)
{

    musicas->push_back("musicas/HERE I AM.mp3");
    musicas->push_back("musicas/asd.mp3");
    musicas->push_back("musicas/HERE I AM.mp3");
}

void use_argv(PlayList * musicas, int argc, char ** argv)
{

    std::string folder_path = argv[1];

    for(int i = folder_path.size() - 1; i >= 0; i--){

        if(folder_path[i] == '\\'){
            folder_path.resize(i);
            break;
        }
    }

    FolderScanner scanner;
    scanner.setPath(folder_path);
    scanner.scan(&musicas);

    println(musicas->_size());
}

int main(int argc, char ** argv)
{
    PlayList playlist;
    normal(&playlist);

    Tocador tocador(&playlist);



    println(tocador.getMusicaAtual());
    tocador.open();
    tocador.skip();
    tocador.play();


    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML Spotify");

    window.setFramerateLimit(22);
    homePage(window);

    return 0;

}
