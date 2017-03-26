// Author : prasadhosad@gmail.com  
// Date : 26/03/2017

#pragma once

#include "bmp.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

class Dft
{
private:
	bmpfile *bfp;      

public:	
	int error, wid;
	char *input_file, *output_file;

	//structure to hold both real and imaginary part
	struct cmplx
	{
		double r;
		double img;
	};	

	cmplx **cplxOutarr_r, **cplxOutarr_g, **cplxOutarr_b;
	cmplx *cplxbuff;

	int **ibuff_rgb;

	cmplx* yy;
	cmplx* yi;

    cmplx **f;
    
	//DFT
	int **RY, **BY, **GY, **SY;
	double **YI, **YR;
	//
	Dft(){}
	Dft(char** sfile);
	~Dft();
	
	void dft_trans();

	int dft1();
	bool dft_oneD(int* ibuff,int r);
	int dft2();
	bool dft_OneD2(double* t1_r,double* t1_i, unsigned int c);
};


