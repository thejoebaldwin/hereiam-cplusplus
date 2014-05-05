#include <string>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;


string command(char*);


string command(char* cmd)
{

	FILE *fp;
	int status;
	char path[1035];
        //open the command for reading
	fp = popen(cmd, "r");
        if (fp == NULL)
	{
	 printf("Failed to run command\n");
	 exit;
	}
        string output = "";
        while (fgets(path, sizeof(path) - 1, fp) != NULL)
	{

	 output = path;
        }
        return output;
}

int main()
{
                char* addressCommand = "ifconfig eth0 | grep 'inet addr' | cut -d: -f2";
                string address = command(addressCommand);
		int spaceIndex = 0;
		for (int i = 0; i < address.length();i++)
		{
			if (address[i] == ' ')
			{
				spaceIndex = i;
				address  = address.substr(0, spaceIndex);
				break;
			}

		}
		for (int i = 0; i < address.length();i++)
		{
			if (address[i] == '.')
			{
			  address[i] = '_';
			}
		}
                char* serialCommand = "tail /proc/cpuinfo -n 1";	
                string serial =  command(serialCommand);
                for (int i = 0; i < serial.length(); i++)
                {
			if (serial[i] == ' ')
			{
				spaceIndex = i;
			}
		}
		serial = serial.substr(spaceIndex + 1, serial.length() - spaceIndex + 1);
                cout << "address:" << address << endl;
 		cout << "serial:" << serial << endl;
 		string request = "curl http://frankensteinosaur.us/htgbot/hereiam/" + address + "/" + serial;
	        cout << "request:" << request << endl;
		system(request.c_str());

		return 0;
}
