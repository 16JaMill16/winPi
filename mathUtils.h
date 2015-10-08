#define MAX_ARRAY_LENGTH 	10

typedef struct BigNumber {
	int *numArray;
	int length;
	int decimalPlace;
	int shiftNum;
};