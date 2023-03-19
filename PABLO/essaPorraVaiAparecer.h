#ifndef LOADPLAYLIST_H_INCLUDED
#define LOADPLAYLIST_H_INCLUDED

#include <sys/stat.h>

using namespace std;

vector<string> get_filenames(const char* dir_path) {
    vector<string> filenames;
    DIR* dir;
    struct dirent* entry;

    // Abre o diret�rio
    dir = opendir(dir_path);

    // Verifica se o diret�rio foi aberto com sucesso
    if (dir == NULL) {
        cerr << "Erro ao abrir o diret�rio: " << dir_path << endl;
        return filenames;
    }

    // L� os arquivos do diret�rio e adiciona seus nomes ao vetor
    while ((entry = readdir(dir)) != NULL) {
        // Obt�m as informa��es do arquivo
        struct stat file_stat;
        string file_path = string(dir_path) + "/" + string(entry->d_name);
        if (stat(file_path.c_str(), &file_stat) < 0) {
            continue;
        }

        // Verifica se o arquivo � regular
        if (S_ISREG(file_stat.st_mode)) {
            string filename = string(entry->d_name);
            size_t pos = filename.find_last_of(".");
            if (pos != string::npos) {
                filename = filename.substr(0, pos);
            }
            filenames.push_back(filename);
        }
    }

    // Fecha o diret�rio
    closedir(dir);

    return filenames;
}

void viewNames() {
    const char* dir_path = "Playlists"; // Substitua pelo caminho do diret�rio desejado

    vector<string> filenames = get_filenames(dir_path);

    // Imprime os nomes dos arquivos
    for (int i = 0; i < filenames.size(); i++) {
        cout << filenames[i] << endl;
    }
    return;
}

#endif // LOADPLAYLIST_H_INCLUDED


