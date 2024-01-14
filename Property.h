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

#pragma once
#include <cmath>

#define BASE_LAND 0;
#define ECO_HOME 2;
#define ECO_HOTEL 4;
#define STAND_HOME 4;
#define STAND_HOTEL 8;
#define LUX_HOME 7;
#define LUX_HOTEL 14;


class Property {
public:
	int getCategory();
	int getBuyPrice();
	int getHousePrice();
	int getHotelPrice();
	int getRentPrice();
	int getStatus();

	void setStatus(int newStatus);

	void buyHouse();
	void buyHotel();
	Property(int newCategory);
	void buyLand();
	void ripPlayer();
	//print

private:
	int Category = -1;
	int BuyPrice = -1;
	int HousePrice = -1;
	int HotelPrice = -1;
	int RentPrice = -1;
	int Status = -1;
	void updateRentPrice();
	//Player owner;

};