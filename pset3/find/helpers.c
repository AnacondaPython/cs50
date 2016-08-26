/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

#include "stdio.h"

#include "stdlib.h"

// ADDED ONE CHANGE TO SEE IF FILE CHANGED

/**
 * Returns true if value is in array of n values, else false.
 */
 
 //This was Linear Search
/*bool search(int value, int values[], int n)
{
   if(n<=0){
       return false;
   }
    for (int i=0; i<n; i++){   //n is size of array
        if(value == values[i]){
        return true;
        }
    
    }
    return false;
}
*/

//assumed sorted
bool Binarysearch(int key, int array[], int n){

    int end = n-1; //indexing for maximum, its one short
    int start = 0; //indexing for minimum
    
    //deadswitch on recursive 
    while(start<end){ //ends program, since you have to look left
    

        if (array[midpoint] == key){
            return true;
        }
        else if (key > array[midpoint]){
            start = midpoint+1;
            //end = startpoint -1;
        }
            
        else if (key < array[midpoint]){
            end = midpoint-1;
        }
        else {
            break;
        }
}

}
return false;
}
/**
 * Sorts array of n values.
 */
void sort(int values[], int n) 
{
    int min = 0;
    // TODO: implement an O(n^2) sorting algorithm search Algorithm SELECTION SORT
    for (int i =0; i<n-1; i++){
        min = i;
        for (int j=i+1; j<n; j++){ 
            if (values[j] <values[min])
                min = j;
        }
        if (min != i)
        values[min] = values[i];
    }
    return;
}
