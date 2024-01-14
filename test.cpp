#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
//#include "Board.h"
#include "Player.h"
#include "Property.h"


int main (){
  std::srand ( unsigned ( std::time(0) ) );

    char v[28] = {'P', 'L','L','E','S','S','S',' ', 'S', 'E', 'S', 'E', 'L', 'E', ' ', 'E', 'E', 'S', 'L', 'S', 'S', ' ', 'E', 'E', 'S', 'L', 'S', 'L'};
    //Stampa griglia
    std::cout<<"     1     2     3     4     5     6     7     8     "<<std::endl;
    std::cout<<"A  | "<<v[0] << " | | "<<v[1]<<" | | "<<v[2]<<" | | "<<v[3]<<" | | "<<v[4]<<" | | "<<v[5]<<" | | "<<v[6]<<" | | "<<v[7]<<" |"<<std::endl;
    std::cout<<"C  | "<<v[27]<<" |                                     | "<<v[8]<<" |"<<std::endl;
    std::cout<<"D  | "<<v[26]<<" |                                     | "<<v[9]<<" |"<<std::endl;
    std::cout<<"E  | "<<v[25]<<" |                                     | "<<v[10]<<" |"<<std::endl;
    std::cout<<"F  | "<<v[24]<<" |                                     | "<<v[11]<<" |"<<std::endl;
    std::cout<<"G  | "<<v[23]<<" |                                     | "<<v[12]<<" |"<<std::endl;
    std::cout<<"H  | "<<v[22]<<" |                                     | "<<v[13]<<" |"<<std::endl;
    std::cout<<"I  | "<<v[21]<<" | | "<<v[20]<<" | | "<<v[19]<<" | | "<<v[18]<<" | | "<<v[17]<<" | | "<<v[16]<<" | | "<<v[15]<<" | | "<<v[14]<<" |"<<std::endl;
    for (int i = 0; i < 28; ++i) {
        std::cout<<v[i];
    }
    std::cout<<std::endl;

    char a[24] = {'L','L','E','S','S','S','S', 'E', 'S', 'E', 'L', 'E', 'E', 'E', 'S', 'L', 'S', 'S', 'E', 'E', 'S', 'L', 'S', 'L'};
    std::random_shuffle(std::begin(a), std::end(a));
    int j=0;
    v[0]='P';
    for (int i = 1; i < 28; ++i) {
        if(i%7==0){
            v[i]=' ';
            ++i;
        }
        v[i] = a[j];
        ++j;
    }
    for (int i = 0; i < 28; ++i) {
        std::cout<<v[i];
    }
    
    std::cout<<std::endl;
    
    std::vector<Player> rounds;
    std::vector<Player> placeHolder = {Player('1', false), Player('2', false), Player('3', false), Player('4', false)};
    
    for (int i = 0; i < 4; ++i) {
        int maxIndex = 0;

        // Trova l'indice del massimo elemento nel resto del vettore
        for (int j = 0; j < placeHolder.size(); ++j) {
            if (placeHolder[j].initTurn > placeHolder[maxIndex].initTurn) {
                maxIndex = j;
            }
        }
        
        // Scambia l'elemento corrente con il massimo trovato
        rounds.push_back(placeHolder[maxIndex]);
        placeHolder.erase(placeHolder.begin() + maxIndex);
        
    }
    std::cout<<std::endl;    
    
    for (int i = 0; i < rounds.size(); ++i) {
        std::cout<<rounds[i].initTurn<< " ";
    }
    std::cout<<std::endl;
    
    Property casa(3);
    std::cout<<"Stampo: "<<casa<< "casella" <<std::endl;

    std::vector<Property> caselle = {Property(3),Property(0),Property(1),Property(2)};
    for (int i = 0; i < caselle.size(); ++i) {
        std::cout<<caselle[i]<< " ";
    }
    
    return 0;
}


