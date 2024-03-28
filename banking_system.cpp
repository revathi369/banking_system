#include <iostream>
#include <ctime>
#include <string>
using namespace std;
class Bank
{
	private:
		string userDetails[1000][5];
		int accountsAvailable = 1000;
		int temporaryAccountNo = 0;
		int accountUserDetails[1000][4];
	public:
		Bank()
		{
			srand((unsigned)time(0));
		}
		bool newAccountCreate(string name, int age, long contactNo, string userName, string pin)
		{
			if(age >= 18 && contactNo >= 1000000000 && contactNo <= 9999999999 && pin.length() == 4)
			{
				userDetails[1000 - accountsAvailable][0] = name;
				userDetails[1000 - accountsAvailable][1] = to_string(age);
				userDetails[1000 - accountsAvailable][2] = to_string(contactNo);
				userDetails[1000 - accountsAvailable][3] = userName;
				userDetails[1000 - accountsAvailable][4] = pin;
				accountUserDetails[1000 - accountsAvailable][0] = (1000000 - accountsAvailable) + 1;
				accountUserDetails[1000 - accountsAvailable][2] = 0;
				accountUserDetails[1000 - accountsAvailable][3] = 0;
				while(temporaryAccountNo == 0 || to_string(temporaryAccountNo).length() != 8 || to_string(temporaryAccountNo)[0] == '0')
				{
					temporaryAccountNo = rand()%100000000;
				}
				accountUserDetails[1000 - accountsAvailable][1] = temporaryAccountNo;
				accountsAvailable -= 1;
				return true;
			}
			else
			{
				return false;
			}
		}
		string getAccountDetails(string userName, string pin)
		{
			string details = "";
			for(int i = 1000;i > accountsAvailable;i--)
			{
				if(userDetails[1000 - i][3] == userName && userDetails[1000 - i][4] == pin)
				{
					details += "Name             : " + userDetails[1000 - i][0] + "\n";
					details += "Age              : " + userDetails[1000 - i][1] + "\n";
					details += "Contact No   : " + userDetails[1000 - i][2] + "\n";
					details += "Account No   : " + to_string(accountUserDetails[1000 - i][1]) + "\n";
					details += "Account Balance  : " + to_string(accountUserDetails[1000 - i][2]) + "\n";
					if(accountUserDetails[1000 - i][3] > 0)
					{
						details += "Last Transaction : Deposit of " + to_string(accountUserDetails[1000 - i][3]) + "\n";
					}
					else if(accountUserDetails[1000 - i][3] < 0)
					{
						details += "Last Transaction : Withdrawal of " + to_string(0 - accountUserDetails[1000 - i][3]) + "\n";
					}
					else
					{
						details += "Last Transaction : No transactions did recently\n";
					}
					break;
				}
			}
			return details;
		}

		bool deposit(string userName, string pin, int depositAmount)
		{
			if(depositAmount > 0)
			{
				for(int i = 1000;i > accountsAvailable;i--)
				{
					if(userDetails[1000 - i][3] == userName && userDetails[1000 - i][4] == pin)
					{
						accountUserDetails[1000 - i][2] += depositAmount;
						accountUserDetails[1000 - i][3] = depositAmount;
						return true;
					}
				}
			}
			return false;
		}
		bool withdraw(string userName, string pin, int withdrawalAmount)
		{
			if(withdrawalAmount > 0)
			{
				for(int i = 1000;i > accountsAvailable;i--)
				{
					if(userDetails[1000 - i][3] == userName && userDetails[1000 - i][4] == pin)
					{
						if(accountUserDetails[1000 - i][2] >= withdrawalAmount)
						{
							accountUserDetails[1000 - i][2] -= withdrawalAmount;
							accountUserDetails[1000 - i][3] = 0 - withdrawalAmount;
							return true;
						}
						else
						{
							break;
						}
					}
				}
			}
			return false;
		}
		bool transferToUser(string userName1, string pin1, string userName2, int transferAmount)
		{
			if(transferAmount > 0)
			{
				for(int i = 1000;i > accountsAvailable;i--)
				{
					if(userDetails[1000 - i][3] == userName1 && userDetails[1000 - i][4] == pin1)
					{
						for(int j = 1000;j > accountsAvailable;j--)
						{
							if(userDetails[1000 - j][3] == userName2)
							{
								if(accountUserDetails[1000 - i][2] >= transferAmount)
								{
									accountUserDetails[1000 - i][2] -= transferAmount;
									accountUserDetails[1000 - i][3] = 0 - transferAmount;
									accountUserDetails[1000 - j][2] += transferAmount;
									accountUserDetails[1000 - j][3] = transferAmount;
									return true;
								}
								else
								{
									return false;
								}
							}
						}
					}
				}
			}
			return false;
		}
};

int main()
{
	string name;
	string userName;
	string pin;
	string userName2;
	int age;
	int amount;
	long contactNo;
	Bank BANK;
	cout << "========== BANKING SYSTEMS ==========\n" << endl;
	while (true) {
		cout << "Officer : How can I help you?" << endl;
		cout << "\t1. To Create a new account" << endl;
		cout << "\t2. To View details of an existing account" << endl;
		cout << "\t3. To Deposit money" << endl;
		cout << "\t4. To Withdraw money" << endl;
		cout << "\t5. To Transfer money to another user" << endl;
		cout << "\t6. To Exit" << endl;
		cout << "USER : ";
		int Input;
		cin >> Input;
		switch (Input) {
			case 1:
				cout << "---------- CREATING NEW ACCOUNT ----------\n" << endl;
				cout << "Officer : Enter your name: ";
				cin.ignore();
				getline(cin, name);
				cout << "Officer : Enter your age: ";
				cin >> age;
				cout << "Officer : Enter your phone number (10 digits): ";
				cin >> contactNo;
				cout << "Officer : Enter a valid username: ";
				cin >> userName;
				cout << "Officer : Enter a valid 4-digit PIN: ";
				cin >> pin;
				if(BANK.newAccountCreate(name, age, contactNo, userName, pin)) {
					cout << "\nOfficer : ACCOUNT SUCCESSFULLY CREATED\n" << endl;
				} else {
					cout << "\nOfficer : ERROR: Account could not be created. Please check your input.\n" << endl;
				}
				break;
			case 2:
				cout << "---------- VIEWING THE DETAILS OF AN EXISTING ACCOUNT ----------\n" << endl;
				cout << "Officer : Enter your username: ";
				cin >> userName;
				cout << "Officer : Enter your PIN: ";
				cin >> pin;
				cout << BANK.getAccountDetails(userName, pin) << endl;
				break;
			case 3:
				cout << "---------- DEPOSITING MONEY ----------\n" << endl;
				cout << "Officer : Enter your username: ";
				cin >> userName;
				cout << "Officer : Enter your PIN: ";
				cin >> pin;
				cout << "Officer : Enter the amount you want to deposit: ";
				cin >> amount;
				if(BANK.deposit(userName, pin, amount)) {
					cout << "\nOfficer : " << amount << " SUCCESSFULLY DEPOSITED\n" << endl;
				} else {
					cout << "\Officer : ERROR: Failed to deposit. Please check your input or account balance.\n" << endl;
				}
				break;
			case 4:
				cout << "---------- WITHDRAWING MONEY ----------\n" << endl;
				cout << "Officer : Enter your username: ";
				cin >> userName;
				cout << "Officer : Enter your PIN: ";
				cin >> pin;
				cout << "Officer : Enter the amount you want to withdraw: ";
				cin >> amount;

				if(BANK.withdraw(userName, pin, amount)) {
					cout << "\nOfficer : " << amount << " SUCCESSFULLY WITHDRAWN\n" << endl;
				} else {
					cout << "\nOfficer : ERROR: Failed to withdraw. Please check your input or account balance.\n" << endl;
				}
				break;
			case 5:
				cout << "---------- TRANSFERRING MONEY ----------\n" << endl;
				cout << "Officer : Enter your username: ";
				cin >> userName;
				cout << "Officer : Enter your PIN: ";
				cin >> pin;
				cout << "Officer : Enter the username of the recipient: ";
				cin >> userName2;
				cout << "Officer : Enter the amount you want to transfer: ";
				cin >> amount;
				if(BANK.transferToUser(userName, pin, userName2, amount)) {
					cout << "\nOfficer : " << amount << " SUCCESSFULLY TRANSFERRED to " << userName2 << "\n" << endl;
				} else {
					cout << "\nOfficer : ERROR: Failed to transfer. Please check your input or account balance and try again later\n" << endl;
				}
				break;
			case 6:
				cout << "\nOfficer : Exiting the bank. Have a great day. Thank You!\n" << endl;
				return 0;
			default:
				cout << "\nOfficer : Invalid option. Please select a valid option.\n" << endl;
		}
	}
	return 0;
}