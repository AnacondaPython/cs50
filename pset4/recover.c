
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
#include <stdint.h>

typedef uint8_t  BYTE; 



int main(void)
{
    //Open the CF card
    FILE* inptr = fopen("card.raw", "r");

    //check if file is null
    if (inptr ==NULL)
    {
        fclose(inptr);
        fprintf(stderr, "card.raw file not working \n");
        return 1;
    }

    char title[8];
    
    FILE* img = NULL;

    //Initialize variables
    BYTE buffer[512];
    int fnumber = 0; 
    int searchjpeg = 1; //1 if true, 0 if false

    //Cycle through each 512 MB block
    while(fread(&buffer, 512, 1, inptr)==1){


        if(searchjpeg==1){ //Start of new jpeg?
            if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1)) //4 of 16 possible
            { //yes
                searchjpeg = 0;

                sprintf(title, "%03d.jpg", fnumber);
                img = fopen(title, "w");
                fwrite(&buffer, 512, 1, img);
            }
            else
            { //no
                printf("nothing\n");
            }
        }



        else{ //already found a jpeg?
            if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
            { //yes
                fclose(img);
                fnumber++;

                sprintf(title, "%03d.jpg", fnumber);
                img = fopen(title, "w");
                fwrite(&buffer, 512, 1, img);
            }
            else
            { //no
                fwrite(&buffer, 512, 1, img);
            }
        }
    }
    fclose(img);
    free(buffer);
}
