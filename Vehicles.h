#include "Owners.h"
class Vehicles : public Owners
{
	protected:
		string OwnerID;
		string LicensePlate;
		string Brand;
		string Model;
		string Color;
		vector<Vehicles>listveh;
	public:
		Vehicles();
		Vehicles(string,string,string,string,string);
		string GetOwnerID();
		string GetLicensePlate();
		string GetBrand();
		string GetModel();
		string GetColor();
		void ReadFromFile();
		void Show();
};
