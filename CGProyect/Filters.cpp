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
	for(int x = 0; x < w; x++) 
		for(int y = 0; y < h; y++) 
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
	for(int x = 0; x < w; x++) 
		for(int y = 0; y < h; y++) 
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
	for(int x = 0; x < w; x++) 
		for(int y = 0; y < h; y++) 
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
	for(int x = 0; x < w; x++) 
		for(int y = 0; y < h; y++) 
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

	/*int total_dim = dim *dim;
	float * filter = new float[total_dim];
	float minred = 0.0, mingreen = 0.0, minblue = 0.0;
	float * color_arr = new float[total_dim];

	for(int i=0;i<total_dim;++i) filter[i] = 1.0f;	 

    //apply the filter 
	for(int x = 0; x < w; x++) 
		for(int y = 0; y < h; y++) 
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
		
	delete [] filter;*/
}


/**
* Laplace filter
*/
void CFilters::Laplace(float *original, float *result, int w, int h){
	int total_dim = 3 * 3;
	float * filter = new float[total_dim];
	filter[0 * total_dim + 0] = filter[2 * total_dim + 2] = filter[0 * total_dim + 2] = filter[2 * total_dim + 0] = 0;
	filter[0 * total_dim + 1] = filter[1 * total_dim + 0] = filter[1 * total_dim + 2] = filter[2 * total_dim + 1] = 1;
	filter[1 * total_dim + 1] = -4;

	float minred = 0.0, mingreen = 0.0, minblue = 0.0;	 

    //apply the filter 
	for(int x = 0; x < w; x++) 
		for(int y = 0; y < h; y++) 
		{ 
			minred = 0.0;
			mingreen = 0.0;
			minblue = 0.0; 
         
			//multiply every value of the filter with corresponding image pixel 
			for(int filterX = 0; filterX < 3; filterX++) 
				for(int filterY = 0; filterY < 3; filterY++) 
				{ 
					int imageX = (x + w - 3 / 2 + filterX) % w; 
					int imageY = (y + h - 3 / 2 + filterY) % h; 

					minred += original[imageY * 3* w + imageX * 3] * filter[filterY * 3 + filterX]; 
					mingreen += original[imageY * 3 * w + imageX * 3 + 1] * filter[filterY * 3 + filterX]; 
					minblue += original[imageY * 3* w + imageX * 3 + 2] * filter[filterY * 3 + filterX]; 
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
	int total_dim = 3 * 3;
	float * filter = new float[total_dim];
	filter[0 * total_dim + 0] = filter[2 * total_dim + 2] = filter[0 * total_dim + 2] = filter[2 * total_dim + 0] = 0;
	filter[0 * total_dim + 1] = filter[1 * total_dim + 0] = filter[1 * total_dim + 2] = filter[2 * total_dim + 1] = 1;
	filter[1 * total_dim + 1] = -4;

	float minred = 0.0, mingreen = 0.0, minblue = 0.0;	 

    //apply the filter 
	for(int x = 0; x < w; x++) 
		for(int y = 0; y < h; y++) 
		{ 
			minred = 0.0;
			mingreen = 0.0;
			minblue = 0.0; 
         
			//multiply every value of the filter with corresponding image pixel 
			for(int filterX = 0; filterX < 3; filterX++) 
				for(int filterY = 0; filterY < 3; filterY++) 
				{ 
					int imageX = (x + w - 3 / 2 + filterX) % w; 
					int imageY = (y + h - 3 / 2 + filterY) % h; 

					minred += original[imageY * 3* w + imageX * 3] * filter[filterY * 3 + filterX]; 
					mingreen += original[imageY * 3 * w + imageX * 3 + 1] * filter[filterY * 3 + filterX]; 
					minblue += original[imageY * 3* w + imageX * 3 + 2] * filter[filterY * 3 + filterX]; 
				} 
        
			//truncate values smaller than zero and larger than 255 
			result[y * w * 3 + x * 3] += min( max(minred, 0.0f) , 255.f); 
			result[y * w * 3 + x * 3 + 1] += min(max(mingreen, 0.0f), 255.f); 
			result[y * w * 3 + x * 3 + 2] += min( max(minblue, 0.0f) , 255.f);
		}
		
	delete [] filter;
}
