#include <iostream> 
#include <string> 
#include <vector>
#include <fstream> 
#include <iomanip> 

using namespace std;
const string ClientsFileName = "Clients.txt";

void StartMainMenu();

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

enum enMainMenuOptions
{
    eShowClientList = 1,
    eAddNewClient,
    eDeleteClient,
    eUpdateClientInfo,
    eFindClient,
    eTransactions,
    eExit
};

enum enTransactionMenuOptions
{
    eDeposit = 1,
    eWithdraw,
    eTotalBalances,
    eMainMenu,
};

// Menu

void ShowMainMenuScreen()
{
    cout << "===========================================\n";
    cout << "\t\tMain Menu Screen \n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List. \n";
    cout << "\t[2] Add New Client. \n";
    cout << "\t[3] Delete Client. \n";
    cout << "\t[4] Update Client Info. \n";
    cout << "\t[5] Find Client. \n";
    cout << "\t[6] Transactions. \n";
    cout << "\t[7] Exit. \n";
    cout << "===========================================\n";
}

short ReadChoice(short NumberOfChoices)
{
    short MenuChoice;
    do
    {
        cout << "Choose what do you want to do? [1 to " << NumberOfChoices << "]? ";
        cin >> MenuChoice;
    } while (MenuChoice < 1 || MenuChoice > NumberOfChoices);

    return MenuChoice;
}

void ShowOptionScreen(string Message)
{
    cout << "\n-----------------------------------\n";
    cout << "\t" << Message;
    cout << "\n-----------------------------------\n";
}

// Show Client List

vector<string> SplitString(string S1, string delim)
{
    vector<string> vString;

    short pos = 0;
    string sWord; // define a string variable  

    // use find() function to get the position of the delimiters  
    while ((pos = S1.find(delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word 

        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + delim.length());  // erase() until positon and move to next word
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string 
    }

    return vString;
}

sClient ConvertLineToRecord(string Line, string Seperator = "#//#")
{
    sClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);  // Cast string to double

    return Client;
}

vector <sClient> LoadClientsDataFromFile(string FileName)
{
    vector <sClient> vClients;
    fstream MyFile;

    MyFile.open(FileName, ios::in); // Read Mode

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }

    return vClients;
}

void PrintClientRecord(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintAllClientsData(vector <sClient> vClients)
{
    // Title
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";

    // Header
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    // Clients
    for (sClient& Client : vClients)
    {
        PrintClientRecord(Client);
        cout << endl;
    }

    // Footer
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

// Add New Client

string ReadClientAccountNumber(string Message)
{
    string AccountNumber = "";

    cout << Message;
    cin >> AccountNumber;

    return AccountNumber;
}

sClient ReadNewClient(string AccountNumber)
{
    sClient Client;
    Client.AccountNumber = AccountNumber;

    cout << "Enter PinCode? ";
    // Usage of std::ws will extract all the whitespace character   
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;

        MyFile.close();
    }
}

void AddNewClient(string AccountNumber)
{
    sClient Client = ReadNewClient(AccountNumber);
    string stDataLine = ConvertRecordToLine(Client);

    AddDataLineToFile(ClientsFileName, stDataLine);
}

bool DoesClientExist(vector <sClient>& vClients, string AccountNumber)
{
    for (sClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
            return true;
    }
    return false;
}

string GetUniqueAccountNumber(vector <sClient> vClients)
{
    string AccountNumber = ReadClientAccountNumber("Enter Account Number ? ");

    while (DoesClientExist(vClients, AccountNumber))
    {
        cout << "\nClient with [" << AccountNumber << "] already exists, ";
        AccountNumber = ReadClientAccountNumber("Enter another Account Number ? ");
    }

    return AccountNumber;
}

void AddNewClients(vector <sClient> vClients)
{
    char AddMore = 'Y';

    do
    {
        ShowOptionScreen("Add New Clients Screen");

        cout << "Adding New Client:\n\n";
        string AccountNumber = GetUniqueAccountNumber(vClients);

        AddNewClient(AccountNumber);
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');
}

// Delete Client

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:";
    cout << "\n-----------------------------------";
    cout << "\nAccount Number : " << Client.AccountNumber;
    cout << "\nPin Code       : " << Client.PinCode;
    cout << "\nName           : " << Client.Name;
    cout << "\nPhone          : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";
}

bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient& Client)
{
    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
    for (sClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }

    return false;
}

void SaveClientsDataToFile(string FileName, vector<sClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out); // Overwrite

    string DataLine;

    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                // We only write records that are not marked for delete.  
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
}

bool DeleteClientByAccountNumber(vector<sClient>& vClients)
{
    sClient Client;
    char Answer = 'n';

    ShowOptionScreen("Delete Client Screen");

    string AccountNumber = ReadClientAccountNumber("\nPlease Enter Account Number ? ");

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        cout << "\n\nAre you sure you want to delete this client? y/n ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveClientsDataToFile(ClientsFileName, vClients);

            // Refresh Clients 
            vClients = LoadClientsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

// Update Client Info

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;
    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

bool UpdateClientByAccountNumber(vector<sClient>& vClients)
{
    sClient Client;
    char Answer = 'n';

    ShowOptionScreen("Update Client Info Screen");

    string AccountNumber = ReadClientAccountNumber("\nPlease Enter Account Number ? ");

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveClientsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!"; return false;
    }
}

// Find Client

void PrintClientByAccountNumber(vector <sClient> vClients)
{
    ShowOptionScreen("Find Client Screen");

    string AccountNumber = ReadClientAccountNumber("\nPlease Enter Account Number ? ");
    sClient Client;

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
    }
}

// New Feature! Transactions

void ShowTransactionsMenuScreen()
{
    cout << "===========================================\n";
    cout << "\t\tTransactions Menu Screen \n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit. \n";
    cout << "\t[2] Withdraw. \n";
    cout << "\t[3] Total balances. \n";
    cout << "\t[4] Main Menu. \n";
    cout << "===========================================\n";
}

// Transactions: Deposit

double ReadDepositAmount()
{
    double DepositAmount;
    do
    {
        cout << "\nPlease enter deposit amount? ";
        cin >> DepositAmount;
    } while (DepositAmount <= 0);

    return DepositAmount;
}

double DepositToAccount(string AccountNumber, vector <sClient>& vClients, double DepositAmount)
{
    for (sClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.AccountBalance = C.AccountBalance + DepositAmount;
            return C.AccountBalance;
        }
    }
}

void PerformDepositTransaction(vector<sClient>& vClients)
{
    sClient Client;
    char Answer = 'n';

    ShowOptionScreen("Deposit Screen");

    string AccountNumber = ReadClientAccountNumber("\nPlease Enter Account Number ? ");

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.";
        AccountNumber = ReadClientAccountNumber("\n\nPlease Enter Account Number ? ");
    }

    PrintClientCard(Client);
    double DepositAmount = ReadDepositAmount();

    cout << "\n\nAre you sure you want to perform this transaction? y/n ? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        double NewBalance = DepositToAccount(AccountNumber, vClients, DepositAmount);
        SaveClientsDataToFile(ClientsFileName, vClients);

        // Refresh Clients 
        vClients = LoadClientsDataFromFile(ClientsFileName);

        cout << "\n\Deposit Successfully. New Balance is: " << NewBalance;
    }
}

// Transactions: Withdraw

double ReadWithdrawAmount(double AccountBalance)
{
    double WithdrawAmount;
    cout << "\nPlease enter withdraw amount? ";
    cin >> WithdrawAmount;

    while (WithdrawAmount > AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to: " << AccountBalance;
        cout << "\nPlease enter another amount? ";
        cin >> WithdrawAmount;
    }

    return WithdrawAmount;
}

double WithdrawToAccount(string AccountNumber, vector <sClient>& vClients, double WithdrawAmount)
{
    for (sClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.AccountBalance = C.AccountBalance - WithdrawAmount;
            return C.AccountBalance;
        }
    }
}

void PerformWithdrawTransaction(vector<sClient>& vClients)
{
    sClient Client;
    char Answer = 'n';

    ShowOptionScreen("Withdraw Screen");

    string AccountNumber = ReadClientAccountNumber("\nPlease Enter Account Number ? ");

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.";
        AccountNumber = ReadClientAccountNumber("\n\nPlease Enter Account Number ? ");
    }

    PrintClientCard(Client);
    double WithdrawAmount = ReadWithdrawAmount(Client.AccountBalance);

    cout << "\n\nAre you sure you want to perform this transaction? y/n ? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        double NewBalance = WithdrawToAccount(AccountNumber, vClients, WithdrawAmount);
        SaveClientsDataToFile(ClientsFileName, vClients);

        // Refresh Clients 
        vClients = LoadClientsDataFromFile(ClientsFileName);

        cout << "\n\nWithdraw Successfully. New Balance is: " << NewBalance;
    }
}

// Transactions: Total Balances

void PrintClientBalance(sClient Client)
{
    cout << "| " << setw(20) << left << Client.AccountNumber;
    cout << "| " << setw(45) << left << Client.Name;
    cout << "| " << setw(24) << left << Client.AccountBalance;
}

void PrintTotalBalances(vector <sClient> vClients)
{
    // Title
    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";

    // Header
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(20) << "Account Number";
    cout << "| " << left << setw(45) << "Client Name";
    cout << "| " << left << setw(24) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double TotalBalances = 0;

    // Clients
    for (sClient& Client : vClients)
    {
        PrintClientBalance(Client);
        cout << endl;

        TotalBalances += Client.AccountBalance;
    }

    // Footer
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    // Total Balances
    cout << "\n\t\t\t\t\t     Total Balances = " << TotalBalances;
}

// Transactions: Main Menu

void HandleTransactionsMenuOption(enTransactionMenuOptions Option)
{
    vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    switch (Option)
    {
    case enTransactionMenuOptions::eDeposit:
        PerformDepositTransaction(vClients);
        break;
    case enTransactionMenuOptions::eWithdraw:
        PerformWithdrawTransaction(vClients);
        break;
    case enTransactionMenuOptions::eTotalBalances:
        PrintTotalBalances(vClients);
        break;
    case enTransactionMenuOptions::eMainMenu:
        StartMainMenu();
        break;
    }
}

void StartTransactionsMenu()
{
    enTransactionMenuOptions Option;

    do
    {
        system("cls");
        ShowTransactionsMenuScreen();
        Option = (enTransactionMenuOptions)ReadChoice(4);

        system("cls");
        HandleTransactionsMenuOption(Option);

        cout << "\n\nPress any key to go back to Transaction Menu...";
        system("pause>0");

    } while (Option != enTransactionMenuOptions::eMainMenu);
}

// Exit

void ExitProgram()
{
    ShowOptionScreen("Program Ends :-)");

    system("pause>0");
}

// All Options

void HandleMainMenuOption(enMainMenuOptions Option)
{
    vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    switch (Option)
    {
    case enMainMenuOptions::eShowClientList:
        PrintAllClientsData(vClients);
        break;
    case enMainMenuOptions::eAddNewClient:
        AddNewClients(vClients);
        break;
    case enMainMenuOptions::eDeleteClient:
        DeleteClientByAccountNumber(vClients);
        break;
    case enMainMenuOptions::eUpdateClientInfo:
        UpdateClientByAccountNumber(vClients);
        break;
    case enMainMenuOptions::eFindClient:
        PrintClientByAccountNumber(vClients);
        break;
    case enMainMenuOptions::eTransactions:
        StartTransactionsMenu();
        break;
    case enMainMenuOptions::eExit:
        ExitProgram();
        break;
    }
}

// Start Point

void StartMainMenu()
{
    enMainMenuOptions Option;

    do
    {
        system("cls");
        ShowMainMenuScreen();
        Option = (enMainMenuOptions)ReadChoice(7);

        system("cls");
        HandleMainMenuOption(Option);

        cout << "\n\nPress any key to go back to Main Menu...";
        system("pause>0");

    } while (Option != enMainMenuOptions::eExit);
}

int main()
{
    StartMainMenu();

    system("pause>0");
}