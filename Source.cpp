// This program was made by Bannikov Nikita, group 9309 
#include "REdBlackTree.h"
#include <iomanip>
#include <iostream>
#include <locale>

using namespace std;

void RedBlackTree::left_turn(RedBlackTree* current)
{
	try
	{
		if (current != NULL && current->right != NULL)
		{
			RedBlackTree* newnode = current;
			RedBlackTree* y = current->right;
			if (y->left != NULL)
			{
				newnode->right = y->left;
				y->left->parent = newnode;
				y->left = NULL;
			}
			else
			{
				newnode->right = NULL;
			}
			if (newnode->parent == NULL)
			{
				root = y;
				y->parent = NULL;
			}
			else if (newnode->parent->left == newnode)
			{
				newnode->parent->left = y;
				y->parent = newnode->parent;
				newnode->parent = NULL;
			}
			else
			{
				newnode->parent->right = y;
				y->parent = newnode->parent;
				newnode->parent = NULL;
			}
			y->left = newnode;
			newnode->parent = y;
		}
	}
	catch (exception&)
	{
		cout << "Something went wrong in left_turn()" << endl;
	}
}

void RedBlackTree::right_turn(RedBlackTree* current)
{
	try
	{
		if (current != NULL && current->left != NULL)
		{
			RedBlackTree* newnode = current->left;
			RedBlackTree* y = current;
			if (newnode->right != NULL)
			{
				y->left = newnode->right;
				newnode->right->parent = y;
				newnode->right = NULL;
			}
			else
			{
				y->left = NULL;
			}
			if (y->parent == NULL)
			{
				root = newnode;
				newnode->parent = NULL;
			}
			else if (y->parent->right == y)
			{
				y->parent->right = newnode;
				newnode->parent = y->parent;
				y->parent = NULL;
			}
			else
			{
				y->parent->left = newnode;
				newnode->parent = y->parent;
				y->parent = NULL;
			}
			newnode->right = y;
			y->parent = newnode;
		}
	}
	catch (exception&)
	{
		cout << "Something went wrong in right_turn()" << endl;
	}
}

void RedBlackTree::insert(int key, string value)
{
	try
	{
		RedBlackTree* current;
		current = root;
		if (root == NULL)
		{
			RedBlackTree* elem = new RedBlackTree;
			elem->color = false;
			elem->key = key;
			elem->value = value;
			elem->left = NULL;
			elem->right = NULL;
			elem->parent = NULL;
			root = elem;
		}
		else
		{
			if (key == current->key)
			{
				cout << "Error! This key is already contained in the tree!\n";
				return;
			}
		point:
			while (current->left != NULL && current->right != NULL)
			{
				if (key < current->key)
				{
					current = current->left;
				}
				else if (key > current->key)
				{
					current = current->right;
				}
				else
				{
					cout << "Error! This key is already contained in the tree!\n";
					return;
				}
			}
			if (key < current->key)
			{
				if (current->left == NULL)
				{
					RedBlackTree* elem = new RedBlackTree;
					elem->color = true;
					elem->key = key;
					elem->value = value;
					elem->left = NULL;
					elem->right = NULL;
					elem->parent = current;
					current->left = elem;
					tree_repair(current->left);
				}
				else
				{
					current = current->left;
					goto point;
				}
			}
			else if (key > current->key)
			{
				if (current->right == NULL)
				{
					RedBlackTree* elem = new RedBlackTree;
					elem->color = true;
					elem->key = key;
					elem->value = value;
					elem->left = NULL;
					elem->right = NULL;
					elem->parent = current;
					current->right = elem;
					tree_repair(current->right);
				}
				else
				{
					current = current->right;
					goto point;
				}
			}
			else
			{
				if (key == current->key)
				{
					cout << "Error! This key is already contained in the tree!\n";
					return;
				}
			}
		}
	}
	catch (exception&)
	{
		cout << "Something went wrong in insert()" << endl;
	}
}

void RedBlackTree::tree_repair(RedBlackTree* newnode)
{
	try
	{
		while (newnode != NULL && newnode->parent != NULL && newnode != root && newnode->parent->color == true) {
			if (newnode->parent->parent != NULL && newnode->parent == newnode->parent->parent->left) {
				RedBlackTree* y = newnode->parent->parent->right;
				if (y != NULL && y->color == true) {
					newnode->parent->color = false;
					y->color = false;
					newnode->parent->parent->color = true;
					newnode = newnode->parent->parent;
				}
				else {
					if (newnode == newnode->parent->right) {
						newnode = newnode->parent;
						left_turn(newnode);
					}
					newnode->parent->color = false;
					newnode->parent->parent->color = true;
					right_turn(newnode->parent->parent);
				}
			}
			else if (newnode->parent->parent != NULL) {
				RedBlackTree* y = newnode->parent->parent->left;
				if (y != NULL && y->color == true) {
					newnode->parent->color = false;
					y->color = false;
					newnode->parent->parent->color = true;
					newnode = newnode->parent->parent;
				}
				else {
					if (newnode == newnode->parent->left) {
						newnode = newnode->parent;
						right_turn(newnode);
					}
					newnode->parent->color = false;
					newnode->parent->parent->color = true;
					left_turn(newnode->parent->parent);
				}
			}
		}
		root->color = false;
	}
	catch (exception&)
	{
		cout << "Something went wrong in tree_repair()" << endl;
	}
}

RedBlackTree* RedBlackTree::find(int key)
{
	try
	{
		RedBlackTree* current = root;
		if (current == NULL)
		{
			return current;
		}
		if (key == current->key)
		{
			return current;
		}
	point:
		while (current->left != NULL && current->right != NULL)
		{
			if (key < current->key)
			{
				current = current->left;
			}
			else if (key > current->key)
			{
				current = current->right;
			}
			else
			{
				return current;
			}
		}
		if (key < current->key)
		{
			if (current->left == NULL)
			{
				current = current->left;
				return current;
			}
			else
			{
				current = current->left;
				goto point;
			}
		}
		else if (key > current->key)
		{
			if (current->right == NULL)
			{
				current = current->right;
				return current;
			}
			else
			{
				current = current->right;
				goto point;
			}
		}
		else
		{
			if (key == current->key)
			{
				return current;
			}
		}
	}
	catch (exception&)
	{
		cout << "Something went wrong in find()" << endl;
	}
}

void RedBlackTree::remove(int key)
{
	try
	{
		RedBlackTree* current = find(key);
		if (current != NULL)
		{
			bool originalcolor;
			originalcolor = current->color;
			if (current == root && current->left == NULL && current->right == NULL)
			{
				root = NULL;
				delete current;
				return;
			}
			if (current->left == NULL && current->right == NULL)
			{
				RedBlackTree* NIL = new RedBlackTree;
				if (current->parent->left == current)
				{
					if (current->color == false)
					{
						current->parent->left = NIL;
						NIL->parent = current->parent;
					}
					else
						current->parent->left = NULL;
				}
				else
				{
					if (current->color == false)
					{
						current->parent->right = NIL;
						NIL->parent = current->parent;
					}
					else
						current->parent->right = NULL;
				}
				if (current->color == false)
				{
					delete_repair_nul(NIL);
				}
				delete current;
			}
			else if (current->left == NULL && current->right != NULL)
			{
				RedBlackTree* del = current;
				current->right->parent = current->parent;
				if (current->parent != NULL && current->parent->left == current)
				{
					current->parent->left = current->right;
					if (current->color == false)
						delete_repair(current->right);
				}
				else if (current->parent != NULL && current->parent->right == current)
				{
					current->parent->right = current->right;
					if (current->color == false)
						delete_repair(current->right);
				}
				else
				{
					root = current->right;
					if (current->color == false)
						delete_repair(current->right);
				}
				current = current->right;
				delete del;
			}
			else if (current->left != NULL && current->right == NULL)
			{
				RedBlackTree* del = current;
				current->left->parent = current->parent;
				if (current->parent != NULL && current->parent->left == current)
				{
					current->parent->left = current->left;
					if (current->color == false)
						delete_repair(current->left);
				}
				else if (current->parent != NULL && current->parent->right == current)
				{
					current->parent->right = current->left;
					if (current->color == false)
						delete_repair(current->left);
				}
				else
				{
					root = current->left;
					if (current->color == false)
						delete_repair(current->left);
				}
				current = current->left;
				delete del;
			}
			else
			{
				RedBlackTree* point = current;
				point = point->right;
				if (point->left == NULL)
				{
					current->key = point->key;
					current->value = point->value;
					current->right = point->right;
					if (point->right != NULL)
					{
						point->right->parent = current;
						if (point->color == false)
							delete_repair(point->right);
					}
					delete point;
					return;
				}
				RedBlackTree* point1;
				point1 = current;
				point1 = point1->right;
				while (point1->left != NULL)
					point1 = point1->left;
				while (point->left != point1)
					point = point->left;
				if (point1->right == NULL)
				{
					RedBlackTree* NIL = new RedBlackTree;
					current->key = point1->key;
					current->value = point1->value;
					if (point1->color == false)
					{
						point->left = NIL;
						NIL->parent = point;
					}
					else
						point->left = NULL;
					if (point1->color == false)
						delete_repair_nul(NIL);
					delete point1;
				}
				else
				{
					current->key = point1->key;
					current->value = point1->value;
					point->left = point1->right;
					if (point1->right != NULL)
					{
						point1->right->parent = point;
						if (point1->color == false)
							delete_repair(point1->right);
					}
				}
				point = NULL;
				point1 = NULL;
				delete point, point1;
			}
			return;
		}
		else
		{
			cout << "Element to delete was not found." << endl;
		}
	}
	catch (exception&)
	{
		cout << "Something went wrong in remove()" << endl;
	}
}

void RedBlackTree::delete_repair(RedBlackTree* newnode) {
	try {
		while (newnode != NULL && newnode->parent != NULL && newnode != root && newnode->color == false) {
			if (newnode == newnode->parent->left) {
				RedBlackTree* y = newnode->parent->right;
				if (y != NULL && y->color == true) {
					y->color = false;
					newnode->parent->color = true;
					left_turn(newnode->parent);
					y = newnode->parent->right;
				}
				if (y != NULL && ((y->left == NULL && y->right == NULL) || (y->right == NULL && y->left != NULL && y->left->color == false) || (y->left == NULL && y->right != NULL && y->right->color == false) || (y->left->color == false && y->right->color == false))) {
					y->color = true;
					newnode = newnode->parent;
				}
				else  if (y != NULL) {
					if (y->right == NULL || y->right->color == false) {
						if (y->left != NULL)
						{
							y->left->color = false;
						}
						y->color = true;
						right_turn(y);
						y = newnode->parent->right;
					}
					y->color = newnode->parent->color;
					newnode->parent->color = false;
					if (y->right != NULL)
					{
						y->right->color = false;
					}
					left_turn(newnode->parent);
					newnode = root;
				}
			}
			else {
				RedBlackTree* y = newnode->parent->left;
				if (y != NULL && y->color == true) {
					y->color = false;
					newnode->parent->color = true;
					right_turn(newnode->parent);
					y = newnode->parent->left;
				}
				if (y != NULL && ((y->left == NULL && y->right == NULL) || (y->right == NULL && y->left != NULL && y->left->color == false) || (y->left == NULL && y->right != NULL && y->right->color == false) || (y->left->color == false && y->right->color == false))) {
					y->color = true;
					newnode = newnode->parent;
				}
				else if (y != NULL) {
					if (y->left == NULL || y->left->color == false) {
						if (y->right != NULL)
						{
							y->right->color = false;
						}
						y->color = true;
						left_turn(y);
						y = newnode->parent->left;
					}
					y->color = newnode->parent->color;
					newnode->parent->color = false;
					if (y->left != NULL)
					{
						y->left->color = false;
					}
					right_turn(newnode->parent);
					newnode = root;
				}
			}
		}
		if (newnode != NULL)
		{
			newnode->color = false;
		}
	}
	catch (exception&)
	{
		cout << "Something went wrong in delete_repair()" << endl;
	}
}

void RedBlackTree::delete_repair_nul(RedBlackTree* newnode)
{
	try
	{
		if (newnode != NULL && newnode->parent != NULL && newnode != root && newnode->color == false) {
			if (newnode == newnode->parent->left) {
				RedBlackTree* y = newnode->parent->right;
				if (y != NULL && y->color == true) {
					y->color = false;
					newnode->parent->color = true;
					left_turn(newnode->parent);
					y = newnode->parent->right;
				}
				if (y != NULL && ((y->left == NULL && y->right == NULL) || (y->right == NULL && y->left != NULL && y->left->color == false) || (y->left == NULL && y->right != NULL && y->right->color == false) || (y->left->color == false && y->right->color == false))) {
					y->color = true;
				}
				else  if (y != NULL) {
					if (y->right == NULL || y->right->color == false) {
						if (y->left != NULL)
						{
							y->left->color = false;
						}
						y->color = true;
						right_turn(y);
						y = newnode->parent->right;
					}
					y->color = newnode->parent->color;
					newnode->parent->color = false;
					if (y->right != NULL)
					{
						y->right->color = false;
					}
					left_turn(newnode->parent);
				}
			}
			else {
				RedBlackTree* y = newnode->parent->left;
				if (y != NULL && y->color == true) {
					y->color = false;
					newnode->parent->color = true;
					right_turn(newnode->parent);
					y = newnode->parent->left;
				}
				if (y != NULL && ((y->left == NULL && y->right == NULL) || (y->right == NULL && y->left != NULL && y->left->color == false) || (y->left == NULL && y->right != NULL && y->right->color == false) || (y->left->color == false && y->right->color == false))) {
					y->color = true;
				}
				else if (y != NULL) {
					if (y->left == NULL || y->left->color == false) {
						if (y->right != NULL)
						{
							y->right->color = false;
						}
						y->color = true;
						left_turn(y);
						y = newnode->parent->left;
					}
					y->color = newnode->parent->color;
					newnode->parent->color = false;
					if (y->left != NULL)
					{
						y->left->color = false;
					}
					right_turn(newnode->parent);
				}
			}
		}
		if (newnode != NULL)
		{
			newnode->color = false;
		}
		RedBlackTree* temp = newnode->parent;
		if (newnode->parent->left == newnode)
		{
			newnode->parent->left = NULL;
			delete newnode;
		}
		else
		{
			newnode->parent->right = NULL;
			delete newnode;
		}
		delete_repair(temp);
		temp = nullptr;
		delete temp;
	}
	catch (exception&)
	{
		cout << "Something went wrong in delete_tree_nul()" << endl;
	}
}

void RedBlackTree::create_queue()
{
	try
	{
		RedBlackTree* marker;
		RedBlackTree* finish;
		start = root;
		if (start == NULL)
		{
			return;
		}
		start->next = NULL;
		finish = start;
		marker = start;
		if (marker->left != NULL)
		{
			finish->next = marker->left;
			finish = finish->next;
			finish->next = NULL;
		}
		if (marker->right != NULL)
		{
			finish->next = marker->right;
			finish = finish->next;
			finish->next = NULL;
		}
		marker = marker->next;
		while (marker != NULL)
		{
			if (marker->left != NULL)
			{
				finish->next = marker->left;
				finish = finish->next;
				finish->next = NULL;
			}
			if (marker->right != NULL)
			{
				finish->next = marker->right;
				finish = finish->next;
				finish->next = NULL;
			}
			if (marker->left == NULL && marker->right == NULL && marker->next == NULL)
			{
				break;
			}
			marker = marker->next;
		}
		marker = NULL;
		finish = NULL;
		delete marker;
		delete finish;
		return;
	}
	catch (exception&)
	{
		cout << "Something went wrong in create_queue()" << endl;
	}
}

void RedBlackTree::clear()
{
	try
	{
		create_queue();
		cout << endl;
		while (start != NULL)
		{
			RedBlackTree* deleter;
			deleter = start;
			deleter->left = NULL;
			deleter->right = NULL;
			start = start->next;
			delete deleter;
		}
	}
	catch (exception&)
	{
		cout << "Something went wrong in clear()" << endl;
	}
}

vector<int> RedBlackTree::get_keys()
{
	vector<int> keys;

	try
	{
		create_queue();
		while (start != NULL)
		{
			keys.push_back(start->key);
			start = start->next;
		}
	}
	catch (exception&)
	{
		cout << "Something went wrong in get_keys()" << endl;
	}
	return keys;
}

vector<string> RedBlackTree::get_values()
{
	vector<string> values;
	try
	{
		create_queue();
		while (start != NULL)
		{
			values.push_back(start->value);
			start = start->next;
		}
	}
	catch (exception&)
	{
		cout << "Something went wrong in get_values()" << endl;
	}
	return values;
}

void RedBlackTree::print()
{
	try
	{
		create_queue();
		cout << endl;
		cout << "RedBlackTree:" << endl;
		cout << "-------------------------------" << endl;
		while (start != NULL)
		{
			cout << start->key << " " << start->value << " ";
			if (start->color == false)
			{
				cout << "black" << endl;
			}
			else
			{
				cout << "red" << endl;
			}
			start = start->next;
		}
		cout << "-------------------------------" << endl;
	}
	catch (exception&)
	{
		cout << "Something went wrong in print()" << endl;
	}
}
