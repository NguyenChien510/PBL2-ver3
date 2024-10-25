#include "Vehicles.h"
#include <iomanip>
Vehicles::Vehicles(string ownid,string lp,string brand,string model,string color)
	:Owners("","","","")
{
	this->OwnerID = ownid;
	this->LicensePlate = lp;
	this->Brand = brand;
	this->Model = model;
	this->Color = color;
}

string Vehicles::GetOwnerID()
{
	return Owners::GetOwnerID();
}

string Vehicles::GetLicensePlate()
{
	return this->LicensePlate;
}
string Vehicles::GetBrand()
{
	return this->Brand;
}
string Vehicles::GetModel()
{
	return this->Model;
}
string Vehicles::GetColor()
{
	return this->Color;
}
void Vehicles::ReadFromFile()
{
	listveh.clear();
	ifstream filein("Vehicles.txt");
	if(!filein.is_open())
	{
		cout << "Cannot open Vehicles.txt"<<endl;
	}
	else
	{
		string ownid,lp,brand,model,color;
		while(getline(filein,ownid,';'))
		{
			getline(filein,lp,';');
			getline(filein,brand,';');
			getline(filein,model,';');
			getline(filein,color);
			Vehicles veh(ownid,lp,brand,model,color);
			listveh.push_back(veh);
		}
		filein.close();
	}
}

Vehicles::Vehicles()
	:Owners("","","","")
{
	ReadFromFile();
}

void Vehicles::Show(){
	cout<< setw(15) << "Owner ID" << " | "
        << setw(13) << "License Plate" << " | "
        << setw(12) << "Brand" << " | "
        << setw(12) << "Model" << " | "
        << setw(5) << "Color" << endl;
	cout<< setfill('-') << setw(71) << "-" << setfill(' ') << endl;
    for (auto& veh : listveh) {
    	cout<< setw(15) << veh.OwnerID << " | "
            << setw(13) << veh.LicensePlate << " | "
            << setw(12) << veh.Brand << " | "
        	<< setw(12) << veh.Model << " | "
        	<< setw(3) << veh.Color << endl;
        }
}
