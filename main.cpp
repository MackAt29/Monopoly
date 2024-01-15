#include "Board.h"
#include "Player.h"
#include "Property.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    std::srand ( unsigned ( std::time(0) ) );

    //CREAZIONE di due vettori di Player, uno d'appoggo e l'altro per far ruotare i turni durante la partita
    std::vector<Player> placeHolder;
    std::vector<Player> rounds;
    //timelimit distingue le partite tra 4 cpu da quelle con lo user. Se ci sono 4 cpu, si attiva il tempo limite e si hanno 10 turni per finire la partita o vince chi ha più fiorini
    bool timelimit = false;
    int turnLimit = 10;

    //Ricevitore di argomento da prompt di comando per la struttura di partecipazione al gioco (aka. Se gioca anche l'utente oppure no)
    if(argv[1] == std::string("computer")){
        std::cout<<"Hai selezionato partita partite con 4 giocatori computer\n"<<std::endl;
        timelimit=true;
        placeHolder = {Player('1', false), Player('2', false), Player('3', false), Player('4', false)};
    }
    else if(argv[1] == std::string("human")){
        std::cout<<"Hai selezionato partita partite 3 giocatori computer e un giocatore umano\n"<<std::endl;
        std::cout<<"--==Tu sei il giocatore 1==--\n"<<std::endl;
        placeHolder = {Player('1', true), Player('2', false), Player('3', false), Player('4', false)};
    }
    for (int i = 0; i < 4; ++i) {
        std::cout << "P"<<i+1<<" rolled: " << placeHolder[i].getInitTurn()<<std::endl;
    }
    
    //Ciclo di Ordinamento dei turni in base al tiro di Dadi
    for (int i = 0; i < 4; ++i) {
        int maxIndex = 0;

        // Trova l'indice del massimo elemento nel resto del vettore
        for (int j = 0; j < placeHolder.size(); ++j) {
            if (placeHolder[j].getInitTurn() > placeHolder[maxIndex].getInitTurn()) {
                maxIndex = j;
            }
        }
        // Scambia l'elemento corrente con il massimo trovato
        rounds.push_back(placeHolder[maxIndex]);
        placeHolder.erase(placeHolder.begin() + maxIndex);
    }
    std::cout<<"Ordine dei turni: ";
    for (int i = 0; i < 4; ++i) {
        std::cout<<"P"<<rounds[i].getName()<<" ";
    }
    std::cout<<std::endl;
    
    //Per prima cosa devo creare la board di gioco
    Board game;
    game.showBoard(rounds);
    bool humanTurn = true;
    std::vector<Player>::iterator p = rounds.begin();
    // Ciclo durata partita
    while (rounds.size() > 1 && turnLimit>0) {
        //REQUIRED: Player Turn
        for(int i = 0; i<rounds.size();++i){
            //REQUIRED: Metodi del turno del giocatore
            rounds[i].advance();
            //REQUIRED: Se il giocatore arriva in una casella angolare, skippa tutto sto bordello di Dio
            if(rounds[i].getPosition()%7!=0){

                Property& casella = game.getCasella(rounds[i].getPosition());
                //SE ARRIVI IN UNA CASELLA DI PROPRIETA' DI UN ALTRO PLAYER, paga.
                if (casella.getOwner() != nullptr && casella.getOwner() != &rounds[i]) {
                    rounds[i].payPlayer(casella.getOwner(), casella.getRentPrice());
                    //DOPO AVER PAGATO UN PLAYER, controlla se sei andato in bancarotta. Se si, vieni eliminato.
                    if(rounds[i].getGold()<=0){
                        std::cout << "Giocatore " << rounds[i].getName() << " è stato eliminato" << std::endl;
                        rounds[i].logToFile("Giocatore " + std::to_string(rounds[i].getName()) + " è stato eliminato");
                        rounds.erase(rounds.begin() + i);
                    }
                }
                else {
                    //GENERA INIZIALMENTE la scelta della CPU al 25%. Se l'utente di turno è umano, choice cambia a seconda della scelta dell'utente.
                    bool choice = (std::rand() % 100) < 25;
                    
                    //Se la casella è libera, puoi comprarla
                    if(casella.getOwner() == nullptr){
                        //BOT: Ha i soldi e si compra la casa
                        //BOT: Ha i soldi, ma non si compra la casa
                        //BOT: Non ha i soldi, quindi non si compra la casa
                        if(rounds[i].getGold()<casella.getBuyPrice()){
                            std::cout << "Giocatore " << rounds[i].getName() << " non ha abbastanza soldi per comprare la Casella nr. "<< rounds[i].getPosition()+1 << std::endl;
                            rounds[i].logToFile("Giocatore " + std::to_string(rounds[i].getName()) + " non ha abbastanza soldi per comprare la Casella nr. " + std::to_string(rounds[i].getPosition()+1));
                        } else {
                            if(rounds[i].isHumanPlayer()){
                                while(humanTurn){
                                    std::cout<<"E' il tuo turno. Sei arrivato alla Casella " << " " <<rounds[i].getPosition()+1 << " " << casella <<  " \nVuoi comprare il terreno per "<<casella.getBuyPrice()<<" fiorini? [Y/N]"<<std::endl;
                                    std::cout<<"Digita ''show'' per vedere la situazione della partita."<<std::endl;
                                    std::string input;
                                    std::cin >> input;

                                    if (input == "Y" || input == "y") {
                                        choice = true;
                                        humanTurn=false;
                                    } else if (input == "N" || input == "n") {
                                        choice = false;
                                        humanTurn=false;
                                    } else if (input == "show") {
                                        game.showBoard(rounds);
                                    } else {
                                        std::cout << "Input non valido. Riprova." << std::endl;
                                        std::cin >> input;
                                    }
                                }
                                humanTurn=true;
                            }
                            if(choice){
                                rounds[i].payProperty(casella.getBuyPrice());
                                rounds[i].acquireProperty(casella);
                                casella.buyLand(&rounds[i]);
                                std::cout << "Giocatore " << rounds[i].getName() << " ha comprato la casella nr. "<< rounds[i].getPosition()+1 << std::endl;
                                rounds[i].logToFile("Giocatore " + std::to_string(rounds[i].getName()) + " ha comprato la casella nr. " + std::to_string(rounds[i].getPosition()+1));
                            }
                        }
                    }
                    else if(casella.getOwner() == &rounds[i]){
                        if(rounds[i].isHumanPlayer()){
                            while(humanTurn){
                                std::cout<<"E' il tuo turno e sei arrivato su una tua casella."<<std::endl;
                                std::string input;
                                if(casella.getCategory()==1){
                                    std::cout<<"\nVuoi comprare una casa per "<<casella.getHousePrice()<<" fiorini? [Y/N]"<<std::endl;
                                    std::cout<<"Digita ''show'' per vedere la situazione della partita."<<std::endl;
                                    std::cin >> input;
                                } else if(casella.getCategory()==2){
                                    std::cout<<"\nVuoi potenziarla in un albergo per "<<casella.getHotelPrice()<<" fiorini? [Y/N]"<<std::endl;
                                    std::cout<<"Digita ''show'' per vedere la situazione della partita."<<std::endl;
                                    std::cin >> input;
                                } else if(casella.getCategory()==3){
                                    std::cout<<"\nHai gia' un albergo in questa casella."<<std::endl;
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
                                    std::cout << "Input non valido. Riprova." << std::endl;
                                    std::cin >> input;
                                }
                            }
                            humanTurn=true;
                            if(choice){
                                if(casella.getStatus()==1){
                                    rounds[i].payProperty(casella.getHousePrice());
                                    casella.buyHouse();
                                    std::cout << "Giocatore " << rounds[i].getName() << " ha costruito una casa nella casella nr. "<< rounds[i].getPosition()+1 << std::endl;
                                    rounds[i].logToFile("Giocatore " + std::to_string(rounds[i].getName()) + " ha costruito una casa nella casella nr. " + std::to_string(rounds[i].getPosition()+1));
                                } else if(casella.getStatus()==2){
                                    rounds[i].payProperty(casella.getHotelPrice());
                                    casella.buyHotel();
                                    std::cout << "Giocatore " << rounds[i].getName() << " ha potenziato la casella nr. "<< rounds[i].getPosition()+1<< " in un albero." << std::endl;
                                    rounds[i].logToFile("Giocatore " + std::to_string(rounds[i].getName()) + " ha potenziato la casella nr. " + std::to_string(rounds[i].getPosition()+1) + " in un albergo");
                                } 
                            }
                            humanTurn=true;
                        }
                    }
                }
            }
        }
        game.showBoard(rounds);

        //TEMP: Rimozione dell'elemento puntato
        //p=rounds.erase(p);
        //std::cout << " Ho rimosso un player"<<std::endl;
        if(timelimit) turnLimit--;
    }
    std::cout<<std::endl;

    if(rounds.size()==1) {
        std::cout << "Il vincitore della partita e': P" << rounds[0].getName() << std::endl;
        rounds[0].logToFile("Il vincitore della partita e': P" + std::to_string(rounds[0].getName()));
    } else std::cout << "Tempo scaduto" << std::endl;
    //REQUIRED: ELSE IF partita conclusa per tempo scaduto, metodo di ricerca GOLD maggiore
    return 0;
}