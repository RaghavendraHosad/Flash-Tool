// Author : prasadhosad@gmail.com  
// Date : 26/03/2017

#pragma once

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include <iostream>
using namespace std;

class bmpfile{
      
      private:         
		       //file pointers to read input file and
		       //to erite output file
               FILE *fp_read_bmp, *fp_write_bmp ;
                                     
			   //only raw data array from input file, no header
               unsigned char *image_raw_array;          
   
			   //file size
               unsigned int file_size;
			   //RGB raw data offset
               unsigned int rgb_raw_data_offset;                     
               
               //new class further
               unsigned char header[54] ;                                      
                                  
      public:     
               //only raw data array for output file, no header
               unsigned char *image_raw_output;          
                     
			   // input image width, image height
               unsigned int width;
               unsigned int height;             
               
			   //red, green and blue band seperated into seperate array.
               unsigned char **image_r;
               unsigned char **image_g;
               unsigned char **image_b;       
                     
               bmpfile();
               virtual ~bmpfile();

			   //To update bmp header in output file              
               void updateheader();
               //Read 24 bit color bmp file 
               int BmpfileRead(const char *);  
			   //Write 24 bit color bmp file
               int BmpfileWrite(const char *); 
 };
      

