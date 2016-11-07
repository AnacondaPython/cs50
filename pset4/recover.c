/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    BYTE: jpeg1;
    BYTE: jpeg2;
    BYTE: jpeg3;
    BYTE: jpeg4;
} __attribute__((__packed__)) 
JPEGCHK;



int main(int argc, char* argv[])
{
    //Open the CF card
    FILE* inptr = fopen("card.raw", "r");
    
    //Initialize variables
    int* buffer = malloc(512);
    int fnumber = 0; //numbering files
    int searchjpeg = 1; //1 if true, 0 if false
    char* title;
    
    //Cycle through each 512 MB block
    while(fread(&buffer, 512, 1, inptr)==1){
        fseek(inptr, -512, SEEK_CUR); //go back 512 paces after first logic check
        
        //Read first 4 bytes
        JPEGCHK j1;
        fread(&j1, sizeof(JPEGCHK),1, inptr);
        fseek(inptr, -4, SEEK_CUR);
        
        
        if(searchjpeg==1){ //Start of new jpeg?
            if(j1.jpeg1 == 0xff && j1.jpeg2 == 0xd8 && j1.jpeg3 == 0xff && j1.jpeg4 == 0xe0) //4 of 16 possible
            { //yes
                searchjpeg = 0;
                fread(&buffer, 512,1,inptr);
                
                sprintf(title, "00%d.jpg", fnumber);
                FILE* img = fopen(title, "a");
                fwrite(&buffer, 512, 1, inptr);
            }
            else
            { //no
                fseek(inptr,512,1,inptr);
            }
        }
        
        
        
        else{ //already found a jpeg?
            if(j1.jpeg1 == 0xff && j1.jpeg2 == 0xd8 && j1.jpeg3 == 0xff && j1.jpeg4 == 0xe0)
            { //yes
                fclose(title);
                fnumber++;
                
                sprintf(title, "00%d.jpg", fnumber);
                FILE* img = fopen(title, "a");
                fwrite(&buffer, 512, 1, inptr);
            }
            else
            { //no
                fread(&buffer, 512, 1,inptr);
            }
        }
    }
    //close last file made
    fclose(title);
    free(buffer);
}
