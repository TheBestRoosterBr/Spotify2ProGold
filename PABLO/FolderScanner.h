#ifndef FOLDERSCANNER_H_INCLUDED
#define FOLDERSCANNER_H_INCLUDED

#include <windows.h>
#include <string>
#include <sstream>
#include <vector>
#include "ListaString.h"
#define println(x) std::cout << x << std::endl

class FolderScanner{

    std::string folder_path;

public:

    static std::string getExtension(std::string file){

        std::size_t size = file.size();

        for(int i = size - 1; i >= 0; i--){
            if(file[i] == '.'){

                std::stringstream str;

                for(int j = 0; j < size - i; j++){
                    str << file[i + j];
                }

                return str.str();

            }
        }

        return "DIR";

    }

    static bool validFormat(std::string extension){

        return extension == ".mp3";
    }


    FolderScanner(std::string path) : folder_path(path){

    }

    FolderScanner(){
        folder_path = "";
    }

    void setPath(std::string path){
        this->folder_path = path;
    }

    std::string getPath() const {
        return this->folder_path;
    }

    void scan(std::vector<std::string> & files){

<<<<<<< HEAD
        WIN32_FIND_DATAA find_data; // estrutura para armazenar informaï¿½ï¿½es sobre o arquivo encontrado
=======
        WIN32_FIND_DATAA find_data; // estrutura para armazenar informações sobre o arquivo encontrado
>>>>>>> 50c78c9828d44c0e32c47df03caef121ae4a06a4
        HANDLE hFind = FindFirstFileA((folder_path + std::string("\\*")).c_str(), &find_data); // procura o primeiro arquivo ou pasta na pasta especificada

        if (hFind != INVALID_HANDLE_VALUE) {
            do {
                if (!(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                    std::string temp = find_data.cFileName;
                    files.push_back(temp);
                }

<<<<<<< HEAD
            } while (FindNextFileA(hFind, &find_data)); // encontra o prï¿½ximo arquivo ou pasta na pasta especificada
=======
            } while (FindNextFileA(hFind, &find_data)); // encontra o próximo arquivo ou pasta na pasta especificada
>>>>>>> 50c78c9828d44c0e32c47df03caef121ae4a06a4

            FindClose(hFind); // fecha o handle de pesquisa
        }

<<<<<<< HEAD
=======
        else {
            throw "Erro ao abrir pasta";
        }
>>>>>>> 50c78c9828d44c0e32c47df03caef121ae4a06a4

    }
    void scan(PlayList ** files){

        WIN32_FIND_DATAA find_data; // estrutura para armazenar informaï¿½ï¿½es sobre o arquivo encontrado
        HANDLE hFind = FindFirstFileA((folder_path + std::string("\\*")).c_str(), &find_data); // procura o primeiro arquivo ou pasta na pasta especificada

        if (hFind != INVALID_HANDLE_VALUE) {
            do {
                if (!(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                    std::string temp = folder_path + "\\" + find_data.cFileName;

                    if(validFormat(getExtension(temp)))
                        files[0]->push_back(temp);

                }

            } while (FindNextFileA(hFind, &find_data)); // encontra o prï¿½ximo arquivo ou pasta na pasta especificada

            FindClose(hFind); // fecha o handle de pesquisa
        }

    }
};


#endif // FOLDERSCANNER_H_INCLUDED
