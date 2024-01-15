//Margherita Cattapan 2008798
#include "player.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

Player::Player(const char& playerName, bool human)
    : name(playerName), isHuman(human), gold(100), currentLocation(0), hasLost(false), initTurn(getDiceRoll()) {}

// Costruttore di copia
Player::Player(const Player& other) : name(other.name), isHuman(other.isHuman), gold(100), currentLocation(0), hasLost(false), initTurn(other.initTurn) {}

//Registrare output su file
void Player::logToFile(const std::string& message) const{
    std::ofstream logFile("game_log.txt", std::ios::app); // apre il file in modalità append
    if (logFile.is_open()) {
        logFile << message << std::endl;
    } else {
        std::cerr << "Errore nell'apertura del file di log della partita!" << std::endl;
    }
}

//lancio dadi
int Player::getDiceRoll() {
    int dice1 = (rand() % 6) + 1;
    int dice2 = (rand() % 6) + 1;
    int totalDiceResult = dice1 + dice2;
    //Se vogliamo mostrare i risultati singoli su questo metodo o su quello di tiro dei dadi
    std::cout << name << "'s turn: Rolled " << dice1 << " and " << dice2 << ". Total: " << totalDiceResult << std::endl;
    logToFile(name + "'s turn: Rolled " + std::to_string(dice1) + " and " + std::to_string(dice2) + ". Total: " + std::to_string(totalDiceResult));
    return totalDiceResult;
}

//inizializza e risetta la posizione
void Player::setPosition(int totalDiceResult) {
    move(totalDiceResult);
}

//metodo pagamento affitto
void Player::payPlayer(Player* propertyOwner, int rentAmount) {
    gold -= rentAmount;
    propertyOwner->gold += rentAmount;

    std::cout << name << " paid rent of " << rentAmount << " to " << propertyOwner->name << ". Remaining gold: " << gold << std::endl;
    logToFile(name + " paid rent of " + std::to_string(rentAmount) + " to " + propertyOwner->name + ". Remaining gold: " + std::to_string(gold));

    if (checkBalance(0)) {
        hasLost = true;
        std::cout << name << " has lost the game!" << std::endl;
        logToFile(name + " has lost the game!");
    }
}

void Player::payProperty(int priceAmount){
    gold -= priceAmount;
}

void Player::advance() {
    //setta il turno
    int totalDiceResult =getDiceRoll();
    setPosition(totalDiceResult);
}

void Player::acquireProperty(Property& land){
    ownList_.push_back(land);
}

void Player::getOwnedList(){
    for(int i=0;i<ownList_.size();++i){
        std::cout<<ownList_[i]<< ", ";
    }
}

/*metodo turno player
void Player::takeTurn(Board& board) {
    //int totalDiceResult = getDiceRoll();
    //std::cout << name << "'s turn: Rolled " << totalDiceResult << std::endl;   
    
    //In questo modo mostra: Nome's turn: (metodo di tiro dei dadi + output dei risultati)
    std::cout << name << "'s turn: ";
    int totalDiceResult =getDiceRoll();
    setPosition(totalDiceResult);
    if (v[currentLocation].owner != nullptr){
        payPlayer(*(v[currentLocation].owner), v[currentLocation].RentPrice);
    }
    else {
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
*/
//mossa della pedina
void Player::move(int steps) {
    //calcola nuova posizione dopo lancio dadi
    int newPosition = (currentLocation + steps) % 28;
    // Se il giocatore è andato oltre il bordo del vettore delle caselle, aggiungi 20 al saldo
    if (newPosition < currentLocation) {
        gold += 20;
        std::cout << name << " passed the starting position and earned 20 gold. New balance: " << gold << std::endl;
        logToFile(name + " passed the starting position and earned 20 gold. New balance: " + std::to_string(gold));
    }
    // Aggiorna currentLocation in base alla nuova posizione
    currentLocation = newPosition;
    std::cout << name << " moved " << steps << " steps. New position: " << currentLocation+1 << std::endl;
    logToFile(name + " moved " + std::to_string(steps) + " steps. New position: " + std::to_string(currentLocation + 1));
}

//controllo saldo disponibile
bool Player::checkBalance(int amount) {
    if (gold < amount) {
        std::cout << name << " has insufficient funds and has lost the game!" << std::endl;
        logToFile(name + " has insufficient funds and has lost the game!");
        return true;
    }
    return false;
}