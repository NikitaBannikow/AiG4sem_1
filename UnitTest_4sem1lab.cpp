// This program was made by Bannikov Nikita, group 9309 
#include "pch.h"
#include "CppUnitTest.h"
#include <stdexcept>
#include <windows.h>
#include "../4sem_1lab/RedBlackTree.h"
#include "../4sem_1lab/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RedBlcakTreeTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		UnitTest() {
			tree = new RedBlackTree;
		}

		~UnitTest() {
			delete tree;
		}

		TEST_METHOD(Find)
		{
			tree->insert(5, "five");
			RedBlackTree* item = tree->find(5);
			Assert::AreEqual((string)"five", item->value);
		}

		TEST_METHOD(NotFound)
		{
			bool test_success = false;

			tree->insert(5, "five");
			RedBlackTree* item = tree->find(7);

			if (item == NULL) {
				test_success = true;
			}
			Assert::AreEqual(true, test_success);
		}

		TEST_METHOD(Remove)
		{
			bool test_success = false;

			tree->insert(5, "five");
			RedBlackTree* item = tree->find(5);
			Assert::AreEqual((string)"five", item->value);

			tree->remove(5);
			item = tree->find(5);
			if (item == NULL) {
				test_success = true;
			}
			Assert::AreEqual(true, test_success);
		}

		TEST_METHOD(GetKeys)
		{
			tree->insert(5, "five");
			tree->insert(10, "ten");
			tree->insert(15, "fifteen");

			vector<int> keys_passed = { 5,10,15 }; // must be sorted

			vector<int> keys = tree->get_keys();
			sort(keys.begin(), keys.end());

			bool test_success = false;
			if (keys_passed == keys) {
				test_success = true;
			}
			Assert::AreEqual(true, test_success);
		}

		TEST_METHOD(GetValues)
		{
			tree->insert(5, "five");
			tree->insert(10, "ten");
			tree->insert(15, "fifteen");

			vector<string> values_passed = {"fifteen","five","ten"}; // must be sorted

			vector<string> values = tree->get_values();
			sort(values.begin(), values.end());

			bool test_success = false;
			if (values_passed == values) {
				test_success = true;
			}
			Assert::AreEqual(true, test_success);
		}
	private:
		// Keeps tree instance
		RedBlackTree* tree;
	};
}
