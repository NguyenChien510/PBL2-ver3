#include "Registrations.h"
#include <iomanip>
#include <map>
const int DAILY = 50000;
const int WEEKLY = 100000;
const int MONTHLY = 200000;
Registrations::Registrations(string regisid,string ownid,string lp,string lotid,int tickettype,int price,string stime)
	:ParkingLots("",'A',0),Vehicles("","","","","")
{	
	this->RegistrationID = regisid;
	this->TicketType = tickettype;
	this->TicketPrice = price;
	this->StartTime = stime;
	this->OwnerID = ownid;
	this->LicensePlate = lp;
	this->LotID = lotid;
}

void Registrations::ReadFromFile()
{
	listregis.clear();
	ifstream filein("Registrations.txt");
	if(!filein.is_open())
	{
		cout << "Cannot open Registrations.txt"<<endl;
	}
	else
	{
		string regisid,lp,lotid,stime,ownid;
		int type, price;
		while(getline(filein,regisid,';'))
		{
			getline(filein,ownid,';');
			getline(filein,lp,';');
			getline(filein,lotid,';');
			filein>>type;filein.ignore();
			getline(filein,stime);
			price = (type == 1) ? DAILY : ((type == 2) ? WEEKLY : MONTHLY);
 			Registrations regis(regisid,ownid,lp,lotid,type,price,stime);
			listregis.push_back(regis);
		}
		filein.close();
	}
}

int Registrations::GetTicketPrice(){
	return this->TicketPrice;
}
int Registrations::GetTicketType(){
	return this->TicketType;
}

Registrations::Registrations()
	: Vehicles("","","","","")
{
	ReadFromFile();
}


void PrintRegistrationDetails(const Registrations& rg,Vehicles veh, bool isAdmin) {
    if (isAdmin) {
        cout << setw(15) << rg.RegistrationID << " | "
             << setw(10) << rg.OwnerID << " | "
             << setw(6) << rg.LotID << " | "
             << setw(15) << rg.LicensePlate << " | "
             << setw(10) << veh.GetBrand() << " | "
             << setw(10) << veh.GetModel() << " | "
             << setw(7) << veh.GetColor() << " | "
             << setw(11) << ((rg.TicketType == 1) ? "DAILY" : (rg.TicketType == 2 ? "WEEKLY" : "MONTHLY")) << " | "
             << setw(7) << rg.TicketPrice << " | "
             << setw(15) << rg.StartTime << endl;
    } else {
        cout << "--------------------------------------" << endl;
        cout << "Registration ID : " << rg.RegistrationID << endl;
        cout << "Owner ID        : " << rg.OwnerID << endl;
        cout << "Lot ID          : " << rg.LotID << endl;
        cout << "License Plate   : " << rg.LicensePlate << endl;
        cout << "Brand           : " << veh.GetBrand() << endl;
        cout << "Model           : " << veh.GetModel() << endl;
        cout << "Color           : " << veh.GetColor() << endl;
        cout << "Ticket Type     : " << ((rg.TicketType == 1) ? "DAILY" : (rg.TicketType == 2 ? "WEEKLY" : "MONTHLY")) << endl;
        cout << "Price           : " << rg.TicketPrice << endl;
        cout << "Start Time      : " << rg.StartTime << endl;
        cout << "--------------------------------------" << endl;
    }
}

void Registrations::Show(string user,bool role) {
    // Map for quick vehicle lookup by license plate
    Vehicles::ReadFromFile();
    map<string, Vehicles> vehicleMap;
    for (auto& veh : listveh) {
        vehicleMap[veh.GetLicensePlate()] = veh;
    }
    if (role == 1) {
        cout << setw(15) << "Registration ID" << " | "
             << setw(10) << "Owner ID" << " | "
             << setw(5) << "Lot ID" << " | "
             << setw(15) << "License Plate" << " | "
             << setw(10) << "Brand" << " | "
             << setw(10) << "Model" << " | "
             << setw(7) << "Color" << " | "
             << setw(10) << "Ticket Type" << " | "
             << setw(7) << "Price" << " | "
             << setw(15) << "Start Time" << endl;
        cout << setfill('-') << setw(134) << "-" << setfill(' ') << endl;
        for (auto& rg : listregis) {
            if (vehicleMap.find(rg.LicensePlate) != vehicleMap.end()) {
                PrintRegistrationDetails(rg, vehicleMap[rg.LicensePlate], true);
            }
        }
    }
    else {
        for (auto& rg : listregis) {
            if (rg.OwnerID == user && vehicleMap.find(rg.LicensePlate) != vehicleMap.end()) {
                PrintRegistrationDetails(rg, vehicleMap[rg.LicensePlate], false);
            }
        }
    }
}

