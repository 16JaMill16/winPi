/*==================================================================================================
 * mathUtils.c
 * Author	: 
 * Purpose	:
 * Date		:
 //===============================================================================================*/
 #include <math.h>
 #include <stdlib.h>
 #include <stdio.h>
 #include "mathUtils.h"
 
  int getMax(int a, int b);
  void addition(struct BigNumber *numA, struct BigNumber *numB, struct BigNumber *result);
  
	int main(int argC, char **argV) {
		int a[] = {1,2,3,4,5,6,7,8,9,7};
		int b[] = {9,6,7,8,9};
		struct BigNumber numA = {a, 10, 1, 0};
		struct BigNumber numB = {b, 5, 1, 0};
		struct BigNumber result;
	
		addition(&numA, &numB, &result);
		
		printf("%d\n",result.length);
		int i;
		for (i = 0; i < result.length; i++) {
			if (result.decimalPlace == i) {
				printf(".");
			}
			printf("%d", result.numArray[i]);
		}
		
		free(result.numArray);
		scanf("asdf",&argC);
	}
 
	void addition(struct BigNumber *numA, struct BigNumber *numB, struct BigNumber *result) {
		//This method returns an array that is the sum of two given equal length arrays
		
		int shiftNum = 0;
		
		//Find and set the decimal place of the new array
		result->decimalPlace = getMax(numA->decimalPlace, numB->decimalPlace);
		
		
		//Find and set the length of the new array
		if (numA->decimalPlace == numB->decimalPlace && numA->numArray[0] + numB->numArray[0] > 9) {
			result->length = getMax(numA->length, numB->length) + 1;
			result->decimalPlace++;
		
			//make sure the array properties are not out of bounds and 
			//remember the amount of decimals we will have to chop off
			if (result->length > MAX_ARRAY_LENGTH) {
				shiftNum = result->length - MAX_ARRAY_LENGTH;
				result->length = MAX_ARRAY_LENGTH;
				printf("Check!");
			}
		} else {
			result->length = getMax(numA->length, numB->length);
		}
		
		
		//Allocate the memory for the new integer
		result->numArray = (int *)malloc(sizeof(int) * (result->length));
		
	
		//The math happens here
		//Set the last array value to 0 as it isn't done by the loop
		result->numArray[result->length] = 0;
		
		int i; 
		for (i = result->length; i - shiftNum >= 0 ; i--) {
			int sum = 0;
			
			//Add the number row to sum if there IS a number at that row
			if (numA->length > i - shiftNum) {
				sum += numA->numArray[i - shiftNum];
			}
		
			if (numB->length > i - shiftNum) {
				sum += numB->numArray[i - shiftNum];
			}
			
			//This makes sure the carriage from previous operations is added
			sum += result->numArray[i];
			
			//If the number goes over ten, carry a one to the next decimal place
			int carriage = sum / 10;
			sum = sum % 10;
			printf("%d ",sum);
			
			result->numArray[i - 1] = carriage;
			result->numArray[i] = sum;
		} 
		printf("\n");
	}
	
	
	int getMax(int a, int b) {
		//Returns the max of two ints not above the max length
		if (a > MAX_ARRAY_LENGTH || b > MAX_ARRAY_LENGTH) {
			return MAX_ARRAY_LENGTH;
		}
		
		if (a > b) {
			return a;
		} else {
			return b;
		}
	}
	
	
	