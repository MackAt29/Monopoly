#include <iostream>

int main (){
    /*int v[28];

    // Popola l'array con valori da 0 a 27
    for (int i = 0; i < 28; ++i) {
        v[i] = 0;
    }*/

    char v[28] = {'P', 'L','L','E','S','S','S',' ', 'S', 'E', 'S', 'E', 'L', 'E', ' ', 'E', 'E', 's', 'L', 'S', 'S', ' ', 'E', 'E', 'S', 'L', 'S', 'Q'};
    //Stampa griglia
    std::cout<<"     1     2     3     4     5     6     7     8     "<<std::endl;
    std::cout<<"A  | "<<v[0]<<" | | "<<v[1]<<" | | "<<v[2]<<" | | "<<v[3]<<" | | "<<v[4]<<" | | "<<v[5]<<" | | "<<v[6]<<" | | "<<v[7]<<" |"<<std::endl;
    std::cout<<"C  | "<<v[27]<<" |                                     | "<<v[8]<<" |"<<std::endl;
    std::cout<<"D  | "<<v[26]<<" |                                     | "<<v[9]<<" |"<<std::endl;
    std::cout<<"E  | "<<v[25]<<" |                                     | "<<v[10]<<" |"<<std::endl;
    std::cout<<"F  | "<<v[24]<<" |                                     | "<<v[11]<<" |"<<std::endl;
    std::cout<<"G  | "<<v[23]<<" |                                     | "<<v[12]<<" |"<<std::endl;
    std::cout<<"H  | "<<v[22]<<" |                                     | "<<v[13]<<" |"<<std::endl;
    std::cout<<"I  | "<<v[21]<<" | | "<<v[20]<<" | | "<<v[19]<<" | | "<<v[18]<<" | | "<<v[17]<<" | | "<<v[16]<<" | | "<<v[15]<<" | | "<<v[14]<<" |"<<std::endl;
    std::cout<<v[17]<<std::endl;
    int newPosition = (18 - 1 + 10) % 28;
    std::cout<<newPosition<<std::endl;
    std::cout<<v[newPosition]<<std::endl;

    return 0;
}


