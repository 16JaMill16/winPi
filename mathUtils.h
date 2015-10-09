<<<<<<< HEAD
//Addition
int * addition(const int *numA, const int *numB, int sizeA, int sizeB, int *sizeOfResult);
//Subtraction
int * subtraction(const int *numA, const int *numB, int sizeA, int sizeB, int *sizeOfResult);
//Multiplication
int * multiplication(const int *numA, const int *numB, int sizeA, int sizeB, int *sizeOfResult);
//Division
int * division(const int *numA, const int *numB, int sizeA, int sizeB, int *sizeOfResult);
//power
int * power(const int *numA, const int *numB, int sizeA, int sizeB, int *sizeOfResult);
=======
#define MAX_ARRAY_LENGTH 	10

typedef struct BigNumber {
	int *numArray;
	int length;
	int decimalPlace;
	int shiftNum;
};
>>>>>>> TH3-DR/master
