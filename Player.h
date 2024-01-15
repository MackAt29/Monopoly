//Margherita Cattapan 2008798
#ifndef PLAYER_H
#define PLAYER_H

#include "Property.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

class Property;

class Player {
private:
    char name;
    bool isHuman;
    int gold;
    int currentLocation;
    bool hasLost;
    int initTurn;
    std::vector<Property> ownList_;

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
    //output su file
    void logToFile(const std::string& message) const;
    void advance();
    char getName(){return name;}
    bool isHumanPlayer(){return isHuman;}
    //Recupero esito del primo tiro di dadi()
    int getInitTurn(){return initTurn;}
    //check gold player
    int getGold(){return gold;}
    void payProperty(int priceAmount);
    void acquireProperty(Property& land);
    //recupero posizione del giocatore
    int getPosition(){return currentLocation;}
    //pagamento affitto casella
    void payPlayer(Player* propertyOwner, int rentAmount);
    void getOwnedList();
};

#endif  // PLAYER_H
