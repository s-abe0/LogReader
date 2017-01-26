
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <unistd.h>

using namespace std;

/*
	A real time log reader program. File to read is passed as a cli argument.
	Continually reads from the log file until program is closed.
	
	LogReader v1.0
	Written by redbull
*/

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		cout << "Error: Invalid number of arguments\nUsage: ./LogReader [filename or path]\n";
		exit(1);
	}
	
	ifstream logFile(argv[1]);
	
	if(!logFile)
	{
		cout << "Error: Invalid path or file does not exist\n";
		exit(1);
	}
	
	
	int pos, length = 0;
	string line;
	
	/*
		Main loop of the program. Continually opens the file, seeks to last position left off,
		and reads new content (if there is any). After reading, file is closed and program 
		sleeps for a few seconds to allow content to build.
	*/
	while(true)                            
	{
		if(!logFile.is_open())             // Open the file if it is closed
			logFile.open(argv[1]);
		
		pos = length;                       
	
		logFile.seekg(0, logFile.end);
		length = logFile.tellg();           // Get length of file
		logFile.seekg(pos, logFile.beg);    // Begin reading at end of previous file size
		
		while(logFile)                      // Read new entries of the file
		{
			getline(logFile, line);
			if(line == "")                  // If the line contains nothing (no new content yet), don't print anything
				continue;
			else
				cout << line << endl;
		}
		
		logFile.close();                    // Close the file after reading
		sleep(5);                           // Sleep for a while until next read
	}	
}




