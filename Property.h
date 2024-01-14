#pragma once
#include "Player.h"
#include <ostream>

#define BASE_LAND 0;
#define ECO_HOME 2;
#define ECO_HOTEL 4;
#define STAND_HOME 4;
#define STAND_HOTEL 8;
#define LUX_HOME 7;
#define LUX_HOTEL 14;

class Property;

class Property {
public:
	int getCategory();
	int getBuyPrice();
	int getHousePrice();
	int getHotelPrice();
	int getRentPrice();
	int getStatus();
	Player getOwner();

	void setStatus(int newStatus);

	void buyHouse();
	void buyHotel();
	Property(int newCategory);
	void buyLand(Player *newOwner);
	void ripPlayer();
	//print

	friend std::ostream& operator<<(std::ostream& output, const Property& Pr);

private:
	int Category = -1;
	int BuyPrice = -1;
	int HousePrice = -1;
	int HotelPrice = -1;
	int RentPrice = -1;
	int Status = -1;

	Player *owner = nullptr;
	void updateRentPrice();
};
