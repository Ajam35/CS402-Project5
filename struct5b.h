
//structs here
typedef struct fileStruct
{

char * fileName;
unsigned int fileSize;

struct fileStruct * next;
}fileInfo;


//prototypes here for p5b
void createArch(char * argv[],int argc);
void preFix(char *preFname, char *binFile);
void xTract(char *binFile);
void isOpen(int fileDesc);
void insertLinkFile(char * fName, unsigned int fSize);