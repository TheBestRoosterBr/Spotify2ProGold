#ifndef ANGRA
#define ANGRA


#include <string>
#include <fstream>
#include <iostream>
#include "customMusic.h"
#include <stdio.h>

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

    PlayList() {
        this->nome = "";
        primeiro = NULL;
        ultimo = NULL;
        tamanho = 0;
    }

    void setNome(string nome){
        this->nome = nome;

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
        println(tamanho);
        if(tamanho == 1){
            delete primeiro;
            primeiro = NULL;
            ultimo = NULL;
            tamanho--;
        }
        else if(temp != NULL) {
            primeiro = primeiro->proxNo;
            delete temp;
            primeiro->antNo = NULL;
            tamanho--;
        }
    }

    void removerFim() {
        if(tamanho == 1) {
            removerInicio();
            return;
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

        std::ofstream file("Playlists\\" + nome + ".txt",  ios::out | ios::trunc);


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

    void apagar(){
        string caminho = "Playlists\\" + nome + ".txt";
        int status = remove(caminho.c_str());
        if(!status){
            println("Arquivo removido");
        }
        else{
            println("foda, deu uma buceta aqui");
        }

    }

    void removerPosicao(int posicao) {
        if(posicao == 0 || tamanho == 1) {
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
        tamanho--;

    }

    void IWillDestroyTheEntireWorld(){
        while(tamanho > 0){
            println(primeiro->musica);
            removerInicio();
        }
    }
};

class Tocador {



  public:


    PlayList * playlist;
    No * musica_atual;
    CustomMusic * music;


    int getMusicPosicion(){
        return music->getCurrentTime();
    }

    int getMusicDuration(){
        return music->getDuration().asSeconds();
    }

    void setPosition(sf::Time time){
        music->setPosition(time);
    }

    Tocador() {
        this->playlist = NULL;
        musica_atual = NULL;
        music = new CustomMusic;
    }

    void setPlaylist(PlayList * p){
        this->playlist = p;
        init();
        update();
    }
    string getMusicaAtual() {
        return musica_atual->musica;
    }

    void init(){
        if(playlist->_size() > 0){
            musica_atual = playlist[0][0];
        }
    }

    bool skip(bool randon = false) {
        if(randon){
            srand(time(NULL));
            musica_atual = playlist[0][rand() % playlist->_size()];
            return true;
        }
        if(musica_atual->proxNo != NULL) {
            musica_atual = musica_atual->proxNo;
            return true;
        }
        else{
            update();
            init();
        }

        return false;
    }

    bool previous() {
        if(musica_atual->antNo != NULL) {
            musica_atual = musica_atual->antNo;
            return true;
        }

        return false;
    }

    bool open() {
         if(!music->open(musica_atual->musica)){

         }
         return false;
    }

    void update(){
        delete music;
        music = new CustomMusic;
        music->open(musica_atual->musica);
    }
    void play() {
        update();
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
