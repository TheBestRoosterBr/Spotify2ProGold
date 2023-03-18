#ifndef ANGRA
#define ANGRA


#include <string>
#include "customMusic.h"
using namespace std;


struct No
{
    string musica;
    No *proxNo, *antNo;
};

class PlayList{



    No * primeiro;
    No * ultimo;
    int tamanho;


    void inserirListaVazia(string musica){
        No * novo = new No;

        novo->musica = musica;
        novo->antNo = NULL;
        novo->proxNo = NULL;
        primeiro = novo;
        ultimo = novo;
        tamanho++;

    }

public:


    PlayList(){

        primeiro = NULL;
        ultimo = NULL;
        tamanho = 0;
    }

    int _size(){
        return tamanho;
    }
    No * operator [] (int i){

        No * temp = primeiro;
        for(int k = 0; k < i; k++)
            temp = temp->proxNo;
        return temp;

    }

    void push_back(string musica){

        if(primeiro == NULL)
            inserirListaVazia(musica);
        else
        {
            No * novoNo = new No;

            novoNo->musica = musica;
            novoNo->proxNo=NULL;
            ultimo->proxNo = novoNo;
            novoNo->antNo = ultimo;
            ultimo = novoNo;
            tamanho++;
        }

    }

    void removerInicio(){
        No * temp = primeiro;
        if(temp != NULL){
            primeiro = primeiro->proxNo;
            primeiro->antNo = NULL;
            delete temp;
            tamanho--;
        }
    }

    void removerFim(){
        if(tamanho == 1){
            removerInicio();
        }

        No * temp = ultimo;
        if(temp != NULL){
            ultimo = temp->antNo;
            ultimo->proxNo = NULL;
            delete temp;
            tamanho--;
        }
    }

    void removerPosicao(int posicao){

        if(tamanho == 1){
            removerInicio();
            return;
        }

        if(tamanho == posicao + 1){
            removerFim();
            return;
        }
        No * temp = primeiro;
        for(int i = 0; i < posicao; i++){
            temp = temp->proxNo;
        }

        No * ant = temp->antNo;
        No * dir = temp->proxNo;

        ant->proxNo = dir;
        dir->antNo = ant;
        delete temp;

    }
};

class Tocador{

    PlayList * playlist;
    No * musica_atual;
    CustomMusic music;


public:


    Tocador(PlayList * playlist){
        this->playlist = playlist;
        musica_atual = playlist[0][0];
    }

    string getMusicaAtual(){
        return musica_atual->musica;
    }

    bool skip(){
        if(musica_atual->proxNo != NULL){
            musica_atual = musica_atual->proxNo;
            return true;
        }
        return false;
    }

    bool previous(){
        if(musica_atual->antNo != NULL){
            musica_atual = musica_atual->antNo;
            return true;
        }
        return false;
    }

    bool open(){
        return music.open(musica_atual->musica);
    }

    bool play(){
        if(open()){
            music.play();
            return true;
        }
        return false;
    }

    bool pause(){

        music.pause();
        return true;

    }

};


#endif // ANGRA
