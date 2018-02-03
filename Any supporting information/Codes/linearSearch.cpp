#include <chrono>
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;


int search(string word, int size, string *Array) {
	
	for (int i = 0; i < size; i++)
	{
		if (word == Array[i])
		{
			return i+1;
		}
		
	}
	return 0;
}

int main()
{
	cout << "Enter The Size Of Data Set:";
	int size;
	cin >> size;

	string *Array = new string[size];

	ifstream file("input.txt");
	if (file.is_open())
	{

		for (int i = 0; i < size; ++i)
		{
			file >> Array[i];
		}
	}
	
	string word;
	char leave;
	int iteration;
	do {
		cout << "Type the word that you want to search:";
		cin >> word;

		auto start = chrono::high_resolution_clock::now();
		iteration = search(word, size, Array);
		auto finish = chrono::high_resolution_clock::now();
		chrono::duration<double> elapsed = finish - start; 
		
		if (iteration == 0) {
			cout << "We couldn't find the word that you searched.\n";
		}
		else {
			cout << "Searched word " << word << " is found with " << iteration << "th attempt"
				<< " and took " << elapsed.count() << " seconds." << "\n";
		}
		
		cout << "Do you want to exit (y/n): ";
		cin >> leave;
	} while (leave == 'n');

	return 0;
}

