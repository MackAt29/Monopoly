/*
File fatto da Jonatan Ademi 2008796
In questo file si trova il main e tutta la gestione dei turni
*/
#include "Board.h"
#include "Player.h"
#include "Property.h"
#include <iostream>
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
        std::cout<<"Hai selezionato partita partite con 4 giocatori computer\n"<<std::endl;
        timelimit=true;
        placeHolder = {Player('1', false), Player('2', false), Player('3', false), Player('4', false)};
    }
    else if(argv[1] == std::string("human")){
        std::cout<<"Hai selezionato partita partite 3 giocatori computer e un giocatore umano\n"<<std::endl;
        std::cout<<"--==Tu sei il giocatore 1==--\n"<<std::endl;
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
    std::cout<<"Ordine dei turni: ";
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
                        std::cout << "Giocatore " << rounds[i].getName() << " è stato eliminato" << std::endl;
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
                            std::cout << "Giocatore " << rounds[i].getName() << " non ha abbastanza soldi per comprare la Casella nr. "<< rounds[i].getPosition()+1 << std::endl;
                        }
                        //SE LA RISPOSTA E' SI', allora procedi.
                        else {
                            //CONTROLLO se il giocatore di turno e' umano. 
                            if(rounds[i].isHumanPlayer()){

                                //SE SI', allora finché il giocatore non decide se eseguire l'acquisto o meno, continua ad essere il suo turno
                                while(humanTurn){
                                    std::cout<<"E' il tuo turno. Sei arrivato alla Casella " << " " <<rounds[i].getPosition()+1 << " " << casella <<  " \nVuoi comprare il terreno per "<<casella.getBuyPrice()<<" fiorini? [Y/N]"<<std::endl;
                                    std::cout<<"Digita ''show'' per vedere la situazione della partita."<<std::endl;
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
                                        std::cout << "Input non valido. Riprova." << std::endl;
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
                                std::cout << "Giocatore " << rounds[i].getName() << " ha comprato la Casella nr. "<< rounds[i].getPosition()+1 << std::endl;
                            }
                        }
                    }
                    //STEP 7.3: Questa casella è già di tua proprietà, PUOI decidere di potenziarla, costruendo una casa e poi un albergo
                    else if(casella.getOwner() == &rounds[i]){
                        //COME PRIMA, se sei un UMANO, la scelta avviene per inserimento
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
                                //SE questa casella è vuota, costruisci una casa.
                                if(casella.getStatus()==1){
                                    rounds[i].payProperty(casella.getHousePrice());
                                    casella.buyHouse();
                                    std::cout << "Giocatore " << rounds[i].getName() << " ha costruito una casa nella Casella nr. "<< rounds[i].getPosition()+1 << std::endl;
                                } 
                                //SE questa casella ha una casa, potenziala in un albergo
                                else if(casella.getStatus()==2){
                                    rounds[i].payProperty(casella.getHotelPrice());
                                    casella.buyHotel();
                                    std::cout << "Giocatore " << rounds[i].getName() << " ha potenziato la Casella nr. "<< rounds[i].getPosition()+1<< " in un albero." << std::endl;
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
    std::cout<<"Partita conclusa" <<std::endl;
    game.showBoard(rounds);

    //STEP 9.1: Se la partita è conclusa perché è rimasto un solo giocatore, stampa il vincitore.
    if(rounds.size()==1)
        std::cout << "Il vincitore della partita e': P" << rounds[0].getName() << std::endl;

    //STEP 9.2: Se la partita era tra 4 CPU E sono passati 10 turni stampa il giocatore che aveva più fiorini alla fine della partita
    else {
        std::cout << "Tempo scaduto" << std::endl;
        int c = 0;
        for(int i = 1; i<rounds.size();++i){
            if(rounds[c].getGold()<rounds[i].getGold()){
                c=i;
            }
        }
        std::cout << "Il vincitore/i della partita per maggior quantita' di fiorini: P" << rounds[c].getName();
        //"In caso di quantità uguale di fiorini, è permessa la vittoria ex-equo"
        for(int i = 0; i<rounds.size();++i){
            if(rounds[c].getGold()==rounds[i].getGold()&& c!=i){
                std::cout << " P" << rounds[i].getName();
            }
        }
    }
    return 0;
}
