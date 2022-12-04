#include<iostream>
#include<fstream>
#include<vector>
#include"HashTable.h"

HashTable::HashTable()
{
	size = 0;
	hashTable = new Movie*[H_TABLE_SIZE];
	for (int i = 0; i < H_TABLE_SIZE; i++)
		hashTable[i] = nullptr;
}

HashTable::HashTable(int& table_size)
{
	size = 0;
	hashTable = new Movie*[table_size];
	for (int i = 0; i < table_size; i++)
		hashTable[i] = nullptr;
}

HashTable::~HashTable()
{
	delete[]hashTable;
}

void HashTable::sortMovie(std::vector<Movie*> collisions)
{
    bool boolFlag = true;
    int intD = collisions.size();
    Movie* wordTemp;
    while(boolFlag || (intD < 1))
    {
        boolFlag = false;
        intD = (intD + 1)/2;
        for(int i = 0; i < (collisions.size()-intD); i++)
        {
            if(collisions[i + intD]->title.compare(collisions[i]->title) < 0)
            {
                wordTemp = collisions[i + intD];
                collisions[i+intD] = collisions[i];
                collisions[i] = wordTemp;
                boolFlag = true;
            }
        }
    }
    int m;
    for(int x = 0; x<collisions.size(); x++)
    {
        m = get_hash_key(collisions[x]->title);
        std::cout << collisions[x]->title << ":" << collisions[x]->year << std::endl;
    }
}

void HashTable::collision_resolution(std::string& in_title, int& in_year, int& key)
{
	Movie* new_movie = new Movie(in_title, in_year, key);
	Movie* it = hashTable[key];
	Movie* prev = it;
	if (new_movie->title.compare(hashTable[key]->title) < 0)	//if it is before the first entry...
	{
		new_movie->next = hashTable[key];
		hashTable[key]= new_movie;
		return;
	}
	it = it->next;
	while (it != nullptr)
	{
		if (new_movie->title.compare(it->title) < 0)
		{
			new_movie->next = it;
			prev->next = new_movie;
			return;
		}
		prev = it;
		it = it->next;
	}
	prev->next = new_movie;	//if it has not returned yet, make it the last of the chain
}

unsigned int HashTable::get_size()
{
	return size;
}

bool HashTable::is_empty()
{
	if (size > 0)
		return false;
	return true;
}

int HashTable::get_hash_key(std::string& in_title)
{
	int sum = 0;
	for (std::string::iterator it = in_title.begin(); it != in_title.end(); it++)
		sum += *it;	//sum ASCII

	return (sum % H_TABLE_SIZE);
}



//--------------------------------------------------------------------

//Insert Movie
void HashTable::insertMovie(std::string& in_title, int& in_year)
{
	int key = get_hash_key(in_title); //Hashes for the key
	if (hashTable[key] != nullptr)
		collision_resolution(in_title, in_year, key); //If it goes into one of the linked lists.
	else
	{
		Movie* temp = new Movie(in_title, in_year, key); //Otherwise creates a new index in the array.
		hashTable[key] = temp;
	}
	
	size++;
}

//Delete Movie
void HashTable::deleteMovie(std::string& in_title)
{

	int key = get_hash_key(in_title);
	if(in_title == "all")
    {
        for(int i = 0; i < 10; i++)
        {
            hashTable[i]->title = "";
            hashTable[i]->year = 0;
        }
        std::cout << "Table has been cleared." << std::endl; // Clears out the entirety of the table.
        return;
    }

	if (hashTable[key]->title == in_title && hashTable[key]->next == nullptr) //If it's the only entry at that point.
	{
		delete hashTable[key];
		hashTable[key] = nullptr;
		size--;
		return;
	}

	Movie* it = hashTable[key];
	Movie* prev = it; //New pointers for the linked list at collisions.
	Movie* del = nullptr;

	while (del == nullptr) //Deals with the linked list situation.
	{
		if (it->title == in_title)
		{
			del = it;
			prev->next = del->next;
			delete del;
			size--;
			return;
		}
		prev = it;
		it = it->next;
	}

	size--;
}

//Search by Title
void HashTable::searchMovie(std::string title)
{	
	int length = title.length();
	int count = 0;
	std :: string currentTitle = "";
	int currentYear;
	bool found = false;
	
	std::cout<<"Showing Results Similar to '"<<title<<"':"<<std::endl;

	for(int i = 0; i < 10; i++)
    {
			Movie* temp = hashTable[i];
						
			while(temp!=NULL)
			{
				
				currentTitle = temp->title;
				currentYear = temp->year;
				
				if(currentTitle.substr(0,length) == title){
					count++;
					std::cout<<count<<". "<<currentTitle<<" : "<<currentYear<<std::endl;
					found = true;
				}
					temp=temp->next;
			}
		
    }
    
    if(found == false){
    	std::cout<<"-- No results found --"<<std::endl;
	}
}

//Print Table Contents
void HashTable::printInventory()
{

    for(int i = 0; i < 10; i++)
    {
			Movie* temp = hashTable[i];
			
			while(temp!=NULL)
			{
				std::cout<<temp->title<<": "<<temp->year<<std::endl;
				temp=temp->next;
			}
		
    }
}

//Filter by Prefix
Movie* HashTable::findMovie(std::string& in_title)
{
	int key = get_hash_key(in_title);
									//case 1
	if (hashTable[key] == nullptr)	//if there is no movie in the index, nothing there, return nullptr for main() to handle
		return nullptr;
	Movie* ans = hashTable[key];	//else handle case 2 & 3
	if (hashTable[key]->title != in_title)
		while ((ans != nullptr) && (ans->title != in_title))	//also takes care of the case where the index is taken, but the movie does not exist
			ans = ans->next;

	return ans;	//at this point, ans either holds the answer the function call came for, or nullptr, which is the default case for not found
}

//Filter by Year
void HashTable::filterbyYear(int& year)
{
	bool found = false;
	
	//search the entire hash table with same year
	// if true print data
	
	int count = 0;
	std :: string currentTitle = "";
	int currentYear;
	
	std::cout<<"Showing Results From the year '"<<year<<"':"<<std::endl;

	for(int i = 0; i < 10; i++)
    {
			Movie* temp = hashTable[i];
						
			while(temp!=NULL)
			{
				
				currentTitle = temp->title;
				currentYear = temp->year;
				
				if(currentYear == year){
					count++;
					std::cout<<count<<". "<<currentTitle<<" : "<<currentYear<<std::endl;
					found = true;
				}
					temp=temp->next;
			}
		
    }
    
    if(found == false){
    	std::cout<<"-- No results found --"<<std::endl;
	}
}

//Check for Space
bool HashTable::isFull()
{
int spaceChecker = 0;
for(int i = 0; i < 10; i++)
{
    if(hashTable[i] == nullptr || hashTable[i]->title == "")
    {
        spaceChecker++; //Counts the number of nulls in the array.
    }
}
if (spaceChecker == 0) //If there aren't any spaces available.
{
    std::cout << "The hash table is full" << std::endl;
    return true;
}
std::cout << "The hash table has " << spaceChecker << " spaces remaining in the array." << std::endl;
return false;
}

//Add Contents to File
void HashTable::addToFile(std::string& file_name)
{
	std::ofstream file;
	file.open(file_name);
	
	std :: string currentTitle = "";
	int currentYear;
	int count = 9;
	
	for(int i = 0; i < 10; i++)
    {
			Movie* temp = hashTable[i];
			
			while(temp!=NULL)
			{
				
//				std::cout<<"writing...";
				currentTitle = temp->title;
				currentYear = temp->year;
				
				file<<currentTitle<<","<<currentYear;				
				temp=temp->next;
				
				if(count>1){
					file<<"\n";
				}
			}
			
			count--;		
    }
    
	file.close();
}


