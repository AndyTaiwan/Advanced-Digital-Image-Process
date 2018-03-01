/************************************************************/
/*  程式名稱：影像兩倍放大                                    */
/*  作者姓名：卓諭                                           */
/*	    學號:106318025                                      */
/*  指導教授：Dr.黃正民                                      */
/*  電子郵件：t106318025@ntut.org.tw                         */
/*                                                          */
/*  問題描述：利用row-column replication 去放大影像            */
/*                                                          */
/*  輸入檔案：lena_256.raw				                    */
/*  輸出檔案：HW2_1_a.raw                                    */
/************************************************************/
#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	FILE *filein = fopen("lena_256.raw", "rb");//宣告輸入檔案
	FILE *fileout = fopen("HW2_1_a.raw", "wb");//宣告輸出檔案

	Mat image(256, 256, CV_8UC1, Scalar(0));
	Mat zoomim(512, 512, CV_8UC1, Scalar(0));
	/*----------------------------讀取.RAW檔-------------------------------*/
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			image.data[j + i*256] = fgetc(filein);
		}
	}
	/*-----------------Zooming2:1(row-column replication)-----------------*/
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			zoomim.data[2 * (512 * i + j)] = image.data[j + 256 * i];
			zoomim.data[2 * (512 * i + j) + 1] = image.data[j + 256 * i];
			zoomim.data[512 * (2 * i + 1) + 2 * j] = image.data[j + 256 * i];
			zoomim.data[512 * (2 * i + 1) + 2 * j + 1] = image.data[j + 256 * i];
		}
	}
	/*-------------------------寫.RAW檔/顯示影像---------------------------*/
	fwrite(zoomim.data,1,512*512,fileout);
	imshow("lena_out", zoomim);
	fclose(fileout);
	fclose(filein);
	waitKey(0);
}