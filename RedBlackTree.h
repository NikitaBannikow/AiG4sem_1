// This program was made by Bannikov Nikita, group 9309 
#pragma once
#include <iomanip>
#include <iostream>
#include <locale>
#include <stdexcept>
#include <vector>
#include <algorithm>
using namespace std;
class RedBlackTree
{
	bool color; //false = black, true = red.
	class RedBlackTree* left;
	class RedBlackTree* right;
	class RedBlackTree* parent;
	class RedBlackTree* root;

public:
	int key;
	string value;
	class RedBlackTree* start;
	class RedBlackTree* next;

	RedBlackTree()
	{
		left = NULL;
		right = NULL;
		parent = NULL;
		start = NULL;
		next = NULL;
		key = 0;
		color = false;
		value = "";
	}

	~RedBlackTree() {
		clear();
	}

	void left_turn(RedBlackTree* current);
	void right_turn(RedBlackTree* current);
	void insert(int key, string value);
	void tree_repair(RedBlackTree* newnode);
	RedBlackTree* find(int key);
	void remove(int key);
	void delete_repair(RedBlackTree* newnode);
	void delete_repair_nul(RedBlackTree* newnode);
	void create_queue();
	void clear();
	vector<int> get_keys();
	vector<string> get_values();
	void print();
};
