#include <iostream>
#include <vector>
#include <string>
#include <fstream> //For ifstream and ofstream (reading files)

using namespace std;

//This function reads the file and put the values (lines) into a vector
string line_Get(){
	ifstream inFile("datasets/smhi-opendata_Visby.csv");
	string line;
	for (int lineno = 0; getline(inFile, line); lineno++){
		if ( lineno > 10){ //can change to obtain either the firts 10 or greater liner depending on what's useful
			cout << line << endl;
		}
	}
	
	inFile.close();

//	return lbsvec;
}




