#ifndef Board_h
#define Board_h
#include "Player.h"
#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

class Board {
	
	public:

		// Il costruttore di Default crea una board con elementi randomici
	    Board(void);

		// Il costruttore con un elemento al suo interno utilizza una board preimpostata (Ai fini di testing)
	    explicit Board(int elem);

		void showBoard();


	private:
		char v_[28];		// Board = array di 28 elementi
};

#endif // Board_h
