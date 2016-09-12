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
//const int NUM_RECORDS = 4110;
const string FILENAME = "temp.txt"; //changed, will be used when adding entry to temp file so that it can later be merged with orginial database
const char WHITE_SPACE(32);
const char NEW_LINE(10);

int DATOS; //used to get # records from a file. This value will then be used to do binary search
string filename; //moved it up here to use without having to pass it around to unnecessary methods

int RecordNum = 0;
const int IDColumnLength = 6;
const int ExperienceColumnLength = 11;
const int MarriedColumnLength = 8;
const int WageColumnLength = 13;
const int IndustryColumnLength = 32;

int main();
void NewEntry(fstream &Infile);
void FileHeader(ofstream &outfile);
/*Get record number n-th (from 1 to DATOS) */
bool GetRecord(fstream &Din, string &Id, int &Experience, string &Married, double &Wage, string &Industry)
{
    bool Success = true;
    string line;

    if ((RecordNum >= 1) && (RecordNum <= DATOS))
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
   int Low = 1;
   int High = DATOS;
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

//Uses binarySearch to search for the record by ID and print out the information.
void SearchDatabaseById(fstream &Infile, string ID)
{
	int Experience = 0;
	string Married = " ";
	double Wage = 0.0;
	string Industry = " ";

	if (binarySearch(Infile, ID , Experience, Married, Wage, Industry))
	{
		 cout << "Record ID information: " << Experience << ", " << Married << ", " << Wage << ", " << Industry << endl << endl;
	}
	else
	{
		 cout << "Record for ID " << ID << " was not found.\n\n";
	}
}

//Modifies fields of a certain record.
void ModifyDatabase(fstream &Infile, string ID)
{
	int Experience = 0;
	string Married = " ";
	double Wage = 0.0;
	string Industry = " ";

	if (binarySearch(Infile, ID , Experience, Married, Wage, Industry))
	{
		int fieldChoice = 0;
		int updatedLength = 0;
		stringstream wageStream;
		stringstream experienceStream;

		cout << "Record ID information: " << Experience << ", " << Married << ", " << Wage << ", " << Industry << endl << endl
				<< "What field would you like to modify?\n"
				<< "1. Experience\n"
				<< "2. Married\n"
				<< "3. Wage\n"
				<< "4. Industry\n";
		cin >> fieldChoice;


		if(fieldChoice == 1)
		{
			cout << "What integer are you changing Experience to?\n";
			cin >> Experience;
			experienceStream << Experience;
			updatedLength = experienceStream.str().length();
			if (updatedLength >= ExperienceColumnLength)
			{
				experienceStream.str().resize(ExperienceColumnLength - 1);
			}
			Infile.seekp(RecordNum * RECORD_SIZE, ios::beg);
			Infile.seekp(IDColumnLength, ios::cur);
			Infile << experienceStream.str();
			for(int i = 0; i < (ExperienceColumnLength - updatedLength); i++)
			{
				Infile << WHITE_SPACE;
			}
		}

		else if(fieldChoice == 2)
		{
			cout << "What are you changing Married to?\n";
			cin >> Married;
			updatedLength = Married.length();
			if (updatedLength >= MarriedColumnLength)
			{
				Married.resize(MarriedColumnLength - 1);
			}
			Infile.seekp(RecordNum * RECORD_SIZE, ios::beg);
			Infile.seekp(IDColumnLength + ExperienceColumnLength, ios::cur);
			Infile << Married;
			for(int i = 0; i < (MarriedColumnLength - updatedLength); i++)
			{
				Infile << WHITE_SPACE;
			}
		}

		else if(fieldChoice == 3)
		{
			cout << "What float are you changing Wage to?\n";
			cin >> Wage;
			wageStream << fixed << setprecision(9) << Wage;
			updatedLength = wageStream.str().length();
			Infile.seekp(RecordNum * RECORD_SIZE, ios::beg);
			Infile.seekp(IDColumnLength + ExperienceColumnLength + MarriedColumnLength, ios::cur);
			Infile << wageStream.str();
			for(int i = 0; i < (WageColumnLength - updatedLength); i++)
			{
				Infile << WHITE_SPACE;
			}
		}

		else if(fieldChoice == 4)
		{
			cout << "What are you changing Industry to?\n";
			cin >> Industry;
			updatedLength = Industry.length();
			if (updatedLength >= IndustryColumnLength)
			{
				Industry.resize(IndustryColumnLength);
			}
			Infile.seekp(RecordNum * RECORD_SIZE, ios::beg);
			Infile.seekp(IDColumnLength + ExperienceColumnLength + MarriedColumnLength + WageColumnLength, ios::cur);
			Infile << Industry;
			for(int i = 0; i < (IndustryColumnLength - updatedLength); i++)
			{
				Infile << WHITE_SPACE;
			}
		}

		else
			cout << "You did not select a valid choice.\n";
	}
	else
	{
		 cout << "Record for ID " << ID << " was not found.\n\n";
	}
}

void DeleteEntry(fstream &Infile, string ID)
{
	int Experience = 0;
	string Married = " ";
	double Wage = 0.0;
	string Industry = " ";
	string confirmDelete = " ";

	if(binarySearch(Infile, ID , Experience, Married, Wage, Industry))
	{
		cout << "Record ID information: " << Experience << ", " << Married << ", " << Wage << ", " << Industry << endl << endl
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

void CreateReport(fstream &Infile, string ID)
{
	int Experience = 0;
	string Married = " ";
	double Wage = 0.0;
	string Industry = " ";
	stringstream wageStream;


	cout << "Id\tExperience\tMarried\tWage\t\tIndustry\n";
	for(int i = 0; i < 10; i++)
	{
		RecordNum = i + 1;
		if(GetRecord(Infile, ID, Experience, Married, Wage, Industry))
		{
			wageStream << fixed << setprecision(9) << Wage;

			if(wageStream.str().length() <= 8)
			{
				cout << ID << "\t" << Experience << "\t\t" << Married << "\t" << wageStream.str() << "\t\t" << Industry << "\n";
			}
			else
				cout << ID << "\t" << Experience << "\t\t" << Married << "\t" << wageStream.str() << "\t" << Industry << "\n";

			wageStream.str("");
		}
	}
}

void Menu(fstream &Infile, int menuOption){
	string ID = " ";

  if(menuOption == 1)
  {
		cout <<"Please enter ID number to search for\n";
		cin >> ID;
		SearchDatabaseById(Infile, ID);
	}

	else if(menuOption == 2)
	{
		cout << "Please enter ID number to delete\n";
		cin >> ID;
		DeleteEntry(Infile, ID);
	}

  else if(menuOption == 3)
		NewEntry(Infile);

  else if(menuOption == 4)
	{
		cout << "Please enter ID number to modify\n";
		cin >> ID;
		ModifyDatabase(Infile, ID);
  }

	else if(menuOption == 5)
		CreateReport(Infile, ID);

  else if(menuOption == 6)
	{
		Infile.close();
		main();
	}

	else
		cout << "You didn't enter a valid option, please try again\n\n";
}//ends Menu function

void NewEntry(fstream &Infile){

	ofstream outfile;
  outfile.open(FILENAME.c_str()); //opens the temp file to add new entries in
  int entries;

  string ID = " ";
  int Experience = 0;
  string Married = " ";
  double Wage = 0.0;
  string Industry = " ";
  stringstream wages;

  cout << "how many entries do you wish to add?\n"; cin >> entries;

  for (int j=0; j < entries; j++)
	{
		cout << "Please enter ID #:\n"; cin >> ID;
		while (binarySearch(Infile, ID , Experience, Married, Wage, Industry))
		{
			if(Experience != -1)
			{
				cout << "it looks like the id you entered is already in use. try again\n\n\n";
				cout << "Please enter ID #:\n"; cin >> ID;
			}//ends if
		}//ends while

  	cout <<"Enter Experience in the form of a whole number (ex: 10 not 10.0) NONNEGATIVES ONLY:\n"; cin >> Experience;

		if(Experience < 0) {
	    cout << "OUCH! you can't follow directions can you...that okay we'll make it right for you\n";
	    Experience=Experience*(-1);//makes the negative a positive
		}//ends if

        do {cout << "Married? yes or no. type out answer in full\n"; cin >> Married;}while( (Married != "yes") && (Married != "no") && (Married != "Yes") && (Married != "No") );

  	cout <<"Enter Wage:\n"; cin >> Wage;
		wages << fixed << setprecision(9)<< Wage;


  	cout << "Enter the Industry he/she works at:\n"; cin >> Industry;

  	outfile << ID << setw(3) << Experience << setw(12) << Married << setw(16) << wages.str() << setw(6) << Industry << endl;
	}//ends for loop

	outfile.flush();
  DATOS += entries;

  system(("cat temp.txt >>"+ filename).c_str());
  system(("sort -n -o"+filename+ " "+filename).c_str());//sort numerically the file that was opened and stores sorted data back to same file
  system("rm temp.txt");
  system(DATOS+"> numero.txt");

  outfile.close();
}//ends NewEntry

void NewDatabase(){

	string ID = " ";
	int Experience = 0;
	string Married = " ";
	double Wage = 0.0;
	string Industry = " ";

  string newdatafile;
  stringstream wages,experienceStream ;
  int entries, updatedLength;

  cout <<"Please enter a name for your new database:\n"<<endl; cin >> newdatafile;

  ofstream outfile; outfile.open(newdatafile.c_str());
//  FileHeader(outfile); //creates file header
  cout << "how many entries do you wish to add?\n"; cin >> entries;

  for (int j=0; j< entries; j++){

     cout << "Please enter ID #:\n"; cin >> ID;//error check ID
     outfile << ID  << WHITE_SPACE ;
    cout <<"Enter Experience in the form of a whole number (ex: 10 not 10.0) NONNEGATIVES ONLY:\n"; cin >> Experience;
    if(Experience < 0) {
       cout << "Looks like you entered a negative number...that okay we'll make it right for you\n";
       Experience=Experience*(-1);//makes the negative a positive
    }//ends if

			experienceStream.str("");
                        experienceStream << Experience;
			updatedLength = experienceStream.str().length();
			if (updatedLength >= ExperienceColumnLength)
			{
				experienceStream.str().resize(ExperienceColumnLength - 1);
			}
			outfile.seekp(RecordNum * RECORD_SIZE, ios::beg);
			outfile.seekp(IDColumnLength, ios::cur);
			outfile << experienceStream.str();
			for(int i = 0; i < (ExperienceColumnLength - updatedLength); i++)
			{
				outfile << WHITE_SPACE;
			}

      do {cout << "Married? yes or no. type out answer in full\n"; cin >> Married;}while( (Married != "yes") && (Married != "no") && (Married != "Yes") && (Married != "No") );
                        updatedLength = Married.length();
			if (updatedLength >= MarriedColumnLength)
			{
				Married.resize(MarriedColumnLength - 1);
			}
			outfile.seekp(RecordNum * RECORD_SIZE, ios::beg);
			outfile.seekp(IDColumnLength + ExperienceColumnLength, ios::cur);
			outfile << Married;
			for(int i = 0; i < (MarriedColumnLength - updatedLength); i++)
			{
				outfile << WHITE_SPACE;
			}

  cout <<"Enter Wage:\n"; cin >> Wage;
  wages.str("");
                        wages << fixed << setprecision(9)<< Wage;
                        updatedLength = wages.str().length();
			outfile.seekp(RecordNum * RECORD_SIZE, ios::beg);
			outfile.seekp(IDColumnLength + ExperienceColumnLength + MarriedColumnLength, ios::cur);
			outfile << wages.str();
			for(int i = 0; i < (WageColumnLength - updatedLength); i++)
			{
				outfile << WHITE_SPACE;
			}


  cout << "Enter the Industry he/she works at:\n"; cin >> Industry;

			updatedLength = Industry.length();
			if (updatedLength >= IndustryColumnLength)
			{
				Industry.resize(IndustryColumnLength - 2);
			}
			outfile.seekp(RecordNum * RECORD_SIZE, ios::beg);
			outfile.seekp(IDColumnLength + ExperienceColumnLength + MarriedColumnLength + WageColumnLength, ios::cur);
			outfile << Industry;
			for(int i = 0; i < (IndustryColumnLength - updatedLength); i++)
			{
				outfile << WHITE_SPACE;
			}
			outfile << NEW_LINE;
			RecordNum++;

  }//ends for loop

//  outfile.flush();
  outfile.close();

  DATOS = entries;

}//ends NewDatabase


void FileHeader(ofstream &outfile){
stringstream input;
int updatedLength;

input << "id";
updatedLength = input.str().length();
if (updatedLength >= IDColumnLength)
{
  input.str().resize(IDColumnLength - 1);
}
//outfile.seekp(IDColumnLength + ExperienceColumnLength + MarriedColumnLength, ios::cur);                    
outfile << input.str();
for(int i = 0; i < (IDColumnLength - updatedLength); i++)
{
  outfile << WHITE_SPACE;
}


input << "experience";
updatedLength = input.str().length();
if (updatedLength >= ExperienceColumnLength)
{
  input.str().resize(ExperienceColumnLength - 1);
}
outfile.seekp(IDColumnLength, ios::cur);                        
outfile << input.str();
for(int i = 0; i < (ExperienceColumnLength - updatedLength); i++)
{
  outfile << WHITE_SPACE;
}


input << "married";
updatedLength = input.str().length();
if (updatedLength >= MarriedColumnLength)
{
  input.str().resize(MarriedColumnLength - 1);
}
outfile.seekp(IDColumnLength + ExperienceColumnLength, ios::cur);                       
outfile << input.str();
for(int i = 0; i < (MarriedColumnLength - updatedLength); i++)
{
  outfile << WHITE_SPACE;
}

input << "wage";
updatedLength = input.str().length();
if (updatedLength >= WageColumnLength)
{
  input.str().resize(WageColumnLength - 1);
}
outfile.seekp(IDColumnLength + ExperienceColumnLength + MarriedColumnLength, ios::cur);                    
outfile << input.str();
for(int i = 0; i < (WageColumnLength - updatedLength); i++)
{
  outfile << WHITE_SPACE;
}


input << "industry";
updatedLength = input.str().length();
if (updatedLength >= IndustryColumnLength)
{
  input.str().resize(IndustryColumnLength - 1);
}
outfile.seekp(IDColumnLength + ExperienceColumnLength + MarriedColumnLength + WageColumnLength, ios::cur);                    
outfile << input.str();
for(int i = 0; i < (IndustryColumnLength - updatedLength); i++)
{
  outfile << WHITE_SPACE;
}
outfile << NEW_LINE;
RecordNum ++;

}//ends file header
int main()
{
    int  openDatabase = 0, menuOption = 0;
    string temp_rec_num;
    bool shouldContinue = true;

    void Menu(fstream &Ifstream, int menuOption);

    cout <<"HELLO! Please enter the number of your choice\n"
         << "(1) Open Database\n(2) Create New Database\n(3) Quit\n";

    cin >> openDatabase;

    if(openDatabase == 1)
    {
      cout << "Please enter the name of the database you wish to open\n";
      cin >> filename;
			fstream Infile(filename.c_str(), ios::in | ios::out);
      system(("wc -l <"+filename+" > numero.txt").c_str());//read number of lines in the database user chose to open
      fstream record_num ("numero.txt", ios::in | ios::out);
      getline(record_num,temp_rec_num);
	   	DATOS = atoi(temp_rec_num.c_str());
 			cout << "the number of lines in the database are: " << DATOS << endl;

			if(Infile.fail())
			{
				cout << "The file could not be opened" << endl;
			}

			else
			{
				//InitializeColumnLengths(Infile);
				while(shouldContinue == true)
				{
				 cout << "Please enter the number of your choice\n"
				      << "(1) Search database\n"
				      << "(2) Delete entry\n"
				      << "(3) Add entry\n"
				      << "(4) Modify an entry\n"
							<< "(5) Create report\n"
				      << "(6) Close Database\n";

				 cin >> menuOption;

				 if(menuOption == 6)
				 {
				   shouldContinue = false;
				 }

				 Menu(Infile, menuOption);
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
