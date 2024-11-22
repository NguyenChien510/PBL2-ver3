#include "Accounts.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
void UserInterface();
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void drawButton(int x, int y, string label, bool isSelected) {
    gotoxy(x, y);
    if (isSelected) {
        setColor(10); // Green color
        cout << "[ " << label << " ]"; // Button is selected
        setColor(7); // Return to default color
    } else {
        cout << "[ " << label << " ]"; // Button is not selected
    }
}
void drawBox(int x, int y, int width, int height) {
    // Ve khung dang nhap
    gotoxy(x, y);
    cout << char(218); // Goc tren trai
    for (int i = 0; i < width - 2; i++) cout << char(196); // Duong ngang
    cout << char(191); // Goc tren phai

    for (int i = 0; i < height - 2; i++) {
        gotoxy(x, y + i + 1);
        cout << char(179); // Duong doc ben trai
        gotoxy(x + width - 1, y + i + 1);
        cout << char(179); // Duong doc ben phai
    }

    gotoxy(x, y + height - 1);
    cout << char(192); // Goc duoi trai
    for (int i = 0; i < width - 2; i++) cout << char(196); // Duong ngang duoi
    cout << char(217); // Goc duoi phai
}

void drawTable(int x, int y, int rows, int cols) {
    int cellWidth = 20;  // Width of each cell
    int cellHeight = 8;  // Height of each cell
    
    // Draw the grid
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            drawBox(x + j * (cellWidth + 1), y + i * (cellHeight + 1), cellWidth, cellHeight);
        }
    }
}
void drawContent(int x, int y, string content) {
    gotoxy(x, y);
    cout << content;
}

void getpos(int baseX, int baseY, int cellWidth, int cellHeight, int row, int col, int &x, int &y) {
    x = baseX + col * (cellWidth + 1);
    y = baseY + row * (cellHeight + 1);
}
#include <iostream>
#include <string>
using namespace std;

int GetMonth(const string& date) {
    if (date.length() == 10 && date[2] == '-' && date[5] == '-') {
        string month_str = date.substr(3, 2); 
        return stoi(month_str); 
    }
    return -1;
}


void Accounts::Show() {
    cout << setw(15) << "Username" << " | "
         << setw(10) << "Password" << " | "
         << setw(10) << "Role" << endl;
    cout << setfill('-') << setw(41) << "-" << setfill(' ') << endl;
    for (auto acc : listacc) {
        cout << setw(16) << acc.username << "|"
             << setw(12) << acc.password << "|"
             << setw(10) << (acc.role == 0 ? "User" : "Admin") << endl;
    }
}



Accounts::Accounts(string username,string password,bool role)
{
	this->username = username;
	this->password = password;
	this->role = role;
}

Accounts::Accounts() {}

void Accounts::ReadFromFile()
{
	ifstream filein("Accounts.txt");
	if(filein.is_open())
	{
		listacc.clear();
		string user,pass;
		bool role;
		while(getline(filein,user,';'))
		{
			getline(filein,pass,';');
			filein>>role;
			filein.ignore();
			Accounts acc(user,pass,role);
			listacc.push_back(acc);
		}
		filein.close();
	}
	else cout << "Cannot open file Accounts.txt" << endl;
}

int	Accounts::checkinput(string s){
	for(char c:s){
		if(!isdigit(c)) return -1;
	}
	if(s=="") return -1;
	else if(s.length()>1) return -1;
	else
	return stoi(s);
}

void Accounts::SetPassword(string pass){
 	this->password = pass;
}

bool Accounts::Login(string user,string pass)
{
	ReadFromFile();
	while(true)
	{
	for(auto acc : listacc)
	{
		if(acc.username == user && acc.password == pass && acc.role == 1)	//ADMIN
		{
			while(1) AdminInterface(user);
		}
		else if(acc.username == user && acc.password == pass && acc.role == 0)   //USER
		{
			while(1) UserInterface(user);
		}
	}
}
}
string GetPassword() {
    string pass = "";
    char ch;
    while ((ch = _getch()) != '\r') { // '\r' lï¿½ ki tu Enter
        if (ch == '\b' && !pass.empty()) { // Xoa ki tu neu nhin Backspace
            pass.pop_back();
            cout << "\b \b"; // Xoa ki tu hien thi tren man hinh
        } else if (ch != '\b') { // Neu khong phai ki tu Backspace
            pass.push_back(ch);
            cout << '*'; // Hien thi '' thay vi ki tu thuc te
        }
    }
    cout << endl;
    return pass;
}

string Accounts::GetPassWord(string user){
	for (auto a : listacc){
		if(a.username == user){
			return a.password;
		}
	}
}


void Accounts::loginForm() {
    here:
    string user, pass;
    char ch;
    int formWidth = 40;
    int formHeight = 10;
    int startX = 35;
    int startY = 5;
    int selectedOption = 0; // 0: Login, 1: Back
    bool isSelected[2] = { true, false }; // To track the selected option
    while (true) {
        drawBox(startX, startY, formWidth, formHeight);
        gotoxy(startX + 12, startY + 1);
        cout << "HE THONG BAI DO XE";
        gotoxy(startX + 5, startY + 3);
        cout << "Username: ";
        gotoxy(startX + 5, startY + 4);
        cout << "Password: ";
        drawButton(startX + 15, startY + 6, "Login", isSelected[0]);
        drawButton(startX + 15, startY + 8, "Back", isSelected[1]);
        // Capture key press
        char key = _getch(); 
        if (key == 72) { // Up arrow key
            isSelected[selectedOption] = false; // Deselect
            selectedOption = (selectedOption == 0) ? 1 : 0; // Toggle selection
            isSelected[selectedOption] = true; // Select again
        } else if (key == 80) { // Down arrow key
            isSelected[selectedOption] = false; // Deselect
            selectedOption = (selectedOption == 1) ? 0 : 1; // Toggle selection
            isSelected[selectedOption] = true; // Select again
        } else if (key == 13) { // Enter key
            if (selectedOption == 0) {
                gotoxy(startX + 15, startY + 3);
                getline(cin, user);
                gotoxy(startX + 15, startY + 4);
                pass = GetPassword();
                bool validLogin = false;
                ReadFromFile();
                for (auto acc : listacc) {
                    if (user == acc.username && pass == acc.password) {
                        gotoxy(startX + 12, startY + 6);
                        cout << "Login successful!";
                        _getch();
                        system("cls");
                        Login(user, pass);
                        validLogin = true;
                        break;
                    }
                }
                if (!validLogin) {
                    gotoxy(startX + 5, startY + 6);
                    cout << "Invalid username or password!";
                    _getch();
                    system("cls");
                    continue; // Redraw the login form
                }
            } else if (selectedOption == 1) {
                system("cls");
                Welcome();
                return;
            }
        }
    }
}

void Accounts::Welcome() 
{
    const int boxWidth = 40;
    const int boxHeight = 8;
    const int boxX = 35;
    const int boxY = 5;
    int selectedValue;
    drawBox(boxX, boxY, boxWidth, boxHeight);
    int selectedOption = 0; // 0: Sign In, 1: Sign Up
    bool isSelected[2] = { true, false }; // To track the selected button
    while (true) {
    	gotoxy(boxX + 11, boxY + 1);
    	cout << "HE THONG BAI DO XE";
        drawButton(boxX + 14, boxY + 3, "Sign In", isSelected[0]);
        drawButton(boxX + 14, boxY + 5, "Sign Up", isSelected[1]);
        // Capture key press
        char key = _getch(); 
        if (key == 72) { // Up arrow key
            isSelected[selectedOption] = false; // Deselect
            selectedOption = (selectedOption == 0) ? 1 : 0; // Switch to the upper option
            isSelected[selectedOption] = true; // Select again
        } else if (key == 80) { // Down arrow key
            isSelected[selectedOption] = false; // Deselect
            selectedOption = (selectedOption == 1) ? 0 : 1; // Switch to the lower option
            isSelected[selectedOption] = true; // Select again
        } else if (key == 13) { // Enter key
            selectedValue = (selectedOption == 0) ? 1 : 2; // Assign value to variable
            break; 
        }
    }
    if(selectedValue == 1){
    	system("cls");loginForm();
	}
	else if (selectedValue == 2) {
    system("cls");
    int formWidth = 50;
    int formHeight = 17;
    int startX = 30;
    int startY = 3;
    int selectedOption = 0; // 0: Sign Up, 1: Back
    bool isSelected[2] = { true, false }; // To track the selected option
    here:
    string user, pass, name, phone, mail;
    while (true) {
        drawBox(startX, startY, formWidth, formHeight); 
        gotoxy(startX + 15, startY + 1);
        cout << "------ SIGN UP ------";
        gotoxy(startX + 5, startY + 3);
        cout << "Username: ";
        gotoxy(startX + 5, startY + 5);
        cout << "Password: ";
        gotoxy(startX + 5, startY + 7);
        cout << "Name    : ";
        gotoxy(startX + 5, startY + 9);
        cout << "Phone   : ";
        gotoxy(startX + 5, startY + 11);
        cout << "Mail    : ";
        drawButton(startX + 19, startY + 13, "Sign Up", isSelected[0]);
        drawButton(startX + 19, startY + 15, "Back", isSelected[1]);
        // Capture key press
        char key = _getch();
        if (key == 72) { // Up arrow key
            isSelected[selectedOption] = false; // Deselect
            selectedOption = (selectedOption == 0) ? 1 : 0; // Toggle selection
            isSelected[selectedOption] = true; // Select again
        } else if (key == 80) { // Down arrow key
            isSelected[selectedOption] = false; // Deselect
            selectedOption = (selectedOption == 1) ? 0 : 1; // Toggle selection
            isSelected[selectedOption] = true; // Select again
        } else if (key == 13) {
            if (selectedOption == 0) {
                gotoxy(startX + 15, startY + 3);
                getline(cin, user);
                Accounts::ReadFromFile();
                for(auto acc : listacc){
                	if(acc.username == user) {
					gotoxy(startX + 15, startY + 3);cout << "Username already used!!"<<endl;_getch();system("cls");goto here;}
				}
                gotoxy(startX + 15, startY + 5);
                getline(cin, pass);
                gotoxy(startX + 15, startY + 7);
                getline(cin, name);
                gotoxy(startX + 15, startY + 9);
                getline(cin, phone);
                gotoxy(startX + 15, startY + 11);
                getline(cin, mail);
                // Display success message
                gotoxy(startX + 15, startY + 13);
                cout << "Sign up success!!";
                _getch();
                system("cls");
                ofstream file("Accounts.txt", ios::app);
                file << user << ";" << pass << ";" << "0" << endl;
                file.close();
                ofstream fileown("Owners.txt", ios::app);
                fileown << user << ";" << name << ";" << phone << ";" << mail << endl;
                fileown.close();
                Welcome();
                return;
            } else if (selectedOption == 1) {
                system("cls");
                Welcome();
                return;
            }
        }
    }
}

}

void SplitDate(const string& date, int& day, int& month, int& year) {
    char delimiter = '-';
    stringstream ss(date);
    string token;
    
    try {
        if (getline(ss, token, delimiter)) {
            day = stoi(token);
        }
        if (getline(ss, token, delimiter)) {
            month = stoi(token);
        }
        if (getline(ss, token, delimiter)) {
            year = stoi(token);
        }
    } catch (const invalid_argument& e) {
        cout << "L?i: Ngày tháng không h?p l? trong d? li?u '" << date << "'" << endl;
        day = month = year = 0; // Ð?t giá tr? m?c d?nh d? tránh l?i ti?p theo
    }
}
void Accounts::AdminInterface(string user)
{
	Registrations rg;Owners owner;Accounts acc;
	const int boxWidth = 43;
    const int boxHeight = 16;
    const int boxX = 30;
    const int boxY = 5;
    int selectedOption = 1; // Track the selected option
    bool isSelected[7] = { false,true,false, false, false, false,false };
    while (true) {
        drawBox(boxX, boxY, boxWidth, boxHeight);
        gotoxy(boxX + 2, boxY + 1);
        cout << "----------- QUAN LI BAI DO XE ---------";
        drawButton(boxX + 12, boxY + 3,  "1. Xem danh sach", isSelected[1]);
        drawButton(boxX + 12, boxY + 5,  "2. Chinh sua", isSelected[2]);
        drawButton(boxX + 12, boxY + 7,  "3. Cap nhat bai do", isSelected[3]);
        drawButton(boxX + 12, boxY + 9, "4. Thong ke", isSelected[4]);
        drawButton(boxX + 12, boxY + 11, "5. Dang xuat", isSelected[5]);
        drawButton(boxX + 12, boxY + 13, "6. Thoat", isSelected[6]);
        char key = _getch();
        if (key == 72) { // Up arrow key
            isSelected[selectedOption] = false; // Deselect current option
            selectedOption = (selectedOption == 1) ? 7 : selectedOption - 1; // Move up
            isSelected[selectedOption] = true; // Select the new option
        } else if (key == 80) { // Down arrow key
            isSelected[selectedOption] = false; // Deselect current option
            selectedOption = (selectedOption == 7) ? 1 : selectedOption + 1; // Move down
            isSelected[selectedOption] = true; // Select the new option
        } else if (key == 13) { // Enter key
            switch(selectedOption){
				case 1:{
					system("cls");
					const int boxWidth = 43;
    				const int boxHeight = 16;
    				const int boxX = 30;
    				const int boxY = 5;
    				int selectedOption = 1; // Track the selected option
    				bool isSelected[7] = { false,true,false, false, false, false,false };
    				while(true){
    					drawBox(boxX,boxY,boxWidth,boxHeight);
    					gotoxy(boxX+2,boxY+1);
    					cout << "---------------- XEM ------------------";
    					drawButton(boxX + 12, boxY + 3,  "1. Accounts", isSelected[1]);
    					drawButton(boxX + 12, boxY + 5,  "2. Owners", isSelected[2]);
    					drawButton(boxX + 12, boxY + 7,  "3. Parking Lots", isSelected[3]);
    					drawButton(boxX + 12, boxY + 9,  "4. Vehicles", isSelected[4]);
    					drawButton(boxX + 12, boxY + 11,  "5. Registrations", isSelected[5]);
    					drawButton(boxX + 12, boxY + 13,  "6. Back", isSelected[6]);
    					char key = _getch();
    					if(key == 72){
    						isSelected[selectedOption] = false;
    						selectedOption = (selectedOption == 1) ? 6 : selectedOption - 1;
    						isSelected[selectedOption] = true;
						}
						else if(key == 80){
							isSelected[selectedOption] = false;
							selectedOption = (selectedOption == 6) ? 1 : selectedOption + 1;
							isSelected[selectedOption] = true;
						}
						else if(key == 13){
							switch(selectedOption){
								case 1:{
									system("cls");
									Show();_getch();system("cls");
									break;
								}
								case 2:{
									system("cls");owner.ReadFromFile();
									owner.Show(user,1);_getch();system("cls");
									break;
								}
								case 3:{
									system("cls");ParkingLots pl;pl.ReadFromFile();
									pl.Show(4);_getch();system("cls");
									break;
								}
								case 4:{
									system("cls");Vehicles veh;veh.ReadFromFile();
									veh.Show();_getch();system("cls");
									break;
								}
								case 5:{
									system("cls");
									rg.Show(user,1);_getch();system("cls");
									break;
								}
								case 6:{
									system("cls");
									AdminInterface(user);
									break;
								}
							}
						}
					}
					break;
				}
				case 2:{
					system("cls");
					bool found = false;
					string option;cout << "Nhap ID can chinh sua : ";getline(cin,option);
					Owners::ReadFromFile();
					for(auto own : listown){
						if(own.GetOwnerID() == option){
							found = true;
							Edit(option,1);
							break;
						}
					}
					if(!found){
						cout << "Cannot find ID!"<<endl;_getch();system("cls");
					}
					break;
				}
				case 3:{
    				system("cls");
    				bool found = false;
    				time_t currentTime = time(nullptr);
					tm *timeInfo = localtime(&currentTime);
					int dn,mn,yn;
					dn=timeInfo->tm_mday ;
   					mn =(timeInfo->tm_mon + 1) ;
       				yn= timeInfo->tm_year + 1900; 
					cout << "Nhap LotID can cap nhat : ";string option;getline(cin,option);
					for(auto &pl:listpark){
						if(pl.GetLotID()==option){
							found = true;
							int de,me,ye;
							SplitDate(pl.GetEndTime(),de,me,ye);
							if((yn < ye) || (yn == ye && mn < me) || (yn == ye && mn == me && dn < de)){
								cout << "Bai do chua het han!"<<endl;_getch();system("cls");break;
							}
							else{
							cout << "Cap nhat LotID thanh cong!"<<endl;_getch();system("cls");
							pl.SetStatus(0);pl.SetEndTimeNull();
							break;
							}
						}
					}
					if(!found) {cout << "Khong tim thay LotID can tim!"<<endl;_getch();system("cls");}
					else{
						ofstream filepl("ParkingLots.txt",ios::out);
						for(auto &park:listpark){
							filepl << park.GetLotID() << ";" << park.GetArea() << ";" << park.GetStatus() <<";"<< park.GetEndTime() <<endl;
						}
					}
					break;
				}
				case 4:{
					system("cls");
					int d1=0,w1=0,m1=0,d2=0,w2=0,m2=0,d3=0,w3=0,m3=0,d4=0,w4=0,m4=0,d5=0,w5=0,m5=0,d6=0,w6=0,m6=0,d7=0,w7=0,m7=0,d8=0,w8=0,m8=0,d9=0,w9=0,m9=0,d10=0,w10=0,m10=0,d11=0,w11=0,m11=0,d12=0,w12=0,m12=0;
					int sum1=0,sum2=0,sum3=0,sum4=0,sum5=0,sum6=0,sum7=0,sum8=0,sum9=0,sum10=0,sum11=0,sum12=0;
					for(auto rg:listregis){
						int month = GetMonth(rg.GetStartTime());
						switch(month){
							//THANG 1
							case 1:{
								if(rg.GetTicketType()==1){d1++;sum1+=rg.GetTicketPrice();}
								else if(rg.GetTicketType()==2){w1++;sum1+=rg.GetTicketPrice();}
								else if(rg.GetTicketType()==3){m1++;sum1+=rg.GetTicketPrice();}
								break;
							}
							case 2:{
								if(rg.GetTicketType()==1){d2++;sum2+=rg.GetTicketPrice();}
								else if(rg.GetTicketType()==2){w2++;sum2+=rg.GetTicketPrice();}
								else if(rg.GetTicketType()==3){m2++;sum2+=rg.GetTicketPrice();}
								break;
							}
							case 3:{
								if(rg.GetTicketType()==1){d3++;sum3+=rg.GetTicketPrice();}
								else if(rg.GetTicketType()==2){w3++;sum3+=rg.GetTicketPrice();}
								else if(rg.GetTicketType()==3){m3++;sum3+=rg.GetTicketPrice();}
								break;
							}
							case 4:{
  								if(rg.GetTicketType()==1){d4++;sum4+=rg.GetTicketPrice();}
  								else if(rg.GetTicketType()==2){w4++;sum4+=rg.GetTicketPrice();}
  								else if(rg.GetTicketType()==3){m4++;sum4+=rg.GetTicketPrice();}
  								break;
							}
							case 5:{
  								if(rg.GetTicketType()==1){d5++;sum5+=rg.GetTicketPrice();}
  								else if(rg.GetTicketType()==2){w5++;sum5+=rg.GetTicketPrice();}
  								else if(rg.GetTicketType()==3){m5++;sum5+=rg.GetTicketPrice();}
  								break;
							}
							case 6:{
  								if(rg.GetTicketType()==1) {d6++;sum6+=rg.GetTicketPrice();}
  								else if(rg.GetTicketType()==2) {w6++;sum6+=rg.GetTicketPrice();}
  								else if(rg.GetTicketType()==3) {m6++;sum6+=rg.GetTicketPrice();}
  								break;
							}
							case 7:{
  								if(rg.GetTicketType()==1) {d7++;sum7+=rg.GetTicketPrice();}
  								else if(rg.GetTicketType()==2) {w7++;sum7+=rg.GetTicketPrice();}
  								else if(rg.GetTicketType()==3) {m7++;sum7+=rg.GetTicketPrice();}
  								break;
							}
							case 8:{
  								if(rg.GetTicketType()==1) {d8++;sum8+=rg.GetTicketPrice();}
  								else if(rg.GetTicketType()==2) {w8++;sum8+=rg.GetTicketPrice();}
  								else if(rg.GetTicketType()==3) {m8++;sum8+=rg.GetTicketPrice();}
  								break;
							}
							case 9:{
  								if(rg.GetTicketType()==1) {d9++;sum9+=rg.GetTicketPrice();}
  								else if(rg.GetTicketType()==2) {w9++;sum9+=rg.GetTicketPrice();}
  								else if(rg.GetTicketType()==3) {m9++;sum9+=rg.GetTicketPrice();}
  								break;
							}
							case 10:{
  								if(rg.GetTicketType()==1) {d10++;sum10+=rg.GetTicketPrice();}
  								else if(rg.GetTicketType()==2) {w10++;sum10+=rg.GetTicketPrice();}
  								else if(rg.GetTicketType()==3) {m10++;sum10+=rg.GetTicketPrice();}
  								break;
							}
							case 11:{
  								if(rg.GetTicketType()==1) {d11++;sum11+=rg.GetTicketPrice();}
  								else if(rg.GetTicketType()==2) {w11++;sum11+=rg.GetTicketPrice();}
  								else if(rg.GetTicketType()==3) {m11++;sum11+=rg.GetTicketPrice();}
  								break;
							}
							case 12:{
  								if(rg.GetTicketType()==1) {d12++;sum12+=rg.GetTicketPrice();}
  								else if(rg.GetTicketType()==2) {w12++;sum12+=rg.GetTicketPrice();}
  								else if(rg.GetTicketType()==3){m12++;sum12+=rg.GetTicketPrice();}
  								break;
							}
						}
					}
					int baseX=10,baseY=3; //Toa do bat dau cua bang
					int rows=3,cols=4;
					int cellWidth=20,cellHeight=8;
					int x,y;
					//THANG 1
					drawTable(baseX,baseY,rows,cols);
					getpos(baseX,baseY,cellWidth,cellHeight,0,0,x,y);
					drawContent(x+6,y+1,"Thang 1");
					drawContent(x+1,y+2,"Tong so ve: ");
					drawContent(x+1,y+3,"DAILY     : ");gotoxy(x+13,y+3);cout<<d1;
					drawContent(x+1,y+4,"WEEKLY    : ");gotoxy(x+13,y+4);cout<<w1;
					drawContent(x+1,y+5,"MONTHLY   : ");gotoxy(x+13,y+5);cout<<m1;
					drawContent(x+1,y+6,"Doanh thu : ");gotoxy(x+13,y+6);cout<<sum1;
					//THANG 2
					drawTable(baseX,baseY,rows,cols);
					getpos(baseX,baseY,cellWidth,cellHeight,0,1,x,y);
					drawContent(x+6,y+1,"Thang 2");
					drawContent(x+1,y+2,"Tong so ve: ");
					drawContent(x+1,y+3,"DAILY     : ");gotoxy(x+13,y+3);cout <<d2;
					drawContent(x+1,y+4,"WEEKLY    : ");gotoxy(x+13,y+4);cout <<w2;
					drawContent(x+1,y+5,"MONTHLY   : ");gotoxy(x+13,y+5);cout <<m2;
					drawContent(x+1,y+6,"Doanh thu : ");gotoxy(x+13,y+6);cout<<sum2;
					//THANG 3
					drawTable(baseX,baseY,rows,cols);
					getpos(baseX,baseY,cellWidth,cellHeight,0,2,x,y);
					drawContent(x+6,y+1,"Thang 3");
					drawContent(x+1,y+2,"Tong so ve: ");
					drawContent(x+1,y+3,"DAILY     : ");gotoxy(x+13,y+3);cout <<d3;
					drawContent(x+1,y+4,"WEEKLY    : ");gotoxy(x+13,y+4);cout <<w3;
					drawContent(x+1,y+5,"MONTHLY   : ");gotoxy(x+13,y+5);cout <<m3;
					drawContent(x+1,y+6,"Doanh thu : ");gotoxy(x+13,y+6);cout<<sum3;
					//THANG 4
					drawTable(baseX,baseY,rows,cols);
					getpos(baseX,baseY,cellWidth,cellHeight,0,3,x,y);
					drawContent(x+6,y+1,"Thang 4");
					drawContent(x+1,y+2,"Tong so ve: ");
					drawContent(x+1,y+3,"DAILY     : ");gotoxy(x+13,y+3);cout <<d4;
					drawContent(x+1,y+4,"WEEKLY    : ");gotoxy(x+13,y+4);cout <<w4;
					drawContent(x+1,y+5,"MONTHLY   : ");gotoxy(x+13,y+5);cout <<m4;
					drawContent(x+1,y+6,"Doanh thu : ");gotoxy(x+13,y+6);cout<<sum4;
					//THANG 5
					drawTable(baseX,baseY,rows,cols);
					getpos(baseX,baseY,cellWidth,cellHeight,1,0,x,y);
					drawContent(x+6,y+1,"Thang 5");
					drawContent(x+1,y+2,"Tong so ve: ");
					drawContent(x+1,y+3,"DAILY     : ");gotoxy(x+13,y+3);cout <<d5;
					drawContent(x+1,y+4,"WEEKLY    : ");gotoxy(x+13,y+4);cout <<w5;
					drawContent(x+1,y+5,"MONTHLY   : ");gotoxy(x+13,y+5);cout <<m5;
					drawContent(x+1,y+6,"Doanh thu : ");gotoxy(x+13,y+6);cout<<sum5;
					//THANG 6
					drawTable(baseX,baseY,rows,cols);
					getpos(baseX,baseY,cellWidth,cellHeight,1,1,x,y);
					drawContent(x+6,y+1,"Thang 6");
					drawContent(x+1,y+2,"Tong so ve: ");
					drawContent(x+1,y+3,"DAILY     : ");gotoxy(x+13,y+3);cout <<d6;
					drawContent(x+1,y+4,"WEEKLY    : ");gotoxy(x+13,y+4);cout <<w6;
					drawContent(x+1,y+5,"MONTHLY   : ");gotoxy(x+13,y+5);cout <<m6;
					drawContent(x+1,y+6,"Doanh thu : ");gotoxy(x+13,y+6);cout<<sum6;
					//THANG 7
					drawTable(baseX,baseY,rows,cols);
					getpos(baseX,baseY,cellWidth,cellHeight,1,2,x,y);
					drawContent(x+6,y+1,"Thang 7");
					drawContent(x+1,y+2,"Tong so ve: ");
					drawContent(x+1,y+3,"DAILY     : ");gotoxy(x+13,y+3);cout <<d7;
					drawContent(x+1,y+4,"WEEKLY    : ");gotoxy(x+13,y+4);cout <<w7;
					drawContent(x+1,y+5,"MONTHLY   : ");gotoxy(x+13,y+5);cout <<m7;
					drawContent(x+1,y+6,"Doanh thu : ");gotoxy(x+13,y+6);cout<<sum7;
					//THANG 8
					drawTable(baseX,baseY,rows,cols);
					getpos(baseX,baseY,cellWidth,cellHeight,1,3,x,y);
					drawContent(x+6,y+1,"Thang 8");
					drawContent(x+1,y+2,"Tong so ve: ");
					drawContent(x+1,y+3,"DAILY     : ");gotoxy(x+13,y+3);cout <<d8;
					drawContent(x+1,y+4,"WEEKLY    : ");gotoxy(x+13,y+4);cout <<w8;
					drawContent(x+1,y+5,"MONTHLY   : ");gotoxy(x+13,y+5);cout <<m8;
					drawContent(x+1,y+6,"Doanh thu : ");gotoxy(x+13,y+6);cout<<sum8;
					//THANG 9
					drawTable(baseX,baseY,rows,cols);
					getpos(baseX,baseY,cellWidth,cellHeight,2,0,x,y);
					drawContent(x+6,y+1,"Thang 9");
					drawContent(x+1,y+2,"Tong so ve: ");
					drawContent(x+1,y+3,"DAILY     : ");gotoxy(x+13,y+3);cout <<d9;
					drawContent(x+1,y+4,"WEEKLY    : ");gotoxy(x+13,y+4);cout <<w9;
					drawContent(x+1,y+5,"MONTHLY   : ");gotoxy(x+13,y+5);cout <<m9;
					drawContent(x+1,y+6,"Doanh thu : ");gotoxy(x+13,y+6);cout<<sum9;
					//THANG 10
					drawTable(baseX,baseY,rows,cols);
					getpos(baseX,baseY,cellWidth,cellHeight,2,1,x,y);
					drawContent(x+6,y+1,"Thang 10");
					drawContent(x+1,y+2,"Tong so ve: ");
					drawContent(x+1,y+3,"DAILY     : ");gotoxy(x+13,y+3);cout <<d10;
					drawContent(x+1,y+4,"WEEKLY    : ");gotoxy(x+13,y+4);cout <<w10;
					drawContent(x+1,y+5,"MONTHLY   : ");gotoxy(x+13,y+5);cout <<m10;
					drawContent(x+1,y+6,"Doanh thu : ");gotoxy(x+13,y+6);cout<<sum10;
					//THANG 11
					drawTable(baseX,baseY,rows,cols);
					getpos(baseX,baseY,cellWidth,cellHeight,2,2,x,y);
					drawContent(x+6,y+1,"Thang 11");
					drawContent(x+1,y+2,"Tong so ve: ");
					drawContent(x+1,y+3,"DAILY     : ");gotoxy(x+13,y+3);cout <<d11;
					drawContent(x+1,y+4,"WEEKLY    : ");gotoxy(x+13,y+4);cout <<w11;
					drawContent(x+1,y+5,"MONTHLY   : ");gotoxy(x+13,y+5);cout <<m11;
					drawContent(x+1,y+6,"Doanh thu : ");gotoxy(x+13,y+6);cout<<sum11;
					//THANG 12
					drawTable(baseX,baseY,rows,cols);
					getpos(baseX,baseY,cellWidth,cellHeight,2,3,x,y);
					drawContent(x+6,y+1,"Thang 12");
					drawContent(x+1,y+2,"Tong so ve: ");
					drawContent(x+1,y+3,"DAILY     : ");gotoxy(x+13,y+3);cout <<d12;
					drawContent(x+1,y+4,"WEEKLY    : ");gotoxy(x+13,y+4);cout <<w12;
					drawContent(x+1,y+5,"MONTHLY   : ");gotoxy(x+13,y+5);cout <<m12;
					drawContent(x+1,y+6,"Doanh thu : ");gotoxy(x+13,y+6);cout<<sum12;
					time_t currentTime = time(nullptr);
					tm *timeInfo = localtime(&currentTime);
					int counthh = 0;
					int dn=timeInfo->tm_mday ;
   					int mn =(timeInfo->tm_mon + 1);
       				int yn= timeInfo->tm_year + 1900; 
					cout << "\n\n\n\n--------------- THONG KE -------------------"<<endl;
					cout << "Danh sach cac bai do het han:"<<endl;
				  	for (auto pl : listpark) {
						if(pl.GetStatus()==1){
        					string endTime = pl.GetEndTime();
            				int de, me, ye;
            				SplitDate(endTime, de, me, ye);
            			if ((yn > ye) || (yn == ye && mn > me) || (yn == ye && mn == me && dn > de)) {
                			counthh++;
                			cout <<pl.GetArea() << " : "<< pl.GetLotID() << endl;
            			}
        			}
        		}
    				cout << "Co " << counthh << " bai do het han" << endl;
					_getch();system("cls");
					break;
				}
				case 5:{
					system("cls");Welcome();
					break;
				}
				case 6:{
					exit(0);
					break;
				}
			}
		}
	}
}




void Accounts::UserInterface(string user) {
	ParkingLots pl;Vehicles veh;Registrations rg;Owners owner;
    // Define the dimensions and position of the user interface
    const int boxWidth = 43;
    const int boxHeight = 12;
    const int boxX = 30;
    const int boxY = 5;
    int selectedOption = 1; // Track the selected option
    bool isSelected[6] = { false,true,false, false, false, false }; // Track which button is selected
    while (true) {
        drawBox(boxX, boxY, boxWidth, boxHeight);
        gotoxy(boxX + 3, boxY + 1);
        cout << "-------------- MENU --------------";
        drawButton(boxX + 13, boxY + 2, "1. Dat ve", isSelected[1]);
        drawButton(boxX + 13, boxY + 4, "2. Xem ve", isSelected[2]);
        drawButton(boxX + 13, boxY + 6, "3. Chinh sua", isSelected[3]);
        drawButton(boxX + 13, boxY + 8, "4. Dang xuat", isSelected[4]);
        drawButton(boxX + 13, boxY + 10, "5. Thoat", isSelected[5]);
        gotoxy(boxX + 1, boxY + 9);
        // Capture key press
        char key = _getch();
        if (key == 72) { // Up arrow key
            isSelected[selectedOption] = false; // Deselect current option
            selectedOption = (selectedOption == 1) ? 5 : selectedOption - 1; // Move up
            isSelected[selectedOption] = true; // Select the new option
        } else if (key == 80) { // Down arrow key
            isSelected[selectedOption] = false; // Deselect current option
            selectedOption = (selectedOption == 5) ? 1 : selectedOption + 1; // Move down
            isSelected[selectedOption] = true; // Select the new option
        } else if (key == 13) { // Enter key
            // Handle the selected option
            switch (selectedOption) {
                case 1:{
                	system("cls");
                    const int boxWidth = 43;
    				const int boxHeight = 12;
    				const int boxX = 30;
    				const int boxY = 5;
    				int selectedOption = 1; // Track the selected option
    				bool isSelected[4] = { false,true, false, false }; // Track which button is selected
    				while (true) {
        			drawBox(boxX, boxY, boxWidth, boxHeight);
        			gotoxy(boxX + 3, boxY + 1);
        			cout << "-------------- ORDER --------------";
        			drawButton(boxX + 14, boxY + 3, "1. DAILY", isSelected[1]);
        			drawButton(boxX + 14, boxY + 5, "2. WEEKLY", isSelected[2]);
        			drawButton(boxX + 14, boxY + 7, "3. MONTHLY", isSelected[3]);
        			drawButton(boxX + 17, boxY + 9, "BACK",isSelected[4]);
        			// Capture key press
        			char key = _getch();
        			if (key == 72) { // Up arrow key
            			isSelected[selectedOption] = false; // Deselect current option
            			selectedOption = (selectedOption == 1) ? 4 : selectedOption - 1; // Move up
            			isSelected[selectedOption] = true; // Select the new option
        			} else if (key == 80) { // Down arrow key
            			isSelected[selectedOption] = false; // Deselect current option
            			selectedOption = (selectedOption == 4) ? 1 : selectedOption + 1; // Move down
            			isSelected[selectedOption] = true; // Select the new option
        			} else if (key == 13) { // Enter key
        				system("cls");
        				if(selectedOption == 4) UserInterface(user);
        				else Register(pl,veh,rg,user,selectedOption);
        				}
   					}
   				}
                    break;
                case 2:
                	system("cls");
                    rg.Show(user,0);
                    break;
                case 3:
                	system("cls");
                    Edit(user,0);
                    break;
                case 4:
                	system("cls");
                    Welcome();
                    break;
                case 5:
                    exit(0); // Exit the program
            }
            _getch(); // Wait for a key press before continuing
            system("cls"); // Clear the screen
        }
    }
}
string CalculationEndTime(int day, int month, int year, int sumday) {
    tm timeInfo = {};
    timeInfo.tm_mday = day;
    timeInfo.tm_mon = month - 1; 
    timeInfo.tm_year = year - 1900; 
    time_t startTime = mktime(&timeInfo);
    const int secondsInDay = 86400; 
    startTime += sumday * secondsInDay;
    tm *endTime = localtime(&startTime);
    stringstream result;
    result << setfill('0') << setw(2) << endTime->tm_mday << "-"
           << setfill('0') << setw(2) << (endTime->tm_mon + 1) << "-"
           << (endTime->tm_year + 1900);
    return result.str();
}
void Accounts::Register(ParkingLots pl,Vehicles veh,Registrations rg,string user,int check){
	string pickLotID,lp,md,br;bool find=false;
	char AreaTemp = ((check == 1) ? 'C' : ((check == 2) ? 'B' : 'A'));
	cout << "---------------------"<<endl;
	pl.Show(check);							
	cout << "Nhap LotID can dat : ";getline(cin,pickLotID);
	for(auto &park : listpark){
		if(park.GetLotID() == pickLotID && park.GetStatus()==0 && park.GetArea()==AreaTemp){
			int daytemp,price;
			if(check == 1) daytemp = 1;
			else if (check==2) daytemp=7;
			else if(check ==3) daytemp =30;
			time_t currentTime = time(nullptr);
			tm *timeInfo = localtime(&currentTime);
			find = true;
			park.SetStatus(1);
			park.SetEndTime(CalculationEndTime(timeInfo->tm_mday,(timeInfo->tm_mon + 1),timeInfo->tm_year + 1900,daytemp));
			cout << "Dang ki LotID " << pickLotID << " thanh cong!!"<<endl; cout << "Press any key to continue";_getch();system("cls");
			ofstream filepl("ParkingLots.txt",ios::out);
			ofstream fileveh("Vehicles.txt",ios::app);
			ofstream filerg("Registrations.txt",ios::app);
			for(auto &park:listpark){
				filepl << park.GetLotID() << ";" << park.GetArea() << ";" << park.GetStatus() <<";"<< park.GetEndTime() <<endl;
			}
			filepl.close();
			cout << "---- Vehice register ------"<<endl;
			cout << "Enter LicensePlate :" ;getline(cin,lp);
			cout << "Enter Brand        :" ;getline(cin,br);
			cout << "Enter Model        :" ;getline(cin,md);
			fileveh << user << ";" << lp << ";" << br << ";" << md << endl;
			cout << "Vehicle Register success!!"<<endl;cout << "Press any key to continue";_getch();system("cls");
			fileveh.close();
			time_t CurrentTime = time(nullptr);
			tm *TimeInfo = localtime(&CurrentTime);
			price = (check == 1) ? DAILY : ((check == 2) ? WEEKLY : MONTHLY);
			filerg << AreaTemp << pickLotID << ";" << user << ";" << lp << ";" << pickLotID << ";" << check << ";" << price << ";"
       			<< setfill('0') << setw(2) << TimeInfo->tm_mday << "-" 
      			<< setfill('0') << setw(2) << (TimeInfo->tm_mon + 1) << "-" 
       			<< timeInfo->tm_year + 1900 << endl;
			break;
	}
		else if(park.GetLotID() == pickLotID && park.GetStatus()==1 && park.GetArea()==AreaTemp){
			find=true;
			cout<<"\nLotID already ordered!!!"<<endl;
			cout<<"Press any key to continue";_getch();system("cls");break;
		}
		else if(park.GetLotID()==pickLotID && park.GetArea()!=AreaTemp){
			find=true;
			cout<<"\nPlease select LotID avaiable for Area : " << AreaTemp<<endl;
			cout<<"Press any key to continue";_getch();system("cls");break;
		}
	}
		if(!find){
		cout<<"\nLotID not in list!!"<<endl;
		cout<<"Press any key to continue";_getch();system("cls");}
}


void Accounts::Edit(string user,bool role)
{
	const int boxWidth = 55;
    const int boxHeight = 14;
    const int boxX = 30;
    const int boxY = 5;
    int selectedOption = 1; // Track the selected option
    bool isSelected[6] = { false,true, false, false,false,false }; // Track which button is selected
    while (true) {
        drawBox(boxX, boxY, boxWidth, boxHeight);
    	gotoxy(boxX + 3, boxY + 1);
        cout << "---------- SELECT INFORMATION TO UPDATE ---------";
        drawButton(boxX + 1, boxY + 3, "1. NAME", isSelected[1]);gotoxy(boxX + 25, boxY + 3);ShowInclude(user,1);
        drawButton(boxX + 1, boxY + 5, "2. PHONE", isSelected[2]);gotoxy(boxX + 25, boxY + 5);ShowInclude(user,2);
        drawButton(boxX + 1, boxY + 7, "3. EMAIL", isSelected[3]);gotoxy(boxX + 25, boxY + 7);ShowInclude(user,3);
        drawButton(boxX + 1, boxY + 9, "4. CHANGE PASSWORD",isSelected[4]);
        drawButton(boxX + 1, boxY + 11,"5. BACK",isSelected[5]);
        // Capture key press
        char key = _getch();
        if (key == 72) { // Up arrow key
            isSelected[selectedOption] = false; // Deselect current option
            selectedOption = (selectedOption == 1) ? 5 : selectedOption - 1; // Move up
            isSelected[selectedOption] = true; // Select the new option
       }else if (key == 80) { // Down arrow key
            isSelected[selectedOption] = false; // Deselect current option
            selectedOption = (selectedOption == 5) ? 1 : selectedOption + 1; // Move down
            isSelected[selectedOption] = true; // Select the new option
        }else if (key == 13) { // Enter key
        	system("cls");
        	if(selectedOption == 5){
        		if(role == 1) AdminInterface(user);
        		else
        		UserInterface(user);
			}
        	else{
        		string name,phone,email,newpass;
        		switch(selectedOption){
        case 1:{
			cout << "Enter new Name : "; getline(cin,name);
			for(auto &own : listown){
				if(own.GetOwnerID() == user) own.SetName(name);
			}
			cout << "Update Name Success!!"<<endl;_getch();system("cls");
			break;
		}
		case 2:{
			cout << "Enter new Phone : "; getline(cin,phone);
			for(auto &own : listown){
				if(own.GetOwnerID() == user) own.SetPhone(phone);	
			}
			cout << "Update Phone Success!!"<<endl;_getch();system("cls");
			break;
		}
		case 3:{
			cout << "Enter new email : "; getline(cin,email);
			for(auto &own : listown){
				if(own.GetOwnerID() == user) own.SetEmail(email);
			}
			cout << "Update Email Success!!"<<endl;_getch();system("cls");
			break;
		}
		case 4:{
			Accounts::ReadFromFile();
			string passtemp,oldpass;
			cout << "Enter old password : ";getline(cin,oldpass);
			for(auto acc: listacc){
				if(acc.username == user) passtemp = acc.password;
			}
			if(oldpass != passtemp){
				cout << "Wrong Password!!!"<<endl;cout << "Press any key to continue";_getch();system("cls");
			}
			else{
				cout << "Enter new password : ";getline(cin,newpass);
				for(auto &acc : listacc){
					if(acc.username == user){
						acc.SetPassword(newpass);break;
					}
				}
				ofstream fileacc("Accounts.txt",ios::out);
				for(auto acc : listacc){
					fileacc << acc.username << ";" << acc.password << ";" << acc.role << endl;
				}
				fileacc.close();
				cout << "Update Password Success!!"<<endl;
			}
			break;
		}
	}
			ofstream file("Owners.txt",ios::out);
			for(auto own:listown){
				file << own.GetOwnerID() <<";"<<own.GetName() << ";" << own.GetPhone() << ";" << own.GetEmail() << endl;
			}
			file.close();
		}
   	}
  }
}
