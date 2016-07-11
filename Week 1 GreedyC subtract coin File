#include <stdio.h>
#include <cs50.h>
#include <math.h> //must include math library for round function

int main (void)
{ 
    float n = -1;
    float y = 0;
    int z = 0;
    int counter = 0;
    
    //initializing, multiply 100, get rid of floating point imprecision
    
    do {
    printf("Input positive money amount such as $5.13 as '5.13' ");
    n = GetFloat();
    } while (n< 0);
    
    n = n * 100;
    y = round(n);
    z = y; //we will use Z from now on, it is a float
    y = y / 100; 
    printf("%.2f\n", y);
    
    //Loop and subtraction method
    
    //While quarters can be used: (no decimal values for now)
    while (z >= 25) {
        z = z - 25;
    counter++;
    }
    while (z >= 10) {
        z = z -10;
    counter++;
    }
    while (z >= 5)
    {
        z = z - 5 ;
    counter++;
    }
    while (z >= 1) 
    {
        z = z -1 ;
    counter++;
    }   
        
    //print answer, use Z , needs to be divded by 100 and must be given back to float y
    printf("number of minimum coins needed %d", counter);
    
}
