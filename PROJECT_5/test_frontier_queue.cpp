#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "frontier_queue.hpp"
#include <time.h> 
#include <vector> 
#include <math.h>
// TODO implement your tests here
// note you can use any supported type for the value type T
// including the Puzzle type as in the solver code

TEST_CASE( "Push and Pop One Item", "[frontier_queue]" ) {
    frontier_queue<int> frontier; 
    REQUIRE(frontier.empty()); 

    frontier.push(7, 0, 0); 

    REQUIRE(!frontier.empty()); 

    REQUIRE(frontier.pop().getValue() == 7); 
}

TEST_CASE( "Multiple Items", "[frontier_queue]") {
    frontier_queue<int> frontier; 

    REQUIRE(frontier.empty()); 

    for(size_t i = 0; i < 10; i++) {
        frontier.push(i, 0, i); 
    }
    REQUIRE(!frontier.empty()); 
    
    REQUIRE(frontier.pop().getValue() == 0);
    REQUIRE(frontier.pop().getValue() == 1);
    REQUIRE(frontier.pop().getValue() == 2);
    REQUIRE(frontier.pop().getValue() == 3);
    REQUIRE(frontier.pop().getValue() == 4);
    REQUIRE(frontier.pop().getValue() == 5);
    REQUIRE(frontier.pop().getValue() == 6);
    REQUIRE(frontier.pop().getValue() == 7);
    REQUIRE(frontier.pop().getValue() == 8);
    REQUIRE(frontier.pop().getValue() == 9);

    
}

TEST_CASE( "Equivalent Children Test", "[frontier_queue]") {
    
    frontier_queue<int> frontier; 
    size_t height = 10; 

    REQUIRE(frontier.empty()); 

    for(size_t i = 0; i < height; i++) {
        for(size_t j = 0; j < pow(2, height-i-1); j++) {
            frontier.push(height-i-1, height-i-1, height-i-1); 
        }
    }
    
    REQUIRE(!frontier.empty()); 

    for(size_t i = 0; i < height; i++) {
        for(size_t j = 0; j < pow(2, i); j++) 
            REQUIRE(frontier.pop().getValue() == i);
    }

    REQUIRE(frontier.empty()); 

}


TEST_CASE( "A large number of items", "[frontier_queue]") {

    frontier_queue<int> frontier; 
    size_t heur, cost; 
    srand(time(NULL)); 

    REQUIRE(frontier.empty()); 

    for(size_t i = 0; i < 1000; i++) {
        cost = rand() % 5000 + 1; 
        heur = rand() % 10 + 1; 
        frontier.push(i, cost, heur);   
    }

    REQUIRE(!frontier.empty()); 
    
    size_t count = 0;
    while(!frontier.empty()) {
        frontier.pop(); 
        count++; 
    }

    REQUIRE(count == 1000); 
}