//Caesars Cipher
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

char lowerCaesar (char a, int r);
char upperCaesar (char a, int r);

//1. Get the key
//2. Get the plaintext
//3. Encipher
//4. Printciphertext

//For step#3, we need to
//A. read each character in the array (string)
//B. read whether the letter is an upper or lowercase character
//C. send that character and/or equivalent text value to a cipher function
//D. return the correct letter into the new string CA to be printed out,
//in the correct order as well (therefore we need 2 strings)

//for step c, we need to: 
//AA. make a function (pass char, pass int key), it returns a char
//one for upper and one for lower, as they have different ASCII values
//BB. Toss those values into ASCII numbers
//CC. subtract those ascii numbers and normalize them to 0
//DD. use Caesar Ciphers math formula with modulus
//EE. Somehow convert that ASCII number into a letter (they didn't really say)
//EE. return the value of the new character (not int)


//Step 1: Get the key g
int main (int argc, string argv[1]){ 
    if (argc != 2)
    {
        return 1;
    }
    int k = atoi(argv[1]); //grab argument in command line as string
    if (k<0) { //I have no idea how to check for anything not a number?
        return -1;
    }
    
//Step 2: Get the plaintext
    //printf("Please enter a word now \n");
    string s = GetString();
    //printf("%s was what you entered \n", s);
    string ca = s; // ca means caesarArray
    
    
    
//Step 3: Encipher
    for (int j=0; j<strlen(s); j++){
        if (isupper(s[j]))
        {
            //pass to the function that will convert upper letters
            ca[j] = upperCaesar(s[j],k);
        }
        if (islower(s[j]))
        {
            //pass to the function that will convert lower letters
            ca[j] = lowerCaesar(s[j],k);
        }
        
    }
    
//Step 4: Print cipher
    printf("%s", ca); // is the cipher text
}

//Step AA: returning a lowercase letter under CaesarsCipher
//97 = a, 122 = z. 
char lowerCaesar (char a, int r){
    int letter = a; //say we get y, which is 121
    letter = letter - 97; // its reduced to now 24, which is y
    letter = (letter+r)%26; // say the key was 5, 24+5 = 29, remainder is 3.
    //since a =0, d = 3. Which si right
    letter = letter +97; // goes back to the original ASCII value
    a = letter;
    return a;
}


//Step AA v2: returning a uppercase letter under CaesarsCipher
//65 = A, 90 =Z  
//..............................
//char upperCaesar (char A, int r) //it shouldn't matter if A is the same, its not global
//(will check) after I do lowercase check

char upperCaesar (char a, int r){
    int letter = a; //say we get y, which is 89
    letter = letter - 65; // its reduced to now 24, which is y
    letter = (letter+r)%26; // say the key was 5, 24+5 = 29, remainder is 3.
    //since a =0, d = 3. Which si right
    letter = letter +65; // goes back to the original ASCII value
    a = letter;
    return a;
}








//Notes not going to be used:
//--------------------------

/* Pseudocode
1. Grab string array
1A. Ask for a secret key K, must be a number. Return 1 if not 
working under main
1B. We can make a string k =argv1
2. Make a second string array for output later
3. Use a FOR LOOP to read the initial array

*/
//-------------------------------

//we're getting characters since we're reading off elements in the string, aka characters
//we then convert the characters into ASCII numbers?
//Then, after the numbers are converted, do the CaesarsCipher

//int caesarCipher (char input) //strings are array of characters, and array of strings is argv under command line
//{
//    input = 
//}

//------------
//Proceed to use the key onto the string now. Need a for loop. We will need another array to store the new values onto
    //ci = (pi + k) % 26 formula must go in there somewhere
