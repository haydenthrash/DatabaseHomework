//created 8/29/16 by Sandy J. Becerra and Hayden Thrasher

#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <cstdlib>
#include <sstream>
using namespace std;

const int RECORD_SIZE = 71;
const int NUM_RECORDS = 4110;
const string FILENAME = "temp.txt"; //changed, will be used when adding entry to temp file so that it can later be merged with orginial database
const char WHITE_SPACE(32);
const char NEW_LINE(10);

void NewEntry();
void NewDatabase();
fstream OpenDatabase(string filename, bool &isOpened);
int main();

//starting values for fields in file, taken from sample code given by Dr. Gauch
string ID = "ID";
int Experience = -1;
string Married = "unknown";
double Wages = -1.0;
string Industry = "Industry";

int RecordNum = 0;
int IDColumnLength = 0;
int ExperienceColumnLength = 0;
int MarriedColumnLength = 0;
int WagesColumnLength = 0;
int IndustryColumnLength = 0;

/*Get record number n-th (from 1 to NUM_RECORDS) */
bool GetRecord(fstream &Din,  string &Id, int &Experience, string &Married, double &Wage, string &Industry)
{
    bool Success = true;
    string line;

    if ((RecordNum >= 1) && (RecordNum <= NUM_RECORDS))
    {
      Din.seekg(RecordNum * RECORD_SIZE, ios::beg);
      Din >> Id >> Experience >> Married >> Wage >> Industry;
    }
    else
    {
      Success = false;
    }

    return Success;
}

/*Binary Search record id */
bool binarySearch (fstream &Din, const string Id, int &Experience, string &Married, double &Wage, string &Industry)
{
   int Low = 0;
   int High = NUM_RECORDS;
   int Middle;
   string MiddleId;

   bool Found = false;
   while (!Found && (High >= Low))
   {
      Middle = (Low + High) / 2;
      Din.seekg(Middle * RECORD_SIZE, ios::beg);
      Din >> MiddleId >> Experience >> Married >> Wage >> Industry;

      if (MiddleId == Id)
			{
				 RecordNum = Middle;
         Found = true;
			}
      else if (MiddleId < Id)
         Low = Middle + 1;
      else
         High = Middle -1;
   }

   return Found;
}

void SearchDatabaseById(fstream &Infile)
{
	if (binarySearch(Infile, ID , Experience, Married, Wages, Industry))
	{
		 cout << "Record ID information: " << Experience << ", " << Married << ", " << Wages << ", " << Industry << endl << endl;
	}
	else
		 cout << "Record for ID " << ID << " was not found.\n\n";
}

void ModifyDatabase(fstream &Infile)
{
	// Change so that if modification goes past column length, it chops off the end
	if (binarySearch(Infile, ID , Experience, Married, Wages, Industry))
	{
		int fieldChoice = 0;
		int updatedLength = 0;
		stringstream wagesStream;

		cout << "Record ID information: " << Experience << ", " << Married << ", " << Wages << ", " << Industry << endl << endl
				<< "What field would you like to modify?\n"
				<< "1. Experience\n"
				<< "2. Married\n"
				<< "3. Wage\n"
				<< "4. Industry\n";
		cin >> fieldChoice;


		switch (fieldChoice)
		{
			case 1:
				cout << "What integer are you changing Experience to?\n";
				cin >> Experience;
				updatedLength = to_string(Experience).length();
				Infile.seekp(RecordNum * RECORD_SIZE, ios::beg);
				Infile.seekp(IDColumnLength, ios::cur);
				Infile << Experience;
				for(int i = 0; i < (ExperienceColumnLength - updatedLength); i++)
				{
					Infile << WHITE_SPACE;
				}
			break;

			case 2:
				cout << "What are you changing Married to?\n";
				cin >> Married;
				updatedLength = Married.length();
				Infile.seekp(RecordNum * RECORD_SIZE, ios::beg);
				Infile.seekp(IDColumnLength + ExperienceColumnLength, ios::cur);
				Infile << Married;
				for(int i = 0; i < (MarriedColumnLength - updatedLength); i++)
				{
					Infile << WHITE_SPACE;
				}
			break;

			case 3:
				cout << "What float are you changing Wage to?\n";
				cin >> Wages;
				wagesStream << fixed << setprecision(9) << Wages;
				updatedLength = wagesStream.str().length();
				cout << updatedLength << endl;
				Infile.seekp(RecordNum * RECORD_SIZE, ios::beg);
				Infile.seekp(IDColumnLength + ExperienceColumnLength + MarriedColumnLength, ios::cur);
				Infile << wagesStream.str();
				for(int i = 0; i < (WagesColumnLength - updatedLength); i++)
				{
					Infile << WHITE_SPACE;
				}
			break;

			case 4:
				cout << "What are you changing Industry to?\n";
				cin >> Industry;
				updatedLength = Industry.length();
				Infile.seekp(RecordNum * RECORD_SIZE, ios::beg);
				Infile.seekp(IDColumnLength + ExperienceColumnLength + MarriedColumnLength + WagesColumnLength, ios::cur);
				Infile << Industry;
				for(int i = 0; i < (IndustryColumnLength - updatedLength); i++)
				{
					Infile << WHITE_SPACE;
				}
				Infile << NEW_LINE;
			break;

			default:
				cout << "You did not select a valid choice.\n";
			break;
		}
	}
	else
	{
		 cout << "Record for ID " << ID << " was not found.\n\n";
	}
}

void DeleteEntry(fstream &Infile)
{
	string confirmDelete = " ";

	if(binarySearch(Infile, ID , Experience, Married, Wages, Industry))
	{
		cout << "Record ID information: " << Experience << ", " << Married << ", " << Wages << ", " << Industry << endl << endl
				<< "Are you sure you want to delete record " << ID << "?\n"
				<< "Y/N\n";
		cin >> confirmDelete;

		if(confirmDelete == "Y" || confirmDelete =="y")
		{
			cout << " . . . \n";
			Infile.seekp(RecordNum * RECORD_SIZE, ios::beg);
			Infile << "-1";
			for(int i = 0; i  < (RECORD_SIZE - 3); i++)
			{
				Infile << WHITE_SPACE;
			}

			Infile << NEW_LINE;

			cout << "Okay then, you've deleted it forever\n";
		}

		else
		{
			cout << "Record " << ID << " was not deleted\n";
		}
	}

	else
	{
		cout << "Record for ID " << ID << " was not found.\n\n";
	}
}

void Menu(fstream &Infile, string filename, int menuOption){
  switch (menuOption)
  {
  	case 1://Displays an entry based on user choice
	   	 cout <<"Please enter ID number to search for\n";
	 	   cin >> ID;
			 SearchDatabaseById(Infile);
		 break;

  	case 2:
      	cout << "Please enter ID number to delete\n";
				cin >> ID;
				DeleteEntry(Infile);
      break;

  	case 3://Adds entry to database
				NewEntry();
      break;

  	case 4:
      	cout << "Please enter ID number to modify\n";
				cin >> ID;
				ModifyDatabase(Infile);
      break;

  	case 5://return to main where user can quit program of do other stuff
				Infile.close();
				main();
      break;

  	default:
				cout << "You didn't enter a valid option, please try again\n\n";
      break;
  }//ends switch
}//ends Menu function

void NewEntry(){//still have to do error checking but we can leave it for the very end as "touch-ups"
  ofstream outfile;
  outfile.open(FILENAME.c_str());
  int entries;

  outfile << "ID" << '\t' << "Experience" << '\t' << "Married" << "\t\t" << "Wage" << "\t\t" << "Industry" << std::endl;
  cout << "how many entries do you wish to add?\n"; cin >> entries;

  for (int j=0; j< entries; j++){
  cout << "Please enter ID #:\n"; cin >> ID;//not so sure we should use the global variables but for now I will
  cout <<"Enter Experience in the form of a whole number (ex: 10 not 10.0):\n"; cin >> Experience;
  cout <<"Maried? yes or no:\n"; cin >> Married;
  cout <<"Enter Wage:\n"; cin >> Wages;
  cout << "Enter the Industry he/she works at:\n"; cin >> Industry;

  outfile << ID << '\t' << Experience << "\t\t" << Married << "\t\t" << Wages << "\t\t" << Industry << endl;
  }//ends for loop

  outfile.close();
}//ends NewEntry

void NewDatabase(){//still have to do error checking but we can leave it for the very end as "touch-ups"

	string newdatafile;
	int entries;

	cout <<"Please enter a name for your new database:\n"<<endl; cin >> newdatafile;
	ofstream outfile;
	outfile.open(newdatafile.c_str());

  outfile << "ID" << '\t' << "Experience" << '\t' << "Married" << "\t\t" << "Wage" << "\t\t" << "Industry" << std::endl;
  cout << "how many entries do you wish to add?\n"; cin >> entries;

  for (int j=0; j< entries; j++){
  cout << "Please enter ID #:\n"; cin >> ID;//not so sure we should use the global variables but for now I will
  cout <<"Enter Experience in the form of a whole number (ex: 10 not 10.0):\n"; cin >> Experience;
  cout <<"Maried? yes or no:\n"; cin >> Married;
  cout <<"Enter Wage:\n"; cin >> Wages;
  cout << "Enter the Industry he/she works at:\n"; cin >> Industry;

  outfile << ID << '\t' << Experience << "\t\t" << Married << "\t\t" << Wages << "\t\t" << Industry << endl;
  }//ends for loop

  outfile.close();

}//ends NewDatabase

void InitializeColumnLengths(fstream &Infile)
{
	Infile.seekg(0, ios::beg);
	string IDTitle;
	Infile >> IDTitle;
	IDColumnLength = IDTitle.length();
	while(Infile.peek() == WHITE_SPACE)
	{
		IDColumnLength++;
		Infile.seekg(1, ios::cur);
	}

	string ExperienceTitle;
	Infile >> ExperienceTitle;
	ExperienceColumnLength = ExperienceTitle.length();
	while(Infile.peek() == WHITE_SPACE)
	{
		ExperienceColumnLength++;
		Infile.seekg(1, ios::cur);
	}

	string MarriedTitle;
	Infile >> MarriedTitle;
	MarriedColumnLength = MarriedTitle.length();
	while(Infile.peek() == WHITE_SPACE)
	{
		MarriedColumnLength++;
		Infile.seekg(1, ios::cur);
	}

	string WagesTitle;
	Infile >> WagesTitle;
	WagesColumnLength = WagesTitle.length();
	while(Infile.peek() == WHITE_SPACE)
	{
		WagesColumnLength++;
		Infile.seekg(1, ios::cur);
	}

	string IndustryTitle;
	Infile >> IndustryTitle;
	IndustryColumnLength = IndustryTitle.length();
	while(Infile.peek() == WHITE_SPACE)
	{
		IndustryColumnLength++;
		Infile.seekg(1, ios::cur);
	}
}

int main()
{
    int  openDatabase = 0, menuOption = 0;
    string filename;
    bool shouldContinue = true;

    void Menu(fstream &Ifstream, string filename, int menuOption);

    cout <<"HELLO! Please enter the number of your choice\n"
         << "(1) Open Database\n(2) Create New Database\n(3) Quit\n";

    cin >> openDatabase;

    if(openDatabase == 1)
    {
      cout << "Please enter the name of the database you wish to open\n";
      cin >> filename;
			fstream Infile(filename.c_str(), ios::in | ios::out);

			if(Infile.fail())
			{
				cout << "The file could not be opened" << endl;
			}

			else
			{
				InitializeColumnLengths(Infile);
				while(shouldContinue == true)
				{
				 cout << "Please enter the number of your choice\n"
				      << "(1) Search database\n"
				      << "(2) Delete entry\n"
				      << "(3) Add entry\n"
				      << "(4) Modify an entry\n"
				      << "(5) Close Database\n";

				 cin >> menuOption;

				 if(menuOption == 5)
				 {
				   shouldContinue = false;
				 }

				 Menu(Infile, filename, menuOption);
				}
			}
    }

    if(openDatabase == 2)
    {
      NewDatabase();
      main();//goes back to main menu where user can quit entire program or do other stuff
    }

    if(openDatabase == 3)
    {
      cout << "Bye Now!\n";
      exit(1);
    }

    return 0;
}//ends main
