#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;
class ParkingLots
{
	protected:
		string LotID;
		char Area;
		bool Status; // 0 = empty
		vector<ParkingLots>listpark;
	public:
		ParkingLots();
		ParkingLots(string,char,bool);
		void ReadFromFile();
		string GetLotID();
		char GetArea();
		bool GetStatus();
		void SetStatus(bool);	
		void Show(int);
};
