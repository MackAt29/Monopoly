#ifndef PLAYER_H
#define PLAYER_H

#include "Property.h"
#include <iostream>
#include <vector>

class Property;

class Player {
public:
    char name;
    std::vector<Property> ownedProperties;
    bool isHuman;
    int gold;
    int currentLocation;
    int initTurn;
    bool HasLost; // Flag per indicare se il giocatore ha perso
    int boardSize = 28;

    Player(const char& playerName, bool human);
    // Costruttore di copia
    Player(const Player& other);

    //metodo per la scelta del turno
    int getDiceRoll();
    //metodo lancio dadi
    int rollDice();
    //inizializzazione e settaggio della posizione del giocatore
    void setPosition(int diceResult);
    //Recupero esito del primo tiro di dadi()
    int getInitTurn(){return initTurn;}
    //recupero informazioni sulla cella pari alla positzione del player
    //const Property* getPosition() const;
    
    //Tira i dadi e avanza
    void advance();
    //effetuare il turno con tiro di due dadi e eventuale mossa di acquisto o pagamento
    void takeTurn(const Property& casella);
    
    //pagamento affitto sulla casella
    void payPlayer(Player* propertyOwner, int rentAmount);


private:
    void move(int steps);
    bool checkBalance(int amount);
    void humanChoice();
};

#endif  // PLAYER_H
