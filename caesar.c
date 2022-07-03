#include <stdio.h>
#include <math.h>
#include <string.h>
#include <cs50.h>
#include <stdlib.h>

//// argv is an array of pointers to char (i.e. array of strings). The length of this array is stored in argc argument.

int main(int argc, char *argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc > 2 || argc == 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    // Make sure every character in argv[1] is a digit

    char character = '0';
    int check; 

    for (int i = 0;; i++)
    {
        character = *(*(argv + 1) + i);
        if (character != 0)
        {
            //you can use functions like is character() for this but this is cooler
            if (character < 48 || character > 57)
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        else
        {
            printf("Good Job!\n");
            check = i;
            break;
        }
    }

    // determine length of argv[1], you can use check or length here but i is cooler as it technically is the size of argv[1]
    int length = strlen(argv[1]);
printf("%i is i, %i is strlen\n", check, length);

    // Convert argv[1] from a `string` to an `int`
    //you can subtract '0' or 48 from a char in order to get its digit equivalent because this would list the numbers in ASCII as their respective number
    int converted = 0;

    //use for loop to manually append each character in the array to the character before it as an integer
    for (int i = 0; i < length ; i++)
    {
        converted = (converted * 10) + ((*(*(argv + 1) + i)) - '0');
    }
printf("new integer is: %i\n", converted);


    // Prompt user for plaintext and store in dynamically allocated string by use of %ms
    char *plaintext = NULL;
    printf("plaintext: ");

    //the m allocates space and [^\n] forces the scan to wait for a newline
    scanf("%m[^\n]s", &plaintext);
    while ((getchar()) != '\n');

printf("before strlen is: %s\n", plaintext);

    int plainlen = strlen(plaintext);
    char plaintext2[plainlen + 1];

    //putting plaintext array into new bucket array so we can free our dynamically allocated array
    for (int i = 0; i <= plainlen; i++)
    {   
        plaintext2[i] = plaintext[i];
    }
    int plainlen2 = strlen(plaintext2);
printf("You typed: %s with length of %i\n", plaintext2, plainlen2);
    free(plaintext);

    //convert the user key input to something to rotate letters by no more than 26
    if (converted >= 26)
    {
        do
        {
            converted = converted - 26;
        }
        while (converted >=26 );
    }
printf("converted integer is %i\n", converted);

    //For each character in the plaintext (figure out how to either add or subtract based on the specific character so you dont roll into non-letters)
    int topupper; //how far away uppercase letter is from top of upercase letters (top is A)
    int bottomupper; //how far uppercase letter is from bottom of uppercase letters (bottom is Z)
    int toplower; //how far from top of lowercase bounds (top is a)
    int bottomlower; //how far away lowercase letter is from bottom of lowercase bounds (bottom is z)

    int newkey; //if converting the inputted key is required to account for alphabet roll over

    //65 is subtraction amount to find how far away uppercase letter is from the bottom of uppercase letters in ascii
    //97 is subctraction amount to find how far from bottom of lowercase bounds

    char ciphertext[plainlen2 + 1]; //get new bucket array ready for final cypher text to be transferred

    //figure out if char is uppercase or lowercase
    for (int i = 0; i <= plainlen2; i++)
    {
        //uppercase
        if (plaintext2[i] >= 65 && plaintext2[i] <= 90)
        {
            topupper = 0;
            bottomupper = 0;
            topupper = plaintext2[i] - 65;
            bottomupper = 25 - topupper;
            //if adding the key to the plaintext would roll it past z in the ascii chart
            if (converted > bottomupper)
            {
                //make a new key that will instead of adding to the char, we add to A to emulate alphabet roll over
                newkey = 0;
                newkey = converted - bottomupper;
                ciphertext[i] = 64 + newkey;
            }
            //if adding the key to the plaintext would NOT roll it past z in ascii chart
            else //if (converted < bottomupper)
            {
                //add the regularly converted key to the plaintext to create cypher
                ciphertext[i] = plaintext2[i] + converted;
            }
        }
        //lowercase
        else if (plaintext2[i] >= 97 && plaintext2[i] <= 122)
        {
            toplower = 0;
            bottomlower = 0;
            toplower = plaintext2[i] - 97;
            bottomlower = 25 - toplower;
            //if adding key rolls alphabet over
            if (converted > bottomlower)
            {
                //make new key that adds to A instead of plaintext[i]
                newkey = 0;
                newkey = converted - bottomlower;
                ciphertext[i] = 96 + newkey;
            }
            else //if (converted < bottomlower)
            {
                //add key normally
                ciphertext[i] = plaintext2[i] + converted;
            }
        }
        //not a character
        else
        {
            ciphertext[i] = plaintext2[i];
        }
    }

    printf("ciphertext: %s\n", ciphertext);
}




//personal notes only from here






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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** how to check for number of arguments
   
int main(int argc, char* argv[])
{
    if (argc > 4)
    {
      printf("Too many arguments\n");
    }
    else if (argc == 1)
    {
        printf("No arguments\n");
    }
    else
    {
        //prints the value of the first index in the array being pointed to by the first value of the array being pointed to by argv
        printf("Your argument was: %c", *(*(argv + 1)));
    }
}
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**how to check an arugment for letters or non-letters (alternativeley for iterations you could just use str(len) but this is cooler)
char character = '0'; 

for (int i = 0;; i++)
{
    character = *(*(argv + 1) + i);
    if (character != 0)
    {
        printf("%c ", character);
        //you can use functions like is_digit() for this but this is cooler
        if ((character >= 65 && character <= 90) || (character >= 97 && character <= 122))
        {
            printf("is a letter\n");
        }
        else
        {
            printf("is not a letter\n");
        }
    }
    else
    {
        break;
    }
}
*/