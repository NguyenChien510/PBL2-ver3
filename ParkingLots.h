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
		string EndTime;
		vector<ParkingLots>listpark;
	public:
		ParkingLots();
		ParkingLots(string,char,bool,string);
		void ReadFromFile();
		string GetLotID();
		char GetArea();
		bool GetStatus();
		void SetStatus(bool);	
		void SetEndTime(string);
		void SetEndTimeNull();
		string GetEndTime();
		void Show(int);
};
