#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include "Registrations.h"
using namespace std;
const int DAILY = 1000;
const int WEEKLY = 7000;
const int MONTHLY = 30000;
class Accounts :  public Registrations
{
	private:
		string username;
		string password;
		bool role;
		vector<Accounts>listacc;
	public:
		Accounts();
		Accounts(string,string,bool);
		void ReadFromFile();
		void Show();
		bool Login(string,string);	
		int checkinput(string);
		void Check();
		void Register(ParkingLots,Vehicles,Registrations,string,int);
		void Edit(string,bool);
		void SetPassword(string);
		string GetPassWord(string);
		void loginForm();
		void Welcome();
		void UserInterface(string);
		void AdminInterface(string);
};
