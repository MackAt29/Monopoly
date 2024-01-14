#ifndef PLAYER_H
#define PLAYER_H

#include "Property.h"
#include <iostream>
#include <vector> 

class Player {
private:
    char name;
    bool isHuman;
    int gold;
    int currentLocation;
    bool hasLost;
    int initTurn;

    //lancio dadi
    int getDiceRoll();
    //settaggio della posizione del giocatore
    void setPosition(int diceResult);
    //recupero posizione del giocatore
    int getPosition(){return currentLocation;}
    //Recupero esito del primo tiro di dadi()
    int getInitTurn(){return initTurn;}
    //mossa pedina e aggiunta gold per passaggio al via
    void move(int steps);
    //pagamento affitto casella
    void payPlayer(const Player& propertyOwner, int rentAmount);
    //check gold disponibile
    bool checkBalance(int amount);

public:
    Player(char playerName, bool human);
    // Costruttore di copia
    Player(const Player& other);
    //turno del giocatore
    void takeTurn(const Board& board);
};

#endif  // PLAYER_H
