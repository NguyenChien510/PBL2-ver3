#include "ParkingLots.h"
#include <iomanip>
#define ADMIN 4
ParkingLots::ParkingLots(string ID,char area,bool status)
{
	this->LotID = ID;
	this->Area  = area;
	this->Status= status;
}
void ParkingLots::ReadFromFile()
{
	listpark.clear();
	ifstream filein("ParkingLots.txt");
	if(!filein.is_open())
	{
		cout << "Cannot open ParkingLots.txt"<<endl;
	}
	else
	{
		string id;
		char area;
		bool status;
		while(getline(filein, id, ';'))
		{
			filein >> area;
			filein.ignore();
			filein >> status;
			filein.ignore();
			ParkingLots park(id,area,status);
			listpark.push_back(park);
		}
		filein.close();
	}
}

ParkingLots::ParkingLots() {ReadFromFile();}

string ParkingLots::GetLotID()
{
	return this->LotID;
}
bool ParkingLots::GetStatus()
{
	return this->Status;
}
void ParkingLots::SetStatus(bool x)
{
	this->Status = x;
}
char ParkingLots::GetArea()
{
	return this->Area;
}
void ParkingLots::Show(int option)
{
	char AreaTemp = ((option == 1) ? 'C' : ((option == 2) ? 'B' : 'A'));
	if(option == 1 || option == 2 || option ==3){
			for(auto park:listpark)
		{
			if(park.Area == AreaTemp){
			cout << "LotID : " << park.LotID << endl;
			cout << "Area  : " << park.Area  << endl;
			cout << "Status: " << ((park.Status) ? "ORDER" : "EMPTY") << endl;
			cout << "-------------------"<<endl;
			}
		}
	}
	else if(option == ADMIN){
		cout<< setw(4) << "Lot ID" << " | "
        << setw(1) << "Area" << " | "
        << setw(5) << "Status" << endl;
	cout<< setfill('-') << setw(24) << "-" << setfill(' ') << endl;
    for (auto& park : listpark) {
    	cout<< setw(6) << park.LotID<< " | "
            << setw(4) << park.Area <<" | "
        	<< setw(5) << (park.Status == 0 ? "EMPTY" : "ORDERED") << endl;
        }
	}
}


