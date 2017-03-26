// Author : prasadhosad@gmail.com  
// Date : 26/03/2017

#include "bmp.h"
#include "dft2d.h"
#include <stdio.h>

int main(int argc, char** argv)
{
	printf("/* * * * * * * * * * * * * * * * * * * * * * */\n");
	printf("/* DFT 2D on 24bpp BMP image of size NxN * * */\n");
	printf("/* * Usage : <input_file> <output_file> * *  */\n");
	printf("/* * * * * * * * * * * * * * * * * * * * * * */\n");

	Dft *p = NULL;
    if(argc < 2)
	{
		printf("Usage : <input_file> <output_file> \n");
	}
	else 
	{
		p = new Dft(argv);  
		if(p->error != -1)
		p->dft_trans();
	}
	 	
	delete p;
	p = NULL;

	printf("\n\nThanks for using...");
	getchar();

	return 0;
}