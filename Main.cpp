#include<iostream>
#include<string>
#include<fstream>
#include"HashTable.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

using namespace std;

int main(int argc, char* argv[])
{
	//initializing hashtable obj
	HashTable* hash = new HashTable();
	
	//reading input from file if any
	std::string filename = "data.txt";
	std::ifstream in_file;
    in_file.open(filename);
    
    //if file exits
	if (in_file.is_open())
	{
		int year;
		string title, buffer;
		while (!in_file.eof())
		{
			//input data format (title,year)
			
			getline(in_file, buffer, ',');
			title = buffer;
						
			getline(in_file, buffer, '\n');
			year = stoi(buffer);
			
			hash->insertMovie(title, year);
		}
	}
	
	//if file dne
	else
	{
		//create empty file
	}  

	int select = 0;
	bool exit = false;

	while (exit != true)
	{

		cout << "======Main Menu======" << endl
			<< "1. Insert Movie" << endl
			<< "2. Delete Movie" << endl
			<< "3. Search by Title" << endl
			<< "4. Print Table Contents" << endl
			<< "5. Filter by Prefix" << endl
			<< "6. Filter by Year" <<endl
			<< "7. Check for Space" << endl
			<< "8. Quit" << endl;

		cin >> select;


		//Insert Movie
		if (select == 1)
		{
			std::string title;
			int year;
			cout << "Enter title:" << endl;
			
			cin.ignore(1000, '\n');
			
			getline(cin, title);
			cout << "Enter year:" << endl;
			cin >> year;
			
			hash->insertMovie(title, year);
		}

		//Delete Movie
		else if (select == 2)
		{
			std::string title;
			cout << "Enter Title:" << endl;
			
			cin.ignore(1000, '\n');
			
			getline(cin, title);
			
			Movie* found_movie = hash->findMovie(title);
			
			if (found_movie == nullptr)
				cout << "Movie Not Found." << endl;
			else
                hash->deleteMovie(title);
		}

		//Search by Title
		else if (select == 3)
		{
			std::string title;
			cout << "Enter Title:" << endl;
			
			cin.ignore(1000, '\n');
			
			getline(cin, title);
			
			Movie* found_movie = hash->findMovie(title);
			
			if (found_movie == nullptr)
				cout << "Not Results Found" << endl;
			else
				cout << found_movie->title << ":" << found_movie->year << endl;
		}

		//Print Table Contenets
		else if (select == 4)
		{
			hash->printInventory();
		}
		        
		//Filter by Prefix
        else if  (select == 5)
        {
            string title;
            cout << "Enter Title Prefix: " << endl;
            cin >> title;
            
            hash->searchMovie(title);
        }
     
	 	//Filter by Year   
        else if(select == 6){
			int year;
			cout<<"Enter Year: "<<endl;
			cin>>year;
			
			hash->filterbyYear(year);
		}
		
		//Check for Space
        else if(select == 7)
        {
            hash->isFull();
        }
        
        //Quit        
		else if (select == 8)
		{
			cout << "Goodbye!" << endl;
			
			hash->addToFile(filename);
			
			exit = true;	
		}
			
		else
		{
			cout << "---Invalid Input---\n\n";
			
			hash->addToFile(filename);
			
			exit = true;
		}
	}

	return 0;
}
