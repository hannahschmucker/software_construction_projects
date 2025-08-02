// Author: Hannah Schmucker
// Best way to read code: I have fairly long comments, so reading horizontally expanded is best for clear code alignment.

// I used stackoverflow for minor assistance with C++ formatting;
// 	(1)bold print --> MemberProfile, K. (2015, May 2). String - bold output in C++ - stack overflow. StackOverflow. https://stackoverflow.com/questions/29997096/bold-output-in-c
// 	(2)left-align --> MemberProfile, B. (2014, December 28). C++ table alignment - cout and IOMANIP - stack overflow. StackOverflow. https://stackoverflow.com/questions/27679569/c-table-alignment-cout-and-iomanip  
//	(3)resolve issues with "$"  placement --> MemberProfile, K. (2015, May 2). String - bold output in C++ - stack overflow. StackOverflow. https://stackoverflow.com/questions/29997096/bold-output-in-c

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{

    // prompt the user and verify that all input is valid.
	double balance;
	cout <<  "Loan Amount: ";
       	cin >> balance;	
		
		// Invalid Loan
        	if (balance <= 0 || cin.fail())
        	{
                  cout << "Error: Invalid Loan" << endl << endl ;
                  return 0;
        	}
		
	double  rate;
	cout << "Interest Rate (% per year): ";
	cin >> rate; 

        	if (rate < 0 || cin.fail())
        	{
                  cout << "Error: Invalid Interest Rate." << endl << endl;
                  return 0;
        	}

	double  payment;
	cout << "Monthly Payments: ";
	cin >> payment;

            if (payment <= 0 || cin.fail())
            {
                cout << "Error: Invalid payment." << endl << endl;
                return 0;
            }
    
        	if ((balance * (rate / 12 * 0.01)) > payment)
        	{
                  cout << "Error: Insufficient payment." << endl << endl;
                  return 0;
        	}

	double down_payment;
	cout << "(Optional) Down Payment: ";
	cin >> down_payment;
       	cout << endl << endl;

		// Invalid down payment
		if (down_payment < 0 || cin.fail()) 
		{
		  cout << "Error: Invalid down payment." << endl << endl;
		  return 0;
		}
		if (down_payment > balance) 
		{
		  cout << "Error: Just pay off the loan, silly." << endl << endl;
		  return 0;
		}





    // amortization table and month zero entry
	
	cout << "***********************************************************************" << endl;
	cout << "	                Amortization Table " << endl;	
	cout << "***********************************************************************" << endl;
	cout << left 
		<< setw(12) << "Month" 			// source(2) for setw(), which informed all subsequent use of setw()
		<< setw(12) << "Balance"
		<< setw(12) << "Payment" 
		<< setw(12) << "Rate" 
		<< setw(12) << "Interest" 
		<< setw(12) << "Principal" << endl;
	
	cout << fixed << setprecision(2) << left 
		<< setw(12) << "0"	
                << "$" << setw(12) << balance		// source(3) for "$" which informed all subsequent use of "$"
                << setw(12) << "N/A"
                << setw(12) << "N/A"
                << setw(12) << "N/A"
                << setw(12) << "N/A" << endl;


    // variables && rate conversion from annual to months

    double monthly_rate = rate / 12.0;    						// monthly interest rate (as it appears on the table)
	int month = 0;
	double interest;
	double principal;
	double total_interest = 0;
	balance = balance - down_payment;

	while((balance * (1 + 0.01 * monthly_rate)) > payment)				// produces output til balance < payment
	{
	 month = month + 1;	 							// tracking months
	 
	 interest = (balance * (1 + 0.01 * monthly_rate)) - balance; 
	 total_interest += interest; 							// calculating and tracking interest
		
	 balance = (balance * (1 + 0.01 * monthly_rate)) - payment; 			// balance tracking after interest is applied and monthly payment made
	 principal = payment - interest;			    			// principal amount
	
	 cout << fixed << setprecision(2) << left					// output statement for each month
		<< setw(12) << month
		<< "$" << setw(12) << balance 
		<< "$" << setw(12) << payment 
		<< setw(12) << monthly_rate 
		<< "$" << setw(12) << interest 
		<< "$" << setw(12) << principal << endl; 
	}


	
    // the final output, where balance < payment
	month = month + 1;
	double final_balance = balance * (1 + 0.01 * monthly_rate);
	cout << fixed << setprecision(2) << left 
		<< setw(12) << month	
	        << "$" << setw(12) << "0.00"
       	        << "$" << setw(12) << final_balance
		<< setw(12) << monthly_rate
 		<< "$" << setw(12) << (final_balance - balance)
		<< "$" << setw(12) << balance << endl;

	total_interest = total_interest + (final_balance - balance); 



	
    // finally, the output of total months and total interest paid.
	cout << "***********************************************************************" << endl <<  endl;
		
	char escape_character = 27;			// Source(1) for escape_character && [1m / [0m formatting
	if (month != 1) 
	{
	cout << "It takes " << escape_character 	
		<< "[1m" << month << escape_character << "[0m" 
		<< " months to pay off the loan." << endl;
	} else
	{
	cout << "It takes " << escape_character
                << "[1m" << month << escape_character << "[0m"
                << " month to pay off the loan." << endl;
	}
	cout << "Total interest paid is: " << escape_character 
		<< "[1m" << "$" << total_interest << escape_character << "[0m" << endl << endl;
}

