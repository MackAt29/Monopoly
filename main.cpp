/*
File fatto da Jonatan Ademi 2008796
In questo file si trova il main e tutta la gestione dei turni
*/
#include "Board.h"
#include "Player.h"
#include "Property.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    std::srand ( unsigned ( std::time(0) ) );

    //PREPARATIVI PER LA PARTITA, creare i giocatori e mettere i loro turni
    //STEP 1: Creo due vector. placeHolder tiene i 4 giocatori, rounds avrà l'ordine dei turni dei giocatori
    std::vector<Player> placeHolder;
    std::vector<Player> rounds;

    //STEP 2: timelimit distingue le partite tra 4 cpu da quelle con lo user. 
    //Se ci sono 4 cpu, si attiva il tempo limite e si hanno 10 turni per finire la partita o vince chi ha più fiorini
    bool timelimit = false;
    int turnLimit = 10;

    //STEP 3: Ricevitore di argomento da prompt di comando per la struttura di partecipazione al gioco
    //In altre parole, se esegui scrivendo computer, la partita avviene con 4 cpu. Se digiti human, invece, sarai il Giocatore 1
    if(argv[1] == std::string("computer")){
        std::cout<<"You selected the Game with 4 CPU\n"<<std::endl;
        timelimit=true;
        placeHolder = {Player('1', false), Player('2', false), Player('3', false), Player('4', false)};
    }
    else if(argv[1] == std::string("human")){
        std::cout<<"You selected the Game with 3 CPU and 1 human player\n"<<std::endl;
        std::cout<<"--==You are Player 1==--\n"<<std::endl;
        placeHolder = {Player('1', true), Player('2', false), Player('3', false), Player('4', false)};
    }
    //STEP3.1: Ogni giocatore tira la coppia di dadi per decidere l'ordine dei turni
    for (int i = 0; i < 4; ++i) {
        std::cout << "P"<<i+1<<" rolled: " << placeHolder[i].getInitTurn()<<std::endl;
    }
    
    //STEP 4: Confronta il tiro dei dadi iniziali di ogni giocatore. maxIndex variabile di appoggio per indicare chi ha ottenuto il risultato più alto
    for (int i = 0; i < 4; ++i) {
        int maxIndex = 0;

        //Trova l'indice di chi ha totalizzato il tiro di dadi più alto
        for (int j = 0; j < placeHolder.size(); ++j) {
            //Se trova qualcuno che ha fatto un tiro più alto, aggiorna l'indice
            if (placeHolder[j].getInitTurn() > placeHolder[maxIndex].getInitTurn()) {
                maxIndex = j;
            }
        }
        //Prende l'elemento all'indice maxIndex da placeholder e lo inserisce su rounds. Dopodichè tale elemento viene cancellato da placeHolder
        rounds.push_back(placeHolder[maxIndex]);
        placeHolder.erase(placeHolder.begin() + maxIndex);
    }

    //STEP 5: Stampa l'ordine dei giocatori della partita
    std::cout<<"Turn order: ";
    for (int i = 0; i < 4; ++i) {
        std::cout<<"P"<<rounds[i].getName()<<" ";
    }
    std::cout<<std::endl;
    
    //PREPARATIVI FATTI, ora comincia la partita
    //STEP 1: Crea la Board e la stampa.
    Board game;
    game.showBoard(rounds);

    //STEP 2: humanTurn è una flag per tenere un loop quando è turno del giocatore Umano
    bool humanTurn = true;

    //STEP 3: Ciclo durata partita. La partita va avanti finchè ci sono almeno 2 giocatori. Se è la partita è tra 4 cpu, termina dopo 10 turni
    while (rounds.size() > 1 && turnLimit>0) {
        
        //STEP 4: Ciclo dei giocatori. Inizia con 4 player, ma ogni volta che un giocatore viene eliminato, il vettore decresce di 1
        for(int i = 0; i<rounds.size();++i){
            
            //STEP 5: Il giocatore di turno avanza. Tira due dadi e si sposta alla casella destinataria.
            rounds[i].advance();
            
            //STEP 6: SE LA CASELLA DESTINATARIA NON è una casella angolare, ALLORA è una casella terreno. Si procedono con le azioni
            if(rounds[i].getPosition()%7!=0){

                //PER SEMPLICITA', ho optato di creare una reference di Property casella che referenzia la casella destinataria.
                Property& casella = game.getCasella(rounds[i].getPosition());
                
                //STEP 7.1: SE ARRIVI IN UNA CASELLA DI PROPRIETA' DI UN ALTRO PLAYER, paga.
                if (casella.getOwner() != nullptr && casella.getOwner() != &rounds[i]) {
                    rounds[i].payPlayer(casella.getOwner(), casella.getRentPrice());
                    
                    //DOPO AVER PAGATO UN PLAYER, controlla se sei andato in bancarotta. Se sì, vieni eliminato.
                    if(rounds[i].getGold()<=0){
                        std::cout << "Player " << rounds[i].getName() << " has been terminated" << std::endl;
                        rounds[i].logToFile("Player " + std::to_string(rounds[i].getName()) + " has been terminated");
                        rounds.erase(rounds.begin() + i);
                    }
                }
                //STEP 7.2: E' una casella vuota o è la tua casella??? In ogni caso puoi investire su questa casella
                else {
                    //GENERA INIZIALMENTE la scelta della CPU al 25%. 
                    //Se l'utente di turno è umano, choice cambia successivamente a seconda della scelta dell'utente.
                    bool choice = (std::rand() % 100) < 25;
                    
                    //Se la casella è libera, puoi comprarla
                    if(casella.getOwner() == nullptr){
                        //Controlla se hai soldi a sufficienza per l'acquisto del terreno. Se la risposta è no, salta avanti.
                        if(rounds[i].getGold()<casella.getBuyPrice()){
                            std::cout << "Player " << rounds[i].getName() << " has not enough money to buy Property nr. "<< rounds[i].getPosition()+1 << std::endl;
                            rounds[i].logToFile("Player " + std::to_string(rounds[i].getName()) + " has not enough money to buy Property nr. " + std::to_string(rounds[i].getPosition()+1));
                        }
                        //SE LA RISPOSTA E' SI', allora procedi.
                        else {
                            //CONTROLLO se il giocatore di turno e' umano. 
                            if(rounds[i].isHumanPlayer()){

                                //SE SI', allora finché il giocatore non decide se eseguire l'acquisto o meno, continua ad essere il suo turno
                                while(humanTurn){
                                    std::cout<<"It's your turn. You've arrived to Property " << " " <<rounds[i].getPosition()+1 << " " << casella <<  " \nWould you like to buy it for "<<casella.getBuyPrice()<<" florins? [Y/N]"<<std::endl;
                                    std::cout<<"Type ''show'' to see the Game situation."<<std::endl;
                                    std::string input;
                                    std::cin >> input;

                                    //Y = choice conferma l'acquisto. Il turno del player è concluso, setta humanTurn a false.
                                    if (input == "Y" || input == "y") {
                                        choice = true;
                                        humanTurn=false;
                                    } 
                                    //N = choice rifiuta l'acquisto. Il turno del player è concluso, setta humanTurn a false.
                                    else if (input == "N" || input == "n") {
                                        choice = false;
                                        humanTurn=false;
                                    } 
                                    //show = Mostra la situazione della partita
                                    else if (input == "show") {
                                        game.showBoard(rounds);
                                    } else {
                                        std::cout << "Invalid Input. Retry." << std::endl;
                                    }
                                }
                                //finito il turno, setta humanTurn a vero in preparazione del suo prossimo round
                                humanTurn=true;
                            }

                            //Ora, indipendentemente se il turno era di cpu o human, è stata fatta la scelta.
                            //Si prosegue con l'acquisto se hanno messo true
                            if(choice){
                                rounds[i].payProperty(casella.getBuyPrice());
                                rounds[i].acquireProperty(casella);
                                casella.buyLand(&rounds[i]);
                                std::cout << "Player " << rounds[i].getName() << " has bought Property nr. "<< rounds[i].getPosition()+1 << std::endl;
                                rounds[i].logToFile("Player " + std::to_string(rounds[i].getName()) + " has bought Property nr. " + std::to_string(rounds[i].getPosition()+1));
                            }
                        }
                    }
                    //STEP 7.3: Questa casella è già di tua proprietà, PUOI decidere di potenziarla, costruendo una casa e poi un albergo
                    else if(casella.getOwner() == &rounds[i]){
                        //COME PRIMA, se sei un UMANO, la scelta avviene per inserimento
                        if(rounds[i].isHumanPlayer()){
                            while(humanTurn){
                                std::cout<<"It's your turn and you've arrived at your Property."<<std::endl;
                                std::string input;
                                if(casella.getStatus()==1){
                                    std::cout<<"\nWould you like to build an House for "<<casella.getHousePrice()<<" florins? [Y/N]"<<std::endl;
                                    std::cout<<"Type ''show'' to see the Game situation."<<std::endl;
                                    std::cin >> input;
                                } else if(casella.getStatus()==2){
                                    std::cout<<"\nWould you like to upgrade it with an Hotel for "<<casella.getHotelPrice()<<" florins? [Y/N]"<<std::endl;
                                    std::cout<<"Type ''show'' to see the Game situation."<<std::endl;
                                    std::cin >> input;
                                } else if(casella.getStatus()==3){
                                    std::cout<<"\nYou already have an hotel here."<<std::endl;
                                    input = "N";
                                }

                                if (input == "Y" || input == "y") {
                                    choice = true;
                                    humanTurn=false;
                                } else if (input == "N" || input == "n") {
                                    choice = false;
                                    humanTurn=false;
                                } else if (input == "show") {
                                    game.showBoard(rounds);
                                } else {
                                    std::cout << "Invalid Input. Retry." << std::endl;
                                    std::cin >> input;
                                }
                            }
                            humanTurn=true;
                            if(choice){
                                //SE questa casella è vuota, costruisci una casa.
                                if(casella.getStatus()==1){
                                    rounds[i].payProperty(casella.getHousePrice());
                                    casella.buyHouse();
                                    std::cout << "Player " << rounds[i].getName() << " has built an house on Property nr. "<< rounds[i].getPosition()+1 << std::endl;
                                    rounds[i].logToFile("Player " + std::to_string(rounds[i].getName()) + " has built an house on Property nr. " + std::to_string(rounds[i].getPosition()+1));
                                } 
                                //SE questa casella ha una casa, potenziala in un albergo
                                else if(casella.getStatus()==2){
                                    rounds[i].payProperty(casella.getHotelPrice());
                                    casella.buyHotel();
                                    std::cout << "Player " << rounds[i].getName() << " has upgraded the Property nr. "<< rounds[i].getPosition()+1<< " into an hotel." << std::endl;
                                    rounds[i].logToFile("Player " + std::to_string(rounds[i].getName()) + " has upgraded the Property nr. " + std::to_string(rounds[i].getPosition()+1) + " into an hotel.");
                                } 
                            }
                        }
                    }

                }
            }
        }
        if(timelimit) turnLimit--;
    }

    //STEP 8: La partita è conclusa, scopriamo come mai.
    std::cout<<"Game ended" <<std::endl;
    game.showBoard(rounds);

    //STEP 9.1: Se la partita è conclusa perché è rimasto un solo giocatore, stampa il vincitore.
    if(rounds.size()==1) {
        std::cout << "The WINNER is: P" << rounds[0].getName() << std::endl;
        rounds[0].logToFile("The WINNER is: P" + std::to_string(rounds[0].getName()));
    }   
    //STEP 9.2: Se la partita era tra 4 CPU E sono passati 10 turni stampa il giocatore che aveva più fiorini alla fine della partita
    else {
        std::cout << "Time out" << std::endl;
        int c = 0;
        for(int i = 1; i<rounds.size();++i){
            if(rounds[c].getGold()<rounds[i].getGold()){
                c=i;
            }
        }
        std::cout << "The WINNER/s for the greatest amount of florins is/are: P" << rounds[c].getName();
        rounds[c].logToFile("The WINNER for the greatest amount of florins is: P" + std::to_string(rounds[c].getName()));
        //"In caso di quantità uguale di fiorini, è permessa la vittoria ex-equo"
        for(int i = 0; i<rounds.size();++i){
            if(rounds[c].getGold()==rounds[i].getGold()&& c!=i){
                std::cout << " P" << rounds[i].getName();
            }
        }
    }
    return 0;
}