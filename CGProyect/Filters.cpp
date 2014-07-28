#include "stdafx.h"
#include "Filters.h"
#include <algorithm>

CFilters::CFilters(){

}


/**
* Min filter
*/
void CFilters::Min(float *original, float *result, int w, int h, int dim){


	float * filter = new float[dim * dim];
	int total_dim = dim *dim;
	float minred = 250.0, mingreen = 250.0, minblue = 250.0; 

	for(int i=0;i<total_dim;++i) filter[i] = 1.0f;	 

    //apply the filter 
	for(int y = 0; y < h; y++) 
		for(int x = 0; x < w; x++) 
		{ 
			minred = 255.0;
			mingreen = 255.0;
			minblue = 255.0; 
         
			//multiply every value of the filter with corresponding image pixel 
			for(int filterX = 0; filterX < dim; filterX++) 
				for(int filterY = 0; filterY < dim; filterY++) 
				{ 
					int imageX = (x + w - dim / 2 + filterX) % w; 
					int imageY = (y + h - dim / 2 + filterY) % h; 

					minred = min(original[imageY * 3* w + imageX * 3] * filter[filterY * dim + filterX], minred); 
					mingreen = min(original[imageY * 3 * w + imageX * 3 + 1] * filter[filterY * dim + filterX], mingreen); 
					minblue = min(original[imageY * 3* w + imageX * 3 + 2] * filter[filterY * dim + filterX], minblue); 
				} 
        
			//truncate values smaller than zero and larger than 255 
			result[y * w * 3 + x * 3] = min( max(minred, 0.0f) , 255.f); 
			result[y * w * 3 + x * 3 + 1] = min(max(mingreen, 0.0f), 255.f); 
			result[y * w * 3 + x * 3 + 2] = min( max(minblue, 0.0f) , 255.f);
		}

	delete [] filter;
}

/**
* Max filter
*/
void CFilters::Max(float *original, float *result, int w, int h, int dim){


	float * filter = new float[dim * dim];
	int total_dim = dim *dim;
	float minred = 0.0, mingreen = 0.0, minblue = 0.0; 

	for(int i=0;i<total_dim;++i) filter[i] = 1.0f;	 

    //apply the filter 
	for(int y = 0; y < h; y++) 
		for(int x = 0; x < w; x++)
		{ 
			minred = 0.0;
			mingreen = 0.0;
			minblue = 0.0; 
         
			//multiply every value of the filter with corresponding image pixel 
			for(int filterX = 0; filterX < dim; filterX++) 
				for(int filterY = 0; filterY < dim; filterY++) 
				{ 
					int imageX = (x + w - dim / 2 + filterX) % w; 
					int imageY = (y + h - dim / 2 + filterY) % h; 

					minred = max(original[imageY * 3* w + imageX * 3] * filter[filterY * dim + filterX], minred); 
					mingreen = max(original[imageY * 3 * w + imageX * 3 + 1] * filter[filterY * dim + filterX], mingreen); 
					minblue = max(original[imageY * 3* w + imageX * 3 + 2] * filter[filterY * dim + filterX], minblue); 
				} 
        
			//truncate values smaller than zero and larger than 255 
			result[y * w * 3 + x * 3] = min( max(minred, 0.0f) , 255.f); 
			result[y * w * 3 + x * 3 + 1] = min(max(mingreen, 0.0f), 255.f); 
			result[y * w * 3 + x * 3 + 2] = min( max(minblue, 0.0f) , 255.f);
		}

	delete [] filter;
}


/**
* Box filter
*/
void CFilters::Box(float *original, float *result, int w, int h, int dim){


	float * filter = new float[dim * dim];
	int total_dim = dim *dim;
	float minred = 0.0, mingreen = 0.0, minblue = 0.0; 

	for(int i=0;i<total_dim;++i) filter[i] = 1.0f;	 

    //apply the filter 
	for(int y = 0; y < h; y++) 
		for(int x = 0; x < w; x++)
		{ 
			minred = 0.0;
			mingreen = 0.0;
			minblue = 0.0; 
         
			//multiply every value of the filter with corresponding image pixel 
			for(int filterX = 0; filterX < dim; filterX++) 
				for(int filterY = 0; filterY < dim; filterY++) 
				{ 
					int imageX = (x + w - dim / 2 + filterX) % w; 
					int imageY = (y + h - dim / 2 + filterY) % h; 

					minred += original[imageY * 3* w + imageX * 3] * filter[filterY * dim + filterX]; 
					mingreen += original[imageY * 3 * w + imageX * 3 + 1] * filter[filterY * dim + filterX]; 
					minblue += original[imageY * 3* w + imageX * 3 + 2] * filter[filterY * dim + filterX]; 
				} 
        
			//truncate values smaller than zero and larger than 255 
			result[y * w * 3 + x * 3] = min( max(minred/total_dim, 0.0f) , 255.f); 
			result[y * w * 3 + x * 3 + 1] = min(max(mingreen/total_dim, 0.0f), 255.f); 
			result[y * w * 3 + x * 3 + 2] = min( max(minblue/total_dim, 0.0f) , 255.f);
		}

	delete [] filter;
}


/**
* Median filter
*/
void CFilters::Median(float *original, float *result, int w, int h, int dim){

	int total_dim = dim *dim;
	float * filter = new float[total_dim];
	int mid_point = int(float(dim) / 2 * (dim + 1));
	float * color_arr_r = new float[total_dim];
	float * color_arr_g = new float[total_dim];
	float * color_arr_b = new float[total_dim];

	for(int i=0;i<total_dim;++i) filter[i] = 1.0f;	 

    //apply the filter 
	for(int y = 0; y < h; y++) 
		for(int x = 0; x < w; x++)
		{ 
			//multiply every value of the filter with corresponding image pixel 
			for(int filterX = 0; filterX < dim; filterX++) 
				for(int filterY = 0; filterY < dim; filterY++) 
				{ 
					int imageX = (x + w - dim / 2 + filterX) % w; 
					int imageY = (y + h - dim / 2 + filterY) % h; 

					color_arr_r[filterY * dim + filterX] = original[imageY * 3* w + imageX * 3] * filter[filterY * dim + filterX]; 
					color_arr_g[filterY * dim + filterX] = original[imageY * 3 * w + imageX * 3 + 1] * filter[filterY * dim + filterX]; 
					color_arr_b[filterY * dim + filterX] = original[imageY * 3* w + imageX * 3 + 2] * filter[filterY * dim + filterX]; 
				} 
        
			std::sort(color_arr_r,color_arr_r + total_dim);
			std::sort(color_arr_g,color_arr_g + total_dim);
			std::sort(color_arr_b,color_arr_b + total_dim);

			//truncate values smaller than zero and larger than 255 
			result[y * w * 3 + x * 3] = min( max(color_arr_r[mid_point], 0.0f) , 255.f); 
			result[y * w * 3 + x * 3 + 1] = min(max(color_arr_g[mid_point], 0.0f), 255.f); 
			result[y * w * 3 + x * 3 + 2] = min( max(color_arr_b[mid_point], 0.0f) , 255.f);
		}

	delete [] filter;
	delete [] color_arr_r;
	delete [] color_arr_g;
	delete [] color_arr_b;
}

/**
* Gaussian filter
*/
void CFilters::Gaussian(float *original, float *result, int w, int h, int dim){

	int total_dim = dim * dim;
	float * filter = new float[total_dim], div;

	if(dim == 3){
		filter[0 * dim + 0] = filter[2 * dim + 2] = filter[0 * dim + 2] = filter[2 * dim + 0] = 1;
		filter[0 * dim + 1] = filter[1 * dim + 0] = filter[1 * dim + 2] = filter[2 * dim + 1] = 2;
		filter[1 * dim + 1] = 4;
		div = 16;
	}else if(dim == 5){
		filter[0] = 1;		filter[1] = 4;		filter[2] = 7;		filter[3] = 4;		filter[4] = 1;
		filter[5] = 4;		filter[6] = 16;		filter[7] = 26;		filter[8] = 16;		filter[9] = 4;
		filter[10] = 7;		filter[11] = 26;	filter[12] = 41;	filter[13] = 26;	filter[14] = 7;
		filter[15] = 4;		filter[16] = 16;	filter[17] = 26;	filter[18] = 16;	filter[19] = 4;
		filter[20] = 1;		filter[21] = 4;		filter[22] = 7;		filter[23] = 4;		filter[24] = 1;
		div = 273;
	}else if(dim == 7){
		filter[0] = 1;		filter[1] = 4;		filter[2] = 8;		filter[3] = 10;		filter[4] = 8;		filter[5] = 4;		filter[6] = 1;		
		filter[7] = 4;		filter[8] = 12;		filter[9] = 25;		filter[10] = 29;	filter[11] = 25;	filter[12] = 12;	filter[13] = 4;	
		filter[14] = 8;		filter[15] = 25;	filter[16] = 49;	filter[17] = 58;	filter[18] = 49;	filter[19] = 25;	filter[20] = 8;		
		filter[21] = 10;	filter[22] = 29;	filter[23] = 58;	filter[24] = 67;	filter[25] = 58;	filter[26] = 29;	filter[27] = 10;		
		filter[28] = 8;		filter[29] = 25;	filter[30] = 49;	filter[31] = 58;	filter[32] = 49;	filter[33] = 25;	filter[34] = 8;	
		filter[35] = 4;		filter[36] = 12;	filter[37] = 25;	filter[38] = 29;	filter[39] = 25;	filter[40] = 12;	filter[41] = 4;	
		filter[42] = 1;		filter[43] = 4;		filter[44] = 8;		filter[45] = 10;	filter[46] = 8;		filter[47] = 4;		filter[48] = 1;	
		filter[2 * dim + 2] = 67;
		div = 999;
	}

	float minred = 0.0, mingreen = 0.0, minblue = 0.0;	 

    //apply the filter 
	for(int y = 0; y < h; y++) 
		for(int x = 0; x < w; x++) 
		{ 
			minred = 0.0;
			mingreen = 0.0;
			minblue = 0.0; 
         
			//multiply every value of the filter with corresponding image pixel 
			for(int filterX = 0; filterX < dim; filterX++) 
				for(int filterY = 0; filterY < dim; filterY++) 
				{ 
					int imageX = (x + w - dim / 2 + filterX) % w; 
					int imageY = (y + h - dim / 2 + filterY) % h; 

					minred += original[imageY * 3* w + imageX * 3] * filter[filterY * dim + filterX]; 
					mingreen += original[imageY * 3 * w + imageX * 3 + 1] * filter[filterY * dim + filterX]; 
					minblue += original[imageY * 3* w + imageX * 3 + 2] * filter[filterY * dim + filterX]; 
				} 
        
			//truncate values smaller than zero and larger than 255 
			result[y * w * 3 + x * 3] = min( max(minred/div, 0.0f) , 255.f); 
			result[y * w * 3 + x * 3 + 1] = min(max(mingreen/div, 0.0f), 255.f); 
			result[y * w * 3 + x * 3 + 2] = min( max(minblue/div, 0.0f) , 255.f);
		}
	
	delete [] filter;
}


/**
* Laplace filter
*/
void CFilters::Laplace(float *original, float *result, int w, int h){
	int dim = 3, total_dim = dim * dim;
	float * filter = new float[total_dim];
	filter[0 * dim + 0] = filter[2 * dim + 2] = filter[0 * dim + 2] = filter[2 * dim + 0] = 0;
	filter[0 * dim + 1] = filter[1 * dim + 0] = filter[1 * dim + 2] = filter[2 * dim + 1] = 1;
	filter[1 * dim + 1] = -4;

	float minred = 0.0, mingreen = 0.0, minblue = 0.0;	 

    //apply the filter 
	for(int y = 0; y < h; y++) 
		for(int x = 0; x < w; x++) 
		{ 
			minred = 0.0;
			mingreen = 0.0;
			minblue = 0.0; 
         
			//multiply every value of the filter with corresponding image pixel 
			for(int filterX = 0; filterX < dim; filterX++) 
				for(int filterY = 0; filterY < dim; filterY++) 
				{ 
					int imageX = (x + w - dim / 2 + filterX) % w; 
					int imageY = (y + h - dim / 2 + filterY) % h; 

					minred += original[imageY * 3* w + imageX * 3] * filter[filterY * dim + filterX]; 
					mingreen += original[imageY * 3 * w + imageX * 3 + 1] * filter[filterY * dim + filterX]; 
					minblue += original[imageY * 3* w + imageX * 3 + 2] * filter[filterY * dim + filterX]; 
				} 
        
			//truncate values smaller than zero and larger than 255 
			result[y * w * 3 + x * 3] = min( max(minred, 0.0f) , 255.f); 
			result[y * w * 3 + x * 3 + 1] = min(max(mingreen, 0.0f), 255.f); 
			result[y * w * 3 + x * 3 + 2] = min( max(minblue, 0.0f) , 255.f);
		}
		
	delete [] filter;
}

/**
* Sharpen filter
*/
void CFilters::Sharpen(float *original, float *result, int w, int h){
	int dim = 3, total_dim = dim * dim;
	float * filter = new float[total_dim];
	filter[0 * dim + 0] = filter[2 * dim + 2] = filter[0 * dim + 2] = filter[2 * dim + 0] = 0;
	filter[0 * dim + 1] = filter[1 * dim + 0] = filter[1 * dim + 2] = filter[2 * dim + 1] = -1;
	filter[1 * dim + 1] = 5;

	float minred = 0.0, mingreen = 0.0, minblue = 0.0;	 

    //apply the filter 
	for(int y = 0; y < h; y++) 
		for(int x = 0; x < w; x++) 
		{ 
			minred = 0.0;
			mingreen = 0.0;
			minblue = 0.0; 
         
			//multiply every value of the filter with corresponding image pixel 
			for(int filterX = 0; filterX < dim; filterX++) 
				for(int filterY = 0; filterY < dim; filterY++) 
				{ 
					int imageX = (x + w - dim / 2 + filterX) % w; 
					int imageY = (y + h - dim / 2 + filterY) % h; 

					minred += original[imageY * 3* w + imageX * 3] * filter[filterY * dim + filterX]; 
					mingreen += original[imageY * 3 * w + imageX * 3 + 1] * filter[filterY * dim + filterX]; 
					minblue += original[imageY * 3* w + imageX * 3 + 2] * filter[filterY * dim + filterX]; 
				} 
        
			//truncate values smaller than zero and larger than 255 
			result[y * w * 3 + x * 3] = min( max(minred, 0.0f) , 255.f); 
			result[y * w * 3 + x * 3 + 1] = min(max(mingreen, 0.0f), 255.f); 
			result[y * w * 3 + x * 3 + 2] = min( max(minblue, 0.0f) , 255.f);
		}
		
	delete [] filter;
}
