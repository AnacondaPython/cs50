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
    
    
    //Initialize values for things like biplanes, bftype, etc
    BITMAPFILEHEADER new_bf;
    BITMAPINFOHEADER new_bi;
    new_bf = bf;
    new_bi = bi;

    fwrite(&new_bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&new_bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    

    
    //Change header values to scale with factor
    //http://i.imgur.com/t4FFzWk.png
    new_bi.biHeight = bi.biHeight*factor;
    new_bi.biWidth = bi.biWidth*factor;
    new_bi.biSizeImage = new_bi.biWidth * new_bi.biHeight * 3; //3 is size of RGBtriple
    new_bf.bfSize = new_bi.biSizeImage + 54; //54 is the size of BF+BI, not contents just the offset totals and bytes allocated for info

    // Padding for original scanlines, values can be 0,1,2,3. 
    // Needs to still be used, multiple of 4 related to bitmap header and fread
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int new_padding =  (4 - (new_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //Now we have everything initialized
    
    
    //define a HEAP value temporary variable
    //RGBTRIPLE *buffer = malloc(sizeof(RGBTRIPLE)*factor);
    


    // iterate over infile's scanlines
    // per row. Iterate over original files
for (int i = 0, old_biHeight = abs(bi.biHeight); i < old_biHeight; i++)   //changed to old_biheight to prevent confusion
{
    
    //We're reading the scanline now    
    //This line reproduces Factor Height times. Its not efficient because we're rereading the same thing factor times
    for (int l = 0; l<factor; l++)
    {
        
        // iterate over pixels in scanline
        // columns within row
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            //We're reading each element within the row (RGB), but we need to reproduce it multiplied by factor and store it ina new variable
            for (int r=0; r<factor; r++){
                fwrite(&triple, sizeof(RGBTRIPLE), 1, inptr);
            }
            
            
            


            // write RGB triple to outfile
            //fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr); //don't need this going replace
        }

        // skip over padding, if any
        //https://www.tutorialspoint.com/c_standard_library/c_function_fseek.htm
        //Basically, there's always padding in a bitmap file by default due to intel's 4 byte standarization
        //This reads any leftover padding in bitmap file
        
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < new_padding; k++)
        {
            fputc(0x00, outptr);
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
