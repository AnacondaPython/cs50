#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int main (void) {
    string s = GetString();
    printf("%c", toupper(s[0]));
    //prints character, toupper (s[0]) is for the array. 
    //it prints the first character of string, first letter

    //now time to output 2nd name, search array
    
    for (int i=0 ; i < strlen(s); i++)
    { 
        if(isspace(s[i]))
        {
            printf("%c", toupper(s[i+1])); //prints next letter
        }
        //this finds the next position value in array
        
    
    
}
printf("\n");
}
