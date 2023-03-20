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


std::string arq = "musicas";
int argumentos = 1;


#include "loadPlaylist.h"
#include "CustomMusic.h"
#include "FolderScanner.h"

void createPlaylist(sf::RenderWindow &window);
void seePlaylist(sf::RenderWindow &window,string playList);
void homePage(sf::RenderWindow& window);
void biblioteca(sf::RenderWindow& window);

#include "ListaString.h"

Tocador tocador;
PlayList playlist("SO AS MELHORES");

#include "asasMorenas.h"
#include "silvanoSalles.h"
#include "bandaDjavu.h"
#include "amadoBatista.h"
#include "bigLove.h"



void normal(PlayList * musicas)
{

    std::string folder_path = "musicas";

    FolderScanner scanner;
    scanner.setPath(folder_path);
    scanner.scan(&musicas);
}

void use_argv(PlayList * musicas, int argc)
{

    std::string folder_path = arq;

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



    if(argc == 2){
        arq = argv[1];
        use_argv(&playlist, argc);
    }
    else
        playlist.load();
    tocador.setPlaylist(&playlist);
    tocador.init();


    if(argc == 2){
        while(arq.compare(tocador.getMusicaAtual())){
            tocador.skip();
        }
    }



    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML Spotify");
    window.setFramerateLimit(22);

    tocador.update();
    tocador.play();

    homePage(window);





    return 0;

}
