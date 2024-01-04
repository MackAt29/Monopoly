#ifndef Board_h
#define Board_h

class Board {
	
	public:

		// Il costruttore di Default crea una board con elementi randomici
	    Board();

		// Il costruttore con un elemento al suo interno utilizza una board preimpostata (Ai fini di testing)
	    explicit Board(int elem);


	private:
		char v_[28];		// Board = array di 28 elementi
};

#endif // Board_h
