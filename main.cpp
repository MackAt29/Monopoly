#include <iostream>
#include "Board.h"
#include <vector>

int main(int argc, char** argv) {
    std::srand ( unsigned ( std::time(0) ) );
    std::vector<char> rounds;

    //Ricevitore di argomento da prompt di comando per la struttura di partecipazione al gioco (aka. Se gioca anche l'utente oppure no)
    if(argv[1] == std::string("computer"))
        rounds = {'1', '2', '3', '4'};
    else if(argv[1] == std::string("human"))
        rounds = {'1', '2', '3', 'H'};

    //REQUIRED: Metodo del Player per il tiro di dado, così da decidere l'ordine di gioco
    
    std::vector<char>::iterator p = rounds.begin();

    // Ciclo durata partita
    std::cout << "Sto puntando: " << *p << std::endl;
    while (rounds.size() > 1) {
        //REQUIRED: Player Turn
        for(int i = 0; i<rounds.size();++i){
            //REQUIRED: Metodi del turno del giocatore

            //REQUIRED: if(Player[i].getGold<=0) p=rounds.erase(p);
        }
        //TEMP: Rimozione dell'elemento puntato
        std::cout << "Rimosso: " << *p << std::endl;
        p=rounds.erase(p);
    }
    
    //Per prima cosa devo creare la board di gioco
    Board game;
    game.showBoard();


    std::cout << "Il vincitore della partita e': " << *p << std::endl;
    return 0;
}