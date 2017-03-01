#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "struct5b.h"

//global declaration here
fileInfo * fileHead;

int main (int argc, char * argv[])
{
	//if arguments are greater than 4 has to be -c
	if (argc > 4)
	{
		//calculates number of files to b
		if(strcmp(argv[1],"-c") == 0)
		{
			//call function to create archive 
			createArch(argv,argc);
		}
		//if not  -c flag
		else
		{
			fprintf(stderr, "inappropriate flag");
			exit(1);
		}
	}
	//if the arguments are equal to 4 then can be -c or -p
	else if (argc == 4)
	{
		if(strcmp(argv[1],"-c") == 0)
		{
			createArch(argv,argc);
		}
		else if(strcmp(argv[1],"-p") == 0)
		{
			//call function to prefix stuffs
			preFix(argv[2], argv[3]);
		}
		//if neither then wrong flag
		else
		{
			fprintf(stderr, "inappropriate flag");
			exit(1);
		}

	}
	//if arguments are equal to 3 then it's -x 
	else if (argc == 3)
	{
		if(strcmp(argv[1],"-x") == 0)
			{
			//call function to extract the archive name
			xTract(argv[2]);
			}
	//if not x then wrong flag was input
		else
			{
				fprintf(stderr, "inappropriate flag");
				exit(1);
			}
	}
	//if it isn't greater than 4, equal to 4 or, equal to 3 than 
	else
	{
	fprintf(stderr, "inappropriate amount of command arguments");
	exit(1);
	}
return(0);
}