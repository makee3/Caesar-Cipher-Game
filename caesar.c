#include <stdio.h>
#include <math.h>
#include <string.h>
#include <cs50.h>

int main(int argc, string argv[]) 
{



}




//take input key from user as digits only

//treat the number as if every multiple of 26 rolls the alphabet completley over in terms of ASCII

//divide the number by 26, if the resulting integer is == 0, carry on. if the resulting integer is > 0 we need to do something

//take the integer produced by dividing user arg by 26, and multiply it by 26 and store that value in a new variable

//subtract the new variable from the original input to convert it to the desired ASCII equivalent conversion factor, then move on

//store plaintext in empty array

//create empty array of the same size to store ciphertext

//create loop that converts each char in plaintext array to the deserved cipher text char and store it in the ciphertext array by iterating as many times as the arrays are large

//print out plaintext and then cipher text arrays by printing out each of their indicies one by one using a loop that must meet the condition that the value stored in the index does not equal the \0 character which indicates the end of the string





/**if you want to make this dynamic you need to be able to take scanf arguments from the user and store those into null terminated arrays.
 * perhaps giving them the choice to input either cypher text or plaintext, and executing a different algorithm for either one (adding or subtracting)
 * once you have a null terminated array you can perform a loop on that array to determine the size by counting until you hit \0.
 * The malloc'd empty array can then be given the (size of first array - 1) because we don't need a null terminator if we know the size already.
 * mallocing the empty array can be done by simply allocating 8*size as chars use 8 bits.
 * we can then iterate a loop that stores the text from the first array into the new array after applying the key that the user inputted.
 * the result can then be printed by performing a loop that prints each char and iterates the number of times equal to the size of the array
 * then print your final output after the loop.
*/

/**you could also be funny and add a time delay for conversion by using the clock_t typedef by writing something like

    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)

 * to initiate a delay in the code by number_of_seconds seconds.
*/ 