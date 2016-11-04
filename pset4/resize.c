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
    // ensure proper usage
    // 4, because we need to add a factor
    if (argc != 4)
    {
        printf("Usage: ./copy factor infile outfile\n");
        return 1;
    }
    
    //added this file for input name
    int factor = atoi(argv[1]);
    if (argv[1] <= 0)
    {
        printf("Must be positive factor\n");
        return 6;
    }

    // remember filenames
    char* infile = argv[2]; //change to argv[2] for newer input
    char* outfile = argv[3];

    // open input file 
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
    BITMAPFILEHEADER old_bf;
    fread(&old_bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER old_bi;
    fread(&old_bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (old_bf.bfType != 0x4d42 || old_bf.bfOffBits != 54 || old_bi.biSize != 40 || 
        old_bi.biBitCount != 24 || old_bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    
    //Files been read for old_bf and old_bi. 
    
    //new BITMAP FILE HEADER CLASS to store the data;
    BITMAPFILEHEADER new_bf; //14 bytes , same number of bytes but diff values
    BITMAPINFOHEADER new_bi; //40 bytes, same # of bytes but diff values
    
    //opens new file to start rewriting new data. Now input and output files are open
    fwrite(&new_bf, sizeof(BITMAPFILEHEADER),1, outptr);
    fwrite(&new_bi, sizeof(BITMAPINFOHEADER),1 ,outptr);
    
    //Initialize new values inside the bitmap such as .biwidth, relative to input factor
    new_bi.biWidth = old_bi.biWidth*factor;
    new_bi.biHeight = old_bi.Height*factor;
    
    int old_padding = (4-)
    
    
    //Initialize new values inside the bitmapfileheader
    
    // determine padding for scanlines
    

    // determine padding for scanlines
    int old_padding =  (4 - (old_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, o_biHeight = abs(old_bi.biHeight); i < o_biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < old_bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
