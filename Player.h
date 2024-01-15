#ifndef PLAYER_H
#define PLAYER_H

#include "Property.h"
<<<<<<< HEAD
#include <iostream>
#include <vector> 
=======
#include <vector>
#include <iostream>
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

class Property;
>>>>>>> 68c52fcc1ef578a9b1220e697eeb7768ec93b948

class Player {
private:
    char name;
    bool isHuman;
    int gold;
    int currentLocation;
    bool hasLost;
    int initTurn;
<<<<<<< HEAD
=======
    std::vector<Property> ownList_;
>>>>>>> 68c52fcc1ef578a9b1220e697eeb7768ec93b948

    //lancio dadi
    int getDiceRoll();
    //settaggio della posizione del giocatore
    void setPosition(int diceResult);
<<<<<<< HEAD
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
=======
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
    void acquireProperty(Property& land);
    //recupero posizione del giocatore
    int getPosition(){return currentLocation;}
    //pagamento affitto casella
    void payPlayer(Player* propertyOwner, int rentAmount);
    void getOwnedList();
>>>>>>> 68c52fcc1ef578a9b1220e697eeb7768ec93b948
};

#endif  // PLAYER_H