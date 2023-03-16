#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;



struct tipoNo
{
    string musica;
    tipoNo *proxNo, *antNo;
};

struct tipoLista
{
    tipoNo *fim, *inicio;
    int quant;
};

void inicializa(tipoLista *listaEnc)
{
    listaEnc->fim = NULL;
    listaEnc->inicio = NULL;
    listaEnc->quant = 0;
}

int insereListaVazia(tipoLista *listaEnc, string valor)
{
    tipoNo *novoNo;
    novoNo = new tipoNo;
    if(novoNo == NULL)
        return 0;
    novoNo->musica = valor;
    novoNo->proxNo = NULL;
    novoNo->antNo = NULL;
    listaEnc->inicio = novoNo;
    listaEnc->fim = novoNo;
    listaEnc->quant++;
    return 1;
}

void exibeLista(tipoLista *listaEnc)
{
    tipoNo *atual;
    atual = listaEnc->inicio;
    cout << "\nMusicas Adcionadas "<< endl;
    while(atual !=NULL)
    {
        cout << atual->musica << " " << endl;
        atual = atual->proxNo;
    }
}

int insereNoFim(tipoLista *listaEnc, string valor)
{
    tipoNo *novoNo;
    if(listaEnc->inicio == NULL)
        insereListaVazia(listaEnc, valor);
    else
    {
        novoNo = new tipoNo;
        if(novoNo == NULL)
            return 0;
        novoNo->musica=valor;
        novoNo->proxNo=NULL;
        listaEnc->fim->proxNo = novoNo;
        novoNo->antNo = listaEnc->fim;
        listaEnc->fim = novoNo;
        listaEnc->quant++;
        return 1;
    }
}

void removerInicio(tipoLista * listaEnc){
    tipoNo * temp = listaEnc->inicio;

    if(temp != NULL){
        listaEnc->inicio = temp->proxNo;
        delete temp;
        temp = NULL;
        listaEnc->quant--;
    }
}


void removerFim(tipoLista * listaEnc){

    if(listaEnc->quant == 1){
        removerInicio(listaEnc);
        return;
    }

    tipoNo * temp = listaEnc->fim;
    if(temp != NULL){
        listaEnc->fim = temp->antNo;
        delete temp;
        listaEnc->fim->proxNo = NULL;
        listaEnc->quant--;
    }
}

void removerPosicao(tipoLista * listaEnc, int posicao){

    if(listaEnc->quant == 1){
        removerInicio(listaEnc);
        return;
    }
    if(listaEnc->quant == posicao + 1){
        removerFim(listaEnc);
        return;
    }

    tipoNo * temp = listaEnc->inicio;
    for(int i = 0; i < posicao; i++){
        temp = temp->proxNo;
    }

    tipoNo * ant = temp->antNo;
    tipoNo * dir = temp->proxNo;

    ant->proxNo = dir;
    dir->antNo = ant;
    delete temp;


}

int main()
{
    tipoLista lista;
    string aux;
    int op;
    inicializa(&lista);

    insereNoFim(&lista, "MARCOS");
    insereNoFim(&lista, "VINCIUS");
    insereNoFim(&lista, "MOTA");
    insereNoFim(&lista, "MENEZES");
    removerPosicao(&lista, 2);
    exibeLista(&lista);


    return 0;
}
