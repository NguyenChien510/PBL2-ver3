#include "Owners.h"
#include <iomanip>
Owners::Owners(string id,string name,string phone,string email)
{
	this->OwnerID = id;
	this->Name = name;
	this->Phone = phone;
	this->Email = email;
}
void Owners::ShowInclude(string user,int check)
{
	ReadFromFile();
	for(auto own:listown){
		if(own.OwnerID == user){
			switch(check){
				case 1:{
					cout << own.Name << endl;
					break;
				}
				case 2:{
					cout << own.Phone << endl;
					break;
				}
				case 3:{
					cout << own.Email << endl;
					break;
				}
			}
		}
	}
}
string Owners::GetOwnerID()
{
	return this->OwnerID;
}
string Owners::GetName(){
	return this->Name;
}
string Owners::GetPhone(){
	return this->Phone;
}
string Owners::GetEmail(){
	return this->Email;
}
void Owners::SetName(string name){
	this->Name = name;
}
void Owners::SetPhone(string phone){
	this->Phone = phone;
}
void Owners::SetEmail(string mail){
	this->Email = mail;
}
void Owners::ReadFromFile()
{
	listown.clear();
	ifstream filein("Owners.txt");
	if(!filein.is_open())
	{
		cout << "Cannot open Owenrs.txt"<<endl;
	}
	else
	{
		string id,name,phone,email;
		while(getline(filein,id,';'))
		{
			getline(filein,name,';');
			getline(filein,phone,';');
			getline(filein,email);
			Owners own(id,name,phone,email);
			listown.push_back(own);
		}
		filein.close();
	}
}


Owners::Owners(){
	ReadFromFile();
}
void Owners::Show(string user,bool role)
{
	cout<< setw(15) << "Owner ID" << " | "
        << setw(20) << "Name" << " | "
        << setw(15) << "Phone" << " | "
        << setw(25) << "Email" << endl;
	cout<< setfill('-') << setw(84) << "-" << setfill(' ') << endl;
	if (role == 1) {
    for (auto& own : listown) {
    	cout<< setw(15) << own.OwnerID << " | "
            << setw(20) << own.Name << " | "
            << setw(15) << own.Phone << " | "
        	<< setw(25) << own.Email << endl;
        }
    }
    else{
    	for (auto& own : listown) {
        if (own.OwnerID == user) {
            cout<< setw(15) << own.OwnerID << " | "
                << setw(20) << own.Name << " | "
                << setw(15) << own.Phone << " | "
                << setw(25) << own.Email << endl;
			}
		}
	}
}
