#ifndef HASHTABLE_H
#define HASHTABLE_H
#define H_TABLE_SIZE 10
#include<string>
#include<vector>

struct Movie
{
    std::string title;
    int year;
	int index;
	bool found;
    Movie* next;

    Movie()
	{
		title = " ";
		year = -1;
		index = -1;
		next = nullptr;
		found = false;
	};

    Movie(std::string& in_title, int& in_year)
    {
        title = in_title;
        year = in_year;
		index = -1;
		next = nullptr;
		found = false;
	};

	Movie(std::string& in_title, int& in_year, int& in_index)
	{
		title = in_title;
		year = in_year;
		index = in_index;
		next = nullptr;
		found = false;
	};

};

class HashTable
{
public:
	HashTable();
	HashTable(int&);
	~HashTable();

	void insertMovie(std::string&, int&);
	
	void deleteMovie(std::string&);	
	
	void searchMovie(std::string title);
	
	void printInventory();
						
	Movie* findMovie(std::string&);
							
	void filterbyYear(int&);
	
	bool isFull();
	
	void addToFile(std::string&);
	
	void collision_resolution(std::string&, int&, int&);	
							
	void sortMovie(std::vector<Movie*> collisions);
	
	Movie* sizeDouble();
		
	std::vector <Movie*> printYears();
	
	unsigned int get_size();
	
	bool is_empty();

private:
	int get_hash_key(std::string&);
	int size;
	Movie** hashTable;

};

#endif // HASHTABLE_H
