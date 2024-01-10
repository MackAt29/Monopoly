#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
//#include "property.h"  // Includi la definizione della classe Property (probabilmente sarà casella)

class Player {
public:
    std::string name;
    //std::vector<Property> ownedProperties;
    bool isHuman;
    int gold;
    //const Property* currentLocation; // Puntatore alla casella corrente
    int currentLocation;
    bool HasLost; // Flag per indicare se il giocatore ha perso
    const int boardSize = 28;

    Player(const std::string& playerName, bool human, int initialDiceRoll);

    //metodo per la scelta del turno
    int getDiceRoll();
    //metodo lancio dadi
    int rollDice();
    //inizializzazione e settaggio della posizione del giocatore
    void setPosition(int diceResult);
    //recupero informazioni sulla cella pari alla positzione del player
    //const Property* getPosition() const;
    
    //effetuare il turno con tiro di due dadi e eventuale mossa di acquisto o pagamento
    void takeTurn();
    
    //pagamento affitto sulla casella
    //void payPlayer(const Player& propertyOwner, int rentAmount);
    
private:
    void move(int steps);
    bool checkBalance(int amount);
    void humanChoice();
};

#endif  // PLAYER_H