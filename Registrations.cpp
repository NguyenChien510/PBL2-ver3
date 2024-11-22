#include "Registrations.h"
#include <iomanip>
#include <map>
#include <algorithm>
#include <unordered_map>
Registrations::Registrations(string regisid,string ownid,string lp,string lotid,int tickettype,int price,string stime)
	:ParkingLots("",'A',0,""),Vehicles("","","","")
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
			filein>>price;filein.ignore();
			getline(filein,stime);
		//	price = (type == 1) ? DAILY : ((type == 2) ? WEEKLY : MONTHLY);
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
string Registrations::GetStartTime(){
	return this->StartTime;
}
Registrations::Registrations()
	: Vehicles("","","","")
{
	ReadFromFile();
}


void Registrations::PrintRegistrationDetails(Registrations rg) {
        cout << setw(15) << rg.RegistrationID << " | "
             << setw(10) << rg.OwnerID << " | "
             << setw(6) << rg.LotID << " | "
             << setw(15) << rg.LicensePlate << " | "
             << setw(11) << ((rg.TicketType == 1) ? "DAILY" : (rg.TicketType == 2 ? "WEEKLY" : "MONTHLY")) << " | "
             << setw(7) << rg.TicketPrice << " | "
             << setw(15) << rg.StartTime << endl;
}

void Registrations::Show(string user,bool role) {
	cout << setw(15) << "Registration ID" << " | "
             << setw(10) << "Owner ID" << " | "
             << setw(5) << "Lot ID" << " | "
             << setw(15) << "License Plate" << " | "
             << setw(11) << "Ticket Type" << " | "
             << setw(7) << "Price" << " | "
             << setw(15) << "Start Time" << endl;
        cout << setfill('-') << setw(98) << "-" << setfill(' ') << endl;
	if(role == 1){
		for(auto rg:listregis){
			PrintRegistrationDetails(rg);
		}
	}
	else if(role == 0)
	{
		for(auto rg:listregis){
			if(rg.OwnerID == user) PrintRegistrationDetails(rg);
		}
	}
}

