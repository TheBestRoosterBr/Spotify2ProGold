
#include <conio.h>
#include <iostream>
#include <vector>
#include <filesystem>
#include <cstring>
#include <windows.h>
#include <dirent.h>

#define println(x) std::cout << x << std::endl

#include "CustomMusic.h"
#include "FolderScanner.h"




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

    println("Diretorio atual: " + folder_path);

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
    }
    else
    {
        println("LENDO DIRETORIO...");
        use_argv(&musicas, argc, argv);
    }

    std::cout << "Numero de musicas: " << musicas.size() << std::endl;
    getch();
    for(std::size_t i = 0; i < musicas.size(); i++)
        println(musicas[i]);


    for(std::size_t i = 0; i < musicas.size(); i++)
    {
        if(!music.open(musicas[i]))
        {
            println("ERRO AO LER ARQUIVO DE SOM");
            exit(1);
        }

        music.play();
        music.setPitch(1);

        getch();

        music.close();
    }

    println("Pressione qualquer tecla para sair...");
    getch();
}
