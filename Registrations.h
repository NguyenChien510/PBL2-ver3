#include "ParkingLots.h"
#include "Vehicles.h"
class Registrations : public ParkingLots, public Vehicles
{
	protected:
		string RegistrationID;
		int TicketType;
		int TicketPrice;
		string StartTime;
		string OwnerID;
		string LicensePlate;
		string LotID;
		vector<Registrations> listregis;
	public:
		Registrations();
		Registrations(string,string,string,string,int,int,string);
		void ReadFromFile();
		void Show(string,bool);
		void PrintRegistrationDetails(Registrations);
		int GetTicketPrice();
		int GetTicketType();
		string GetStartTime();
};
