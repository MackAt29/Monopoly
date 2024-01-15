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

		Property& getCasella(int currentLocation);

		void showBoard(std::vector<Player>& players);
		
	private:
		std::vector<Property> v_;
		
};

#endif // Board_h
