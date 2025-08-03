// Author: Hannah Schmucker

// How to run:
// 	(1) Download the tarball file to your computer
// 	(2) Use the command 'tar -xvzf file.tgz' to download all files on your terminal
// 	(3) Use the command 'pwd' to find your unique home path (eg, mine in /home/u2/*username*)
// 	(4) Complile in the home directory and use './a.out' command to run.
// 	(5) Now you can input the path to the file as "folder/fileName.txt" or "homepath/folder/fileName.txt" to access the four files named:
// 
// 		ideal.txt	malform_1.txt	malform_2.txt	malform_3.txt
// 
// 	(eg of valid paths)     Project3/ideal.txt     or 	/home/u2/*username*/Project3/ideal.txt

// Best way to read: Expand horizontally so that all comments align
// Sources: I used the textbook provided for class (Joel Murach, Mary Delamater -- 
// 		Murach's C++ Programming) with assistance implementing vectors, 
// 		push_back, pop_back, and the sort algorithm. As per the syllabus, I won't cite them.


#include <iostream> 	// Standard header for in/cout
#include <fstream>  	// Standard header for reading files in
#include <iomanip>  	// Used to set precision
#include <sstream> 	// Header for string 'fullLine' which is used to read in lines	
#include <string>   	
#include <vector>   	// Used for vectors to track items with dynamic memory 
#include <algorithm>	// Used for the sort call in Stats
#include <cctype> 	// To catch non-double inputs for numFiles
using namespace std;

// ---------------------------------------------------------------------//
//     		       	  Function Prototypes                           //
// ---------------------------------------------------------------------//

void prompt(int& currentFile, string& name);
void file(string& name,int& numFiles,int& currentFile,vector<double>& fileItems, vector<double>& allItems);
void stats(double& mean, double& median, double& mode, vector<double>& allItems, double& avgMode);
void branch(string outFileName, double mean, double median, double mode, vector<double> allItems, double avgMode);

// ---------------------------------------------------------------------//
//      			Main                                    //
// ---------------------------------------------------------------------//

int main(){
   vector<double> fileItems;												// Track single file elements
   vector<double> allItems;												// Track all file elements
   string name;														// User input file name
   int currentFile = 1; 												// What file you're on
   string numberFiles;
   string outFileName;

   cout << fixed << setprecision(4);											// Fixing output to four decimals
  															// User input for number of files
   cout << endl << "*** Welcome to " << "\033[31m" << "Hannah's " << "\033[0m" << " Data Analyzer ***" << endl;
   int numFiles = 0;

   while(true) {
	cout << "Enter the number of files to read: ";
   	cin >> numberFiles;
   	cout << endl << endl;
	bool allDigits = true;

	for (char c: numberFiles) {										// Check numFiles is not an illegal type
   		if (!(isdigit(c))){
			allDigits = false;
			break;
   		}
   	}
   
  	 if (!allDigits) { 
	   cout << "Please enter a valid number of files." << endl;
	   continue;
   	 }

  	 numFiles = stoi(numberFiles);
   
  	 if (numFiles < 1 ) {											// Test that the number of files is a valid double
		cout << "Please enter a valid number of files." << endl << endl;
		continue;
  	 }
	 break;
   } 

   file(name, numFiles,currentFile, fileItems, allItems);							// Call the function 'file'
   
   double mode = 0;
   double avgMode = 0;
   double median;
   double mean;
   stats(mean, median, mode, allItems, avgMode);								// Call the function 'stats'
   branch(outFileName,mean, median, mode, allItems, avgMode);												// Call the function 'branch'
}

// ---------------------------------------------------------------------//
//      File: Nested in a while loop, this function executes for as     //
//            long as the currentFile is <= (total)numFiles. It begins  //
//            by opening the file, then checking that the file was      //
//            found. Runs two iterations through the file, the first	//
//            to read in lines, the second to read in only doubles.	//
//     	      If lines [count] != doubles [line], then the file will	//
//	      be flagged for illegal content. If not, its values are	//
//	      printed, and added to a vector [totalItems] which 	//
//	      is used in the function Stats.				//
// ---------------------------------------------------------------------//

void file(string& name,int& numFiles,int& currentFile,vector<double>& fileItems, vector<double>& allItems)
{
     while (currentFile <= numFiles) {
	prompt(currentFile, name);
	ifstream inFile(name);													// Declare file variable and open
			
	if(!inFile){														// Check file was opened
       		cout << "File not found. Please try again." << endl << endl;	
     		continue;
	}

     	
     	string fullLine;
	int count = -1;
        inFile.seekg(0, ios::beg);
	while(!inFile.eof()) { 													// Take in all lines
		count = count + 1;
		getline(inFile, fullLine);
		for (char c : fullLine) {
			if (isspace(c)) {break;}
		}
	}

	inFile.clear();														// Clear and reset file (to point to beginning)
	inFile.seekg(0, ios::beg);
	
	double line;
	while (inFile >> line){													// Take in only doubles
		fileItems.push_back(line);
                allItems.push_back(line);
	}
    	
	

       	if (fileItems.size() == 0 || fileItems.size() != count) {								// If file contains no values, non-doubles, or values
	        inFile.clear();													//    not separated by newlines
                inFile.close();													
                fileItems.pop_back();
                allItems.pop_back();
	       	cout << "Not an input file. Illegal content/structure detected. Please try again." << endl << endl;	
	} else {														// Else, the file contains only valid inputs
     		cout << "The list of " << fileItems.size() << " values in file " << name << " is: " << endl;
     		for (int j = 0; j < fileItems.size(); j++)	{cout << fileItems[j] << endl; }
		cout << endl;
		currentFile = currentFile + 1;
	}
     	fileItems.clear();
	inFile.clear(); 
	inFile.close();														// Clear and close file
    }
}


// ---------------------------------------------------------------------//
//      Prompt: Generates the file name prompt.			        //
// ---------------------------------------------------------------------//

void prompt(int& currentFile, string& name)
{
	cout << "Enter the filename for file " << currentFile << ": ";
	cin >> name;
}


// ---------------------------------------------------------------------//
//	Stats: Calculates the mean, median, and mode before outputting 	//
// 		an end of program message.				//
//									//
// ---------------------------------------------------------------------//

void stats(double& mean, double& median, double& mode, vector<double>& allItems, double& avgMode)
{
	sort(allItems.begin(), allItems.end());									// Sort the list
	cout << endl << "*** Summarized Statistics ***" << endl << endl;
	cout << "The orderly sorted list of " << allItems.size() << " values is: " << endl;			// Outprint the list
	for (int i = 0; i < allItems.size(); i++) { cout << allItems[i] << " "; }
	cout << endl << endl;
	
	int totalCount = allItems.size();									// Find median
	if (totalCount % 2 == 0)	{median = (allItems[totalCount / 2 - 1] + allItems[totalCount / 2]) / 2; 
	} else 				{median = allItems[totalCount / 2]; }
	
	double tempMean = 0;											// Find mean
	for(int i = 0; i < totalCount; i++) {tempMean = (allItems[i] + tempMean); }
	mean = tempMean / totalCount ;

											// Find the mode, including the average of all modes if number of occurances is equal
	double max = 1;
	double track = 1;
	mode  = allItems[0];
	vector<double> modes;
	modes.push_back(allItems[0]);
	avgMode = modes[0]; 
		
	for (int i = 1; i < totalCount; i++) {
		if (allItems[i] == allItems[i-1]) {
			track++;
		} else {
			track = 1;
		}
		if (track > max) {
			max = track;
			modes.clear();
			modes.push_back(allItems[i]);
		} else if (track == max && track != 1){
			modes.push_back(allItems[i]);
		}else 	{continue;}
	}
		double sum = 0;
		if (modes.size() > 1) {
			for (int j = 0; j < modes.size(); j++)	{ sum += modes[j]; } 
		avgMode = sum / modes.size();
		} else {
		avgMode = modes[0];
		}

	cout << "The mean is " << mean << endl;
	cout << "The median is " << median << endl;
	cout << "The mode is " << avgMode << endl << endl; 
}

// ---------------------------------------------------------------------//
//                      Project 4 branch                                //
// ---------------------------------------------------------------------//
void branch(string outFileName,double mean, double median, double mode, vector<double> allItems, double avgMode ){

   while(true) {
        cout << "Enter the output filename to save: ";								// Prompt for the file name
        cin >> outFileName;
        cout << endl << endl;
	
        ofstream outFile;
        outFile.open(outFileName, ios:: app);

        if (!outFile.is_open()) {  					  	                                // Check if file was opened
                cout << "The file could not be opened." << endl;
		continue;	
        }
	if(outFileName.length() < 4) {										// Set a condition that requires the file name
		cout << "Please enter a valid file name." << endl;						// to end in .csv and contain at least one character
		continue;
	} else {
		if (outFileName.substr(outFileName.length() - 4) != ".csv") {  
			cout << "Please enter a csv file name (.csv)." << endl;
                	continue;
		}

	}
	
	if (outFile.is_open()) {
		outFile << "The orderly sorted list of " << allItems.size() << " values is: " << endl;           // All statements to write into file
		for (int i = 0; i < allItems.size() - 1; i++) {
                	outFile << allItems[i] << ",";
          	}
   		outFile << allItems[allItems.size() - 1];
		outFile << endl << endl;
        	outFile << "mean," << mean << endl;
       		outFile << "median," << median << endl;
        	outFile << "mode," << avgMode << endl << endl;
        	outFile.close();

		cout << "*** File " << outFileName << " has been written to disk ***" << endl;
		cout << "*** Goodbye. *** """ << endl << endl;
		break;
	}
   }	
}
