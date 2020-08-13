/* ------------------------------------------------------------------
Final Project Milestone 2
Module:      Parking
Filename:    Parking.cpp
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
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Parking.h"


using namespace std;

namespace sdds {

	Parking::Parking(const char* datafile, int noOfSpots)
	{
		if (noOfSpots <10 || noOfSpots >100||datafile == nullptr || datafile[0] == '\0') {
			m_menu = nullptr;
			v_menu = nullptr;
			m_parking = nullptr;
			parkednum = 0;
			spotnum = 0;
		}
		else {
			m_parking = new char[strlen(datafile) + 1];
			strcpy(m_parking, datafile);
			spotnum = noOfSpots;
			parkednum = 0;
		}
		for (int i = 0; i < spotnum; i++) {
			m_vehicle[i] = nullptr;
		}
		if (loadDataFile()) {
			m_menu = new Menu("Parking Menu, select an action:", 0);
			m_menu->add("Park Vehicle");
			m_menu->add("Return Vehicle");
			m_menu->add("List Parked Vehicles");
			m_menu->add("Close Parking (End of day)");
			m_menu->add("Exit Program");

			v_menu = new Menu("Select type of the vehicle:", 1);
			v_menu->add("Car");
			v_menu->add("Motorcycle");
			v_menu->add("Cancel");

		}
		else {
			cout << "Error in data file" << endl;
			m_parking = nullptr;
		}

	}
	bool Parking::isEmpty() {
		if (m_parking == nullptr || m_parking[0] == '\0') {
			return true;
		}
		else {
			return false;
		}
	}

	void Parking::parkingStatus() {
		cout << "****** Seneca Valet Parking ******" << endl;
		cout << "*****  Available spots: ";
		cout.width(4);
		cout << left << spotnum - parkednum << " *****" << endl;

	}

	void Parking::parkVehicle() {
		if (spotnum - parkednum == 0) {
			cout << "Parking is full" << endl;

		}
		else {
			
			int choice = v_menu->run();
			bool breaking = false;
			switch (choice) {


			case 1:
				breaking = false;
				Vehicle * temp;
				temp = new Car;
				temp->setCsv(false);
				temp->read();
				for (int i = 0; i < spotnum && !breaking; i++) {
					if (m_vehicle[i] == nullptr) {
						m_vehicle[i] = temp;
						parkednum++;
						m_vehicle[i]->setParkingSpot(i + 1);
						cout << endl<< "Parking Ticket" << endl;
						m_vehicle[i]->write(cout);
						cout << endl;
						breaking = true;
					}

				}
				break;

			case 2:
				Vehicle * temp2;
				temp2 = new Motorcycle;
				temp2->setCsv(false);
				temp2->read();
				breaking = false;

				for (int i = 0; i < spotnum && !breaking; i++) {
					if (m_vehicle[i] == nullptr) {
						m_vehicle[i] = temp2;
						parkednum++;
						m_vehicle[i]->setParkingSpot(i + 1);
						cout <<endl<< "Parking Ticket" << endl;
						m_vehicle[i]->write(cout);
						cout << endl;
						breaking = true;
					}

				}

				break;

			case 3: 
				cout << "Parking cancelled" << endl;
				break;

			}
		}


	}

	void Parking::returnVehicle() {
		cout << "Return Vehicle" << endl;
		char temp[100];
		cout << "Enter Licence Plate Number: ";
		cin.getline(temp, 10, '\n');
		while (strlen(temp) > 8 && strlen(temp) < 1) {
			cout << "Invalid Licence Plate, try again: ";
			cin.getline(temp, 10, '\n');
		}
		bool breaking = false;
		for (int i = 0; i < spotnum && !breaking; i++) {
			if ((*m_vehicle[i]) == temp) {
				cout<<endl << "Returning: "<<endl; 
                                cout<< (*m_vehicle[i]);
                                cout<<endl;
				delete m_vehicle[i];
				m_vehicle[i] = nullptr;
				parkednum--;
				breaking = true;
			}
		}
		if (!breaking) {
			cout << "License plate " << temp << " Not found" << endl;
			
		}

	}

	void Parking::listParkedVehicles() {
		cout << "*** List of parked vehicles ***" << endl;
		for (int i = 0; i < spotnum; i++) {
			if (m_vehicle[i] != nullptr) {
				cout << (*m_vehicle[i]);
				cout << "-------------------------------" << endl;

			}
		}

	}

	bool Parking::closeParking() {

		bool closed = true;
		if (isEmpty()) {
			cout << "Closing Parking" << endl;
		}
		else {
			bool breaking = false;
			char yesNo[40];
			cout << "This will Remove and tow all remaining vehicles from the parking!" << endl << "Are you sure? (Y)es/(N)o: ";
			do {
				cin.getline(yesNo, 40, '\n');
				if (((strcmp("N", yesNo) == 0 || strcmp("Y", yesNo) == 0 || strcmp("n", yesNo) == 0 || strcmp("y", yesNo) == 0)) && strlen(yesNo) == 1) {
					breaking = true;
				}
				else {
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				}

				if (yesNo[0] == 'y'|| yesNo[0] =='Y') {
					cout << "Closing Parking" << endl;
					for (int i = 0; i < spotnum; i++) {
						if (m_vehicle[i] != nullptr) {
                                                        cout <<endl;
							cout << "Towing request" << endl;
							cout << "*********************" << endl;
							cout << (*m_vehicle[i]);
							delete m_vehicle[i];
							m_vehicle[i] = nullptr;
							parkednum--;
						}
					}
				}
				else if ((yesNo[0]) == 'n'||yesNo[0] =='N') {
					cout << "Aborted!" << endl;
					closed = false;
				}
				else {
					closed = false;
				}
			} while (!breaking);
		}
		
		return closed;

		//return true;
	}

	bool Parking::exitParkingApp() {
		bool breaking = false;
		char yesNo[40];

		cout << "This will terminate the program!" << endl;
		cout << "Are you sure? (Y)es/(N)o: ";

		do {
			cin.getline(yesNo,40,'\n');
			if (strcmp("N", yesNo) == 0 || strcmp("Y", yesNo) == 0 || strcmp("n", yesNo) == 0 || strcmp("y", yesNo) == 0) {
				breaking = true;
			}
			else {
				cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
			}
		} while (!breaking);

		if (yesNo[0] == 'y'||yesNo[0] == 'Y') {
			cout << "Exiting program!" << endl;
		}

		return ((yesNo[0]) == ('y') || (yesNo[0]) == ('Y')) ? true : false;

	}
	bool Parking::loadDataFile() {
		bool parking = false;
		if (isEmpty()) {
			parking = false;
		}
		else {
			ifstream fs(m_parking);
			fs.clear();
			if (fs.is_open()) {

				while (!fs.eof()) {
					char CorM;

					fs >> CorM;
					fs.ignore();

					if (fs.fail()) {
						return true;
					}
					Vehicle* temp = nullptr;

					if (CorM == 'M') {
						temp = new Motorcycle;
					}
					else if (CorM == 'C') {
						temp = new Car;
					}

					temp->setCsv(true);

					if (temp->read(fs)) {
						int indexnum = temp->getParkingSpot();
						m_vehicle[indexnum - 1] = temp;
						temp->setCsv(false);
						parkednum++;
					}
					else
					{
						delete temp;
						return false;
					}

				}
				return true;
			}
			else {
				return false;
			}



		}
		return parking;
	}
	void Parking::saveDataFile() {
		if (!isEmpty()) {
			ofstream of;
			of.open(m_parking);

			if (of.is_open()) {
				for (int i = 0; i < spotnum; i++) {
					if (m_vehicle[i] != nullptr) {
						m_vehicle[i]->setCsv(true);
						m_vehicle[i]->write(of);
					}
				}
			}

		}
	}
	Parking::~Parking() {
		saveDataFile();

		delete m_menu;
		delete v_menu;
		delete[] m_parking;
		for (int i = 0; i < parkednum; i++) {
			// if it cause memory leak change it to i< spotnum
			delete m_vehicle[i];
			m_vehicle[i] = nullptr;
		}

	}
	int Parking::run() {

		bool run = false;
		if (!isEmpty()) {


			do {
				parkingStatus();
				int choice = m_menu->run();


				switch (choice) {

				case 1:
					parkVehicle();
					break;

				case 2:
					returnVehicle();
					break;

				case 3:
					listParkedVehicles();
					break;

				case 4:
					if (closeParking()) {
						run = true;
					}
					break;

				case 5:
					if (exitParkingApp()) {
						run = true;
					}
					break;

				}
			} while (run == false);


			return 0;
		}
		return 1;
	}
}