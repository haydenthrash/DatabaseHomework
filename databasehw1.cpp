//created 8/29/16 by Sandy J. Becerra

#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <cstdlib>
using namespace std;

const int RECORD_SIZE = 71;
const int NUM_RECORDS = 4110;
const string FILENAME = "temp.txt"; //changed, will be used when adding entry to temp file so that it can later be merged with orginial database

void NewEntry();
void NewDatabase();

//starting values for fields in file, taken from sample code given by Dr. Gauch
     string ID="ID";
     int Experience=-1;
     string Married="unknown";
     float Wages=-1.0;
     string Industry="Industry";

/*Get record number n-th (from 1 to NUM_RECORDS) */
bool GetRecord(ifstream &Din, const int RecordNum, string &Id, int &Experience, string &Married, float &Wage, string &Industry)
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
bool binarySearch (ifstream &Din, const string Id, int &Experience, string &Married, float &Wage, string &Industry)
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
         Found = true;
      else if (MiddleId < Id)
         Low = Middle + 1;
      else
         High = Middle -1;
   }

   return Found;
}

void Menu(string filename, int menuOption){
  ifstream Infile;
  Infile.open(filename.c_str());

  switch (menuOption)
  {
  	case 1://Displays an entry based on user choice
   	 cout <<"Please enter ID number to search for\n";
 	 cin >> ID;
	 
           if (binarySearch(Infile, ID , Experience, Married, Wages, Industry))
   	       {
              cout << "Record ID information: " << Experience << ", " << Married << ", " << Wages << ", " << Industry << endl << endl;
   	       }
           else
      	      cout << "Record for ID " << ID << " was not found.\n\n";

      break;
  	case 2:
      cout << "Delete an entry. This might be tricky but according to Dr.G we can fill it up with spaces instead of deleting everything and having to shift everyhting up or down";
      break;
  	case 3://Adds entry to database
           NewEntry();
      break;
  	case 4:
      cout << "Modify an entry...I have no clue how to go about it";
      break;
  	case 5://creates a new database
         NewDatabase();
      break;
    case 6:
      Infile.close();
      cout << "Bye Now!\n";
      break;

  	default:
      cout << "You didn't enter a valid option, please try again";
      break;
  }//ends switch
}//ends Menu function

void NewEntry(){//still have to do error checking but we can leave it for the very end as "touch-ups"
  ofstream outfile;
  outfile.open(FILENAME.c_str()); 
  int entries;

  outfile << "ID" << '\t' << "Experience" << '\t' << "Married" << '\t' << "Wage" << '\t' << "Industry" << std::endl; //IT'S NOT CREATING NEW LINES IN THE FILE!!
  cout << "how many entries do you wish to add?\n"; cin >> entries;
  
  for (int j=0; j< entries; j++){
  cout << "Please enter ID #:\n"; cin >> ID;//not so sure we should use the global variables but for now I will
  cout <<"Enter Experience in the form of a whole number (ex: 10 not 10.0):\n"; cin >> Experience;
  cout <<"Maried? yes or no:\n"; cin >> Married;
  cout <<"Enter Wage:\n"; cin >> Wages;
  cout << "Enter the Industry he/she works at:\n"; cin >> Industry;

  outfile << ID << '\t' << Experience << '\t' << Married << '\t' << Wages << '\t' << Industry << endl;
  }//ends for loop
  
  outfile.close();


}//ends NewEntry

void NewDatabase(){//still have to do error checking but we can leave it for the very end as "touch-ups"

 string newdatafile;
 int entries;

 cout <<"Please enter a name for your new database:\n"<<endl; cin >> newdatafile;
 ofstream outfile;
 outfile.open(newdatafile.c_str());

  outfile << "ID" << '\t' << "Experience" << '\t' << "Married" << '\t' << "Wage" << '\t' << "Industry" << std::endl;
  cout << "how many entries do you wish to add?\n"; cin >> entries;
  
  for (int j=0; j< entries; j++){
  cout << "Please enter ID #:\n"; cin >> ID;//not so sure we should use the global variables but for now I will
  cout <<"Enter Experience in the form of a whole number (ex: 10 not 10.0):\n"; cin >> Experience;
  cout <<"Maried? yes or no:\n"; cin >> Married;
  cout <<"Enter Wage:\n"; cin >> Wages;
  cout << "Enter the Industry he/she works at:\n"; cin >> Industry;

  outfile << ID << '\t' << Experience << '\t' << Married << '\t' << Wages << '\t' << Industry << endl;
  }//ends for loop
  
  outfile.close();

}//ends NewDatabase

int main()
{   
    int  openDatabase = 0, menuOption = 0;
    string file;
    bool shouldContinue = true;

    void Menu(string file, int menuOption);

    cout <<"HELLO! Please enter the number of your choice\n"
         << "(1) Open Database (2) Close Database\n";

    cin >> openDatabase;

    if(openDatabase == 1)
    {
      cout << "Please enter the name of the database you wish to open\n";
      cin >> file;

      //while loop keeps menu up until they choose to quit
       while(shouldContinue == true)
       {
         cout << "Please enter the number of your choice\n"
              << "(1) Search database\n"
              << "(2) Delete entry\n"
              << "(3) Add entry\n"
              << "(4) Modify an entry\n"
              << "(5) Create new Database\n"
              << "(6) Quit\n";

         cin >> menuOption;

         if(menuOption == 6)
         {
           shouldContinue = false;
         }

         Menu(file, menuOption);
       }
    }

    if(openDatabase == 2)
    {
      cout << "Goodbye!";
      exit(1);
    }
    
    return 0;
}//ends main
