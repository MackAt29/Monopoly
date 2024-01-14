/*Casella:{
const int category; (0-1-2) economica-standard-lusso
const int tPrice; Costo della casella per l’acquisto (6-10-20 fiorini in base alla categoria)
const int hPrice; Costo per costruire la Casa=Costo per costruire l’albergo (3-5-10 fiorini in base alla categoria)
const int upPrice; Costo per costruire l’albergo (3-5-10 fiorini in base alla categoria)
int stayCost=0; Costo quando un giocatore non proprietario si ferma sulla casella (non è const perchè durante la partita il valore aumenta)
int status = 0; (0-1-2-3) vuota-acquistata-casa-albergo
&Pedina owner; a chi appartiene la casella (se è stata acquistata)
array &Pedina occupied[]; array di quanti giocatori sono attualmente in questa casella, una idea su come segnare se e quali player ci sono.
metodo Print(): mostra in output (category + status + occupied[](mostra i giocatori presenti, altrimenti null quindi lascia vuoto)
}
*/
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
	void Property::buyLand() {
		if (Category == 3) { throw "Nothing to buy over here."; }
		Status = 1;
		updateRentPrice();
	}
	void Property::buyHouse() {
		if (Category == 3) { throw "Nothing to buy over here."; }
		Status = 2;
		updateRentPrice();
	}
	
	//bisognerebbe controllare che in tutti i buy io non abbia gia lo stesso status... cioe
	//se compro una casa devo controllare anche che io non l abbia gia comprata, uguale per albergo e terreno

	//devo controllare che abbia prima comprato una casa
	void Property::buyHotel() {
		if (Category == 3) { throw "Nothing to buy over here."; }
		Status = 3;
		updateRentPrice();
	}
	void Property::ripPlayer() {
		Status = 0;
		updateRentPrice();
	}

	//print
	//devo fare l overload dell ostrem ....


	//Player owner;


	void Property::updateRentPrice() {
		switch (Status)
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

