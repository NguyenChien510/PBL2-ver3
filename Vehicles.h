#include "Owners.h"
class Vehicles : public Owners
{
	protected:
		string OwnerID;
		string LicensePlate;
		string Brand;
		string Model;
		vector<Vehicles>listveh;
	public:
		Vehicles();
		Vehicles(string,string,string,string);
		string GetOwnerID();
		string GetLicensePlate();
		string GetBrand();
		string GetModel();
		void ReadFromFile();
		void Show();
};
