#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
using namespace std;

class Node {

private:

public:

	Node *Rchild;
	Node *Lchild;
	string key;

	Node(string word) {
		key = word;
		Rchild = NULL;
		Lchild = NULL;
	}
	string getKey() {

		return key;
	}

};
int ascii(string word, string orjword) {
	int length = word.length();
	for (int counter = 0; counter < length; counter++) {

		int iw;
		int iow;

		iw = word[counter];
		iow = orjword[counter];

		if (iw > iow) {
			return 0;
		}
		else if (iw < iow)
			return 1;
	}
}
class BinarySearchTree {
private:
	Node* root;
	int counter = 0;
public:
	BinarySearchTree() {
		root = NULL;
	}

	void insert(string word)
	{
		Node* newNode = new Node(word);
		if (root == NULL)
		{
			root = newNode;
			root->key = word;
			root->Lchild = NULL;
			root->Rchild = NULL;
			return;
		}
		Node* current = root;
		while (true) {
			if (ascii(newNode->key, current->key) == 1)
			{
				if (current->Lchild == NULL)
				{
					current->Lchild = newNode;
					break;
				}
				current = current->Lchild;
			}
			else
			{
				if (current->Rchild == NULL)
				{
					current->Rchild = newNode;
					break;
				}
				current = current->Rchild;
			}
		}
	}
	void preorder(Node* root)
	{
		if (root == NULL)
			return;
		cout << root->key << endl;
		preorder(root->Lchild);
		preorder(root->Rchild);
	}
	void display()
	{
		preorder(root);
		cout << endl;
	}

	void search(string word)
	{
		Node* current = root;
		int iteration = 0;
		auto start = chrono::high_resolution_clock::now();
		while (true) {
			iteration++;
			if (current->key == word)
			{
				auto finish = chrono::high_resolution_clock::now();
				chrono::duration<double> elapsed = finish - start;
				cout << "Searched word " << word << " is found with " << iteration << "th attempt"
					<< " and took " << elapsed.count() << " seconds." << "\n";
				break;
			}
			else if (ascii(word, current->key) == 1)
			{
				current = current->Lchild;
			}
			else if (ascii(word, current->key) == 0)
			{
				current = current->Rchild;
			}
			if (current == NULL)
			{
				cout << "We cannot found the word that you searched.\n";
				break;
			}
		}
	}
};
int main() {
	BinarySearchTree BST;
	string file = "input.txt";
	ifstream input(file.c_str());
	string word;
	int temp;
	//string* wordarray = new string[1000000];
	cout << "Enter number of element:";
	cin >> temp;
	clock_t start = clock();
	for (int i = 0; i < temp; i++) {
		input >> word;
		//cout « wordarray[i] « endl;
		BST.insert(word);

	}
	cout << "Insertion has been done.\n" << endl;
	double time;
	//BST.search("");
	time = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Time:" << time << '\n';

	string search;
	char leave;
	do {
		cout << "Type the word that you want to search:";
		cin >> search;
		BST.search(search);
		cout << "Do you want to exit (y/n): ";
		cin >> leave;
	} while (leave == 'n');

	return 0;
}
