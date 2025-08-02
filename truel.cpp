// Author: Hannah Schmucker

// Note for while running: press 'enter' twice when prompted to press 'enter'
// Best way to read: extend as far horizontally as possible

// Sources -- (besides snippets from project outline)
//	(1) Posted a question about the test drivers to Piazza, used pseudocode to format four of my drivers.
//	(2) Used ChatGPT for help as follows, "How do I print red text in c++ for only certain parts of a string". 
//			  Answer provided code "std::cout << "\033[31m" << "this is red text" << "\033[0m"; ".
//			  Using this I took the portions  "\033[31m" and "\033[0m" to integrate into my code.
//			  Normally I would only use ChatGPT as a last resort, but since red text wasn't required I just needed a quick answer.


#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <ctime>
using namespace std;


// ********** Constants & Variables ****************
const double runs = 10000;
const int a_accuracy = 33;
const int b_accuracy = 50;
const int c_accuracy = 100;

bool A_alive = true, B_alive = true, C_alive = true;

// ********** Function Prototypes ****************

bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);
void Aaron_shoots1(bool& B_alive, bool& C_alive);
void Bob_shoots(bool& A_alive, bool& C_alive);
void Charlie_shoots(bool& A_alive, bool& B_alive);
void Aaron_shoots2(bool& B_alive, bool& C_alive);
void strategy1(int runs, double& a_wins, double& b_wins, double& c_wins);
void strategy2(int runs, double& a_wins, double& b_wins, double& c_wins);

// ********** Test Driver Prototypes **************
void test_at_least_two_alive(void);
void test_Aaron_shoots1(void);
void test_Bob_shoots(void);
void test_Charlie_shoots(void);
void test_Aaron_shoots2(void);


// ******** Main ****************************
int main()
{
    // initializing random number generator
        srand((unsigned)time(0));

        cout << endl << "*** Welcome to Hannah's Truel of the Fates Simulator ***" << endl << endl;

	// calling test drivers
        test_at_least_two_alive();
	test_Aaron_shoots1();
	test_Bob_shoots();
	test_Charlie_shoots();
	test_Aaron_shoots2();	
        
	// call Strategy1
	double a_wins = 0, b_wins = 0, c_wins = 0;
        cout << endl << "Ready to test strategy 1 (run 10000 times): " << endl;
        cout << "Press Enter to continue...";
        cin.ignore().get();

        strategy1(runs, a_wins, b_wins, c_wins); //                     --- Source (2) used for cout statements --- 
        cout << "Aaron won " << "\033[31m" << a_wins << "/10000 truels" << "\033[0m" << " or " << "\033[31m" << a_wins / runs * 100 << "%" << "\033[0m" << endl;
        cout << "Bob won " << "\033[31m" << b_wins << "/10000 truels" << "\033[0m" << " or " << "\033[31m" << b_wins / runs * 100 << "%"<< "\033[0m" << endl;
        cout << "Charlie won " << "\033[31m" << c_wins << "/10000 truels" << "\033[0m" << " or " << "\033[31m" << c_wins / runs * 100 << "%" << "\033[0m" << endl;
        double strat1_a_wins = a_wins;

        // call Stategy2
        a_wins = 0, b_wins = 0, c_wins = 0;  // Resetting wins

        cout << endl << "Ready to test strategy 2 (run 10000 times): " << endl;
        cout << "Press Enter to continue...";
        cin.ignore().get();

        strategy2(runs, a_wins, b_wins, c_wins); //		        --- Source (2) used for cout statements --- 
        cout << "Aaron won " << "\033[31m" << a_wins << "/10000 truels" << "\033[0m" << " or " << "\033[31m" << a_wins / runs * 100 << "%" << "\033[0m" << endl;
        cout << "Bob won " << "\033[31m" << b_wins << "/10000 truels" << "\033[0m" << " or " << "\033[31m" << b_wins / runs * 100 << "%"<< "\033[0m" << endl;
        cout << "Charlie won " << "\033[31m" << c_wins << "/10000 truels" << "\033[0m" << " or " << "\033[31m" << c_wins / runs * 100 << "%" << "\033[0m" << endl;
        double strat2_a_wins = a_wins;

        cout << endl;

	// outputting best strategy for Aaron 				--- Source (2) used for cout statements ---
        if (strat1_a_wins > strat2_a_wins){
                cout << "Strategy " << "\033[31m" << "1" << "\033[0m" << " is better than strategy " << "\033[31m" << "2" << "\033[0m" << "." << endl;
        } else {
                cout << "Strategy " << "\033[31m" << "2" << "\033[0m" << " is better than strategy " << "\033[31m" << "1" << "\033[0m" << "." << endl;
        }
   	
	cout << endl << endl;
        return 0;
}

// ********* Implemented Functions ******************************
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive){
        int count = 0;
        if (A_alive) count++;
        if (B_alive) count++;
        if (C_alive) count++;

        return (count >= 2);
}


void Aaron_shoots1(bool& B_alive, bool& C_alive){
	int shoot_target_result = rand() % 100;
        if (C_alive){				// Logic is simple + repetitive : If (most lethal player) is alive and rand < accuracy then hit
         if (shoot_target_result < a_accuracy) { C_alive = false;}
        }
        else if (B_alive){
          if (shoot_target_result < a_accuracy){ B_alive = false;}
        }
}


void Bob_shoots(bool& A_alive, bool& C_alive){
	int shoot_target_result = rand() % 100;
        if (C_alive){
          if (shoot_target_result < b_accuracy){ C_alive = false; } 
        }
        else if (A_alive){
          if (shoot_target_result < b_accuracy){ A_alive = false; }
        }
}


void Charlie_shoots(bool& A_alive, bool& B_alive){
        if (B_alive)      { B_alive = false; }          
        else if (A_alive) { A_alive = false; }
}


void Aaron_shoots2(bool& B_alive, bool& C_alive){
	int shoot_target_result = rand() % 100;
        if ((!C_alive && B_alive) || (C_alive && !B_alive)) { //Ensures that it's past the first round, in which Aaron misses.
        
	if (C_alive){
          if (shoot_target_result < a_accuracy) { C_alive = false;}
        }
        else if (B_alive){
          if (shoot_target_result < a_accuracy) { B_alive = false;}
        }
        }
}

// ********* Strategy1 & Strategy2 ******************************

void strategy1(int runs, double& a_wins, double& b_wins, double& c_wins){
        for (int i=0; i< runs; i++) {                                   //Simulates 10,000 rounds
         bool A_alive = true;                                           //Resets all bool values to true
         bool B_alive = true;
         bool C_alive = true;

          while (at_least_two_alive(A_alive,B_alive,C_alive)){          //Simulates a single truel
           if (A_alive){  Aaron_shoots1(B_alive, C_alive);  }             //Aaron shoots first
           if (B_alive){  Bob_shoots(A_alive, C_alive);     }             //Bob shoots second
           if (C_alive){  Charlie_shoots(A_alive, B_alive); }             //Charlie shoots last
          }
          if (A_alive)     { a_wins++; }                                //Totaling the number of wins
          else if(B_alive) { b_wins ++;}
          else             { c_wins ++;}
       }
}

void strategy2(int runs, double& a_wins, double& b_wins, double& c_wins){
         for (int i=0; i< runs; i++) {
         bool A_alive = true;
         bool B_alive = true;
         bool C_alive = true;

          while (at_least_two_alive(A_alive,B_alive,C_alive)){
           if (A_alive){  Aaron_shoots2(B_alive, C_alive);  }           //here is where strategy 1 and 2 differ
           if (B_alive){  Bob_shoots(A_alive, C_alive);     }
           if (C_alive){  Charlie_shoots(A_alive, B_alive); }
          }
          if (A_alive)     { a_wins++; }                                //Totaling the number of wins
          else if(B_alive) { b_wins ++;}
          else             { c_wins ++;}
       }
}

// ********* Test Drivers *********************************
void test_at_least_two_alive(void){
        cout << "Unit Testing 1: Function - at_least_two_alive()\n";

        cout << "	Case 1: Aaron alive, Bob alive, Charlie alive\n";
        assert(true == at_least_two_alive(true, true, true));
        cout << "		Case passed ...\n";

        cout << "	Case 2: Aaron dead, Bob alive, Charlie alive\n";
        assert(true == at_least_two_alive(false, true, true));
        cout << "		Case passed ...\n";

        cout << "	Case 3: Aaron alive, Bob dead, Charlie alive\n";
        assert(true == at_least_two_alive(true, false, true));
        cout << "		Case passed ...\n";

        cout << "	Case 4: Aaron alive, Bob alive, Charlie dead\n";
        assert(true == at_least_two_alive(true, true, false));
        cout << "		Case passed ...\n";

        cout << "	Case 5: Aaron dead, Bob dead, Charlie alive\n";
        assert(false == at_least_two_alive(false, false, true));
        cout << "		Case passed ...\n";

        cout << "	Case 6: Aaron dead, Bob alive, Charlie dead\n";
        assert(false == at_least_two_alive(false, true, false));
        cout << "		Case passed ...\n";

        cout << "	Case 7: Aaron alive, Bob dead, Charlie dead\n";
        assert(false == at_least_two_alive(true, false, false));
        cout << "		Case passed ...\n";

        cout << "	Case 8: Aaron dead, Bob dead, Charlie dead\n";
        assert(false == at_least_two_alive(false, false, false));
        cout << "		Case passed ...\n";

        cout << "	Press Enter to continue...";
        cin.ignore().get();
}

void test_Aaron_shoots1(void){ //					--- Source (1) for general format of all subsequent test drivers --- 
	cout << "Unit Testing 2: Function Aaron_shoots1(Bob_alive, Charlie_alive)\n";
	bool b = true;
	bool c = true;
	cout << "	Case 1: Bob alive, Charlie alive\n";
	Aaron_shoots1(b,c);
	cout << "		Aaron is shooting at Charlie\n";

	 b = false;
	 c = true;
	cout << "	Case 2: Bob dead, Charlie alive\n";
        Aaron_shoots1(b,c);
        cout << "		Aaron is shooting at Charlie\n";

	 b = true;
	 c = false;
	cout << "	Case 3: Bob alive, Charlie dead\n";
        Aaron_shoots1(b,c);
        cout << "		Aaron is shooting at Bob\n";

	cout << "	Press Enter to continue...";
        cin.ignore().get();
}

void test_Bob_shoots(void){
	cout << "Unit Testing 3: Function Bob_shoots(Aaron_alive, Charlie_alive)\n";
	bool a = true;
	bool c = true;
        cout << "	Case 1: Aaron alive, Charlie alive\n";
        Bob_shoots(a, c);
        cout << "		Bob is shooting at Charlie\n";

	 a = false;
	 c = true;
        cout << "	Case 2: Aaron dead, Charlie alive\n";
        Bob_shoots(a, c);
        cout << "		Bob is shooting at Charlie\n";

	 a = true;
	 c = false;
        cout << "	Case 3: Aaron alive, Charlie dead\n";
        Bob_shoots(a, c);
        cout << "		Bob is shooting at Aaron\n";

	cout << "	Press Enter to continue...";
        cin.ignore().get();
}

void test_Charlie_shoots(void){
	cout << "Unit Testing 4: Function Charlie_shoots(Aaron_alive, Bob_alive)\n";
	
	bool a = true;
	bool b = true;
        cout << "	Case 1: Aaron alive, Bob alive\n";
        Charlie_shoots(a,b);
        cout << "		Charlie is shooting at Bob\n";

	 a = false;
	 b = true;
        cout << "	Case 2: Aaron dead, Bob alive\n";
        Charlie_shoots(a,b);
        cout << "		Charlie is shooting at Bob\n";

	 a = true;
	 b = false;
        cout << "	Case 3: Aaron alive, Bob dead\n";
        Charlie_shoots(a, b);
        cout << "		Charlie is shooting at Aaron\n";
	
	cout << "	Press Enter to continue...";
        cin.ignore().get();
}

void test_Aaron_shoots2(void){
	cout << "Unit Testing 5: Function Aaron_shoots2(Bob_alive, Charlie_alive)\n";

	bool b = true;
	bool c = true;
        cout << "	Case 1: Bob alive, Charlie alive\n";
        Aaron_shoots2(b,c);
        cout << "		Aaron intentionally misses his first shot\n";
	cout << "		Both Bob and Charlie are alive.\n";

	 b = false;
	 c = true;
        cout << "	Case 2: Bob dead, Charlie alive\n";
        Aaron_shoots2(b, c);
        cout << "		Aaron is shooting at Charlie\n";

	 b = true;
	 c = false;
        cout << "	Case 3: Bob alive, Charlie dead\n";
        Aaron_shoots2(b, c);
        cout << "		Aaron is shooting at Bob\n";

        cout << "	Press Enter to continue...";
        cin.ignore().get();
}
