/************************************************************/
/*  程式名稱：顯示.raw檔圖像	    						    */
/*  作者姓名：卓諭                                           */
/*	    學號:106318025                                      */
/*  指導教授：Dr.黃正民                                       */
/*  電子郵件：t106318025@ntut.org.tw                         */
/*                                                          */
/*  問題描述：這個程式將顯示輸入的.raw檔灰階圖像                */
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
	Mat figure(256, 256, CV_8UC1, Scalar(0));//利用OpenCV函示庫宣告一個256*256的矩陣空間
	FILE *filein;//利用C++函示庫宣告一個filein以存放開啟檔案後的位址
	int col = 256;//設定要行向量要掃描幾個pixel
	int row = 256;//設定要列向量要掃描幾個pixel
	int i, j;

	filein = fopen("lena256.raw", "rb");//fopen()會傳回一個FILE實例的位址值到filein，"rb"表只讀取一個二進制資料
	for (j = 0; j < row; j++)
	{
		for (i = 0; i < col; i++)
		{
			figure.data[i + j*row] = fgetc(filein);//fgetc()傳入FILE實例的位址值，每執行一次就會從檔案中讀取一個字元，直到讀到檔尾(End of File, EOF)為止
		}
	}

	imshow("lena256.raw", figure);//顯示影像
	waitKey(0);
	fclose(filein);//用 fclose() 函數來將開啟的檔案關閉，這樣資料才會真正寫入
}
