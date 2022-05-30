#include <iostream>
#include <vector>
#include <string>

using namespace std;


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
	void del_pop() {
		cout << "Do you really want to delete employee " << FirstName << " " << LastName << " ?(y/n) : ";
		//y[i] = 0;
	}
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
		cout << "Last Name : ";
		cin >> LastName;
		while (check_number(LastName) == true)
		{
			cout << "Please  enter a string!  Try again: ";
			cin.clear();
			cin.ignore();
			cin >> LastName;
		}

		cout << "How many hours a week is his/her work? =";
		while (!(cin >> WorkingHours) && (negative_check(WorkingHours)==false))
		{
			cout << "Please  enter a number!  Try again: ";
			cin.clear();
			cin.ignore();
		}
		cout << "How much per hour is his/her salary? =";
		while (!(cin >> CostPerHour) &&( negative_check(CostPerHour)==false))
		{
			cout << "Please  enter a number!  Try again: ";
			cin.clear();
			cin.ignore();
		}
		Salary = WorkingHours * CostPerHour * 52;


		emp_id_cpy[k] = PersonalID;
		sal_cpy[k] = Salary;
		h[k] = LastName;
		k++;

	}

	void get_FieldName() {
		cout << endl;
		cout << FirstName << "		" << LastName << "			" << PersonalID << "			" << Salary << "\t" << endl;

	}
	void getFirstName()
	{
		cin >> FirstName;
	}

	void getLastName()
	{
		cin >> LastName;
	}
	void getWorkinghour()
	{
		cin >> WorkingHours;
		Salary = WorkingHours * CostPerHour * 52;
	}
	void getCostperhour()
	{
		cin >> CostPerHour;
		Salary = WorkingHours * CostPerHour * 52;
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

	void DeletePerson() {
		int empId;
		int che;
		char re1, re2;
		che = 0;
		re1 = 'y';
		while (re1 == 'y' || re1 == 'Y') {

			cout << "Enter ID of employee to remove: ";

			while (!(cin >> empId))
			{
				cout << "Please  enter a number!  Try again: ";
				cin.clear();
				cin.ignore();
			}

			for (i = 0; i < n; ++i) {


				if (emp_id_cpy[i] == empId) {
					em[i].del_pop();
					em[i] = em[i + 1];
					che = 1;
					cin >> re2;
					if (re2 == 'Y' || re2 == 'y') {
						int a;
						a = n;
						cout << "\nNew Employee List is as Follows :" << endl;
						cout << "\nFirst Name       Last Name       Personal ID         Salary per year (Euros)";
						cout << "\n--------------   --------------  ------------       -------------------------" << endl;
						for (int i = 0; i < a; i++) {
							em[i].get_FieldName();
							a--;
							n = a;
							n++;
						}
					}
					cout << endl;
				}
			}
			cout << " Do you want to delete another (y/n)?: ";
			cin >> re1;

			if (che == 0) {
				cout << "Sorry, there is not any employee with requested personal number."
					<< " Do you want to repeat delete by entering the new personal number (y/n)?:";
				cin >> re1;
			}
		}
	}


	void UpdatePerson() {
		int empId;
		char s1, s2;

	
		cout << endl<<"Enter Employee ID : ";

		while (!(cin >> empId))  
		{
			cout << "Please  enter a number!  Try again: ";
			cin.clear();
			cin.ignore(); 
		}
		int el_num = 0;
		for (int i = 0; i < n; ++i) {

			if (emp_id_cpy[i] != empId) {
				el_num++;

			}
		}
		cout << endl;
	

		for (int i = 0; i < n; ++i) {


			if (emp_id_cpy[i] == empId) {

				cout << "matching=" << emp_id_cpy[i];

				flag = true;
				int choice = 0;
				char redo;

				do {
					cout << endl << endl;
					cout << "Please enter the related number of field which you would like to update" << endl;
					cout << "1. First name" << endl;
					cout << "2. Family name" << endl;
					cout << "3. Working hours per week" << endl;
					cout << "4. Payment for one hour" << endl;
					cout <<endl;

					cin >> choice;
					if (choice == 1) {
						cout << " First name: ";
						em[i].getFirstName();
					}
					else if (choice == 2) {
						cout << " Last name: ";
						em[i].getLastName();
					}
					else if (choice == 3) {
						cout << " Working hours per week: ";
						em[i].getWorkinghour();
					}
					else if (choice == 4) {
						cout << " Payment for one hour: ";
						em[i].getCostperhour();
					}
					cout << "Do you want to update another field (Y/N)=";
					cin >> redo;
				} while (redo == 'y' || redo == 'Y');
			}
		}
		int a;
		a = n;
		cout << "\nThe Modified employee list is as follows :" << endl;
		cout << "\nFirst Name       Last Name       Personal ID         Salary per year (Euros)";
		cout << "\n--------------   --------------  ------------       -------------------------" << endl;
		for (int i = 0; i < a; i++) {
			em[i].get_FieldName();

		}

	}

	void ReportList() {
		char op;
		bool doMore;
		cout << "\nPlease enter the related number of the field which you would like to sort the list based on it.\n(1. Last name, 2.Salary)?\n" << endl;
		while (!(cin >> op)) 
		{
			cout << "Please  enter a number!  Try again: ";
			cin.clear();
			cin.ignore();  
		}


		switch (op)
		{
		case '1':
			cout << "\nSorting based on Family Name\n" << endl;
			for (int i = 0; i <= n; i++)
			{
				for (int j = i + 1; j <= n - 1; j++)
				{
					if (h[i] > h[i + 1])
					{
						em_cpy[i] = em[i];
						em[i] = em[j];
						em[j] = em_cpy[i];
					}
				}
			}


			for (int i = 0; i < n; i++)
			{
				em[i].get_FieldName();
			}
			cout << "\nsorted\n";

			break;
		case'2':
			cout << "\nSorting based on Salary\n" << endl;
			for (int h = 0; h < n; h++)
			{
				for (int q = h + 1; q < n; q++)
				{
					if (sal_cpy[h] > sal_cpy[h + 1]);
					{
						em_cpy[h] = em[h];
						em[h] = em[q];
						em[q] = em_cpy[h];
					}
				}
			}
			for (int j = 0; j < n; j++)
			{
				em[j].get_FieldName();
			}

			break;

		}
	
	}

	void SearchPerson() {
		int c;
		char redo1;
		string familyname;
		double min, max;
		do {
			cout << "Search is based on two different fields (1.Last name, 2.Salary), please enter your choice?=" << endl;
			while (!(cin >> c))  
			{
				cout << "Please  enter a number!  Try again: ";
				cin.clear();
				cin.ignore();  
			}


			if (c == 2)

			{
				cout << "Please define your search range for salary of employees ." << endl;
				cout << "What is minimum salary for search (S_min)?=" << endl;
				while (!(cin >> min))  
				{
					cout << "Please  enter a number!  Try again: ";
					cin.clear();
					cin.ignore();  
				}
				cout << "What is maximum salary for search (S_max)?=" << endl;
		
				while (!(cin >> max))  
				{
					cout << "Please  enter a number!  Try again: ";
					cin.clear();
					cin.ignore();  
				}
				int a;
				a = n;
				for (int i = 0; i < n; i++) {


					if (sal_cpy[i] > min && sal_cpy[i] < max) {

						cout << "Matching Found"<<endl;
						cout << "\nThe employee info is as follows:" << endl;
						cout << "\nFirst Name       Last Name       Personal ID         Salary per year (Euros)";
						cout << "\n--------------   --------------  ------------       -------------------------" << endl;
						em[i].get_FieldName();
						
					}
					else {
						cout << endl << "No Match Found " << endl;
					}
				}
			
			}

			else if (c == 1)
			{
				cout << "Please enter the family name of employee?" << endl;
				cin >> familyname;

				for (int i = 0; i < n; i++) {


					if (h[i] == familyname) {

						
						cout << "Matching Found";
						cout << "\nThe employee info is as follows:" << endl;
						cout << "\nFirst Name       Last Name       Personal ID         Salary per year (Euros)";
						cout << "\n--------------   --------------  ------------       -------------------------" << endl;
						em[i].get_FieldName();
						
					}
					else {
						cout << endl<<"No Match Found " << endl;
					}
				}
			}
			
			cout << "\nDo you want to Search any other field (y/n)?\n" << endl;
			cin >> redo1;
		 


		}
		while (redo1 == 'y' || redo1 == 'Y');

	}



};



int main()
{
	HRM doo;
	char def{ 'Y' };
	string b{ " " };
	int num;
	do {
		cout << "Welcome to Human Resource Management (HRM) Software of Company XYZ.";
		cout << "To do specific task please choose one of the following commands." << endl << endl << endl;
		cout << "    1. Add new employee" << endl;
		cout << "    2. Delete employee information" << endl;
		cout << "    3. Update employee information" << endl;
		cout << "    4. Make reports based on specific field" << endl;
		cout << "    5. Search employee" << endl;
		cout << "    6. Quit" << endl << endl;
		cout << endl << endl << "Please enter the related number of your requested command? : ";
		cin >> num;
		cin.ignore();

		switch (num)
		{
		case 1:
			cout << "\nEnter the information of the new employee" << endl;
			doo.AddPerson();
			break;
		case 2:
			doo.DeletePerson();
			break;
		case 3:
			doo.UpdatePerson();
			break;
		case 4:
			doo.ReportList();
			break;
		case 5:
			doo.SearchPerson();
			break;
		case 6:
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
