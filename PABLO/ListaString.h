#ifndef ANGRA
#define ANGRA


#include <string>
#include <fstream>
#include <iostream>
#include "customMusic.h"
using namespace std;


struct No {
    string musica;
    No *proxNo, *antNo;
};

class PlayList {



    No * primeiro;
    No * ultimo;
    int tamanho;
    string nome;


    void inserirListaVazia(string musica) {
        No * novo = new No;

        novo->musica = musica;
        novo->antNo = NULL;
        novo->proxNo = NULL;
        primeiro = novo;
        ultimo = novo;
        tamanho++;

    }

  public:


    PlayList(string nome) {
        this->nome = nome;
        primeiro = NULL;
        ultimo = NULL;
        tamanho = 0;
    }

    string getNome(){
        return nome;
    }

    int _size() {
        return tamanho;
    }
    No * operator [] (int i) {

        No * temp = primeiro;
        for(int k = 0; k < i; k++)
            temp = temp->proxNo;
        return temp;

    }

    void push_back(string musica) {

        if(primeiro == NULL)
            inserirListaVazia(musica);
        else {
            No * novoNo = new No;

            novoNo->musica = musica;
            novoNo->proxNo=NULL;
            ultimo->proxNo = novoNo;
            novoNo->antNo = ultimo;
            ultimo = novoNo;
            tamanho++;
        }

    }

    void removerInicio() {
        No * temp = primeiro;
        if(temp != NULL) {
            primeiro = primeiro->proxNo;
            primeiro->antNo = NULL;
            delete temp;
            tamanho--;
        }
    }

    void removerFim() {
        if(tamanho == 1) {
            removerInicio();
        }

        No * temp = ultimo;
        if(temp != NULL) {
            ultimo = temp->antNo;
            ultimo->proxNo = NULL;
            delete temp;
            tamanho--;
        }
    }

    void savePlaylist() {

        std::fstream file("Playlists\\" + nome + ".txt",  ios::out);

        file.seekp(0);

        No * cabeca_de_gelo = primeiro;

        while(cabeca_de_gelo != NULL) {
            file << cabeca_de_gelo->musica << endl;
            cabeca_de_gelo = cabeca_de_gelo->proxNo;
        }

        file.close();

    }

    void load(){


        std::fstream f("Playlists\\" + nome + ".txt",  ios::in);

        string n;
        while(f.eof() == false){

            getline(f, n);
            push_back(n);
        }

    }



    void removerPosicao(int posicao) {
        if(tamanho == 1) {
            removerInicio();
            return;
        }

        if(tamanho == posicao + 1) {
            removerFim();
            return;
        }
        No * temp = primeiro;
        for(int i = 0; i < posicao; i++) {
            temp = temp->proxNo;
        }

        No * ant = temp->antNo;
        No * dir = temp->proxNo;

        ant->proxNo = dir;
        dir->antNo = ant;
        delete temp;

    }
};

class Tocador {

    PlayList * playlist;
    No * musica_atual;
    CustomMusic * music;


  public:


    Tocador() {
        this->playlist = NULL;
        musica_atual = NULL;
        music = new CustomMusic;
    }

    void setPlaylist(PlayList * p){
        this->playlist = p;
        init();
    }
    string getMusicaAtual() {
        return musica_atual->musica;
    }

    void init(){
        if(playlist->_size() > 0){
            musica_atual = playlist[0][0];
        }
    }

    bool skip() {
        if(musica_atual->proxNo != NULL) {
            musica_atual = musica_atual->proxNo;
            update();
            play();
            return true;
        }
        return false;
    }

    bool previous() {
        if(musica_atual->antNo != NULL) {
            musica_atual = musica_atual->antNo;
            update();
            play();
            return true;
        }
        return false;
    }

    bool open() {
        return music->open(musica_atual->musica);
    }

    void update(){
        delete music;
        music = new CustomMusic;
        music->open(musica_atual->musica);
    }
    void play() {

        music->play();

    }

    void pause() {
        music->pause();
    }

    void desPause(){
        music->play();
    }

};


#endif // ANGRA
