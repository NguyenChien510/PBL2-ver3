#include "Accounts.h"
#include <fstream>
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
			while(1) AdminInterface(user,pass);
		}
		else if(acc.username == user && acc.password == pass && acc.role == 0)   //USER
		{
			while(1) UserInterface(user,pass);
		}
	}
}
}
string GetPassword() {
    string pass = "";
    char ch;
    while ((ch = _getch()) != '\r') { // '\r' l� ki tu Enter
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

void Accounts::Welcome() {
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

void Accounts::AdminInterface(string user,string pass)
{
	ParkingLots pl;Vehicles veh;Registrations rg;Owners owner;Accounts acc;
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
        drawButton(boxX + 12, boxY + 3,  "1. Xem Danh Sach", isSelected[1]);
        drawButton(boxX + 12, boxY + 5,  "2. Chinh sua", isSelected[2]);
        drawButton(boxX + 12, boxY + 7,  "3. Xoa", isSelected[3]);
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
									system("cls");pl.ReadFromFile();
									pl.Show(4);_getch();system("cls");
									break;
								}
								case 4:{
									system("cls");veh.ReadFromFile();
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
									AdminInterface(user,pass);
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
					for(auto own : listown){
						if(own.GetOwnerID() == option){
							found = true;
							Edit(option,GetPassWord(option),1);
							break;
						}
					}
					if(!found){
						cout << "Cannot find ID!"<<endl;system("cls");
					}
					break;
				}
				case 3:{
					break;
				}
				case 4:{
					
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




void Accounts::UserInterface(string user,string pass) {
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
        drawButton(boxX + 13, boxY + 3, "1. Dat ve", isSelected[1]);
        drawButton(boxX + 13, boxY + 4, "2. Xem ve", isSelected[2]);
        drawButton(boxX + 13, boxY + 5, "3. Chinh sua", isSelected[3]);
        drawButton(boxX + 13, boxY + 6, "4. Dang xuat", isSelected[4]);
        drawButton(boxX + 13, boxY + 7, "5. Thoat", isSelected[5]);
        gotoxy(boxX + 1, boxY + 9);
        cout << "LUU Y: Moi user chi dang ky toi da 3 ve!!";
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
        				if(selectedOption == 4) UserInterface(user,pass);
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
                    Edit(user,pass,0);
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

void Accounts::Register(ParkingLots pl,Vehicles veh,Registrations rg,string user,int check){
	string pickLotID,lp,md,br,cl;bool find=false;
	char AreaTemp = ((check == 1) ? 'C' : ((check == 2) ? 'B' : 'A'));
	cout << "---------------------"<<endl;
	pl.Show(check);							
	cout << "Nhap LotID can dat : ";getline(cin,pickLotID);
	for(auto &park : listpark){
		if(park.GetLotID() == pickLotID && park.GetStatus()==0 && park.GetArea()==AreaTemp){
			find = true;
			park.SetStatus(1);
			cout << "Dang ki LotID " << pickLotID << " thanh cong!!"<<endl; cout << "Press any key to continue";_getch();system("cls");
			ofstream filepl("ParkingLots.txt",ios::out);
			ofstream fileveh("Vehicles.txt",ios::app);
			ofstream filerg("Registrations.txt",ios::app);
			for(auto &park:listpark){
				filepl << park.GetLotID() << ";" << park.GetArea() << ";" << park.GetStatus() << endl;
			}
			filepl.close();
			cout << "---- Vehice register ------"<<endl;
			cout << "Enter LicensePlate :" ;getline(cin,lp);
			cout << "Enter Brand        :" ;getline(cin,br);
			cout << "Enter Model        :" ;getline(cin,md);
			cout << "Enter Color        :" ;getline(cin,cl);
			fileveh << user << ";" << lp << ";" << br << ";" << md << ";" << cl << endl;
			cout << "Vehicle Register success!!"<<endl;cout << "Press any key to continue";_getch();system("cls");
			fileveh.close();
			time_t currentTime = time(nullptr);
			tm *timeInfo = localtime(&currentTime);
			filerg << AreaTemp << pickLotID << ";" << user << ";" << lp << ";" << pickLotID << ";" << check << ";" 
       			<< setfill('0') << setw(2) << timeInfo->tm_hour << ":" 
       			<< setfill('0') << setw(2) << timeInfo->tm_min << " " 
       			<< setfill('0') << setw(2) << timeInfo->tm_mday << "-" 
      			<< setfill('0') << setw(2) << (timeInfo->tm_mon + 1) << "-" 
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


void Accounts::Edit(string user,string pass,bool role)
{
	here:
	Owners owner;
	owner.Show(user,0);
	const int boxWidth = 43;
    const int boxHeight = 14;
    const int boxX = 30;
    const int boxY = 5;
    int selectedOption = 1; // Track the selected option
    bool isSelected[6] = { false,true, false, false,false,false }; // Track which button is selected
    while (true) {
        drawBox(boxX, boxY, boxWidth, boxHeight);
    	gotoxy(boxX + 3, boxY + 1);
        cout << "---- SELECT INFORMATION TO UPDATE ----";
        drawButton(boxX + 15, boxY + 3, "1. NAME", isSelected[1]);
        drawButton(boxX + 15, boxY + 5, "2. PHONE", isSelected[2]);
        drawButton(boxX + 15, boxY + 7, "3. EMAIL", isSelected[3]);
        drawButton(boxX + 15, boxY + 9, "4. CHANGE PASSWORD",isSelected[4]);
        drawButton(boxX + 15, boxY + 11,"5. BACK",isSelected[5]);
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
        		if(role == 1) AdminInterface(user,pass);
        		else
        		UserInterface(user,pass);
			}
        	else{
        		string name,phone,email,oldpass,newpass;
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
			cout << "Enter old password : ";getline(cin,oldpass);
			if(oldpass != pass){
				cout << "Wrong Password!!!"<<endl;cout << "Press any key to continue";_getch();system("cls");goto here;
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
