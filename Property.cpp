#include "Property.h"

	int Property::getCategory() {
		return Category;
	}
	int Property::getBuyPrice() {
		return BuyPrice;
	}
	int Property::getHousePrice() {
		return HousePrice;
	}
	int Property::getHotelPrice() {
		return HotelPrice;
	}
	int Property::getRentPrice() {
		return RentPrice;
	}
	int Property::getStatus() {
		return Status;
	}

	Player* Property::getOwner() {
		std::cout<<"Ciaoo\n";
		if (owner == nullptr) {
			std::cout<<"Ciaoo\n";
			//throw "No owner for this land.";
		}
		std::cout<<"Ciaoo\n";
		return owner;
	}

	void Property::setStatus(int newStatus) {
		Status = newStatus;
		Property::updateRentPrice();
	}


	Property::Property(int newCategory) {
		//if (Category > 3 || Category < 0) throw "Invalid category value.";
		switch (newCategory)
		{
		case 0:
			this->Category = newCategory;
			this->BuyPrice = 6;
			this->HousePrice = 3;
			this->HotelPrice = 3;
			this->Status = 0;
			updateRentPrice();
			break;
		case 1:
			this->Category = newCategory;
			this->BuyPrice = 10;
			this->HousePrice = 5;
			this->HotelPrice = 5;
			this->Status = 0;
			updateRentPrice();
			break;
		case 2:
			this->Category = newCategory;
			this->BuyPrice = 20;
			this->HousePrice = 10;
			this->HotelPrice = 10;
			this->Status = 0;
			updateRentPrice();
			break;
		case 3:
			this->Category = newCategory;
			this->Status = 0;
			break;
		default:
			throw "Invalid category value.";
			break;
		}
	}
	void Property::buyLand(Player *newOwner) {
		if (Category == 3) { throw "Nothing to buy over here."; }
		Status = 1;
		owner = newOwner;
		updateRentPrice();
	}
	void Property::buyHouse() {
		if (Category == 3) { throw "Nothing to buy over here."; }
		if (true) {
			Status = 2;
			updateRentPrice();
		}
	}
	
	//bisognerebbe controllare che in tutti i buy io non abbia gia lo stesso status... cioe
	//se compro una casa devo controllare anche che io non l abbia gia comprata, uguale per albergo e terreno

	 //devi controllare che abbia prima comprato una casa
	void Property::buyHotel() {
		if (Category == 3) { throw "Nothing to buy over here."; }
		if (true) {
			Status = 3;
			updateRentPrice();
		}
	}
	void Property::ripPlayer() {
		Status = 0;
		owner = nullptr;
		updateRentPrice();
	}

	//print
	//devi fare l overload dell ostrem ....


	//Player owner;
	void Property::updateRentPrice() {
		switch (getStatus())
		{
		case 0:
		case 1:
			RentPrice = 0;
			break;
		case 2:
			if (Category == 0) RentPrice = 2;
			else if (Category == 1) RentPrice = 4;
			else if (Category == 2) RentPrice = 7;
			else throw "Invalid category value.";
			break;
		case 3:
			if (Category == 0) RentPrice = 4;
			else if (Category == 1) RentPrice = 8;
			else if (Category == 2) RentPrice = 14;
			else throw "Invalid category value.";
			break;
		default:
			break;
		}
	}
	/*
	std::ostream& operator<<(std::ostream& output, const Property& P) {
		output << "Categoria casella: ";
		if (P.Category == 0) { output << "Casella Economica"; };
		if (P.Category == 1) { output << "Casella Standard"; };
		if (P.Category == 2) { output << "Casella Lusso"; };
		if (P.Category == 3) { output << "Casella Angolare"; return output; };
		output 	<< "  Prezzo affitto: " << P.RentPrice << "  Prezzo Terreno: " << P.BuyPrice << "  Prezzo casa: " << P.HousePrice << "  Prezzo Albergo: " << P.HotelPrice << "  Stato casella: " << P.Status;
		return output;
	}
	*/
	std::ostream& operator<<(std::ostream& output, const Property& Pr) {
		if (Pr.Category == 0) { output << "E";
			switch (Pr.Status) {
				case 0: break;
				case 1: break;
				case 2: output << "*"; break;
				case 3: output << "^"; break;
				default: break;
			}
		};
		if (Pr.Category == 1) {output << "S";
			switch (Pr.Status){
				case 0: break;
				case 1: break;
				case 2: output << "*"; break;
				case 3: output << "^"; break;
				default: break;
			}
		};
		if (Pr.Category == 2) { output << "L";
			switch (Pr.Status) {
				case 0: break;
				case 1: break;
				case 2: output << "*"; break;
				case 3: output << "^"; break;
			default: break;
			}
		};
		if (Pr.Category == 3) {return output; }; 
		return output;
	}