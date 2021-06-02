// This program was made by Bannikov Nikita, group 9309 
#include "REdBlackTree.h"
#include <iomanip>
#include <iostream>
#include <locale>
using namespace std;
int main()
{
	RedBlackTree* tree = new RedBlackTree;

	cout << "Add items..." << endl;
	cout << " 5-five" << endl;
	tree->insert(5, "five");
	cout << " 10-ten" << endl;
	tree->insert(10, "ten");
	cout << " 15-fifteen" << endl;
	tree->insert(15, "fifteen");

	cout << endl << "Get and print keys:";
	vector<int> keys = tree->get_keys();
	for (int i = 0; i < keys.size(); i++)
	{
		cout << " ";
		cout << keys[i];
		if (i < keys.size() - 1) {
			cout << ",";
		}
	}
	cout << endl;


	cout << "Get and print values:";
	vector<string> values = tree->get_values();

	for (int i = 0; i < values.size(); i++)
	{
		cout << " ";
		cout << values[i];
		if (i < values.size() - 1) {
			cout << ",";
		}
	}
	cout << endl << endl;

	cout << "Print tree...";
	tree->print();

	cout << endl << "Add 12-twelve" << endl;
	tree->insert(12, "twelve");

	cout << "Print tree...";
	tree->print();

	delete tree;
}
