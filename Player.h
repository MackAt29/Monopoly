#ifndef PLAYER_H
#define PLAYER_H

#include "Property.h"
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
    //check gold disponibile
    bool checkBalance(int amount);

public:
    Player(const char& playerName, bool human);
    // Costruttore di copia
    Player(const Player& other);
    //turno del giocatore
    //void takeTurn(Board& board);
    void advance();
    char getName(){return name;}
    bool isHumanPlayer(){return isHuman;}
    //Recupero esito del primo tiro di dadi()
    int getInitTurn(){return initTurn;}
    //check gold player
    int getGold(){return gold;}
    void payProperty(int priceAmount);
    //recupero posizione del giocatore
    int getPosition(){return currentLocation;}
    //pagamento affitto casella
    void payPlayer(Player* propertyOwner, int rentAmount);
};

#endif  // PLAYER_H
