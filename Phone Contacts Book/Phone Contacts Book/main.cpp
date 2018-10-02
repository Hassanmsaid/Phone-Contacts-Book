#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <Windows.h>

using namespace std;

string Name, Address, Number[50];
int NumberCounter = 0; /* Number of phones for a single contact*/
int Operation = 0, Operation1 = 0; /* Operation for minior operations & Operation1 for major ones */
bool Found = false; /* Support Searching without using key */

ofstream myfile("Phone Contacts Book.txt", ios_base::app);

void colour(int col)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, col);
}

class Contact
{
public:

	string Name, Address, Numbers[50];
	int NumberCounter;

	Contact()
	{
		NumberCounter = 0;
		Name = Address = "";
	};
};

void Add(map <  string, Contact >& PhoneBook,
	map <  string, Contact > ::iterator IT)
{ 
	Contact C;
	bool Break = false ; /* Support Valid Operations Entered*/
	cout << " Name : ";
	while (true)
	{


		getline(cin.ignore(), C.Name);
		IT = PhoneBook.find(C.Name);
		if (IT != PhoneBook.end())
		{

			cout << "Name Already Exists ! ";
			cout << endl;
			break;

		}

		cout << " Address : ";
		cin.sync();
		getline(cin, C.Address);
		
		cout << " Number : ";
		while (cin >> C.Numbers[C.NumberCounter])
		{  
			
			C.NumberCounter++;
			cout << " Add Another Number : " << endl;
			cout << " 1) Yes " << endl << " 2) No " << endl;
			while (cin >> Operation)
			{
				if (Operation == 1)
				{
					cout << " Number : ";
					
					break; 
				}
				else if (Operation == 2)
				{
					Break = true; 
					break;
				}
				else if (Operation > 2) /* operation out of scope*/
				{
					cout << "Operation You Entered Is Not Valid , Please Re-Enter Operation Number : " << endl;
					cout << " Add Another Number : " << endl;
					cout << " 1) Yes " << endl << " 2) No " << endl;
					continue;
				}
			}
			if (Break == true)
			{
				break; 
			}
		}

		PhoneBook[C.Name] = C; /* Saving Contact into map*/ 
		break;
	}
	cout << "**************************************************" << endl;

}

void Display_All(map <  string, Contact > PhoneBook,
	map <  string, Contact > ::iterator IT)
{

	IT = PhoneBook.begin();
	while (IT != PhoneBook.end())
	{
		cout << endl << " Name : " << IT->second.Name << endl;
		cout << " Address : " << IT->second.Address << endl;
		for (int i = 0; i < IT->second.NumberCounter; i++)
		{
			cout << " Number" << i + 1 << " : " << IT->second.Numbers[i] << endl;
		}
		
		IT++;
	}
	if (PhoneBook.size() == 0)
	{
		cout << " PhoneBook Is Empty " << endl;
	}
	cout << "**************************************************" << endl;

}

void Display_Contact(map <  string, Contact > PhoneBook,
	map <  string, Contact > ::iterator IT)
{
	cout << " Name : " << IT->second.Name << endl;
	cout << " Address : " << IT->second.Address << endl;
	for (int i = 0; i < IT->second.NumberCounter; i++)
	{
		cout << " Number" << i + 1 << " : " << IT->second.Numbers[i] << endl;
	}
	cout << "**************************************************" << endl;

}

void Edit(map <  string, Contact >& PhoneBook,
	map <  string, Contact > ::iterator IT)
{
	map <  string, Contact > ::iterator NewIT;

	cout << " Enter Contact's Name : ";
	cin.sync();
	getline(cin.ignore(), Name);
	IT = PhoneBook.find(Name);
	if (IT != PhoneBook.end())
	{
		Display_Contact(PhoneBook, IT);
		cout << " Would You Like To Edit : " << endl;
		cout << " 1) Name " << endl << " 2) Address " << " 3) Number " << endl;
		while (cin >> Operation)
		{
			
			if (Operation == 1)
			{
				cout << " New Name : ";
				cin.sync();
				getline(cin.ignore(), Name);
				NewIT = PhoneBook.find(Name);
				if (NewIT != PhoneBook.end())
				{

					cout << "Name Already Exists ! ";
					cout << endl;
					break;

				}
				else
				{
					IT->second.Name = Name;
					PhoneBook[Name] = PhoneBook[IT->first];
					PhoneBook.erase(IT->first);
					break;
				}
			}
			else if (Operation == 2)
			{
				cout << " New Address : ";
				cin.sync();
				getline(cin.ignore(), Address);
				IT->second.Address = Address;
				break;
			}
			else if (Operation == 3)
			{
				string NewNumber;
				if (IT->second.NumberCounter == 1)
				{
					cout << " New Number : ";
					cin >> NewNumber;
					IT->second.Numbers[0] = NewNumber;
				}
				else if (IT->second.NumberCounter != 1)
				{
					for (int i = 0; i < IT->second.NumberCounter; i++)
					{
						cout << i + 1 << ") " << IT->second.Numbers[i] << endl;
					}
					cout << " Which Number You Want To Edit : ";
					cin >> Operation;
					cout << " New Number : ";
					cin >> NewNumber;
					IT->second.Numbers[Operation - 1] = NewNumber;
				}
				break;
			}
			
			else if (Operation > 3)
			{
				cout << " Operation You Entered Is Not Valid , Please Re-Enter Operation Number : " << endl;
				continue;
			}
		}
		cout << " Contact Is Successfully Edited " << endl;
		cout << "**************************************************" << endl;
	}
	else
	{
		cout << " Contact Is Not Found ! " << endl;
	}
	

}

void Search_By_Name(map <  string, Contact > PhoneBook,
	map <  string, Contact > ::iterator IT)
{

	cout << " Contact Name : ";
	cin.sync();
	getline(cin.ignore(), Name);
	IT = PhoneBook.find(Name);


	if (IT == PhoneBook.end())
	{
		cout << " Contact Not Found ! " << endl;
		cout << "**************************************************" << endl;
	}
	else
	{
		Display_Contact(PhoneBook, IT);
	}


}

void Search_By_Number(map <  string, Contact > PhoneBook,
	map <  string, Contact > ::iterator IT)
{
	string Number;
	cout << " Contact Number : ";
	cin >> Number;
	IT = PhoneBook.begin();
	while (IT != PhoneBook.end())
	{
		for (int i = 0; i < IT->second.NumberCounter; i++)
		{
			if (IT->second.Numbers[i] == Number)
			{
				Display_Contact(PhoneBook, IT);
				Found = true;
				break;
			}
		}
		IT++;
	}
	if (Found == false)
	{
		cout << " Contact Not Found ! " << endl;
		cout << "**************************************************" << endl;
	}


}

void Delete_All(map <  string, Contact > & PhoneBook)
{
	PhoneBook.clear();
	cout << " Contact Book Is Empty " << endl;
	cout << "**************************************************" << endl;

}

void Delete_Contact(map <  string, Contact >& PhoneBook,
	map <  string, Contact > ::iterator IT)
{
	cout << " Contact Name : ";
	cin.sync();
	getline(cin.ignore(), Name);
	IT = PhoneBook.find(Name);
	if (IT == PhoneBook.end())
	{
		cout << " Contact Not Found ! " << endl;
	}
	else
	{
		IT = PhoneBook.erase(IT);
		cout << " Contact Is Successfully Deleted " << endl;
	}
	cout << "**************************************************" << endl;

}

void File_To_Map(map <string, Contact> & PhoneBook)
{

	ifstream myfile("Phone Contacts Book.txt");
	string line;
	int counter = 1;
	Contact C;
	while (getline(myfile, line))
	{
		if (line == "")
		{
			continue;
		}
		if (counter == 1)
		{
			C.Name = line;
			counter++;
		}
		else if (counter == 2)
		{
			C.Address = line;
			counter++;
		}
		else if (counter == 3)
		{
			C.Numbers[C.NumberCounter] = line;
			C.NumberCounter++;
			while (getline(myfile, line))
			{
				if (line == "")
				{
					break;
				}
				C.Numbers[C.NumberCounter] = line;
				C.NumberCounter++;
			}
			PhoneBook[C.Name] = C;
			//Contact C;
			C.NumberCounter = 0;
			counter = 1;

		}

	}

}

void Clear_File()
{
	ofstream myfile("Phone Contacts Book.txt", ios_base::trunc);
}

void Map_To_File(map <string, Contact> & PhoneBook, map <string, Contact> ::iterator IT)
{
	Clear_File();
	IT = PhoneBook.begin();
	while (IT != PhoneBook.end())
	{
		myfile << IT->second.Name << endl;
		myfile << IT->second.Address << endl;
		for (int i = 0; i < IT->second.NumberCounter; i++)
		{
			myfile << IT->second.Numbers[i] << endl;
		}
		myfile << endl;
		IT++;
	}
}

int main()
{
	map < string, Contact > PhoneBook;
	map <  string, Contact > ::iterator IT;
	File_To_Map(PhoneBook);
	while (Operation1 != 6)
	{
		colour(9);
		cout << endl << " Would You Like To : \n" << endl;
		colour(14);
		cout << " 1) Add New Contact " << endl;
		cout << " 2) Edit A Contact " << endl;
		cout << " 3) Search For A Contact " << endl;
		cout << " 4) Display Contacts " << endl;
		cout << " 5) Delete Contacts " << endl;
		cout << " 6) Exit" << endl;
		cin >> Operation1;
		colour(11);
		cout << "**************************************************" << endl;
		IT = PhoneBook.begin();
		if (Operation1 == 1)
		{
			Add(PhoneBook, IT);
		}
		else if (Operation1 == 2)
		{
			Edit(PhoneBook, IT);
		}
		else if (Operation1 == 3)
		{
			cout << " 1) Search By Number " << endl << " 2) Search By Name " << endl;
			while (cin >> Operation)
			{
				if (Operation == 1)
				{
					Search_By_Number(PhoneBook, IT);
					break;
				}
				else if (Operation == 2)
				{
					Search_By_Name(PhoneBook, IT);
					break;
				}
				else if (Operation > 2)
				{
					cout << " Operation You Entered Is Not Valid , Please Re-Enter Operation Number : " << endl;
					continue;
				}
			}
		}
		else if (Operation1 == 4)
		{

			Display_All(PhoneBook, IT);

		}
		else if (Operation1 == 5)
		{
			cout << " 1) Delete All Contacts " << endl << " 2) Delete Specific Contact " << endl;
			while (cin >> Operation)
			{
				if (Operation == 1)
				{
					Delete_All(PhoneBook);
					break;
				}
				else if (Operation == 2)
				{
					Delete_Contact(PhoneBook, IT);
					break;
				}
				else if (Operation > 2)
				{
					cout << " Operation You Entered Is Not Valid , Please Re-Enter Operation Number : " << endl;
					continue;
				}
			}

		}
		else if (Operation1 > 6)
		{
			cout << " Operation You Entered Is Not Valid , Please Re-Enter Operation Number : " << endl;
			continue;
		}
		Map_To_File(PhoneBook, IT);

	}

	return 0;
}