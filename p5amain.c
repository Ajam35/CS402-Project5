#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include "struct5a.h"


 

int main (int argc, char * argv[])
{
//directory holding pathname
DIR * dirptr;
//dirent struct declaration
struct dirent * fileStruct;
treeNode * treeN = NULL;
//stat struct delcaration
struct stat * fstats;
char path[255];
char * dateBuff;
struct tm * timeLocal;
//assign memory for fstats
dirptr = opendir(argv[1]);
dateBuff = malloc(13);
fstats = (struct stat *)malloc(sizeof(struct stat));
   


if (dirptr == NULL)
{

printf("dp is null");

}
			//iterates while reading through current directory
		while ( (fileStruct = readdir(dirptr) ) != NULL) 
		{
			//check for ~,.,
 
			//copy actual pathname into path
			strcpy(path, argv[1]);
			strcat(path,"/");
			strcat(path,fileStruct->d_name);
			//Checks if file starts with a . and skips files that ONLY contain . and ..	
			
				//if it returns 0 (which is false)
			if ( (strcmp(fileStruct -> d_name, ".") ) && (strcmp(fileStruct -> d_name, "..") ) && (fileStruct->d_name[0] == '.') ) 
				{
					//call stat function on actual filepath
					stat(path,fstats);
					
					//translating time read in into a struct so it can be broken down by strftime
					timeLocal = localtime( &(fstats -> st_mtime) );
					//formats the broken down time data
					strftime(dateBuff,13, "%b %d %Y",timeLocal);

					//printout to make sure correct information is being read in
					if(!argv[2])
					{
					printf("%s %d %s\n", fileStruct->d_name, fstats->st_size, dateBuff);
					//feed filestruct,fstats and dateBuff into function fillBin to fill binary tree.
					//pass it just d_name, st_size, and dateBuff
					}
					insertFunc(&treeN, fileStruct->d_name, fstats->st_size, dateBuff);
				}	
		}
		//printf("First: %s\n", treeN->fileName);									
		if(argv[2]){
				if(strcmp(argv[2],"-s") == 0)
				{
					printBST(treeN);
				}
		}
	//close directory
	closedir(dirptr);
}