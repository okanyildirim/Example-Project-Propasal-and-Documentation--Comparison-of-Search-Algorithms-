#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <chrono>
#include <cstdlib>

using namespace std;

class HashTable {
private:
	string* normalTable;									
	string*	hashTable;							
	int normalTablePointer;
	int hashTablePointer;
	int hashTableSize;									
	int normalTableSize;
	int maxIteration;

public:
	HashTable(int numberOfLines)
	{
		normalTableSize = numberOfLines;
		normalTable = new string[numberOfLines];
		normalTablePointer = 0;
		hashTablePointer = 0;
		hashTableSize = (numberOfLines * 2) - 1;				
		hashTable = new string[hashTableSize];		
		maxIteration = 0;
		for (int i = 0; i<hashTableSize; i++)
		{
			hashTable[i] = "-";					
		}
	}
	void setTable(string word)
	{
		normalTable[normalTablePointer++] = word;
	}
	void insertTable()
	{
		long long int hashIndex = 0;
		for (int i = 0; i < normalTableSize; i++)				
		{
			bool isEmpty = false;
			int iteration = 0;
			do {
				hashIndex = (hashFunc1(normalTable[i], hashTableSize) + (iteration * hashFunc2(normalTable[i]))) % hashTableSize;
				iteration++;
				if (hashTable[hashIndex] == "-")
				{
					isEmpty = true;
				}
			} while ((!isEmpty) && iteration <= hashTableSize);
			if (iteration > maxIteration)
			{
				maxIteration = iteration;
			}
			if (iteration >= hashTableSize)
			{
				cout << "There is a problem.\n";
				return;
			}
			hashTable[hashIndex] = normalTable[i];
		}

	}

	void retrieve(string word)
	{
		long long int hashIndex = 0;
		int iteration = 0;
		bool isFound = false;
		auto start = chrono::high_resolution_clock::now();
		do {
			hashIndex = (hashFunc1(word, hashTableSize) + (iteration * hashFunc2(word))) % hashTableSize;
			iteration++;
			if (hashTable[hashIndex] == word)
			{
				isFound = true;
			}
		} while ((!isFound) && iteration <= maxIteration);
		auto finish = chrono::high_resolution_clock::now();
		chrono::duration<double> elapsed = finish - start;
		if (isFound)
		{
			cout << "Searched word " << hashTable[hashIndex] << " is found with " << iteration << "th attempt"
				<< " and took " << elapsed.count() << " seconds." << "\n";
		}
		else
		{
			cout << "We couldn't find the word that you searched.\n";
		}

	}

	long long int hashFunc1(string word, int tableSize) {			
		long long int hashIndex = 1;
		for (int i = 0; i < word.length(); i++) {
			hashIndex = (hashIndex * word[i]) % tableSize;
		}
		return hashIndex;
	}

	long long int hashFunc2(string word) {			
		long long int hashIndex = 1;
		for (int i = 0; i < word.length(); i++) {
			hashIndex = ((hashIndex * word[i]) % (hashTableSize - 2)) + 2;
		}
		return hashIndex;
	}


	void printTable()
	{
		for (int i = 0; i < normalTablePointer; i++)
		{
			cout << normalTable[i] << endl;
		}
		cout << endl << endl;
	}

	void printHashTable()
	{
		string out = "output.txt";
		ofstream write(out);
		for (int i = 0; i < hashTableSize; i++)
		{
			if (hashTable[i] == "-")
			{
				continue;
			}
			write << hashTable[i] << endl;
		}
		cout << endl << endl;
	}

	void getMaxIteration()
	{
		cout << "Max iteration is: " << maxIteration << endl;
	}


};


int main(int argc, char* argv[])
{
	string txtFile = argv[1];			
	int n = stoi(argv[2]);				
	ifstream read(txtFile);			

	HashTable hashTable(n);
	string temp;
	int counter = 0;

	while (counter < n) {									
		read >> temp;
		hashTable.setTable(temp);							
		counter++;
	}
	hashTable.insertTable();
	cout << "insertion has been done.\n";
	hashTable.getMaxIteration();
	hashTable.printHashTable();
	string word;
	char leave;
	do {
		cout << "Type the word that you want to search:";
		cin >> word;
		hashTable.retrieve(word);
		cout << "Do you want to exit?(y/n)";
		cin >> leave;
	} while (leave == 'n');

	return 0;
}

