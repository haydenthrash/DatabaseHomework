//created 8/29/16 by Sandy J. Becerra

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;
 
int main()
{ int choice, option; string file; void Menu(string file, int option);
  cout<<"HELLO! Please enter the number of your choice\n(1) Open Database (2) Close Database\n";
  cin >> choice;

  if(choice == 1){
     cout<<"Please enter the name of the database you wish to open\n";
     cin >> file; //will have to make file an fstream not a string in order to open it
     cout << "Please enter the number of your choice\n(1)View database\n(2)Delete entry\n(3)Add entry\n(4)Modify an entry\n(5)Create new Database\n(6)Quit\n";
     cin >>option;
     Menu(file, option);
     }

  if(choice == 2){cout<<"Goodbye!"; exit(1); }
  

  //cout << "this is testing the exit code in option 2" << endl;




}//ends main

void Menu(string filename, int option){

  switch (option){
	case 1: cout <<"will need to print out file to user in view mode only!!"; break;
	case 2: cout <<"Delete an entry. This might be tricky but according to Dr.G we can fill it up with spaces instead of deleting everything and having to shift everyhting up or down"; break;
	case 3: cout <<"Adding an entry should not be to hard. We would have to add it to a new file and after a certain count have the program merge and sort the file with the original database"; break;
	case 4: cout <<"Modify an entry...I have no clue how to go about it"; break;
	case 5: cout <<"Creating a new database shoud be easy. A few questions..we will want to have a count for the number of entries in the file, also sort the file as we go??"; break;
	case 6: cout <<main(); break;
	default: cout <<"You didn't enter a value option, please try again"; main(); break;


   }//ends switch
	
}//ends Menu function
