/* ------------------------------------------------------------------
Final Project Milestone 2
Module:      Parking
Filename:    Parking.h
Version 1.0
Author:         Fardad Soleimanloo
Revision History
---------------------------------------------------------------------
Date         Reason
2020/6/27    Preliminary release
---------------------------------------------------------------------
Name:        Doohie Lee
Student No:  163244197
Email:       dlee175@myseneca.ca
Section:     NBB
Date:        July 12 2020
---------------------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
---------------------------------------------------------------------*/
#ifndef SDDS_PARKING_h
#define SDDS_PARKING_h
#include "Menu.h"
#include "Utils.h"
#include "Vehicle.h"
#include <ctype.h>
#include "Car.h"
#include "Motorcycle.h"
#include <fstream>
namespace sdds {
	class Parking {
		char* m_parking;
		Menu* v_menu;
		Menu* m_menu;
		int spotnum; 
		Vehicle* m_vehicle[100];
		int parkednum;


		bool isEmpty();
		void parkingStatus();
		void parkVehicle();
		void returnVehicle();
		void listParkedVehicles();
		bool closeParking();
		bool exitParkingApp();
		bool loadDataFile();
		void saveDataFile();


	public:
		//Parking(const char* parking);
		Parking(const char* datafile, int noOfSpots);

		~Parking();
		Parking(const Parking& parking) = delete;
		Parking& operator =(const Parking parking) = delete;
		int run();
		

	};

}
#endif