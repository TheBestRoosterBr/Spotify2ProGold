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

    std::string folder_path = "musicas";

    FolderScanner scanner;
    scanner.setPath(folder_path);
    scanner.scan(&musicas);
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


std::vector<string> * getPlaylistsSaved(){

    std::vector<string> * vec = new std::vector<string>;

    FolderScanner scanner;
    scanner.setPath("Playlists");
    scanner.scan(*vec);
    return vec;

}

void printPlaylists(const std::vector<string> & vecto){

    for(int i = 0; i < vecto.size(); i++){
        println(vecto[i]);
    }
}

int main(int argc, char ** argv)
{


    Tocador tocador;
    PlayList playlist("SO AS MELHORES");

    playlist.load();

    tocador.setPlaylist(&playlist);

    tocador->init();
    tocador->play();



    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML Spotify");

    window.setFramerateLimit(22);
    homePage(window);

    return 0;

}
