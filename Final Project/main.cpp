#include "MovieTree.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

void displayMenu();

int main(int argc,char *argv[])
{
    MovieTree mt;
   ifstream inFile;
   inFile.open("Assignment6Movies.txt");
   string line,word,title;
   int quantity,rating,year;
   string command;
   while(!inFile.eof())
   {
       getline(inFile,line);
       stringstream ss(line);
       string word;
       getline(ss,word,',');
       istringstream(word)>>rating;
       getline(ss,word,',');
       title=word;
       getline(ss,word,',');
       istringstream(word)>>year;
       getline(ss,word,',');
       istringstream(word)>>quantity;
       mt.addMovieNode(rating,title,year,quantity);
       ss.clear();
   }
   while(command != "6")
   {
       displayMenu();
       getline(cin,command);
        if(command == "1")
        {
            cout << "Enter title:" << endl;
            string input;
            getline(cin, input);
            mt.findMovie(input);
        }
        else if(command=="2")
        {
            cout << "Enter title:" << endl;
            string input;
            getline(cin, input);
            mt.rentMovie(input);
        }
        else if(command == "3")
        {
            mt.printMovieInventory();
        }
        else if (command=="4")
        {
            cout<< "Enter title:"<<endl;
            string input;
            getline(cin, input);
            mt.deleteMovieNode(input);
        }
        else if (command=="5")
        {
            cout<<"Tree contains: "<<mt.countMovieNodes()<<" movies."<<endl;
        }
    }
    cout<<"Goodbye!"<<endl;
    return 0;
}

void displayMenu()
{
    cout << "======Main Menu======" << endl;
    cout << "1. Find a movie" << endl;
    cout << "2. Rent a movie" << endl;
    cout << "3. Print the inventory" << endl;
    cout << "4. Delete a movie" << endl;
    cout << "5. Count the movies" <<endl;
    cout << "6. Quit" << endl;
}
