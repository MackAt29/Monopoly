#include "Board.h"
#include "Player.h"
#include "Property.h"
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    std::srand ( unsigned ( std::time(0) ) );

    std::vector<Player> placeHolder;
    std::vector<Player> rounds;
    bool timelimit = false;
    int turnLimit = 10;

    //Ricevitore di argomento da prompt di comando per la struttura di partecipazione al gioco (aka. Se gioca anche l'utente oppure no)
    if(argv[1] == std::string("computer")){
        std::cout<<"Hai selezionato partita partite con 4 giocatori computer\n"<<std::endl;
        timelimit=true;
        placeHolder = {Player('1', false), Player('2', false), Player('3', false), Player('4', false)};
    }
    else if(argv[1] == std::string("human")){
        std::cout<<"Hai selezionato partita partite 3 giocatori computer e un giocatore umano\n"<<std::endl;
        std::cout<<"--==Tu sei il giocatore 1==--\n"<<std::endl;
        placeHolder = {Player('1', true), Player('2', false), Player('3', false), Player('4', false)};
    }
    for (int i = 0; i < 4; ++i) {
        std::cout << "P"<<i+1<<" rolled: " << placeHolder[i].initTurn<<std::endl;
    }
    
    //Ciclo di Ordinamento dei turni in base al tiro di Dadi
    for (int i = 0; i < 4; ++i) {
        int maxIndex = 0;

        // Trova l'indice del massimo elemento nel resto del vettore
        for (int j = 0; j < placeHolder.size(); ++j) {
            if (placeHolder[j].initTurn > placeHolder[maxIndex].initTurn) {
                maxIndex = j;
            }
        }
        // Scambia l'elemento corrente con il massimo trovato
        rounds.push_back(placeHolder[maxIndex]);
        placeHolder.erase(placeHolder.begin() + maxIndex);
    }
    std::cout<<"Ordine dei turni: ";
    for (int i = 0; i < 4; ++i) {
        std::cout<<"P"<<rounds[i].name<<" ";
    }
    std::cout<<std::endl;
    
    //Per prima cosa devo creare la board di gioco
    Board game;
    game.showBoard();

    std::vector<Player>::iterator p = rounds.begin();
    // Ciclo durata partita
    while (rounds.size() > 1 && turnLimit>0) {
        //REQUIRED: Player Turn
        for(int i = 0; i<rounds.size();++i){
            //REQUIRED: Metodi del turno del giocatore

            //REQUIRED: if(Player[i].getGold<=0) p=rounds.erase(p);

            //REQUIRED: Salvare ogni evento su un file LOG
        }

        //TEMP: Rimozione dell'elemento puntato
        p=rounds.erase(p);
        std::cout << "\nHo rimosso un player";
        if(timelimit) turnLimit--;
    }
    std::cout<<std::endl;

    if(rounds.size()==1)
        std::cout << "Il vincitore della partita e': P" << rounds[0].name << std::endl;
    //REQUIRED: ELSE IF partita conclusa per tempo scaduto, metodo di ricerca GOLD maggiore
    return 0;
}