/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Lucas Vanzelli
 * Date        : 9/13/2024
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
    // Can use the pointer as the name of the array 
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.

    cout << endl << "Number of primes found: " << num_primes_ << endl;
    cout << "Primes up to " << limit_ << ":" << endl;

    const int max_prime_width = num_digits(max_prime_);
    const int primes_per_row = 80 / (max_prime_width + 1);

    int count = 0;
    //If the number of primes in the array is less that maximum primes per row
    if(num_primes_ < primes_per_row){
        //Loop through max_prime to print out True values
        for(int i = 2; i < limit_ + 1; i++){
            //If the index is = to max_prime
            if(max_prime_ == i){
                //No space will be printed after the number
                cout << i;
            }
            //Else if the value at index i is True (indicating that it is prime)
            else if (is_prime_[i]) { 
                //A space will be printed after the number
                cout << i << " "; 
            }
        }
    //Else the number of primes in the array must be greater than the number of maximum primes per row
    } else {
        //Loop through max_prime to print out True values
        for(int i = 2; i < limit_ + 1; i++){
            //If this is the last prime that can be printed on this row
            if(count == primes_per_row - 1){
                //if the last prime that can be printed on this row is the max_prime_
                if(max_prime_ == i){
                    //print the last prime
                    cout << setw(max_prime_width) << i;
                //else if the value at i is true (signifying it is prime) it will print the index and endl.
                //setting the count to 0 allows you to start counting the number of primes on the new line. 
                } else if (is_prime_[i]) {
                    //print th elast prime and then end the line
                    cout << setw(max_prime_width) << i << endl; 
                    count = 0;
                }
            //Else the # of primes printed out does not equal the maximum primes per row
            } else { 
                //If the index is equal to the maximum prime number in the array, it will print the prime without a space after. 
                if(max_prime_ == i){
                    cout << setw(max_prime_width) << i;
                //If the index is not equal to the maximum prime number in the array, it will print the prime with a space after.
                //Then it will add 1 to the count to track the number of pritned primes.
                } else if (is_prime_[i]) {
                    cout << setw(max_prime_width) << i << " "; 
                    count++;
                }
            }
        }
    }
}

//Performs the sieve algorithm
void PrimesSieve::sieve() {
    //Array initalization
    for(int i = 2; i < limit_ + 1; i++){
        is_prime_[i]= true;
    }
    is_prime_[0] = false;
    is_prime_[1] = false;

    //Sieve algorithm
    for(int i = 2; i <= sqrt(limit_); i ++){
        if(is_prime_[i]){
            for(int j = (i * i); j <= limit_; j = j + i){
                is_prime_[j] = false;
            }
        }
    }

    //Tracks the number of prime numbers in the array and the maximum prime number in the array.
    num_primes_ = 0;
    for(int i = 2; i < limit_ + 1; i++){
        if(is_prime_[i]){
            num_primes_ += 1;
            max_prime_ = i;
        }
    }
}

//Divides the input by 10 continously until it reach 0 to track the number of digits in the input.
int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int counter = 0;
    while(num != 0){
        num = num/10;
        counter++;
    }
    return counter;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    //Uses your the PrimesSieve class to produce the desired output.
    PrimesSieve sieve(limit);
    sieve.display_primes();


    return 0;
}
