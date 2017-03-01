#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "struct5a.h"

//a function to insert file name size and date modified into linked list

void insertFunc(treeNode ** tNode, char * fileNameIn, int fileSizeIn, char * dateLmod)
{
treeNode * newNode;

if (*tNode == NULL)
	{
		//create space for new node
		newNode = (treeNode *) malloc(sizeof(treeNode));
		//create space for filename variable
		newNode->fileName = malloc( strlen(fileNameIn) );
		//create space for datemodified variable
	newNode->dateModded = malloc( strlen(dateLmod) );
		//copy fileName into node
		strcpy(newNode ->fileName, fileNameIn );
		//copy filesize into node
		newNode -> fileSize = fileSizeIn;
		//copy date into node
		strcpy(newNode -> dateModded, dateLmod);
		//set the left and right children to null
		newNode -> lChild = newNode -> rChild = NULL;
		//sets to head of tree to the node with data in it
		*tNode = newNode; 
		
	}

	else
	{
		//if filesize input is less than filesize node, store left
		if(fileSizeIn < (*tNode) -> fileSize)
		{
			//recursively calls the function and stores in left
			insertFunc(&((*tNode) -> lChild), fileNameIn, fileSizeIn, dateLmod);
		}
		// else if filesize input is more than filesize node, store right
		else if (fileSizeIn > (*tNode) -> fileSize)
		{
			//recursively calls the function and stores in left
			insertFunc(&((*tNode) -> rChild), fileNameIn, fileSizeIn, dateLmod);

		}

	}
}
//a function to print the BST in ascending order of file size.
void printBST(treeNode * tNode)
{

	if (tNode != NULL) 
	{
		//recursively calls function to print left child	
	 printBST(tNode->lChild);
	 
	 printf("%s %d %s \n",tNode->fileName, tNode->fileSize, tNode->dateModded);
	 //recursively calls function to print right child
	 printBST(tNode->rChild);

	}
}