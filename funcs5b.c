#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "struct5b.h"
#include "externs5b.h"

/*
function to open archive file for writing, takes the data from arguments to get file number,
gets file size and name from stat, calls a function to store file name and size into linked list

*/
void createArch(char * argv[],int argc)
{
//to store location of file to be opened to read from
int fileToOpen;
// to store location of archive to be opened to write to
int archFloc;
//holds amount of workable files
int fNum;
//variable for file name length
unsigned int fileNameLen;
//File name length char parse
unsigned char fileNameLenChar;
//char variable for file number for writing
char fNumChar;
//declaration for file info
struct stat * fileStats; 
//creates room in memory for stat structure
fileStats = (struct stat *) malloc(sizeof(struct stat) );
//for loop counter
int i;
//holds name of file 
char * fileName;
//stores data from files
char * dataBuff;

//structure declaration for linked list
fileInfo * currFileNode;
//open the binary archive file to be written to
archFloc = open(argv[2], O_WRONLY | O_CREAT, 0644);

if (archFloc == -1)
{
	fprintf(stderr, "couldn't open archive");
	exit(1);
}
//takes number of arguments and subtracts: p5b,the flag,and archive from it [(3) args].
//then parses it into an character for writing
fNum = argc - 3;
//parses into a char for writing
fNumChar = (char)fNum;
//writes number of files to archive file, size of 1 since chars are 1 byte
write(archFloc, (const void*)&fNumChar, 1);


//loop to make nodes(FOR BOTH FILENAME + SIZE and DATA)
for (i=3; i < argc; i++)
{
//gets length of file name
fileNameLen = strlen(argv[i]);
//gets size of file
stat(argv[i], fileStats);
//calling insert function and passing arguments of filename and size from stats structure.
insertLinkFile(argv[i],fileStats->st_size);
}


//set nodes to heads
currFileNode = fileHead;

//for loop to write headers
for (i=3; i < argc; i++)
{

fileNameLenChar = strlen(currFileNode->fileName);
//writes size of filename to archive file
write(archFloc, (const void*)&fileNameLenChar,1 );
//writes name of file to archive file
write(archFloc, currFileNode->fileName,strlen(currFileNode->fileName)); 
//writes file size to archive file 
write(archFloc, (const void*)&(currFileNode->fileSize),sizeof(unsigned int) );
//move to next
currFileNode = currFileNode-> next;

}
//reset to head again
currFileNode = fileHead;
//for loop that starts at the first file to be opened until the end of files
//then reads in data from files and writes to archive file
for (i=3; i < argc; i++)
{
	//opens file for reading data
	fileToOpen = open(argv[i],O_RDONLY);
	//creates room in memory to store the data being read from file
	dataBuff = malloc(currFileNode->fileSize);
	//checks if its open
	isOpen(fileToOpen);  
	//reads in the data from file storing it into databuff
	read(fileToOpen, dataBuff, currFileNode->fileSize);
	//writes the information that was just read from file to archive file
	write(archFloc, dataBuff,currFileNode->fileSize);
	//advances to next node
	currFileNode = currFileNode-> next;
}
//close file
close(archFloc);
}  
// a function that takes in file name and size from stat() and stores it into a linked list
void insertLinkFile(char * fName, unsigned int fSize)
{
	//sets current to head
fileInfo * curr = fileHead;
//create temp to store data to be copied to actual list
fileInfo * temp;

//Make room for node
temp = malloc(sizeof(fileInfo) );
//creates room in memory for filename
temp -> fileName = malloc(strlen(fName) );
//copy filename into node
strcpy(temp -> fileName,fName);
//copies size into node
temp -> fileSize = fSize;
//set next to NULL
temp -> next = NULL;

//if the head is null then store data into head
	if (fileHead == NULL)
	{
		fileHead = temp;
	}
	else
	{
		//while next of the head is not null
		while(curr->next != NULL)
		{
			//set current node to point to next node from head
			curr = curr-> next;
		}
		//once it finds null, assigns the next of head to temp thus storing the data.
			curr -> next = temp;
	}

}
//a function that extracts the name size and data from the archive file
//and creates the file then writes the data to it 
void xTract(char *binFile)
{
	
	//sets location of file to open from
	int opFile;
	//sets location of file to read from
	int rdFile;
	//variable to hold number read from file to be parsed
	char fileNumChar;
	//variable for file amount after parsing
	int fileNum;
	//variable for for loop
	int i;
	//filename from file
	char * fileName;
	//filename length
	char fileNameLen;
	//file size
	int fileSize;
	//to store data
	char * dataBuff;
	//hold location of opened file
	int fileOpened;
	//instantiating my structure
	fileInfo * currFnode;
	//opens file to read only
	opFile = open(binFile,O_RDONLY);
	//check if file is open
		isOpen(opFile);
	// first read number of files from archive and store in fileNumChar
   rdFile = read(opFile,&fileNumChar,1);
	
	fileNum= (int)fileNumChar;
	
	for(i=0; i < fileNum; i++)
		{
		
		//gets the number of files in the header 
		read(opFile,&fileNameLen,1);
		//makes room for filename
		fileName = malloc(fileNameLen );
		//read in from file the file name
		read(opFile,fileName, fileNameLen);
		//read in from file the size of file 
		read(opFile,&fileSize, sizeof(int));
		//inserts data read from archive file into linked list
		insertLinkFile(fileName, fileSize);
	}
	//resets to point to head
	currFnode = fileHead;
		while(currFnode != NULL)
		{
			//opens file at node
			fileOpened = open(currFnode->fileName,O_WRONLY | O_CREAT, 0644);
			//read the file store data into buffer
			dataBuff = malloc(currFnode->fileSize);
			//read data in from file
			read(opFile, dataBuff, currFnode->fileSize);
			//write to file being opened
			write(fileOpened,dataBuff,currFnode->fileSize );
			//iterate to next node
			currFnode = currFnode -> next;
		}
		

}
//a function that looks through the file names for matching cases
//then prints the file name and size to screen
void preFix(char *preFname, char *binFile)
{
	int opFile;
	int preFxLen;
	int openFile;
	char * fileName;
	//filename length
	char fileNameLen;
	//file size
	int fileSize;
	int i;
	int fileNum;
	fileInfo * currNode;
	char fileNumChar;

openFile = open(binFile,O_RDONLY);
	//check if file is open
	isOpen(openFile);
	// first read number of files from archive and store in fileNumChar
   read(openFile,&fileNumChar,1);
	
	fileNum= (int)fileNumChar;

for(i=0; i < fileNum; i++)
	{
		//gets the number of files in the header 
		read(openFile,&fileNameLen,1);
		//makes room for filename
		fileName = malloc(fileNameLen );
		//read in from file the file name
		read(openFile,fileName, fileNameLen);
		//read in from file the size of file 
		read(openFile,&fileSize, sizeof(int));

		insertLinkFile(fileName, fileSize);
	}
	currNode = fileHead;
	
	preFxLen = strlen(preFname);

	while(currNode != NULL)
	{
		for (i = 0; i < preFxLen; i++)
		{
			if((currNode-> fileName)[i] != preFname[i])
			{
				
				break;
			}
		}
		if(i<preFxLen)
		{
			currNode = currNode -> next;
			continue;
		}
		else
		{
			printf("name: %s size: %d \n",currNode -> fileName, currNode -> fileSize);
			currNode = currNode -> next;
		}
	}
	printf("No matching files found\n");
}






//helper function to check if file was opened properly or not.
void isOpen(int fileDesc)
{
	if (fileDesc < 0)
	{
		fprintf(stderr, "File could not be opened");
		exit(1);
	}
}





