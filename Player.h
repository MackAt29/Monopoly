#ifndef PLAYER_H
#define PLAYER_H

#include "Property.h"
#include "Board.h"
#include <iostream>
#include <vector> 

class Property;

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
    //mossa pedina e aggiunta gold per passaggio al via
    void move(int steps);
    //pagamento affitto casella
    void payPlayer(Player& propertyOwner, int rentAmount);
    //check gold disponibile
    bool checkBalance(int amount);

public:
    Player(const char& playerName, bool human);
    // Costruttore di copia
    Player(const Player& other);
    //turno del giocatore
    void takeTurn(Board& board);
    void advance();
    char getName(){return name;}
    //Recupero esito del primo tiro di dadi()
    int getInitTurn(){return initTurn;}
    //recupero posizione del giocatore
    int getPosition(){return currentLocation;}
};

#endif  // PLAYER_H
