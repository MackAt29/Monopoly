#include "Board.h"

// Default constructor
Board::Board(){
    std::srand ( unsigned ( std::time(0) ) );
	char a[24] = {'L','L','E','S','S','S','S', 'E', 'S', 'E', 'L', 'E', 'E', 'E', 'S', 'L', 'S', 'S', 'E', 'E', 'S', 'L', 'S', 'L'};
    std::random_shuffle(std::begin(a), std::end(a));
    int j=0;
    this->v_[0]='P';
    for (int i = 1; i < 28; ++i) {
        if(i%7==0){
            this->v_[i]=' '; 
            ++i;
        }
        this->v_[i] = a[j];
        ++j;
    }
    for (int i = 0; i < 28; ++i) {
        std::cout<<this->v_[i] ;
    }
    std::cout<<std::endl;

}

// Explicit constructor
Board::Board(int elem){
	char v[28] = {'P', 'L','L','E','S','S','S',' ', 'S', 'E', 'S', 'E', 'L', 'E', ' ', 'E', 'E', 'S', 'L', 'S', 'S', ' ', 'E', 'E', 'S', 'L', 'S', 'L'};
    for (int i = 0; i < 28; ++i) {
        this->v_[i] = v[i];
    }
}

void Board::showBoard(){
    std::cout<<"     1     2     3     4     5     6     7     8     "<<std::endl;
    std::cout<<"A  | "<<v_[0]<<" | | "<<v_[1]<<" | | "<<v_[2]<<" | | "<<v_[3]<<" | | "<<v_[4]<<" | | "<<v_[5]<<" | | "<<v_[6]<<" | | "<<v_[7]<<" |"<<std::endl;
    std::cout<<"C  | "<<v_[27]<<" |                                     | "<<v_[8]<<" |"<<std::endl;
    std::cout<<"D  | "<<v_[26]<<" |                                     | "<<v_[9]<<" |"<<std::endl;
    std::cout<<"E  | "<<v_[25]<<" |                                     | "<<v_[10]<<" |"<<std::endl;
    std::cout<<"F  | "<<v_[24]<<" |                                     | "<<v_[11]<<" |"<<std::endl;
    std::cout<<"G  | "<<v_[23]<<" |                                     | "<<v_[12]<<" |"<<std::endl;
    std::cout<<"H  | "<<v_[22]<<" |                                     | "<<v_[13]<<" |"<<std::endl;
    std::cout<<"I  | "<<v_[21]<<" | | "<<v_[20]<<" | | "<<v_[19]<<" | | "<<v_[18]<<" | | "<<v_[17]<<" | | "<<v_[16]<<" | | "<<v_[15]<<" | | "<<v_[14]<<" |"<<std::endl;
}
