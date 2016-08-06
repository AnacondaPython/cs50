//Vigenere
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

char vigenereConversion(char asciiChar, int varKey);

int arrayConversion (char asciiChar);


/*---------------------------------------
	1. Get the Key
		a. 2nd command line argument : argv[1]
		b. Must be alphabetical : isalpha
	2. Get the plain text
	    a. Create the new text like "I_Like_You" from cipher key "Panda" as "P_anda_Pan"
	3. Encipher
    4. Print ciphertext
----------------------------------------*/

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

//2. Get the plaintext 
    string plainText = GetString();
    string newCipherText = plainText; // sets all values to null / spaces for the same length as the string entered

    printf("%s, intiial cipher text \n", newCipherText);
    if (strlen(cipherText)<strlen(plainText)){
      
            int counter = 0;    //for loop array, needs to be outside scope
        for (int j=0; j<strlen(plainText); j++){ //loop the entire array
        
        if (!isspace(plainText[j])){
            newCipherText[j] = (cipherText[(j-counter)%(strlen(cipherText))]); //modulo function, its to get letters to loop in a specific position under cipherText
        }
        if (isspace(plainText[j])){
            newCipherText[j] = ' ';
            counter++;
    
        }
        
    }
printf("%s, CipherText did it work?", newCipherText);    





//3. Encipher (need to convert that encipher text into an array of values)
    int cipherArray[20] = {0};
    for (int k=0; k<strlen(newCipherText); k++){
        cipherArray[k] =  arrayConversion(newCipherText[k]);
    }
    //printf("%d, Did CipherText to numbers work?", cipherArray);

//3.5 now I have to convert the other array into a number. We have an array of values now , toss that into a new function

    string finalCipherText = newCipherText;
    for (int m =0; m<strlen(newCipherText); m++){
        finalCipherText[m] = vigenereConversion(plainText[m], cipherArray[m]);
    }
    
    printf("%s, did ciphertext work", finalCipherText);

}
}



}

//Functions below

char vigenereConversion(char asciiChar, int varKey){

    int letter = asciiChar;
    
    if(isupper(asciiChar)){
        letter = letter - 65; 
    letter = (letter+varKey)%26; 
    letter = letter +65; 
    asciiChar = letter;
    return asciiChar;
    }
    
    if(islower(asciiChar)){
        letter = letter - 97; 
    letter = (letter+varKey)%26; 
    letter = letter +97; 
    asciiChar = letter;
    return asciiChar;
    }
    
}




int arrayConversion (char asciiChar){
    int letter = asciiChar;
    
    if(isupper(asciiChar)){
        letter = letter - 65;
        return letter;
    }
    
    if(islower(asciiChar)){
        letter = letter - 97;
        return letter;
    }
    
    
}
