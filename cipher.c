#include <stdio.h>
#include <math.h>
#include <string.h>
#include <cs50.h>
#include <stdlib.h>
#include <time.h>

//funny loading function
void elapse(int numberofseconds);

//// argv is an array of pointers to char (i.e. array of strings). The length of this array is stored in argc argument.

int main(void)
{
    printf("\n");
    int decision;

    do
    {
    decision = 0;
    printf("Type 1 to encrypt or 2 to decrypt: ");
    scanf("%i", &decision);
    while ((getchar()) != '\n');
    }
    while (decision < 1 || decision > 2);
    printf("\n");

    char *plaintext = NULL;
    if (decision == 1)
    {
        printf("What message would you like to encrypt?: ");
        // Prompt user for plaintext and store in dynamically allocated string by use of %ms, the m allocates space and [^\n] forces the scan to wait for a newline
        scanf("%m[^\n]s", &plaintext);
        while ((getchar()) != '\n');
    }
    else if (decision == 2)
    {
        printf("What message would you like to decrypt?: ");
        scanf("%m[^\n]s", &plaintext);
        while ((getchar()) != '\n');
    }
    
    //printf("decision was %i\n", decision);
    
    printf("Key: ");

    //scanf in a string of digits that will serve as the key (scanning in a string because code was initially set up with a CLI argument) we will also call this string argv[1] to skip recoding
    char *argv[2]; 
    argv[1] = NULL;
    scanf("%m[^\n]s", &argv[1]);
    while ((getchar()) != '\n');

    // Make sure every character in argv[1] is a digit
    char character = '0';
    int check; 

    for (int i = 0;; i++)
    {
        character = *(*(argv + 1) + i);
        if (character != 0)
        {
            //check if the character is a non-number. you can use functions like is character() for this but this is cooler
            if (character < 48 || character > 57)
            {
                free(argv[1]);
                printf("Key(digits only): ");
                argv[1] = NULL;

                scanf("%m[^\n]s", &argv[1]);
                while ((getchar()) != '\n');

                i--;
            }
            //also make sure number is less than 10 digits as longs can only hold 9 reliably
            else if (strlen(argv[1]) > 9)
            {
                free(argv[1]);
                printf("Key(up to 9 digits): ");
                argv[1] = NULL;
                scanf("%m[^\n]s", &argv[1]);
                while ((getchar()) != '\n');

                i--;                
            }
        }
        else
        {
            //printf("Good Job!\n");
            break;
        }
    }
    //printf("scanf made: %s\n", argv[1]);

    // determine length of argv[1], you can use check or length here but i is cooler as it technically is the size of argv[1]
    int length = strlen(argv[1]);

    //printf("%i is strlen\n", length);

    // Convert argv[1] from a `string` to an `int`
    //you can subtract '0' or 48 from a char in order to get its digit equivalent because this would list the numbers in ASCII as their respective number
    long converted = 0;

    //use for loop to manually append each character in the array to the character before it as an integer
    for (int i = 0; i < length ; i++)
    {
        converted = (converted * 10) + ((*(*(argv + 1) + i)) - '0');
    }
    free(argv[1]);

    //convert the user key input to something to rotate letters by no more than 26
    if (converted >= 26)
    {
        do
        {
            converted = converted - 26;
        }
        while (converted >=26 );
    }
    //force long converted to an int after it's shortened
    int converted2 = (int)converted;
    
    //printf("new integer is: %ld\n", converted);


    //find length of input text and drop in a new array so we can free it
    int plainlen = strlen(plaintext);
    char plaintext2[plainlen + 1];

    //putting plaintext array into new bucket array so we can free our dynamically allocated array
    for (int i = 0; i <= plainlen; i++)
    {   
        plaintext2[i] = plaintext[i];
    }
    int plainlen2 = strlen(plaintext2);

    //printf("You typed: %s with length of %i\n", plaintext2, plainlen2);

    free(plaintext);

    //printf("converted integer is %i\n", converted2);

    //For each character in the plaintext (figure out how to either add or subtract based on the specific character so you dont roll into non-letters)
    int topupper; //how far away uppercase letter is from top of upercase letters (top is A)
    int bottomupper; //how far uppercase letter is from bottom of uppercase letters (bottom is Z)
    int toplower; //how far from top of lowercase bounds (top is a)
    int bottomlower; //how far away lowercase letter is from bottom of lowercase bounds (bottom is z)

    int newkey; //if converting the inputted key is required to account for alphabet roll over

    //65 is subtraction amount to find how far away uppercase letter is from the bottom of uppercase letters in ascii
    //97 is subctraction amount to find how far from bottom of lowercase bounds

    char finaltext[plainlen2 + 1]; //get new bucket array ready for final cypher text to be transferred

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

            //check if decrypt or encrypt

            //ENCRYPT
            if(decision == 1)
            {
                //if adding the key to the plaintext would roll it past z in the ascii chart
                if (converted2 > bottomupper)
                {
                    //make a new key that will instead of adding to the char, add to A to emulate alphabet roll over
                    newkey = 0;
                    newkey = converted2 - bottomupper;
                    finaltext[i] = 64 + newkey;
                }
                //if adding the key to the plaintext would NOT roll it past z in ascii chart
                else if (converted2 <= bottomupper)
                {
                    //add the regularly converted2 key to the plaintext to create cypher
                    finaltext[i] = plaintext2[i] + converted2;
                }
            }
            //DECRYPT
            else
            {
                //if subtracting key rolls alphabet over
                if (converted2 > topupper)
                {
                    //make new key that subtracts from Z instead of plaintext[i]
                    newkey = 0;
                    newkey = converted2 - topupper;
                    finaltext[i] = 91 - newkey;
                }
                else if (converted2 <= topupper)
                {
                    //add key normally
                    finaltext[i] = plaintext2[i] - converted2;
                }
            }
        }
        //lowercase
        else if (plaintext2[i] >= 97 && plaintext2[i] <= 122)
        {
            toplower = 0;
            bottomlower = 0;
            toplower = plaintext2[i] - 97;
            bottomlower = 25 - toplower;

            //check if decrypt or encrypt

            //ENCRYPT
            if (decision == 1)
            {
                //if adding key rolls alphabet over
                if (converted2 > bottomlower)
                {
                    //make new key that adds to A instead of plaintext[i]
                    newkey = 0;
                    newkey = converted2 - bottomlower;
                    finaltext[i] = 96 + newkey;
                }
                else if (converted2 <= bottomlower)
                {
                    //add key normally
                    finaltext[i] = plaintext2[i] + converted2;
                }
            }
            //DECRYPT
            else
            {
                //if subtracting key rolls alphabet over
                if (converted2 > toplower)
                {
                    //make new key that subtracts from Z instead of plaintext[i]
                    newkey = 0;
                    newkey = converted2 - toplower;
                    finaltext[i] = 123 - newkey;
                }
                else if (converted2 <= toplower)
                {
                    //add key normally
                    finaltext[i] = plaintext2[i] - converted2;
                }
            }
        }
        //not a character
        else
        {
            finaltext[i] = plaintext2[i];
        }
    }

    //define many funny strings labelled with a number
    char *s[30];

    s[0] = "Pushing random keys";
    s[1] = "Churning RAM";
    s[2] = "Mining for coal";
    s[3] = "Burning fossil fuels";
    s[4] = "Fracking";
    s[5] = "Cooling the CPU";
    s[6] = "Chugging freon";
    s[7] = "Firing thrusters";
    s[8] = "Igniting engine";
    s[9] = "Stealing GPUs";
    s[10] = "Scalping 3080s";
    s[11] = "Overclocking";
    s[12] = "Parsing arguments";
    s[13] = "Counting numbers";
    s[14] = "Smashing rocks";
    s[15] = "Cutting trees";
    s[16] = "Limiting FPS";
    s[17] = "Updating drivers";
    s[18] = "Applying to Google";
    s[19] = "Going to college";
    s[20] = "Working on it";
    s[21] = "Turning off and on";
    s[22] = "Spilling oil";
    s[23] = "Cleaning transistors";
    s[24] = "Hacking and slashing";
    s[25] = "Punching holes";
    s[26] = "Allocating spacetime";
    s[27] = "Dozing off";
    s[28] = "Reseating motherboard?";
    s[29] = "Installing cool lights";

    printf("\n");
    int n;
    int m;
    int o;
    srand(time(0));

    for (int i = 0; i < 3; i++)
    {
        n = 0;
        n = rand();
        m = 0;
        m = n % 100;
        o = 0;
        o = m;

        while (o >= 30)
        {
            o = o - 30;
            //printf("o is %i", o);
        }

        //n = (rand() / (RAND_MAX / 30 + 1));
        printf("%s... \n", s[o]);
        elapse(1);
    }

    if (decision == 1)
    {
        printf("\nPlaintext is: %s\n", finaltext);
    }
    else
    {
        printf("\nCyphertext is: %s\n", finaltext);
    }

    double x;
    printf("\nThanks for playing! Type 1 and press enter to play again, type anything else and enter to exit. ");
    scanf("%lf", &x);
    
    while ((getchar()) != '\n');
    printf("\n");

    if (x == 1)
    {
        main();
    }
    else
    {
        return 0;
    }
}


//time elapse function
void elapse(int numberofseconds)
{
    //converting time into milliseconds
    int milliseconds = 1000 * numberofseconds;
  
    // Storing start time
    clock_t starttime = clock();
  
    // looping till required time is not achieved
    while (clock() < starttime + milliseconds);
}










//personal notes only from here




/**
based on first answer ask "What would you like to encrypt/decrypt?: "
based on the asnwer either do the normal encryption or fault to a new version

after user puts in their text, add funny clock message that gives a loading message every second for 3 seconds

if user asked to encrypt, make the resulting output finaltext: ...
if user asked to decrypt, make the resulting output Plaintext: ...

prompt user if they want to try again or end the program
*/





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/** Make sure program was run with just one command-line argument
  
    if (argc > 2 || argc == 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
*/


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