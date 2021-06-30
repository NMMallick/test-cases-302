#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include <iostream>
#include <vector> 
#include "catch.hpp"
#include "XMLParser.cpp"

using namespace std;

// TODO Implement tests of your Stack class and XMLParser class here

TEST_CASE( "Test Bag add", "[XMLParser]" )
{
	   INFO("Hint: testing Bag add()");
		// Create a Bag to hold ints
		Bag<int> intBag;
		int testSize = 2;
		int bagSize;
		bool success;
		for (int i=0; i<testSize; i++) {
			success = intBag.add(i);
			REQUIRE(success);
			bagSize = intBag.size();
			success = (bagSize == (i+1));
			REQUIRE(success);
		}
}

TEST_CASE( "Test Stack push", "[XMLParser]" )
{
	   INFO("Hint: testing Stack push()");
		// Create a Stack to hold ints
		Stack<int> intStack;
		int testSize = 3;
		int stackSize;
		bool success;
		for (int i=0; i<testSize; i++) {
			success = intStack.push(i);
			REQUIRE(success);
			stackSize = intStack.size();
			success = (stackSize == (i+1));
			REQUIRE(success);
		}
}

TEST_CASE( "Test XMLParser tokenizeInputString", "[XMLParser]" )
{
	   INFO("Hint: tokenize single element test of XMLParse");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<test>stuff</test>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
}

TEST_CASE( "Test all provided HTML files", "[XMLParser]") {
/*THIS TESTS EVERY HTML FILE GIVEN IN THE HTML DIRECTORY*/ 
	XMLParser parser; 
	std::vector<std::string> htmlFileNames;
	ifstream htmlFile("./htmlFiles.txt"),
			 myfile; 
	std::string temp, inputString; 
	char c;

	if(htmlFile.is_open()) {
		while(!htmlFile.eof()) {
			htmlFile >> temp;
			htmlFileNames.push_back(temp); 
		}
	}

	for(size_t i = 0; i < htmlFileNames.size(); i++) {
		myfile.open("./html/" + htmlFileNames[i]); 
		// read in the test file
		if (myfile.is_open()) {
			while (!myfile.eof()) {
				myfile.get(c);
				inputString.push_back(c);
			}
			myfile.close();
		}
		
		REQUIRE(parser.tokenizeInputString(inputString));
		REQUIRE(parser.parseTokenizedInput());
		myfile.close(); 

	}

	htmlFile.close(); 	
}