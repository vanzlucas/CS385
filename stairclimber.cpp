/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Lucas Vanzelli
 * Date        : 10/2/2024
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>


using namespace std;

vector<int> stair;
vector<vector<int>> ways;

vector<vector<int>> get_ways(int num_stairs) {
    //Returns a vector of vectors of ints representing the different combinations of ways to 
    //climb num_stairs stairs, moving up either 1, 2, or 3 stairs at a time.

    //Base Case
    if(num_stairs <= 0){
        return {{}};
    }

    //Nested vector that will hold every possible way up the stairs
    vector<vector<int>> ways;

    //Followed the canvas python sudo code
    for(int i = 1; i <=3 ; i++){
        if(num_stairs >= i){
            vector<vector<int>> result = get_ways(num_stairs - i);
            for(unsigned int j = 0; j < result.size(); j++){
            result[j].insert(result[j].begin(), i);
            ways.push_back(result[j]);
            }   
        }
    }

    return ways;
}


void display_ways(const vector< vector<int>> &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.

    //Sets the first element of ways to a vector. The sum of the elements in this vector should be the number of stairs. 
    vector<int> first_element = ways[0];
    
    //Checks for the case in which there is only 1 stair
    if(first_element.size() == 1){
        cout << "1 way to climb 1 stair." << endl;
    
    //Else it finds the sum of the elements in the vector  
    } else {
        int total = 0;
        for(unsigned int i = 0; i < first_element.size(); i++){
            total += first_element[i];
        }
        
        //Prints out the first message
        cout << ways.size() << " ways to climb " << total << " stairs." << endl;
    }

    //Finds the total number of ways you can climb the stairs. Then finds how many digits that number is.
    int number_of_ways = ways.size();
    int counter = 0;
    while(number_of_ways != 0){
        number_of_ways = number_of_ways/10;
        counter++;
    }
    
    //Loops this each element of the nested vector and prints it 
    int counter2 = 1; 
     for (auto &way : ways) {
        //setw is used to account for formatting
        cout << setw(counter) << counter2;
        cout << ". [";
        counter2++;
        int counter3 = 0;
        for (int step : way) {
            int count_of_ints = way.size() - 1;
            //Will only print if it is not printing the last element in that way
            if(counter3 < count_of_ints){
                cout << step << ", ";
                counter3++;
            } else {
                //Will only if it is the last element in that way. In this case, it will not include the comma. 
                cout << step;
            }
        }
        cout << "]" << endl;
    }
}


int main(int argc, char * const argv[]) {

    int n;
    istringstream iss;

    //Case for if the user does not input any agruments
    if(argc <= 1){
        cerr << "Usage: ./stairclimber <number of stairs>" << endl;
        return 1;
    }

    //Case for if the user inputs more than one argument
    if(argc >= 3){
        cerr << "Usage: ./stairclimber <number of stairs>" << endl;
        return 1;
    }

    //Case for if the user inputs an arument that is not an integer
    iss.str(argv[1]);
    if(!(iss >> n)){
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }

    //Case for if the user input an argyment that is not a positive integer
    if(n <= 0){
        cout << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }

   //Function calls 
    display_ways(get_ways(n));




}
