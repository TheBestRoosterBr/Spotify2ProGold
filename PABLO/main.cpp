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




void normal(std::vector<std::string> & musicas)
{

    musicas.push_back("musicas/HERE I AM.mp3");
    musicas.push_back("musicas/euAmoVoce.mp3");
    musicas.push_back("musicas/asd.mp3");
    musicas.push_back("musicas/serestaDoParedao.mp3");

}

void use_argv(std::vector<std::string> * musicas, int argc, char ** argv)
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

    println(musicas->size());
}

int main(int argc, char ** argv)
{
    CustomMusic music;
    std::vector <std::string> musicas;

    if(argc == 1)
    {
        normal(musicas);
        music.open(musicas[0]);
    }
    else
    {
        println("LENDO DIRETORIO...");
        use_argv(&musicas, argc, argv);
        for(std::size_t i = 0; i < musicas.size(); i++){
            if(!strcmp(argv[1], musicas[i].c_str())){
                music.open(musicas[i]);
                break;
            }
        }
    }

    std::cout << "Numero de musicas: " << musicas.size() << std::endl;
    for(std::size_t i = 0; i < musicas.size(); i++)
        println(musicas[i]);

    music.play();

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML Spotify");

    homePage(window);

    music.close();
    return 0;

}
