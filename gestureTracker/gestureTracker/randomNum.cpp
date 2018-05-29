//
//	Filename:	randomNum.c
//	Project:	fflor4305_ast_2017_a2
//	By:			Felipe Flor
//	Date:		February 16, 2017
//	Description:
//		This is the source code for the game function that creates a random number. 
//


#include "randomNum.h"




//	Function: getRandomNumber()
//	Description: This function returns a random integer number within a pre-defined range, that is,
//				 from inferiorLimit to superiorLimit.
//	Parameters:
//		- int inferiorLimit: The smallest number the function can return.
//		- int superiorLimit: The largest number the function can return.
//	Returns:
//		- int randomNumber
int getRandomNumber(int inferiorLimit, int superiorLimit)
{
	return inferiorLimit + rand() % (1 + superiorLimit - inferiorLimit);
}