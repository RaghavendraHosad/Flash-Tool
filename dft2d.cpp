#include "bmp.h"
#include "dft2d.h"

Dft::Dft(char **sfile)
{       
	    error = 0;

		input_file = NULL;
	    output_file = NULL;

	    if(sfile[1] != "")
		{
			input_file = sfile[1];
		}

		if(sfile[2] != "")
		{
			output_file = sfile[2];
		}
        
	    //read bmp file and capture attributes
		bfp = new bmpfile();
		if(bfp->BmpfileRead(input_file) == -1)
		{
			error = -1;
			bfp->width = -1;
			return;
		}

        yy = new cmplx[bfp->width];				
        if(yy == NULL) 
		{
			printf("\n ERROR: Dft() - memory allocation issue\n");
			return;
		}
		
		YR = new double*[bfp->width];
        for(unsigned int i = 0; i < bfp->width; ++i)
        YR[i] = new double[bfp->width]; 
        if (YR == NULL)
		{
			printf("\n ERROR: Dft() - memory allocation issue\n");
			return;
		}

	    YI = new double*[bfp->width];
        for(unsigned int i = 0; i < bfp->width; ++i)
        YI[i] = new double[bfp->width]; 
        if (YI == NULL) 
		{
			printf("\n ERROR: Dft() - memory allocation issue\n");
			return;
		}        
}

Dft::~Dft()
{          
	if(bfp->width != -1)
	{
		for(unsigned int i=0; i<bfp->width; i++) 
		{
			delete [] cplxOutarr_r[i];
			delete [] cplxOutarr_g[i];
			delete [] cplxOutarr_b[i];
			delete [] YR[i];
			delete [] YI[i];
		}
	
		delete [] cplxOutarr_r;
		delete [] cplxOutarr_g;
		delete [] cplxOutarr_b;
		delete [] YR;
		delete [] YI;

		cplxOutarr_r = NULL;
		cplxOutarr_g = NULL;
		cplxOutarr_b = NULL;
		YR = NULL;
		YI = NULL;
	
		delete [] yy;
		yy = NULL;

		if(bfp != NULL)
			delete bfp;
	}
}

int Dft::dft1()
{
        unsigned int m, n, k;
		
		cplxbuff = new cmplx[bfp->width];
        if(cplxbuff == NULL) 
		{
			return -1;
		}
		
		ibuff_rgb = new int*[bfp->width];
		for(unsigned int i = 0; i < 3; i++)
		ibuff_rgb[i] = new int[bfp->width];
        if(ibuff_rgb == NULL) 
		{
			return -1;
		}   
        
        cplxOutarr_r = new cmplx*[bfp->width];
        for(unsigned int i = 0; i < bfp->height; i++)
        cplxOutarr_r[i] = new cmplx[bfp->height]; 

		cplxOutarr_g = new cmplx*[bfp->width];
        for(unsigned int i = 0; i < bfp->height; i++)
        cplxOutarr_g[i] = new cmplx[bfp->height]; 

		cplxOutarr_b = new cmplx*[bfp->width];
        for(unsigned int i = 0; i < bfp->height; i++)
        cplxOutarr_b[i] = new cmplx[bfp->height]; 
        
        if ((cplxOutarr_r == NULL)||((cplxOutarr_g == NULL))||((cplxOutarr_b == NULL))) {
        return -1;
        }    
       
	   for( k=0; k < bfp->height; k++ )                     
	   {
		for(n=0; n < bfp->width; n++)
		{
			//only taking column values
			//ibuff[n] = bfp->image_r[n][k];		   
			ibuff_rgb[0][n] = bfp->image_r[n][k];		   
			ibuff_rgb[1][n] = bfp->image_g[n][k];
			ibuff_rgb[2][n] = bfp->image_b[n][k];

		}                 
		      //only computing column vise fft	
              if( dft_oneD(ibuff_rgb[0],bfp->width) != true)
              {
				  printf("\nERROR: dft1() ...");
                    return -1;
              }
			  for(m=0; m < bfp->width; m++)         
			  {
					cplxOutarr_r[m][k].r = yy[m].r;                 
					cplxOutarr_r[m][k].img = yy[m].img;
			  }

			  if( dft_oneD(ibuff_rgb[1],bfp->width) != true)
              {
				  printf("\nERROR: dft1() ...");
                    return -1;
              }
			  for(m=0; m < bfp->width; m++)         
			  {
					cplxOutarr_g[m][k].r = yy[m].r;                 
					cplxOutarr_g[m][k].img = yy[m].img;
			  }

			  if( dft_oneD(ibuff_rgb[2],bfp->width) != true)
              {
				  printf("\nERROR: dft1() ...");
                    return -1;
              }
			  for(m=0; m < bfp->width; m++)         
			  {
					cplxOutarr_b[m][k].r = yy[m].r;                 
					cplxOutarr_b[m][k].img = yy[m].img;
			  }
     }
     
	delete [] cplxbuff;
	cplxbuff = NULL;

    for(unsigned int i = 0; i < 3; i++)
	{
		delete [] ibuff_rgb[i];
	}
	delete [] ibuff_rgb;

	ibuff_rgb = NULL;
   
    return 0;
	
}

bool Dft::dft_oneD(int *x, int r)
{
	int n,l;
	double c1,c2,twedle,sp1=0.0,sp2=0.0;     

	for(l=0;l<r;l++)
	{
		for(n=0; n<r; n++){

			twedle = 2.0*(3.141592653589)*n*l/r;

			c1 = *(x+n)*cos(twedle);
			c2 = *(x+n)*sin(-twedle);

			sp1 = sp1+c1;
			sp2 = sp2+c2;
		}
		
		yy[l].r = sp1;
		yy[l].img = sp2;
		
		sp1 = 0.0;
		sp2 = 0.0;
	}
	
	return true;
}

int Dft::dft2()
{
	unsigned int k,m,cnt=0;
    int **temparr_f;
	int count = 0;
	double **temparr_r_rgb, **temparr_i_rgb;	

	int wd = 0;
	
	    temparr_r_rgb = new double*[bfp->width];
		for(unsigned int i = 0; i < 3; i++)
		temparr_r_rgb[i] = new double[bfp->width];

        if(temparr_r_rgb == NULL) 
		{
			return -1;
		}
		
		temparr_i_rgb = new double*[bfp->width];
		for(unsigned int i = 0; i < 3; i++)
		temparr_i_rgb[i] = new double[bfp->width];

        if(temparr_i_rgb == NULL) 
		{
			return -1;
		}
	
        temparr_f = new int*[bfp->width/2];
        for(unsigned int i = 0; i <bfp->width/2; ++i)
        temparr_f[i] = new int[bfp->width/2]; 
        if (temparr_f == NULL) {
        return -1;
        }

	    RY = new int*[bfp->width];
        for(unsigned int i = 0; i < bfp->width; ++i)
        RY[i] = new int[bfp->width]; 
        if (RY == NULL) {
        return -1;
        }

		BY = new int*[bfp->width];
        for(unsigned int i = 0; i < bfp->width; ++i)
        BY[i] = new int[bfp->width]; 
        if (BY == NULL) {
        return -1;
        }

		SY = new int*[bfp->width/2];
        for(unsigned int i = 0; i < bfp->width/2; ++i)
        SY[i] = new int[bfp->width/2]; 
        if (SY == NULL) {
        return -1;
        }

		GY = new int*[bfp->width];
        for(unsigned int i = 0; i < bfp->width; ++i)
        GY[i] = new int[bfp->width]; 
        if (GY == NULL) {
        return -1;
        }

	    YR = new double*[bfp->width];
        for(unsigned int i = 0; i < bfp->width; ++i)
        YR[i] = new double[bfp->width]; 
        if (YR == NULL) {
        return -1;
        }

	    YI = new double*[bfp->width];
        for(unsigned int i = 0; i < bfp->width; ++i)
        YI[i] = new double[bfp->width]; 
        if (YI == NULL) {
        return -1;
        }
        
        for(unsigned n=0;n<bfp->width;n++)                           
	    {
			for(k=0;k<bfp->width;k++)
			{
				temparr_r_rgb[0][k] = cplxOutarr_r[n][k].r;      
				temparr_i_rgb[0][k] = cplxOutarr_r[n][k].img;

				temparr_r_rgb[1][k] = cplxOutarr_g[n][k].r;      
				temparr_i_rgb[1][k] = cplxOutarr_g[n][k].img;

				temparr_r_rgb[2][k] = cplxOutarr_b[n][k].r;      
				temparr_i_rgb[2][k] = cplxOutarr_b[n][k].img;
			}

		bool res = dft_OneD2(temparr_r_rgb[0],temparr_i_rgb[0],bfp->width);
		
		for(m=0;m<bfp->width;m++)
		{
			YR[n][m] = yi[m].r;
			YI[n][m] = yi[m].img;
			
			if(YR[n][m] == YR[n][m]*(-1)) YR[n][m]*=(-1);
			if(YI[n][m] == YI[n][m]*(-1)) YI[n][m]*=(-1);
				
			RY[n][m] =  (int) abs(YR[n][m]*YR[n][m] + YI[n][m]*YI[n][m]);
			RY[n][m] = (int)sqrt(RY[n][m]*1.0)/bfp->width;
		}

		res = dft_OneD2(temparr_r_rgb[1],temparr_i_rgb[1],bfp->width);
		
		for(m=0;m<bfp->width;m++)
		{
			YR[n][m] = yi[m].r;
			YI[n][m] = yi[m].img;
			
			if(YR[n][m] == YR[n][m]*(-1)) YR[n][m]*=(-1);
			if(YI[n][m] == YI[n][m]*(-1)) YI[n][m]*=(-1);
				
			BY[n][m] =  (int) abs(YR[n][m]*YR[n][m] + YI[n][m]*YI[n][m]);
			BY[n][m] = (int)sqrt(BY[n][m]*1.0)/bfp->width;
		}

		res = dft_OneD2(temparr_r_rgb[2],temparr_i_rgb[2],bfp->width);
		
		for(m=0;m<bfp->width;m++)
		{
			YR[n][m] = yi[m].r;
			YI[n][m] = yi[m].img;
			
			if(YR[n][m] == YR[n][m]*(-1)) YR[n][m]*=(-1);
			if(YI[n][m] == YI[n][m]*(-1)) YI[n][m]*=(-1);
				
			GY[n][m] =  (int) abs(YR[n][m]*YR[n][m] + YI[n][m]*YI[n][m]);
			GY[n][m] = (int)sqrt(GY[n][m]*1.0)/bfp->width;
		}
	}

	//shift phase
	unsigned int temps = 0;
	for(unsigned int j = 0; j != bfp->width/2; ++j) 
	{    
		for(unsigned int i = 0; i != bfp->width/2; ++i) 
			{
				SY[j][i] = RY[bfp->width/2-j][bfp->width/2-i];
		    }
	}

	for(unsigned int j = 0; j != bfp->width/2; ++j) 
	{    
		for(unsigned int i = 0; i != bfp->width/2; ++i) 
			{
				RY[i][j] = SY[j][i];
		    }
	}

	for(unsigned int j = bfp->width/2; j != bfp->width; j++) 
	{    
		for(unsigned int i = bfp->width/2; i != bfp->width; i++) 
			{

				SY[j-bfp->width/2][i-bfp->width/2] = RY[bfp->width-j][bfp->width-i];
		    }
	}
	
	for(unsigned int j = 0; j != bfp->width/2; ++j) 
	{    
		for(unsigned int i = 0; i != bfp->width/2; ++i) 
			{
				RY[bfp->width/2+j][bfp->width/2+i] = SY[j][i];
		    }
	}


	for(unsigned int j = bfp->width/2; j != bfp->width; j++) 
	{    
		for(unsigned int i = 0; i != bfp->width/2; i++) 
			{

				SY[j-bfp->width/2][i] = RY[j][i];
		    }
	}
	
	for(unsigned int j = 0; j != bfp->width/2; ++j) 
	{    
		for(unsigned int i = 0; i != bfp->width/2; ++i) 
			{
				RY[bfp->width/2+j][i] = SY[i][j];
		    }
	}

	for(unsigned int j = 0; j != bfp->width/2; j++) 
	{    
		for(unsigned int i = bfp->width/2; i != bfp->width; i++) 
			{

				SY[j][i-bfp->width/2] = RY[j][i];
		    }
	}
	
	for(unsigned int j = 0; j != bfp->width/2; ++j) 
	{    
		for(unsigned int i = 0; i != bfp->width/2; ++i) 
			{
				RY[j][bfp->width/2+i] = SY[i][j];
		    }
	}

	for(unsigned int j = 0; j != bfp->width/2; ++j) 
	{    
		for(unsigned int i = 0; i != bfp->width/2; ++i) 
			{
				SY[j][i] = BY[bfp->width/2-j][bfp->width/2-i];
		    }
	}

	for(unsigned int j = 0; j != bfp->width/2; ++j) 
	{    
		for(unsigned int i = 0; i != bfp->width/2; ++i) 
			{
				BY[i][j] = SY[j][i];
		    }
	}

	for(unsigned int j = bfp->width/2; j != bfp->width; j++) 
	{    
		for(unsigned int i = bfp->width/2; i != bfp->width; i++) 
			{

				SY[j-bfp->width/2][i-bfp->width/2] = BY[bfp->width-j][bfp->width-i];
		    }
	}
	
	for(unsigned int j = 0; j != bfp->width/2; ++j) 
	{    
		for(unsigned int i = 0; i != bfp->width/2; ++i) 
			{
				BY[bfp->width/2+j][bfp->width/2+i] = SY[j][i];
		    }
	}


	for(unsigned int j = bfp->width/2; j != bfp->width; j++) 
	{    
		for(unsigned int i = 0; i != bfp->width/2; i++) 
			{

				SY[j-bfp->width/2][i] = BY[j][i];
		    }
	}
	
	for(unsigned int j = 0; j != bfp->width/2; ++j) 
	{    
		for(unsigned int i = 0; i != bfp->width/2; ++i) 
			{
				BY[bfp->width/2+j][i] = SY[i][j];
		    }
	}

	for(unsigned int j = 0; j != bfp->width/2; j++) 
	{    
		for(unsigned int i = bfp->width/2; i != bfp->width; i++) 
			{

				SY[j][i-bfp->width/2] = BY[j][i];
		    }
	}
	
	for(unsigned int j = 0; j != bfp->width/2; ++j) 
	{    
		for(unsigned int i = 0; i != bfp->width/2; ++i) 
			{
				BY[j][bfp->width/2+i] = SY[i][j];
		    }
	}

	for(unsigned int j = 0; j != bfp->width/2; ++j) 
	{    
		for(unsigned int i = 0; i != bfp->width/2; ++i) 
			{
				SY[j][i] = GY[bfp->width/2-j][bfp->width/2-i];
		    }
	}

	for(unsigned int j = 0; j != bfp->width/2; ++j) 
	{    
		for(unsigned int i = 0; i != bfp->width/2; ++i) 
			{
				GY[i][j] = SY[j][i];
		    }
	}

	for(unsigned int j = bfp->width/2; j != bfp->width; j++) 
	{    
		for(unsigned int i = bfp->width/2; i != bfp->width; i++) 
			{

				SY[j-bfp->width/2][i-bfp->width/2] = GY[bfp->width-j][bfp->width-i];
		    }
	}
	
	for(unsigned int j = 0; j != bfp->width/2; ++j) 
	{    
		for(unsigned int i = 0; i != bfp->width/2; ++i) 
			{
				GY[bfp->width/2+j][bfp->width/2+i] = SY[j][i];
		    }
	}


	for(unsigned int j = bfp->width/2; j != bfp->width; j++) 
	{    
		for(unsigned int i = 0; i != bfp->width/2; i++) 
			{

				SY[j-bfp->width/2][i] = GY[j][i];
		    }
	}
	
	for(unsigned int j = 0; j != bfp->width/2; ++j) 
	{    
		for(unsigned int i = 0; i != bfp->width/2; ++i) 
			{
				GY[bfp->width/2+j][i] = SY[i][j];
		    }
	}

	for(unsigned int j = 0; j != bfp->width/2; j++) 
	{    
		for(unsigned int i = bfp->width/2; i != bfp->width; i++) 
			{

				SY[j][i-bfp->width/2] = GY[j][i];
		    }
	}
	
	for(unsigned int j = 0; j != bfp->width/2; ++j) 
	{    
		for(unsigned int i = 0; i != bfp->width/2; ++i) 
			{
				GY[j][bfp->width/2+i] = SY[i][j];
		    }
	}

	//write to file
	for(unsigned int j = 0; j != bfp->height; ++j) 
	{    
		for(unsigned int i = 0; i != bfp->width; ++i) 
			{
				bfp->image_r[j][i] = RY[j][i];
                bfp->image_g[j][i] = GY[j][i];  
                bfp->image_b[j][i] = BY[j][i];  
            }
    } 
    
	if(output_file != NULL)
	{
		bfp->BmpfileWrite(output_file);                       
	}
	else
	{
		bfp->BmpfileWrite("dft.bmp");                       
	}

	//clean
	for(unsigned int i = 0; i < bfp->width; ++i)
	{
		delete [] RY[i];
		delete [] GY[i];
		delete [] BY[i];
	}

	for(unsigned int i = 0; i < bfp->width/4; ++i)
	{
		delete [] SY[i];
	}

	delete [] SY;

	delete [] RY;
	delete [] BY;
	delete [] GY;

	RY = NULL;
	BY = NULL;
	GY = NULL;

	delete [] temparr_f;
	temparr_f = NULL;

	for(unsigned int i = 0; i < 3; ++i)
	{
		delete [] temparr_r_rgb[i];
	}

	delete [] temparr_r_rgb;
	temparr_r_rgb = NULL;

	delete [] temparr_i_rgb;
	temparr_i_rgb = NULL;

	return 0;
}

bool Dft::dft_OneD2(double* xr, double* xi, unsigned int row)
{
	unsigned int n,k;
	double c1,c2,twedle,sp1=0.0,sp2=0.0;

	yi = new cmplx[bfp->width];
    if(yi == NULL) 
	{
		return false;
	}

	for(k=0;k<row;k++)
	{
		for(n=0;n<row;n++){

			twedle = 2.0*(3.141592653589)*n*k/row;

			c1 = xr[n]*cos(twedle)+xi[n]*sin(twedle);
			c2 = xi[n]*cos(twedle)-xr[n]*sin(twedle);

			sp1 = sp1+c1;
			sp2 = sp2+c2;
		}

		yi[k].r = sp1;
		yi[k].img = sp2;
		
		sp1 = 0.0;
		sp2 = 0.0;
	}   //loop k ends

	return true;
}

void Dft::dft_trans()
{
	 //first call 1d dft
     if(dft1() == -1)
	 {
		 printf("Dft1d - error\n");
	 }
     else
	 {
		 printf("Dft1d - success\n");
	 }
	 
	 //call 2d dft
     if(dft2() != 0)
	 {
       printf("dft2d - error\n");
     }
	 else
	 {
		printf("dft2d - success\n");
	 }
}
