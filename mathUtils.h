<<<<<<< HEAD
//Addition
void addition(struct BigNumber *numA, struct BigNumber *numB, struct BigNumber *result);
//Subtraction
void subtraction(struct BigNumber *numA, struct BigNumber *numB, struct BigNumber *result);
//Multiplication
int * multiplication(const int *numA, const int *numB, int sizeA, int sizeB, int *sizeOfResult);
//Division
int * division(const int *numA, const int *numB, int sizeA, int sizeB, int *sizeOfResult);
//power
int * power(const int *numA, const int *numB, int sizeA, int sizeB, int *sizeOfResult);
//getMax
int getMax(int a, int b);
//getMin
int getMin(int a, int b);
=======
#define MAX_ARRAY_LENGTH 	10

typedef struct BigNumber {
	int *numArray;
	int length;
	int decimalPlace;
	int shiftNum;
};
>>>>>>> TH3-DR/master
