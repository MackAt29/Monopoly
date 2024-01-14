#include "player.h"
#include <iostream>
#include <cstdlib>

Player::Player(const char& playerName, bool human)
    : name(playerName), isHuman(human), gold(100), currentLocation(0), HasLost(false), initTurn(getDiceRoll()) {}

// Costruttore di copia
Player::Player(const Player& other) : name(other.name), isHuman(other.isHuman), gold(100), currentLocation(0), HasLost(false), initTurn(other.initTurn) {}

//lancio dadi
int Player::getDiceRoll() {
    int dice1 = (rand() % 6) + 1;
    int dice2 = (rand() % 6) + 1;
    int totalDiceResult = dice1 + dice2;
    //Se vogliamo mostrare i risultati singoli su questo metodo o su quello di tiro dei dadi
    std::cout << name << "'s turn: Rolled " << dice1 << " and " << dice2 << ". Total: " << totalDiceResult << std::endl;
    return totalDiceResult;
}

//inizializza e risetta la posizione
void Player::setPosition(int totalDiceResult) {
    move(totalDiceResult);
}

//restitutisce l'intero della posizione
int Player::getPosition() const {
    return currentLocation;
}

//metodo pagamento affitto
void Player::payPlayer(const Player& propertyOwner, int rentAmount) {
    gold -= rentAmount;
    propertyOwner.gold += rentAmount;

    std::cout << name << " paid rent of " << rentAmount << " to " << propertyOwner.name
        << ". Remaining gold: " << gold << std::endl;

    if (checkBalance(0)) {
        hasLost = true;
        std::cout << name << " has lost the game!" << std::endl;
    }
}

//metodo turno player
void Player::takeTurn() {
    //int totalDiceResult = getDiceRoll();
    //std::cout << name << "'s turn: Rolled " << totalDiceResult << std::endl;   
    
    //In questo modo mostra: Nome's turn: (metodo di tiro dei dadi + output dei risultati)
    std::cout << name << "'s turn: ";
    int totalDiceResult =getDiceRoll();
    setPosition(totalDiceResult);

    if (v[currentLocation].owner != nullptr){
        payPlayer(*(v[currentLocation].owner), v[currentLocation].RentPrice);
    }
    } else {
        if (isHuman) {
            char choice;
            std::cout << "Vuoi comprare questa casella? [S/N]: ";
            std::cin >> choice;

            if (choice == 'S' || choice == 's') {
                //compra la casella
                if (property->getCategory() == 3) {
                    std::cout << "Cannot buy this property." << std::endl;
                } else {
                    gold -= property->getBuyPrice();
                    // Add the property to the player's owned properties.
                    // Example: addOwnedProperty(property);
                    std::cout << name << " bought the property. Remaining gold: " << gold << std::endl;
                }
            } else {
                std::cout << name << " decides to do nothing." << std::endl;
            }
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
}

//mossa della pedina
void Player::move(int steps) {
    //calcola nuova posizione dopo lancio dadi
    int newPosition = (currentLocation + steps) % 28;
    // Aggiorna currentLocation in base alla nuova posizione
    currentLocation = newPosition;
    std::cout << name << " moved " << steps << " steps. New position: " << currentLocation+1 << std::endl;

    // Se il giocatore è andato oltre il bordo del vettore delle caselle, aggiungi 20 al saldo
    if (newPosition < currentLocation) {
        gold += 20;
        std::cout << name << " passed the starting position and earned 20 gold. New balance: " << gold << std::endl;
    }
}

//controllo saldo disponibile
bool Player::checkBalance(int amount) {
    if (gold < amount) {
        std::cout << name << " has insufficient funds and has lost the game!" << std::endl;
        return true;
    }
    return false;
}

/*void Player::humanChoice() {
    // Logica per la scelta del giocatore umano
    std::cout << "What do you want to do?" << std::endl;
    // Implementa le azioni disponibili, ad esempio acquisto di proprietà, costruzione di edifici, ecc.
}*/
void Player::humanChoice() {
    // Logica per la scelta del giocatore umano
    std::cout << "What do you want to do?" << std::endl;
    // Implementa le azioni disponibili, ad esempio acquisto di proprietà, costruzione di edifici, ecc.
}
