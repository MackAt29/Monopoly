#include "Player.h"

Player::Player(const char& playerName, bool human)
    : name(playerName), isHuman(human), gold(100), currentLocation(0), HasLost(false), initTurn(getDiceRoll()) {}

// Costruttore di copia
Player::Player(const Player& other) : name(other.name), isHuman(other.isHuman), gold(100), currentLocation(0), HasLost(false), initTurn(other.initTurn) {}

//Potrebbe essere superfluo in caso decidiamo di mostrare gli esiti dei singoli dadi
int Player::getDiceRoll() {
    int diceResult1 = rollDice();
    int diceResult2 = rollDice();
    int totalDiceResult = diceResult1 + diceResult2;
    return totalDiceResult;
}

//lancio di due dadi
int Player::rollDice() {
    return (rand() % 6) + 1;
}

void Player::setPosition(int diceResult) {
    move(diceResult);
}

/*
//deve restituire un intero
const Property* Player::getPosition() const {
    return currentLocation;
}
*/

void Player::payPlayer(Player* propertyOwner, int rentAmount) {
    gold -= rentAmount;
    propertyOwner->gold += rentAmount;

    std::cout << name << " paid rent of " << rentAmount << " to " << propertyOwner->name << ". Remaining gold: " << gold << std::endl;

    if (checkBalance(0)) {
        HasLost = true;
        std::cout << name << " has lost the game!" << std::endl;
    }
}

void Player::advance() {
    //In questo modo mostra: Nome's turn: (metodo di tiro dei dadi + output dei risultati)
    std::cout << name << "'s turn: ";
    int totalDiceResult =getDiceRoll();
    setPosition(totalDiceResult);
}

/*
void takeTurn(const Property& casella){
    // Esegui altre azioni durante il turno, come controllare l'affitto, l'acquisto di proprietà, ecc.
    if (casella.getOwner() != nullptr) {
        //payPlayer(*(casella.getOwner()), currentLocation->rent);
    } else {
        if (isHuman) {
            humanChoice();
        } else {
            // Logica per la scelta del giocatore robot (25% di probabilità)
            if (rand() % 4 == 0) {
                std::cout << name << " decides to take a random action." << std::endl;
                // Implementa l'azione casuale del giocatore robot
            } else {
                std::cout << name << " decides to do nothing." << std::endl;
            }
        }
    }
}*/

void Player::move(int steps) {
    // Numero totale di caselle nel gioco                                                           

    // Calcola la nuova posizione sulla base del vettore delle caselle
    //currentLocation è l'indice del vettore delle posizioni dei giocatori
    int newPosition = (currentLocation + steps) % boardSize;

    // Aggiorna currentLocation in base alla nuova posizione
    currentLocation = newPosition;

    std::cout << name << " moved " << steps << " steps. New position: " << currentLocation+1 << std::endl;

    // Se il giocatore è andato oltre il bordo del vettore delle caselle, aggiungi 20 al saldo
    if (newPosition < currentLocation) {
        gold += 20;
        std::cout << name << " passed the starting position and earned 20 gold. New balance: " << gold << std::endl;
    }
}

bool Player::checkBalance(int amount) {
    if (gold < amount) {
        std::cout << name << " has insufficient funds and has lost the game!" << std::endl;
        return true;
    }
    return false;
}

void Player::humanChoice() {
    // Logica per la scelta del giocatore umano
    std::cout << "What do you want to do?" << std::endl;
    // Implementa le azioni disponibili, ad esempio acquisto di proprietà, costruzione di edifici, ecc.
}