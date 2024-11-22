#include "ParkingLots.h"
#include <iomanip>
#define ADMIN 4
ParkingLots::ParkingLots(string ID,char area,bool status,string endtime)
{
	this->LotID = ID;
	this->Area  = area;
	this->Status= status;
	this->EndTime = endtime;
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
		string id,endtime;
		char area;
		bool status;
		while(getline(filein, id, ';'))
		{
 			if (id.empty()) continue;
            filein >> area;
            if (filein.fail()) break;
            filein.ignore();
            filein >> status;
            if (filein.fail()) break;
            filein.ignore(); 
            getline(filein,endtime);
            if (endtime.empty()) continue;
            ParkingLots park(id, area, status,endtime);
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
void ParkingLots::SetEndTime(string endtime)
{
	this->EndTime = endtime;
}
string ParkingLots::GetEndTime()
{
	return this->EndTime;
}
char ParkingLots::GetArea()
{
	return this->Area;
}
void ParkingLots::SetEndTimeNull()
{
	this->EndTime = "NULL";
}
void ParkingLots::Show(int option)
{
	char AreaTemp = ((option == 1) ? 'C' : ((option == 2) ? 'B' : 'A'));
	if(option == 1 || option == 2 || option ==3){
			for(auto park:listpark)
		{
			if(park.Area == AreaTemp){
			cout << "LotID    : " << park.LotID << endl;
			cout << "Area     : " << park.Area  << endl;
			cout << "Status   : " << ((park.Status) ? "ORDER" : "EMPTY");
			if(park.Status==1){
			cout << "\nEnd Time : " << park.EndTime << endl;}
			else cout << endl;
			cout << "-------------------"<<endl;
			}
		}
	}
	else if(option == ADMIN){
		cout<< setw(4) << "Lot ID" << " | "
        << setw(1) << "Area" << " | "
        << setw(5) << "Status" << " | "
        << setw(8) << "End Time" << endl;
	cout<< setfill('-') << setw(33) << "-" << setfill(' ') << endl;
    for (auto park : listpark) {
    	cout<< setw(6) << park.LotID<< " | "
            << setw(4) << park.Area <<" | "
        	<< setw(5) << (park.Status == 0 ? "EMPTY" : "ORDERED");
        	if(park.Status == 1){
        		cout << setw(3)<<" "<<park.EndTime << endl;
			}
			else cout << endl;
        }
	}
}


