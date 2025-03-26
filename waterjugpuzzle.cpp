/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Lucas Vanzelli and James Schorle
 * Date        : 10/12/2024
 * Description : Solves the water jug puzzle.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
using namespace std;

// Struct to represent state of water in the jugs.
struct State {
  int a, b, c;
  string directions;
  State* parent;
  bool visited;

  State() : a{ 0 }, b{ 0 }, c{ 0 }, directions{ "" }, parent{ nullptr }, visited{ false } {}

  State(int _a, int _b, int _c, string _directions)
    : a{ _a }, b{ _b }, c{ _c }, directions{ _directions }, parent{ nullptr }, visited{ false } {}
  // String representation of state in tuple form.
  string to_string() {
    ostringstream oss;
    oss << "(" << a << ", " << b << ", " << c << ")";
    return oss.str();
  }
};

// checks if a pour from jug_from to jug_to is possible
bool check_pour(int jug_from, int jug_to, int to_cap) {
  if (jug_from == 0 || jug_to == to_cap) {
    return false;
  }
  else { 
    return true; }
}

// returns a queue of all possible options of pouring, given the current jug states
queue<State> pour_options(State current, State cap, State**& array, queue<State> queue) {
  int num_gallons = 0;
  // from C to A
  if (check_pour(current.c, current.a, cap.a)) {
    State ca(current.a, current.b, current.c, "");
    ca.parent = &array[current.a][current.b];
    while (ca.c > 0 && ca.a < cap.a) {
      ca.c--;
      ca.a++;
      num_gallons++;
    }
    if (!(array[ca.a][ca.b].visited)) {
      if(num_gallons == 1){
        //case for a single gallon
        ca.directions = "Pour " + to_string(num_gallons) + " gallon from C to A. ";
        queue.push(ca);
      } else {
        ca.directions = "Pour " + to_string(num_gallons) + " gallons from C to A. ";
        queue.push(ca);
      }
    }
  }

  // from B to A
  if (check_pour(current.b, current.a, cap.a)) {
    State ba(current.a, current.b, current.c, "");
    ba.parent = &array[current.a][current.b];
    num_gallons = 0;
    while (ba.b > 0 && ba.a < cap.a) {
      ba.b--;
      ba.a++;
      num_gallons++;
    }
    if (!(array[ba.a][ba.b].visited)) {
      if(num_gallons == 1){
        //case for a single gallon
        ba.directions = "Pour " + to_string(num_gallons) + " gallon from B to A. ";
        queue.push(ba);
      } else {
        ba.directions = "Pour " + to_string(num_gallons) + " gallons from B to A. ";
        queue.push(ba);
      }
    }
  }

  // from C to B
  if (check_pour(current.c, current.b, cap.b)) {
    State cb(current.a, current.b, current.c, "");
    cb.parent = &array[current.a][current.b];
    num_gallons = 0;
    while (cb.c > 0 && cb.b < cap.b) {
      cb.c--;
      cb.b++;
      num_gallons++;
    }
    if (!(array[cb.a][cb.b].visited)) {
      if(num_gallons == 1){
        //case for a single gallon
        cb.directions = "Pour " + to_string(num_gallons) + " gallon from C to B. ";
        queue.push(cb);
      } else {
        cb.directions = "Pour " + to_string(num_gallons) + " gallons from C to B. ";
        queue.push(cb);
      }
    }
  }

  // from A to B
  if (check_pour(current.a, current.b, cap.b)) {
    State ab(current.a, current.b, current.c, "");
    ab.parent = &array[current.a][current.b];
    num_gallons = 0;
    while (ab.a > 0 && ab.b < cap.b) {
      ab.a--;
      ab.b++;
      num_gallons++;
    }

    if (!(array[ab.a][ab.b].visited)) {
      if(num_gallons == 1){
        //case for a single gallon
        ab.directions = "Pour " + to_string(num_gallons) + " gallon from A to B. ";
        queue.push(ab);
      } else {
        ab.directions = "Pour " + to_string(num_gallons) + " gallons from A to B. ";
        queue.push(ab);
      }
    }
  }

  // from B to C
  if (check_pour(current.b, current.c, cap.c)) {
    State bc(current.a, current.b, current.c, " ");
    bc.parent = &array[current.a][current.b];
    num_gallons = 0;
    while (bc.b > 0 && bc.c < cap.c) {
      bc.b--;
      bc.c++;
      num_gallons++;
    }
    if (!(array[bc.a][bc.b].visited)) {
      if(num_gallons == 1){
        //case for a single gallon
        bc.directions = "Pour " + to_string(num_gallons) + " gallon from B to C. ";
        queue.push(bc);
      } else {
        bc.directions = "Pour " + to_string(num_gallons) + " gallons from B to C. ";
        queue.push(bc);
      }
    }
  }

  // from A to C
  if (check_pour(current.a, current.c, cap.c)) {
    State ac(current.a, current.b, current.c, "");
    ac.parent = &array[current.a][current.b];
    num_gallons = 0;
    while (ac.a > 0 && ac.c < cap.c) {
      ac.a--;
      ac.c++;
      num_gallons++;
    }
    if (!(array[ac.a][ac.b].visited)) {
      if(num_gallons == 1){
        //case for a single gallon
        ac.directions = "Pour " + to_string(num_gallons) + " gallon from A to C. ";
        queue.push(ac);
      } else {
        ac.directions = "Pour " + to_string(num_gallons) + " gallons from A to C. ";
        queue.push(ac);
      }
    }
  }
  return queue;
}

// takes in two states, a current state and a goal state and uses breadth first searches until curr reaches the goal state
void my_alg(State caps, State goal) {

  //creates a 2D array with A+1 rows and B+1 columns
  //initializes every value in this array to false
  State** array = new State * [caps.a + 1];
  for (int i = 0; i < caps.a + 1; i++) {
    array[i] = new State[caps.b + 1];
    fill(array[i], array[i] + (caps.b + 1), State(0, 0, 0, ""));
  }

  //sets the initial sate (0,0,C)
  State initial(0, 0, caps.c, "Initial State. ");
  array[initial.a][initial.b] = initial;

  //queue the stores pours to explor
  queue<State> alg_queue;

  State curr(initial.a, initial.b, initial.c, " ");
  curr.parent = nullptr;
  alg_queue.push(initial);

  //begins the BFS algorithm
  while (!alg_queue.empty()) {
    curr = alg_queue.front();
    alg_queue.pop();

    //checks if the current jug state is equal to the desired goal state
    if (curr.to_string() == goal.to_string()) {
      //backtrack
      vector<State> path_vector;
      while (curr.parent != nullptr) {
        path_vector.push_back(curr);
        curr = *curr.parent;
      }

      //print vector
      cout << "Initial state. (0, 0, " << caps.c << ")" << endl;
      for (int i = path_vector.size() - 1; i >= 0; --i) {
        cout << path_vector[i].directions << path_vector[i].to_string() << endl;
      }

      //deletes 2D array
      for(int i = 0; i < caps.a + 1; i++){
        delete [] array[i];
      }
      delete [] array;
      return;
    }else {
      //finds every possible pour given the starting point of the current state
      array[curr.a][curr.b] = curr;
      array[curr.a][curr.b].visited = true;
      alg_queue = pour_options(curr, caps, array, alg_queue);
    }
  }

  //case for no solution
  if (alg_queue.empty()) {
    for(int i = 0; i < caps.a + 1; i++){
        delete [] array[i];
      }
    delete [] array;
    cout << "No solution." << endl;
  }
}

//checks the input parameters to ensure theyre valid
bool check_int(int argc, char* const argv[]) {
  if (argc != 7) {
    cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
    return false;
  }

  istringstream iss1;
  int n;
  char letter = 'A';

  //check capacity paramters
  for (int i = 1; i <= 3; i++) {
    iss1.clear();
    iss1.str(argv[i]);
    if (!(iss1 >> n) || n <= 0) {
      //found stat_cast through: https://www.geeksforgeeks.org/static_cast-in-cpp/
      cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << static_cast<char>(letter + i - 1) << "." << endl;
      return false;
    }
  }

  //check goal paramters
  for (int i = 4; i <= 6; i++) {
    iss1.clear();
    iss1.str(argv[i]);
    if (!(iss1 >> n) || n < 0) {
      //found stat_cast through: https://www.geeksforgeeks.org/static_cast-in-cpp/
      cerr << "Error: Invalid goal '" << argv[i] << "' for jug " << static_cast<char>(letter + i - 4) << "." << endl;
      return false;
    }
  }

  return true;
}

int main(int argc, char* const argv[]) {
  //declaring iss and ensuring each parameter is valid
  istringstream iss;
  //calls check_int
  if (!(check_int(argc, argv))) {
    return 1;
  }
  //declaring and assigning each int paramenter to a variable
  int a, b, c, d, e, f;
  for (int i = 1; i < argc; i++) {
    iss.str(argv[i]);
    //found switch and case statements through: https://www.w3schools.com/cpp/cpp_switch.asp
    switch (i) {
    case 1:
      iss >> a;
      break;
    case 2:
      iss >> b;
      break;
    case 3:
      iss >> c;
      break;
    case 4:
      iss >> d;
      break;
    case 5:
      iss >> e;
      break;
    case 6:
      iss >> f;
      break;
    }
    iss.clear();
  }

  //checks if the goal does not exceed the capacity for jug A
  if (d > a) {
    cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
    return 1;
  }
  //checks if the goal does not exceed the capacity for jug B
  if (e > b) {
    cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
    return 1;
  }
  //checks if the goal does not exceed the capacity for jug C
  if (f > c) {
    cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
    return 1;
  }
  //checks if the goal is achievable given the starting condition that jug C
  //contains all fluid initially
  if ((d + e + f) != c) {
    cerr << "Error: Total gallons in goal state must be equal to the capacity "
      "of jug C."
      << endl;
    return 1;
  }
  // At this point we've ensured there are no errors in the conditions
  // must go from [0,0,c] to [d,e,f] given jug caps of [a,b,c]
  State cap(a, b, c, "Caps of each jug.");
  State goal(d, e, f, "Goal state.");

  //case if initial state already equals goal state
  if (goal.a == 0 && goal.b == 0 && goal.c == cap.c) {
    cout << "Initial state. " << goal.to_string() << endl;
    return 0;
  }
  my_alg(cap, goal);
  return 0;
}
