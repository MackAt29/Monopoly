#include <iostream>
#include "Board.h"
#include <vector>

int main(int argc, char** argv) {
    std::srand ( unsigned ( std::time(0) ) );
    //Ricevitore di argomento da prompt di comando
    if(argv[1] == std::string("computer"))
        std::cout<<1<< std::endl;
    else if(argv[1] == std::string("human"))
        std::cout<<-1<< std::endl;
    
    
    //Per prima cosa devo creare la board di gioco
    Board game;
    game.showBoard();


    // Definizione del vettore con i turni dei giocatori.
    std::vector<int> rounds = {1, 2, 3, 4};
    std::vector<int>::iterator p = rounds.begin();

    std::cout << "Sto puntando: " << *p << std::endl;
    // Ciclo durata partita
    while (rounds.size() > 1) {
        // Rimozione casuale di un valore con un puntatore
        std::cout << "Rimosso: " << *p << std::endl;
        p=rounds.erase(p);
    }

    std::cout << "Il vincitore della partita e': " << *p << std::endl;
    return 0;
}