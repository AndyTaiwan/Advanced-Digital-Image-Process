/************************************************************/
/*  程式名稱：Negative the image								*/
/*  作者姓名：卓諭											*/
/*	    學號:106318025										*/
/*  指導教授：Dr.黃正民										*/
/*  電子郵件：t106318025@ntut.org.tw							*/
/*                                                          */
/*  問題描述：將lena512.raw 做負片效果						*/
/*                                                          */
/*  輸入檔案：lena512.raw				                    */
/*  輸出檔案：HW3_1_a.raw                                    */
/************************************************************/
#include <cstdio>
#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
	FILE *filein = fopen("lena512.raw", "rb");//宣告輸入檔案
	FILE *fileout = fopen("HW3_1_a.raw", "wb");//宣告輸出檔案
	Mat image(512, 512, CV_8UC1, Scalar(0));
	/*----------------------------讀取.RAW檔-------------------------------*/
	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			image.data[j + i * 512] = 255 - fgetc(filein); //負片效果
		}
	}
	fwrite(image.data,1,512*512,fileout);
	imshow("HW3_1_a",image);
	waitKey();
	fclose(filein);
	fclose(fileout);
}
