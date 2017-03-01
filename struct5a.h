
//structure for binary search tree
//variables are self explanatory
typedef struct trNode
	{
 char * fileName; 
unsigned int fileSize;
char * dateModded;

struct trNode *lChild, *rChild;

	}treeNode;

//prototypes for p5a
void insertFunc(treeNode ** tNode, char * fileNameIn, int fileSize, char * dateLmod);
void printBST(treeNode * tNode);
void printBSTinOrd(treeNode * tNode);