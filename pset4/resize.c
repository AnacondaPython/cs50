/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // 4 arguments
    if (argc != 4)
    {
        printf("Usage: ./copy factor infile outfile\n");
        return 1;
    }

    //Checks for factor
    int factor = atoi(argv[1]);
    if (factor <= 0 || factor >= 100)
    {
        printf("Must be between 0 and 100\n");
        return 6;
        
    }
    
    
    char* infile = argv[2];
    char* outfile = argv[3];

    // Input file open
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    //----------------new files -------------
    
    
    //Initialize the new_bf
    BITMAPFILEHEADER new_bf;
    BITMAPINFOHEADER new_bi;
    new_bf = bf;
    new_bi = bi;

    //Set newest 
    new_bi.biHeight = bi.biHeight*factor;
    new_bi.biWidth = bi.biWidth*factor;
    
    //Padding for fseek, multiple of 4
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int new_padding =  (4 - (new_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //New Image Size
    new_bi.biSizeImage = (new_bi.biWidth *sizeof(RGBTRIPLE) + new_padding) * abs(new_bi.biHeight); 
    new_bf.bfSize = new_bi.biSizeImage + 54; //54 is BF+BI
    
    //open file to write output
    fwrite(&new_bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&new_bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    


    // iterate over infile's scanlines
    for (int i = 0, old_biHeight = abs(bi.biHeight); i < old_biHeight; i++)   //changed to old_biheight to prevent confusion
    {
        
        //Not efficient, but scans over the same input line for factor*output rows
        for (int l = 0; l<factor; l++)
        {
            
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                //BGR + BGR + BGR factor # of times on width
                for (int r=0; r<factor; r++){
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            //Input files padding, pass over seeker
            fseek(inptr, padding, SEEK_CUR);
    
            //Add multiple of 4 padding to new image size
            for (int k = 0; k < new_padding; k++)
            {
                fputc(0x00, outptr);
            }
            
            //pushes cursor back and iterate # of factor times on "L" row
            if (l < factor - 1) 
            {
                long offset = bi.biWidth*sizeof(RGBTRIPLE)+padding; //By default, files are unsigned (nonnegative). Need to define negative signed long
                fseek(inptr, -offset, SEEK_CUR);  //this shoves cursor back the entire length to start
            }
        }
    }

// close infile
fclose(inptr);

// close outfile
fclose(outptr);

// that's all folks
return 0;
}
