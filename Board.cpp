#include "Board.h"

// Default constructor
Board::Board(){
	char v[28] = {'P', 'L','L','E','S','S','S',' ', 'S', 'E', 'S', 'E', 'L', 'E', ' ', 'E', 'E', 'S', 'L', 'S', 'S', ' ', 'E', 'E', 'S', 'L', 'S', 'L'};
    for (int i = 0; i < 28; ++i) {
        this->v_[i] = v[i];
    }

}

// Explicit constructor
Board::Board(int elem){
	char v[28] = {'P', 'L','L','E','S','S','S',' ', 'S', 'E', 'S', 'E', 'L', 'E', ' ', 'E', 'E', 'S', 'L', 'S', 'S', ' ', 'E', 'E', 'S', 'L', 'S', 'L'};
    
}
