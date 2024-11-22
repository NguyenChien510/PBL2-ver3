#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
class Owners
{
	protected:
		string OwnerID;
		string Name;
		string Phone;
		string Email;
		vector<Owners>listown;
	public:
		Owners(string,string,string,string);
		Owners();
		string GetOwnerID();
		string GetName();
		string GetPhone();
		string GetEmail();
		void SetName(string);
		void SetPhone(string);
		void SetEmail(string);
		void ReadFromFile();
		void Show(string,bool);
		void ShowInclude(string,int);
};
