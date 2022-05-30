#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

//////////for file
vector<string> fil;



////////global variables

int a_x = 892101;
int n, i, k = 0;
string vl = "a";
string vu = "Z";
int emp_id_cpy[100];

bool flag = 0;

string h[100];
double sal_cpy[100];
int check = 0;

int Working_Hours;


bool check_number(string str) {
	for (int i = 0; i < str.length(); i++)
		if (isdigit(str[i]) == false) {
			return false;
		}
	return true;
}


bool negative_check(int num) {
	if (num > 0) {
		return false;
	}
	return true;


}


/// ////////////////////////////////////////////////////// CLASS PERSON //////////////////////////////////////////////////////////////////

class Person {
private:
	string FirstName{ "null " };
	string LastName{ "null" };
	int PersonalID{ 0 };
	double Salary{ 0 };
	double WorkingHours{ 0 };
	double CostPerHour{ 0 };

public:

	void set_FieldName() {
		PersonalID = a_x;
		a_x++;
		cout << "First Name : ";
		cin >> FirstName;
		while (check_number(FirstName) == true)
		{
			cout << "Please  enter a string!  Try again: ";
			cin.clear();
			cin.ignore();
			cin >> FirstName;
		}
		fil.push_back(FirstName);



		cout << "Last Name : ";
		cin >> LastName;
		while (check_number(LastName) == true)
		{
			cout << "Please  enter a string!  Try again: ";
			cin.clear();
			cin.ignore();
			cin >> LastName;
		}
		fil.push_back(LastName);
		cout << "How many hours a week is his/her work? =";
		while (!(cin >> WorkingHours) && (negative_check(WorkingHours) == false))
		{
			cout << "Please  enter a number!  Try again: ";
			cin.clear();
			cin.ignore();
		}
		
		cout << "How much per hour is his/her salary? =";
		while (!(cin >> CostPerHour) && (negative_check(CostPerHour) == false))
		{
			cout << "Please  enter a number!  Try again: ";
			cin.clear();
			cin.ignore();
		}
		Salary = WorkingHours * CostPerHour * 52;
		string s = to_string(Salary);
		string ee = to_string(PersonalID);
		fil.push_back(ee);
		fil.push_back(s);

		k++;

	}
	void get_FieldName() {
		cout << endl;
		cout << FirstName << "		" << LastName << "			" << PersonalID << "			" << Salary << "\t" << endl;

	}
};


/// ////////////////////////////////////////////////////// CLASS HRM?????? ////////////////////////////////////////////////

class HRM {
private:
	Person em[100];
	Person em_cpy[100];


public:
	void AddPerson() {

		char ch;

		do
		{
			n++;
			em[i].set_FieldName();
			i++;

			cout << "\nThe employee with the following information has been added to the system:" << endl;
			cout << "\nFirst Name       Last Name       Personal ID         Salary per year (Euros)";
			cout << "\n--------------   --------------  ------------       -------------------------" << endl;
			for (int i = 0; i < n; i++) {
				em[i].get_FieldName();
			}
			cout << "Do u want to add another employee?(y/n) : " << endl;
			cin >> ch;
		}

		while ((ch == 'y' || ch == 'Y'));


	}

};



int main()
{
	fstream myFile;
	string myLine;
	myFile.open("Emp.txt", ios::in | ios::out);
	if (!myFile)
	{
		cout << "File did not open!";
		exit(1);
	}

	myFile << "First Name				Last Name				Personal ID					Salary per year (Euros)" << endl;
	myFile << "                                                                                                 " << endl;
	HRM doo;
	char def{ 'Y' };
	string b{ " " };
	int num;



	do {
		cout << "Welcome to Human Resource Management (HRM) Software of Company XYZ.";
		cout << "To do specific task please choose one of the following commands." << endl << endl << endl;
		cout << "    1. Add new employee" << endl;
		cout << "    2. Quit" << endl << endl;
		cout << endl << endl << "Please enter the related number of your requested command? : ";
		cin >> num;
		cin.ignore();

		switch (num)
		{
		case 1:
			cout << "\nEnter the information of the new employee" << endl;
			doo.AddPerson();
			//cout << fil[0];
			myFile << fil[0] << "				" << fil[1]<<"				" << fil[2]<<"				"<< fil[3]<< endl;
			break;
		case 2:
			def = 'n';
			cout << "Thanks for Visiting, Bye!! " << endl;
			break;

		default:
			cout << "\nInvalid option try again";
		}
	
	}
	while (def != 'y' || def == 'Y');
	return 0;
}