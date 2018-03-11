#define _USE_MATH_DEFINES
#include <cstdio>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <time.h>

using namespace cv;
clock_t time0, time1;
int main()
{
	double M = 256.0, N = 256.0;
	double Total_re_1 = 0.0;
	double Total_im_1 = 0.0;
	double Total_re_2 = 0.0;
	double Total_im_2 = 0.0;
	double MAX_1 = 0.0;
	double MAX_2 = 0.0;
	double *re_1=new double[256 * 256];
	double *im_1=new double[256 * 256];
	double *re_2 = new double[256 * 256];
	double *im_2 = new double[256 * 256];

	unsigned char image_char_bw256[256*256];
	unsigned char image_char_bw256_rotate[256 * 256];
	unsigned char image_out_DFT_magnitude_1[256 * 256];
	unsigned char image_out_DFT_magnitude_2[256 * 256];
	unsigned char image_out_DFT_phase_1[256 * 256];
	unsigned char image_out_DFT_phase_2[256 * 256];
	FILE *filein;
	FILE *fileout;
	/*************************************讀檔*************************************/
	filein = fopen("blackwhite256.raw", "rb");
	fread(image_char_bw256, sizeof(image_char_bw256), 1, filein);//將影像資訊讀入char
	fclose(filein);
	filein = fopen("blackwhite256_rotate.raw", "rb");
	fread(image_char_bw256_rotate, sizeof(image_char_bw256_rotate), 1, filein);//將影像資訊讀入char
	fclose(filein);
	time0 = clock();//execution time
		for (int v = 0; v < 256; v++)
		{
			for (int u = 0; u < 256; u++)
			{
				for (int y = 0; y < 256; y++)
				{
					for (int x = 0; x < 256; x++)
					{
						double theta = 2 * M_PI*((double)(u + M / 2+0.5)*(double)x / M + (double)(v + N / 2+0.5)*(double)y / 256);
						Total_re_1 += (double)image_char_bw256[y * 256 + x] * cos(theta);
						Total_im_1 += (double)image_char_bw256[y * 256 + x] * (-sin(theta));
						Total_re_2 += (double)image_char_bw256_rotate[y * 256 + x] * cos(theta);
						Total_im_2 += (double)image_char_bw256_rotate[y * 256 + x] * (-sin(theta));
					}
				}
				re_1[v * 256 + u] = Total_re_1;
				im_1[v * 256 + u] = Total_im_1;
				re_2[v * 256 + u] = Total_re_2;
				im_2[v * 256 + u] = Total_im_2;
				//printf("re[%d]=%d\n", v * 256 + u, re[v * 256 + u]);
				//printf("im[%d]=%d\n\n", v * 256 + u, im[v * 256 + u]);
				if (log(1.0+pow(pow(re_1[v * 256 + u], 2) + pow(im_1[v * 256 + u], 2), 0.5)) > MAX_1)
				{
					MAX_1 = log(1.0 + pow(pow(re_1[v * 256 + u], 2) + pow(im_1[v * 256 + u], 2), 0.5));
				}
				if (log(1.0 + pow(pow(re_2[v * 256 + u], 2) + pow(im_2[v * 256 + u], 2), 0.5)) > MAX_2)
				{
					MAX_2 = log(1.0 + pow(pow(re_2[v * 256 + u], 2) + pow(im_2[v * 256 + u], 2), 0.5));
				}
				Total_re_1 = 0.0;
				Total_im_1 = 0.0;
				Total_re_2 = 0.0;
				Total_im_2 = 0.0;
			}
		}

		/*system("pause");*/
	for (int v = 0; v < 256; v++)
	{
		for (int u = 0; u < 256; u++)
		{
			image_out_DFT_magnitude_1[v * 256 + u] = log(1.0 + (pow(pow(re_1[v * 256 + u], 2) + pow(im_1[v * 256 + u], 2), 0.5))) * (double)255 / MAX_1;
			if (atan2(im_1[v * 256 + u] / (M*N), re_1[v * 256 + u] / (M*N)) <= 0.0)
			{
				image_out_DFT_phase_1[v * 256 + u] = (unsigned char)((atan2(im_1[v * 256 + u] / (M*N), re_1[v * 256 + u] / (M*N)) + 2 * M_PI) * 255 / (2 * M_PI));
			}
			if (atan2(im_1[v * 256 + u] / (M*N), re_1[v * 256 + u] / (M*N)) > 0.0)
			{
				image_out_DFT_phase_1[v * 256 + u] = (unsigned char)(atan2(im_1[v * 256 + u] / (M*N), re_1[v * 256 + u] / (M*N)) * 255 / (2 * M_PI));
			}
			
			image_out_DFT_magnitude_2[v * 256 + u] = log(1.0 + (pow(pow(re_2[v * 256 + u], 2) + pow(im_2[v * 256 + u], 2), 0.5))) * (double)255 / MAX_2;
			if (atan2(im_1[v * 256 + u] / (M*N), re_1[v * 256 + u] / (M*N)) <= 0.0)
			{
				image_out_DFT_phase_2[v * 256 + u] = (unsigned char)((atan2(im_2[v * 256 + u] / (M*N), re_2[v * 256 + u] / (M*N)) + 2 * M_PI) * 255 / (2 * M_PI));
			}
			if (atan2(im_1[v * 256 + u] / (M*N), re_1[v * 256 + u] / (M*N)) > 0.0)
			{
				image_out_DFT_phase_2[v * 256 + u] = (unsigned char)(atan2(im_2[v * 256 + u] / (M*N), re_2[v * 256 + u] / (M*N)) * 255 / (2 * M_PI));
			}

		}
	}
	time1 = clock();//execution time
	printf("DFT execution time (Two Image)= %d ms\n", time1 - time0);//execution time
	system("pause");
	fileout = fopen("HW6_1_a_magnitude_1.raw", "wb");
	fwrite(image_out_DFT_magnitude_1, 256 * 256, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW6_1_a_magnitude_2.raw", "wb");
	fwrite(image_out_DFT_magnitude_2, 256 * 256, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW6_1_a_phase_1.raw", "wb");
	fwrite(image_out_DFT_phase_1, 256 * 256, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW6_1_a_phase_2.raw", "wb");
	fwrite(image_out_DFT_phase_2, 256 * 256, 1, fileout);
	fclose(fileout);
}