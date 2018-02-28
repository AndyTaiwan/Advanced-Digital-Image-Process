/************************************************************/
/*  程式名稱：旋轉圖像    	    						    */
/*  作者姓名：卓諭                                           */
/*	    學號:106318025                                      */
/*  指導教授：Dr.黃正民                                       */
/*  電子郵件：t106318025@ntut.org.tw                         */
/*                                                          */
/*  問題描述：這個程式將輸入的.raw檔灰階圖像做90度的旋轉         */
/*                                                          */
/*  輸入檔案：lena256.raw					                    */
/*  輸出檔案：利用imshow顯示一個二維矩陣(灰階圖像)              */
/*  需求項目：無                                             */
/************************************************************/
#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	FILE *filein;
	Mat figure(256, 256, CV_8UC1, Scalar(0));
	int col = 256;//設定要行向量要掃描幾個pixel
	int row = 256;//設定要列向量要掃描幾個pixel
	int i, j;

	filein = fopen("lena256.raw","rb");
	for (j = 0; j < row; j++)
	{
		for (i = 0; i < col; i++)
		{
			figure.data[256 * i+j] = fgetc(filein);
		}
	}
	fclose(filein);
	imshow("lena256_retate.raw", figure);
	waitKey(0);
}