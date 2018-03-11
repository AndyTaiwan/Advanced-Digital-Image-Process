#define _USE_MATH_DEFINES
#include <cstdio>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace cv;

int main()
{
	double M = 256.0, N = 256.0;
	double MAX_1 = 0.0;
	double MAX_2 = 0.0;

	double Total_RE_1 = 0.0;
	double Total_IM_1 = 0.0;
	double Total_RE_2 = 0.0;
	double Total_IM_2 = 0.0;
	double Total_re_1 = 0.0;
	double Total_im_1 = 0.0;
	double Total_re_2 = 0.0;
	double Total_im_2 = 0.0;

	double *RE_1 = new double[256 * 256];
	double *IM_1 = new double[256 * 256];
	double *RE_2 = new double[256 * 256];
	double *IM_2 = new double[256 * 256];
	double *re_1 = new double[256 * 256];
	double *im_1 = new double[256 * 256];
	double *re_2 = new double[256 * 256];
	double *im_2 = new double[256 * 256];

	unsigned char image_char_bw256[256 * 256];
	unsigned char image_char_bw256_rotate[256 * 256];
	unsigned char image_out_IDFT_1[256 * 256];
	unsigned char image_out_IDFT_2[256 * 256];

	FILE *filein;
	FILE *fileout;
	/*************************************讀檔*************************************/
	filein = fopen("blackwhite256.raw", "rb");
	fread(image_char_bw256, sizeof(image_char_bw256), 1, filein);//將影像資訊讀入char
	fclose(filein);
	filein = fopen("blackwhite256_rotate.raw", "rb");
	fread(image_char_bw256_rotate, sizeof(image_char_bw256_rotate), 1, filein);//將影像資訊讀入char
	fclose(filein);
	/***********************************對原影像做DFT***********************************/
	for (int v = 0; v < 256; v++)
	{
		for (int u = 0; u < 256; u++)
		{
			for (int y = 0; y < 256; y++)
			{
				for (int x = 0; x < 256; x++)
				{
					double theta_1 = 2 * M_PI*((double)(u + M / 2)*(double)x / M + (double)(v + N / 2)*(double)y / N);
					Total_RE_1 += (double)image_char_bw256[y * 256 + x] * cos(theta_1);
					Total_IM_1 += (double)image_char_bw256[y * 256 + x] * (-sin(theta_1));
					Total_RE_2 += (double)image_char_bw256_rotate[y * 256 + x] * cos(theta_1);
					Total_IM_2 += (double)image_char_bw256_rotate[y * 256 + x] * (-sin(theta_1));
				}
			}
			RE_1[v * 256 + u] = Total_RE_1;
			IM_1[v * 256 + u] = Total_IM_1;
			RE_2[v * 256 + u] = Total_RE_2;
			IM_2[v * 256 + u] = Total_IM_2;

			Total_RE_1 = 0.0;
			Total_IM_1 = 0.0;
			Total_RE_2 = 0.0;
			Total_IM_2 = 0.0;
		}
	}
	/***********************************對DFT輸出做IDFT***********************************/
	for (int y = 0; y < 256; y++)
	{
		for (int x = 0; x < 256; x++)
		{
			for (int v = 0; v < 256; v++)
			{
				for (int u = 0; u < 256; u++)
				{
					double theta_2 = 2 * M_PI*((double)u * (double)x / M + (double)v * (double)y / N);
					Total_re_1 += RE_1[v * 256 + u] * cos(theta_2) - IM_1[v * 256 + u] * sin(theta_2);
					Total_im_1 += RE_1[v * 256 + u] * sin(theta_2) + IM_1[v * 256 + u] * cos(theta_2);
					Total_re_2 += RE_2[v * 256 + u] * cos(theta_2) - IM_2[v * 256 + u] * sin(theta_2);
					Total_im_2 += RE_2[v * 256 + u] * sin(theta_2) + IM_2[v * 256 + u] * cos(theta_2);
				}
			}
			re_1[y * 256 + x] = Total_re_1;
			im_1[y * 256 + x] = Total_im_1;
			re_2[y * 256 + x] = Total_re_2;
			im_2[y * 256 + x] = Total_im_2;
			
			if (pow(pow(re_1[y * 256 + x], 2) + pow(im_1[y * 256 + x], 2), 0.5) > MAX_1)
			{
				MAX_1 = pow(pow(re_1[y * 256 + x], 2) + pow(im_1[y * 256 + x], 2), 0.5);
			}

			if (pow(pow(re_2[y * 256 + x], 2) + pow(im_2[y * 256 + x], 2), 0.5) > MAX_2)
			{
				MAX_2 = pow(pow(re_2[y * 256 + x], 2) + pow(im_2[y * 256 + x], 2), 0.5);
			}
			
			
			Total_re_1 = 0.0;
			Total_im_1 = 0.0;
			Total_re_2 = 0.0;
			Total_im_2 = 0.0;
		}
	}
	for (int y = 0; y < 256; y++)
	{
		for (int x = 0; x < 256; x++)
		{
			image_out_IDFT_1[y * 256 + x] = (unsigned char)(pow(pow(re_1[y * 256 + x], 2) + pow(im_1[y * 256 + x], 2), 0.5) * (double)255 / MAX_1);
			image_out_IDFT_2[y * 256 + x] = (unsigned char)(pow(pow(re_2[y * 256 + x], 2) + pow(im_2[y * 256 + x], 2), 0.5) * (double)255 / MAX_2);
		}
	}
	/***********************************寫檔***********************************/
	fileout = fopen("HW6_1_b_IDFT_1.raw", "wb");
	fwrite(image_out_IDFT_1, 256 * 256, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW6_1_b_IDFT_2.raw", "wb");
	fwrite(image_out_IDFT_2, 256 * 256, 1, fileout);
	fclose(fileout);
}