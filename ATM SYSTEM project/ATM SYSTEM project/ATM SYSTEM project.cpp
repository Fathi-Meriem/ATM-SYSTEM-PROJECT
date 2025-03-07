#include <iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include<vector>
using namespace std;
string FileName = "Clients.txt";
void ShowATMMenu();
int ShowQuickDrawMenu();
void Login();
enum MenuATM {Quickdraw=1,Normaldraw=2,Deposit=3,CheckBalance=4,Logout=5};
void ShowLogin() {
    cout << "\n------------------------------------\n";
    cout << " \t Login Screen \t\t\n";
    cout << "------------------------------------\n";
}
struct stClient {
    string AccountNumber = "";
    string PinCode = "";
    string Name = "";
    string Phone = "";
    int AccountBalance = 0;
    bool MarkForDelete = false;
};
stClient Client;
vector <string> SplitString(string S1, string Delim = "#//#") {
    vector <string> vString;
    string sWord;
    short pos = 0;
    while ((pos = S1.find(Delim)) != string::npos) {
        sWord = S1.substr(0, pos);
        if (!sWord.empty()) {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());
    }
    if (!S1.empty()) {
        vString.push_back(S1);
    }
    return vString;
}
stClient ConvertLineToRecord(string S1) {
    stClient Client;

    vector <string> vString;
    vString = SplitString(S1);
    if (vString.size() >= 5) {  
        Client.AccountNumber = vString[0];
        Client.PinCode = vString[1];
        Client.Name = vString[2];
        Client.Phone = vString[3];
        Client.AccountBalance = stoi(vString[4]);  
    }
    else {
       
        cout << "Error: Malformed client record in file." << endl;
    }

    return Client;
}
string ConvertRecordToLine(stClient Client, string Delim = "#//#") {
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Delim;
    stClientRecord += Client.PinCode + Delim;
    stClientRecord += Client.Name + Delim;
    stClientRecord += Client.Phone + Delim;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}
vector <stClient> LoadClientsDataFromFile() {
    vector <stClient> vClients;
    stClient Client;
    fstream File;
    File.open(FileName, ios::in);
    if (File.is_open()) {
        string Line;
        while (getline(File, Line)) {
            Client = ConvertLineToRecord(Line);
            vClients.push_back(Client);
        }
        File.close();
    }

    return vClients;
}
int CalculateTotalBalances(vector <stClient> vClients) {
    int TotalBalances = 0;
    for (stClient Client : vClients)
    {
        TotalBalances += Client.AccountBalance;
    }
    return TotalBalances;
}
vector <stClient> SaveClientsDataToFile(vector <stClient>vClients) {
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    string DataLine;
    if (MyFile.is_open())
    {
        for (stClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}
void PrintClientTotalBlanace() {
    cout << "===========================================================================\n";
    cout << "\t\t Check Balance Screen\t\t\n";
    cout << "===========================================================================\n";
    cout << "Your Balance is: " << Client.AccountBalance <<endl <<endl;
    system("pause");
}
bool FindClient(string AccountNumber,string PinCode, vector <stClient> vClients,stClient &Client) {
    for (stClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber && C.PinCode==PinCode)
        {
            Client = C;
            return true;
        }
    }

    return false;
}
string ReadAccountNumber() {
    string AccountNumber;
    cout << "Enter Account Number? ";
    cin >> AccountNumber;
    return AccountNumber;
}
string ReadPinCode() {
    string PinCode;
    cout << "Enter Pin Code? ";
    cin >> PinCode;
    return PinCode;
}
int ReadPositiveAmount(){
    int Number = 0;
    do{
        cin >> Number;
    } while (Number <= 0);
    return Number;
}
short ReadClientChoice() {
       short choice;
     cin >> choice;
      return choice;
         
         
    }
void ApplyQuickWithdrawChoice(int choice) {
    switch (choice) {
    case 1:
        Client.AccountBalance -= 20;
        break;
    case 2:
        Client.AccountBalance -= 50;
        break;
    case 3:
        Client.AccountBalance -= 100;
        break;
    case 4:
        Client.AccountBalance -= 200;
        break;
    case 5:
        Client.AccountBalance -= 400;
        break;
    case 6:
        Client.AccountBalance -= 600;
        break;
    case 7:
        Client.AccountBalance -= 800;
        break;
    case 8:
        Client.AccountBalance -= 1000;
        break;
    case 9:
        system("cls");
        ShowATMMenu();
        break;
    }
}
bool CheckQuickWithdrawChoice(int choice) {
    switch (choice) {
    case 1:
        if(Client.AccountBalance < 20)
            return false;
        break;
    case 2:
        if (Client.AccountBalance < 50)
        return false;
        break;
    case 3:
        if (Client.AccountBalance < 100)
        return false;
        break;
    case 4:
        if (Client.AccountBalance < 200)
        return false;
        break;
    case 5:
        if (Client.AccountBalance < 400)
        return false;
        break;
    case 6:
        if (Client.AccountBalance < 600)
        return false;
        break;
    case 7:
        if (Client.AccountBalance < 800)
        return false;
        break;
    case 8:
        if (Client.AccountBalance < 1000)
        return false;
        break;
    case 9:
        return true;
        break;
    }
    return true;
}
int ShowQuickDrawMenu() {
    int choice = 0;
    cout << "===========================================================================\n";
    cout << "\t\t Quick Withdraw Screen\t\t\n";
    cout << "===========================================================================\n";
    cout << "\t " << left << setw(10) << "[1] 20";
    cout << "\t " << left << setw(10) << "[2] 50\n";
    cout << "\t " << left << setw(10) << "[3] 100";
    cout << "\t " << left << setw(10) << "[4] 200\n";
    cout << "\t " << left << setw(10) << "[5] 400";
    cout << "\t " << left << setw(10) << "[6] 600\n";
    cout << "\t " << left << setw(10) << "[7] 800";
    cout << "\t " << left << setw(10) << "[8] 1000\n";
    cout << "\t " << left << setw(10) << "[9] Exit\n";
    cout << "==============================================================================\n";
    cout << "Your Balance is: " << Client.AccountBalance << endl;
    cout << "Choose what to draw from [1] to [8] ?";
    choice = ReadClientChoice();
    while (!CheckQuickWithdrawChoice(choice)) {
        cout << "\n Amount exceeds your balance, make another choice.\n";
        system("pause");
        system("cls");
        choice=ShowQuickDrawMenu();
    }
    return choice;
}
void  QuickDraw() {
    vector <stClient> vClients= LoadClientsDataFromFile();
    char choice1 = 'n';
    system("cls");
    int choice2=ShowQuickDrawMenu();
    if (choice2 == 9) {
        ApplyQuickWithdrawChoice(choice2);
    }
    else {
        cout << "\n Are you sure you want perform this transaction ? y/n? ";
        cin >> choice1;
        if (choice1 == tolower('Y')) {
            ApplyQuickWithdrawChoice(choice2);
            cout << "Done successfully. New Balance is: " << Client.AccountBalance << endl;
            system("pause");
        }
        else {
            system("cls");
            ShowQuickDrawMenu();
        }
    }
    for (stClient& C : vClients)
    {
        if (C.AccountNumber == Client.AccountNumber && C.PinCode == Client.PinCode)
        {
            C = Client;
        }
    }
    SaveClientsDataToFile(vClients);

}
bool CheckMultipleOfFive(int N) {
    return (N % 5 == 0);
}
void NormalDraw() {
    vector <stClient> vClients = LoadClientsDataFromFile();
    int choice = 0;
    char choice1 = 'n';
    cout << "===========================================================================\n";
    cout << "\t\t Normal Withdraw Screen\t\t\n";
    cout << "===========================================================================\n";
    cout << "Enter an amount multiple of 5's?  ";
    choice = ReadClientChoice();
    while (!CheckMultipleOfFive(choice)) {
        cout << "Enter an amount multiple of 5's?  ";
        choice = ReadClientChoice();
    }
    if (choice > Client.AccountBalance) {
        cout << "\n Amount exceeds your balance, make another choice.\n";
        system("pause");
        system("cls");
        NormalDraw();
    }
    else {
        cout << "\n Are you sure you want perform this transaction ? y/n? ";
        cin >> choice1;
        if (choice1 == tolower('Y')) {
            Client.AccountBalance -= choice;
            cout << "Done successfully. New Balance is: " << Client.AccountBalance << endl;
            system("pause");
        }
        else {
            system("cls");
            ShowQuickDrawMenu();
        }
        for (stClient& C : vClients)
        {
            if (C.AccountNumber == Client.AccountNumber && C.PinCode == Client.PinCode)
            {
                C = Client;
            }
        }
        SaveClientsDataToFile(vClients);

    }
}
void DepositAmount() {
    vector <stClient> vClients = LoadClientsDataFromFile();
    int amount = 0;
    char choice1 = 'n';
    cout << "===========================================================================\n";
    cout << "\t\t Deposit Screen\t\t\n";
    cout << "===========================================================================\n";
    cout << "Enter a positive  Deposite amount: ";
    amount = ReadPositiveAmount();
    cout << "\n Are you sure you want perform this transaction ? y/n? ";
    cin >> choice1;
    if (choice1 == tolower('Y')) {
        Client.AccountBalance += amount;
        cout << "Done successfully. New Balance is: " << Client.AccountBalance << endl;
        system("pause");
    }
    else {
        system("cls");
        ShowATMMenu();
    }
    for (stClient& C : vClients)
    {
        if (C.AccountNumber == Client.AccountNumber && C.PinCode == Client.PinCode)
        {
            C = Client;
        }
    }
    SaveClientsDataToFile(vClients);

}
void ApplyClientChoice(MenuATM ClientChoice) {
    system("cls");
    switch (ClientChoice) {
    case Quickdraw:
        QuickDraw();
        ShowATMMenu();
        break;
    case Normaldraw:
        NormalDraw();
        ShowATMMenu();
        break;
    case Deposit:
        DepositAmount();
        ShowATMMenu();
        break;
    case CheckBalance:
        PrintClientTotalBlanace();
        ShowATMMenu();
        break;
    case Logout:
        Login();
        break;
    }
    }
void ShowATMMenu() {
    system("cls");
    short choice = 0;
    cout << "===========================================================================\n";
    cout << "\t\t ATM Main Menue Screen\t\t\n";
    cout << "===========================================================================\n";
    cout << "[1] Quick Withdraw.\n";
    cout << "[2] Normal Withdraw.\n";
    cout << "[3] Deposit.\n";
    cout << "[4] Check Balance.\n";
    cout << "[5] Logout.\n";
    cout << "===========================================================================\n";
    cout << "Choose what do you want to do? [1 to 5]? ";
    choice = ReadClientChoice();
    ApplyClientChoice(MenuATM(choice));
}
void Login() {
    bool Find = false;
    string AccountNumber, PinCode;
    vector <stClient> vClients = LoadClientsDataFromFile();
    ShowLogin();
    while (Find == false) {
        AccountNumber = ReadAccountNumber();
        PinCode = ReadPinCode();
        if (FindClient(AccountNumber,PinCode,vClients,Client)) {
     
            Find = true;
            ShowATMMenu();
        }
        else {
            system("cls");
            ShowLogin();
            cout << "Invalid Username/Password\n";
        }
    }
}
int main() {
    Login();
    system("pause=0");
    return 0;

}