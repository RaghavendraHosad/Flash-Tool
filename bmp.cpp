// Author : prasadhosad@gmail.com  
// Date : 26/03/2017

#include "bmp.h"   
#include <windows.h>

//constructor
bmpfile::bmpfile()
{
   //Raw image data                                                      
   image_raw_array = NULL;
   image_raw_output = NULL;                                                
	
   //Raw R,G and B bands
   image_r = NULL;
   image_g = NULL;
   image_b = NULL;   
}

//destructor
bmpfile::~bmpfile()
{
              
    delete [] image_raw_array;
    delete [] image_raw_output;                                
                                                                 
	//clean
	for(unsigned int i = 0; i < height; ++i)    
       {
		   delete [] image_r[i];
           delete [] image_g[i];
           delete [] image_b[i];                                                              
       }
            
	delete [] image_r;
    delete [] image_g;
    delete [] image_b;                         
                                
    image_raw_array = NULL;
    image_raw_output = NULL;
                               
    image_r = NULL;
    image_g = NULL;
    image_b = NULL;
}                  

void bmpfile::updateheader()
{
    header[0] = 0x42;                      
    header[1] = 0x4d;
    header[2] = 0;
    header[3] = 0;
    header[4] = 0;
    header[5] = 0;
    header[6] = 0;
    header[7] = 0;
    header[8] = 0;
    header[9] = 0;
    header[10] = 54;
            
    header[11] = 0;
    header[12] = 0;
    header[13] = 0;
    header[14] = 40;
    header[15] = 0;
    header[16] = 0;
    header[17] = 0;
    header[18] = 0;
    header[19] = 0;
    header[20] = 0;
            
    header[21] = 0;
    header[22] = 0;
    header[23] = 0;
    header[24] = 0;
    header[25] = 0;
    header[26] =1;
    header[27] =0;
    header[28] =24;
    header[29] =0;
    header[30] =0;
            
    header[31] =0;
    header[32] =0;
    header[33] =0;
    header[34] =0;
    header[35] =0;
    header[36] =0;
    header[37] =0;
    header[38] =0;
    header[39] =0;
    header[40] =0;
            
    header[41] =0;
    header[42] =0;
    header[43] =0;
    header[44] =0;
    header[45] =0;
    header[46] =0;
    header[47] =0;
    header[48] =0;
    header[49] =0;
    header[50] =0;
            
    header[51] =0;
    header[52] =0; 
    header[53] =0;
    header[54] =0;           
             
    // file size  
    unsigned int file_size = (width) * (height) * 3 + (rgb_raw_data_offset);
    //printf("In updateheader\n");
    header[2] = (unsigned char)(file_size & 0x000000ff);
    header[3] = (file_size >> 8)  & 0x000000ff;
    header[4] = (file_size >> 16) & 0x000000ff;
    header[5] = (file_size >> 24) & 0x000000ff;
               
    // width
    header[18] = width & 0x000000ff;
    header[19] = (width >> 8)  & 0x000000ff;
    header[20] = (width >> 16) & 0x000000ff;
    header[21] = (width >> 24) & 0x000000ff;
               
    // height
    header[22] = height &0x000000ff;
    header[23] = (height >> 8)  & 0x000000ff;
    header[24] = (height >> 16) & 0x000000ff;
    header[25] = (height >> 24) & 0x000000ff;   
}
          
//Method open bmp file seperates header, raw data is stored in an arry
int bmpfile::BmpfileRead(const char *fname_s) 
{
	int bpp_check = 0;
                               
	fopen_s(&fp_read_bmp,fname_s,"rb");
    if (fp_read_bmp == NULL)
    {
		cout << "Error opening in file ";
        return -1;
    }

	//confirm 24bpp image, right now only supporting 24bpp
	// move offset to 18 to get width & height;
    fseek(fp_read_bmp, 28, SEEK_SET); 
    fread(&bpp_check,  sizeof(unsigned int), 1, fp_read_bmp);
	if(bpp_check != 24)
	{
		printf("\nERROR: BmpfileRead() - Works only for 24bpp image");		
		return -1;
	}
                                                  
    // move offset to 10 to find rgb raw data offset
    fseek(fp_read_bmp, 10, SEEK_SET);
    fread(&rgb_raw_data_offset, sizeof(unsigned int), 1, fp_read_bmp);

    // move offset to 18 to get width & height;
    fseek(fp_read_bmp, 18, SEEK_SET); 
    fread(&width,  sizeof(unsigned int), 1, fp_read_bmp);
    fread(&height, sizeof(unsigned int), 1, fp_read_bmp);
                                                                             
    // move offset to rgb_raw_data_offset to get RGB raw data
    fseek(fp_read_bmp, rgb_raw_data_offset, SEEK_SET);
                                                                                                
    //copy raw data into image_s array                                    
    image_raw_array = new unsigned char [width * height * 3];
    if (image_raw_array == NULL) 
	{
		printf("new - images_s error\n");
        return -1;
    }
                                       
    //Alocate memory buffer
    image_raw_output = new unsigned char [width * height * 3];
    if (image_raw_output == NULL) 
	{
       printf("new - image_t error\n");
       return -1;
    }
                                       
    //R
    image_r = new unsigned char*[width];
    for(unsigned int i = 0; i < height; ++i)
        image_r[i] = new unsigned char[height]; 
                                      
    if (image_r == NULL) 
	{
		printf("new - image_t error\n");
        return -1;
    }
    
	//G
    image_g = new unsigned char*[width];
    for(unsigned int i = 0; i < height; ++i)
       image_g[i] = new unsigned char[height]; 
                                       
    if (image_g == NULL) 
	{
		printf("new - image_t error\n");
        return -1;
    }
    //B
    image_b = new unsigned char*[width];
    for(unsigned int i = 0; i < height; ++i)
        image_b[i] = new unsigned char[height]; 
                                       
    if (image_b == NULL) 
	{
		printf("new - image_t error\n");
        return -1;
    }
    
	//store raw data into image_raw_array, now sufficient to hold 3 bands of data 
    fread(image_raw_array, sizeof(unsigned char), (size_t)(long)width * height * 3, fp_read_bmp);
                                        
    for(int y = 0; y != height; ++y) 
	{
		for(int x = 0; x != width; ++x) 
		{
			image_r[y][x] = *(image_raw_array + 3 * (width * y + x) + 2);
            image_g[y][x] = *(image_raw_array + 3 * (width * y + x) + 1);
            image_b[y][x] = *(image_raw_array + 3 * (width * y + x) + 0);			
        }
    }
                                              
    fclose(fp_read_bmp);     
	return 0;
}
               
//write bitmap into a new file      
int bmpfile::BmpfileWrite(const char *fname_t) 
{
	//write R,G,B into a single pixel pack            
    for(int y = 0; y != height; ++y) 
	{
		for(int x = 0; x != width; ++x) 
		{
			*(image_raw_output + 3 * (width * y + x) + 2) = image_r[y][x];  
            *(image_raw_output + 3 * (width * y + x) + 1) = image_g[y][x];
            *(image_raw_output + 3 * (width * y + x) + 0) = image_b[y][x];
        }
	}        
	//open copy image file             
    fp_write_bmp = fopen(fname_t, "wb");
    if (fp_write_bmp == NULL) 
    {
		cout << "Error opening out file";
        return -1;
    }
                                                              
     //calling update header method
     updateheader();
     // write header
     fwrite(header, sizeof(unsigned char), rgb_raw_data_offset, fp_write_bmp);
     // write image
     fwrite(image_raw_output, sizeof(unsigned char), (size_t)(long)width * height * 3, fp_write_bmp);
     
	 fclose(fp_write_bmp);
    return 0;
 }  

