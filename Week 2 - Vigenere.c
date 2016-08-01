//Vigenere
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


/*---------------------------------------
	1. Get the Key
		a. 2nd command line argument : argv[1]
		b. Must be alphabetical : isalpha
	2. Get the plain text
	    a. Create the new text like "I_Like_You" from cipher key "Panda" as "P_anda_Pan"
	3. Encipher
    4. Print ciphertext
----------------------------------------*/

//okay fuck this I'm going to rewrite the program from the ground up again, using caesar.c code when needed 

int main(int argc, string argv[1]){
    if (argc!=2){
        return 1; //because you need two arguments. Argv is always a array of strings. argv[1] is just a string
    }
    string cipherText = argv[1];
//1. Get the Key, we are now going to run a check on each letter . See check : http://i.imgur.com/ly9Hirn.png
    for (int i=0; i<strlen(cipherText); i++){
        if (!isalpha(cipherText[i])){  // ! is used in C to denote not true boolean
            printf("Keyword must only contain letters A-Z and a-z");
            return -1;
        }

//everything works thus far:

//2. Get the plaintext 
    string plainText = GetString();
    string newCipherText = plainText; // sets all values to null / spaces for the same length as the string entered

    printf("%s, intiial cipher text \n", newCipherText);
    if (strlen(cipherText)<strlen(plainText)){
        /*make the newest array
        int a = strlen(cipherText)%strlen(plainText);
        int b = strlen(cipherText)/strlen(plainText);
        newCipherText = () */
        
        for (int j=0; j<strlen(plainText); j++){ //loop the entire array
        if (!isspace(plainText[j])){
            newCipherText[j] = (cipherText[j%(strlen(cipherText))]); //this should work, but we need to include spaces somehow.
        }
        if (isspace(plainText[j])){
            newCipherText[j] = ' ';
        }
        
    }
printf("%s, CipherText did it work?", newCipherText);    
}
}
}
