/************************************************************/
/*  程式名稱：影像兩倍縮小                                    */
/*  作者姓名：卓諭                                           */
/*	    學號:106318025                                      */
/*  指導教授：Dr.黃正民                                      */
/*  電子郵件：t106318025@ntut.org.tw                        */
/*                                                         */
/*  問題描述：利用row-column replication                     */
/*           1.原圖縮小影像，                                */
/*           2.利用XnView將影像模糊化後再縮小，               */ 
/*           兩者比較。                                      */
/*                                                          */
/*  輸入檔案：lena_256.raw				                    */
/*           lena_256_blurring.raw                          */
/*  輸出檔案：HW2_1_c_with blurring.raw                      */
/*           HW2_1_c_without blurring.raw                   */
/************************************************************/
#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	FILE *filein_1 = fopen("lena_256.raw", "rb");//宣告輸入檔案
	FILE *filein_2 = fopen("lena_256_blurring.raw", "rb");//經XnView模糊化輸出的影像
	FILE *fileout_1 = fopen("HW2_1_c_with blurring.raw", "wb");//宣告輸出檔案
	FILE *fileout_2 = fopen("HW2_1_c_without blurring.raw", "wb");

	Mat image_1(256, 256, CV_8UC1, Scalar(0));
	Mat image_2(256, 256, CV_8UC1, Scalar(0));
	Mat shrinkim_1(128, 128, CV_8UC1, Scalar(0));
	Mat shrinkim_2(128, 128, CV_8UC1, Scalar(0));
	/*----------------------------讀取.RAW檔-------------------------------*/
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			image_1.data[j + i * 256] = fgetc(filein_1);
		}
	}
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			image_2.data[j + i * 256] = fgetc(filein_2);
		}
	}
	/*-----------------Shrinking1:2(row-column replication)-----------------*/
	for (int i = 0; i < 128; i++)
	{
		for (int j = 0; j < 128; j++)
		{
			shrinkim_1.data[j + 128 * i] = image_1.data[j * 2 + 256 * 2 * i];
		}
	}
	for (int i = 0; i < 128; i++)
	{
		for (int j = 0; j < 128; j++)
		{
			shrinkim_2.data[j + 128 * i] = image_2.data[j * 2 + 256 * 2 * i];
		}
	}
	/*-------------------------寫.RAW檔/顯示影像---------------------------*/
	fwrite(shrinkim_1.data, 1, 128 * 128, fileout_1);
	fwrite(shrinkim_2.data, 1, 128 * 128, fileout_2);
	imshow("lena_out_1", shrinkim_1);
	imshow("lena_out_2", shrinkim_2);
	fclose(fileout_1);
	fclose(filein_1);
	fclose(fileout_2);
	fclose(filein_2);
	waitKey(0);
}