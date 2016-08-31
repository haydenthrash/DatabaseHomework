//created 8/29/16 by Sandy J. Becerra

#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
using namespace std;

const int RECORD_SIZE = 71;
const int NUM_RECORDS = 4110;
const string FILENAME = "input.txt";

/*Get record number n-th (from 1 to NUM_RECORDS) */
bool GetRecord(ifstream &Din, const int RecordNum,
               string &Id, int &Experience, string &Married, float &Wage, string &Industry)
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
bool binarySearch (ifstream &Din, const string Id,
                   int &Experience, string &Married, float &Wage, string &Industry)
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
  switch (menuOption)
  {
  	case 1:
      cout << "will need to print out file to user in view mode only!!";
      break;
  	case 2:
      cout << "Delete an entry. This might be tricky but according to Dr.G we can fill it up with spaces instead of deleting everything and having to shift everyhting up or down";
      break;
  	case 3:
      cout << "Adding an entry should not be to hard. We would have to add it to a new file and after a certain count have the program merge and sort the file with the original database";
      break;
  	case 4:
      cout << "Modify an entry...I have no clue how to go about it";
      break;
  	case 5:
      cout << "Creating a new database shoud be easy. A few questions..we will want to have a count for the number of entries in the file, also sort the file as we go??";
      break;
    case 6:
      cout << "Bye Now!\n";
      break;

  	default:
      cout << "You didn't enter a valid option, please try again";
      break;
  }//ends switch
}//ends Menu function

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
      cin >> file; //will have to make file an fstream not a string in order to open it

      //while loop keeps menu up until they choose to quit
       while(shouldContinue == true)
       {
         cout << "Please enter the number of your choice\n"
              << "(1) View database\n"
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

    //cout << "this is testing the exit code in option 2" << endl;
    return 0;
}//ends main
