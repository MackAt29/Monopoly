#include "Board.h"

// Default constructor
Board::Board(){
    std::srand ( unsigned ( std::time(0) ) );
	int a[24] = {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2};
    std::random_shuffle(std::begin(a), std::end(a));
    int j=0;
    this->v_.push_back(Property(3));
    for (int i = 1; i < 28; ++i) {
        if(i%7==0){
            this->v_.push_back(Property(3));
            ++i;
        }
        this->v_.push_back(Property(a[j]));
        ++j;
    }

}

Property& Board::getCasella(int currentLocation){
    return v_[currentLocation];
}

void Board::showBoard(const std::vector<Player>& players){
    std::string a[28] = {"","","","","","","","","","","","","","","","","","","","","","","","","","",""};
    for(int i=0;i<players.size();++i){
        a[players[i].currentLocation]=a[players[i].currentLocation] + players[i].name;
    }

    std::cout<<"\n     1     2     3     4     5     6     7     8     "<<std::endl;
    std::cout<<"A  | P"<<v_[0]<<a[0]<<" | | "<<v_[1]<<a[1]<<" | | "<<v_[2]<<a[2]<<" | | "<<v_[3]<<a[3]<<" | | "<<v_[4]<<a[4]<<" | | "<<v_[5]<<a[5]<<" | | "<<v_[6]<<a[6]<<" | | "<<v_[7]<<a[7]<<"  |"<<std::endl;
    std::cout<<"C  | "<<v_[27]<<a[27]<<" |                                     | "<<v_[8]<<a[8]<<" |"<<std::endl;
    std::cout<<"D  | "<<v_[26]<<a[26]<<" |                                     | "<<v_[9]<<a[9]<<" |"<<std::endl;
    std::cout<<"E  | "<<v_[25]<<a[25]<<" |                                     | "<<v_[10]<<a[10]<<" |"<<std::endl;
    std::cout<<"F  | "<<v_[24]<<a[24]<<" |                                     | "<<v_[11]<<a[11]<<" |"<<std::endl;
    std::cout<<"G  | "<<v_[23]<<a[23]<<" |                                     | "<<v_[12]<<a[12]<<" |"<<std::endl;
    std::cout<<"H  | "<<v_[22]<<a[22]<<" |                                     | "<<v_[13]<<a[13]<<" |"<<std::endl;
    std::cout<<"I  |  "<<v_[21]<<a[21]<<" | | "<<v_[20]<<a[20]<<" | | "<<v_[19]<<a[19]<<" | | "<<v_[18]<<a[18]<<" | | "<<v_[17]<<a[17]<<" | | "<<v_[16]<<a[16]<<" | | "<<v_[15]<<a[15]<<" | | "<<v_[14]<<a[14]<<"  |"<<std::endl;
    
}
