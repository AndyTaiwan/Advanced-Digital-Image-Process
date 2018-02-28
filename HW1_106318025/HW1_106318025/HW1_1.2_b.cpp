/************************************************************/
/*  程式名稱：找出圖像像素點資訊							    */
/*  作者姓名：卓諭                                           */
/*	    學號:106318025                                      */
/*  指導教授：Dr.黃正民                                       */
/*  電子郵件：t106318025@ntut.org.tw                         */
/*                                                          */
/*  問題描述：這個程式將根據使用者輸入的像素位置去獲得像素值      */
/*                                                          */
/*  輸入檔案：lena256.raw					                 */
/*  輸出檔案：從標準輸出檔輸出一個整數 (代表一個像素值)          */
/*  需求項目：無                                             */
/************************************************************/
#include "stdlib.h"
#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	
	Mat figure(256, 256, CV_8UC1, Scalar(0));//利用OpenCV函示庫宣告一個256*256的矩陣空間
	FILE *filein;//利用C++函示庫宣告一個filein以存放開啟檔案後的位址

	int input_row, input_col;//使用者輸入的像素位置
	int input_pix;//使用者輸入的第幾號像素
	int i, j;
	int pick;

	filein = fopen("lena256.raw", "rb");
	//fopen()會傳回一個FILE實際的位址值到filein，"rb"表只讀取一個二進制資料

	for (j = 0; j < 256; j++)
	{
		for (i = 0; i < 256; i++)
		{
			figure.data[i + j*256] = fgetc(filein);
			//fgetc()傳入FILE實例的位址值，每執行一次就會從檔案中讀取一個字元，直到讀到檔尾(End of File, EOF)為止
		}
	}
	fclose(filein);//用 fclose() 函數來將開啟的檔案關閉，這樣資料才會真正寫入
	/*-------------------選取要使用的像素位置表達方式並輸出該點像素值-----------------*/

	while (1)
	{
		printf(" 1.position of pixel\n ");
		printf("2.The number of the pixel\n ");
		printf(" Please choose a number : ");
		scanf("%d", &pick);
		switch (pick)
		{
		case 1:
			printf("input row :");
			scanf("%d", &input_row);
			printf("input col :");
			scanf("%d", &input_col);
			printf("The intensity value of the %dth row & %dth colum is :%d\n", input_row, input_col, figure.data[input_row * 256 + input_col]);
			system("pause");
			break;
		case 2:
			printf("The number of the pixel :");
			scanf("%d", &input_pix);
			printf("The intensity value of the %d th pixel is :%d\n", input_pix, figure.data[input_pix-1]);
			system("pause");
			break;
		default:
			printf("Are you an illiteracy ? \n");
			system("pause");
			printf("Such a poor guy\n");
			system("pause");
			break;
		}
	}
}
