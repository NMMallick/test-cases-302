#include "XMLParser.hpp"
#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include <iostream>
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
	string testString;
	bool success;

	/**					Possible					**/
	testString = "<?xml?><hey></hey>"; 
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(success);

	testString = "<yo>works<hey>works</hey></yo>";
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(success);

	testString = "<?stop?>";
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(success);


	/**					Impossible					**/
	testString = "can't<put></it></there>";
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(!success);

	testString = "<put><?it?><there/>no";
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(!success);

	testString = "<hey></hey>no<?yo?>";
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(!success);

	testString = "<?yo?> no <stop></stop>";
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(!success);
	
	testString = "hey";
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(!success);
}

TEST_CASE( "Test XMLParser parseTokenizedInput", "[XMLParser]" )
{
	XMLParser myXMLParser;
	string testString;
	bool success;

	/**					Parsable				**/
	testString = "<?xml?><hey></hey>"; 
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(success);
	success = myXMLParser.parseTokenizedInput();
	REQUIRE(success);

	testString = "<?yo?>";
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(success);
	success = myXMLParser.parseTokenizedInput();
	REQUIRE(success);

	testString = "<yo/>";
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(success);
	success = myXMLParser.parseTokenizedInput();
	REQUIRE(success);

	testString = "<hey><you><look/><great></great></you></hey>";
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(success);
	success = myXMLParser.parseTokenizedInput();
	REQUIRE(success);

	/**				Imparsable					**/
	testString = "<yo><that><crazy></that></crazy><yo/>";
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(success);
	success = myXMLParser.parseTokenizedInput();
	REQUIRE(!success);

	testString = "<yo>";
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(success);
	success = myXMLParser.parseTokenizedInput();
	REQUIRE(!success);
	
	testString = "</yo>";
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(success);
	success = myXMLParser.parseTokenizedInput();
	REQUIRE(!success);
	
	testString = "<yo><my></yo>";
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(success);
	success = myXMLParser.parseTokenizedInput();
	REQUIRE(!success);
	
	testString = "<yo></yo></my>";
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(success);
	success = myXMLParser.parseTokenizedInput();
	REQUIRE(!success);

}

TEST_CASE( "Test XMLParser clear", "[XMLParser]")
{
	XMLParser myXMLParser;
	string testString = "<tag1></tag1>";
	vector<TokenStruct> test;
	bool success;

	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(success);

	test = myXMLParser.returnTokenizedInput();
	REQUIRE(test.size() == 2);
	
	myXMLParser.clear();

	
	test = myXMLParser.returnTokenizedInput();
	REQUIRE(test.size() == 0);
}
