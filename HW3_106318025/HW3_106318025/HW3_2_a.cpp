/************************************************************/
/*  程式名稱：Plot the histogram of the HW3_1_a & HW3_1_b    */
/*  作者姓名：卓諭											*/
/*	    學號:106318025										*/
/*  指導教授：Dr.黃正民										*/
/*  電子郵件：t106318025@ntut.org.tw                         */
/*                                                          */
/*  問題描述：畫出 HW3_1_a & HW3_1_b 作業中原影像及輸出影像的	*/
/*           直方圖											*/
/*                                                          */
/*  輸入檔案：lena512.raw									*/
/*           HW3_1_a.raw									*/
/*			 cameraman_b512.raw								*/
/*			 HW3_1_b1.raw									*/
/*			 HW3_1_b3.raw									*/
/*			 livingroom_d512.raw							*/
/*			 HW3_1_b2.raw									*/
/*			 HW3_1_b4.raw									*/
/*  輸出檔案：HW3_2_a_lena512_Hist.raw						*/
/*           HW3_2_a_lena512Negative_Hist.raw				*/
/*           HW3_2_a_cameraman_Hist.raw						*/
/*           HW3_2_a_cameramanPowLaw_Hist.raw				*/
/*           HW3_2_a_cameramanPiWiLi_Hist.raw				*/
/*           HW3_2_a_livingroom_Hist.raw					*/
/*           HW3_2_a_livingroomPowLaw_Hist.raw				*/
/*           HW3_2_a_livingroomPiwiLi_Hist.raw				*/
/************************************************************/
#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;

void histogram(FILE *filein, FILE *fileout)
{
	int getpix;
	int Cal[256];
	int total = 0;
	int MAX = 0;
	unsigned char Hist[256][256];
	/*------------------------------初始化矩陣------------------------------*/
	for (int i = 0; i < 256; i++)
	{
		Cal[i] = 0;
	}
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			Hist[i][j] = 0;
		}
	}
	/*------------------------------累計每像素值數量------------------------------*/
	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			getpix = fgetc(filein);
			Cal[getpix] = Cal[getpix] + 1;
		}
	}
	fclose(filein);
	/*------------------------------找最大值------------------------------*/
	for (int i = 0; i < 256; i++)
	{
		if (Cal[i]>MAX)
		{
			MAX = Cal[i];
		}
		//printf("像素值=%d，有%d個\n",i ,Cal[i]);
	}
	//printf("Total：%d\n MAX=%d", total,MAX);
	//system("pause");
	/*------------------------------畫直方圖------------------------------*/
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < Cal[i] * 255 / MAX; j++)
		{
			Hist[255 - j][i] = 255;
		}
	}
	fwrite(Hist, 1, 256 * 256, fileout);
	fclose(fileout);
}
int main()
{
	FILE *filein;
	FILE *fileout;

	filein = fopen("lena512.raw", "rb");
	fileout = fopen("HW3_2_a_lena512_Hist.raw", "wb");
	histogram(filein, fileout);

	filein = fopen("HW3_1_a.raw", "rb");
	fileout = fopen("HW3_2_a_lena512Negative_Hist.raw", "wb");
	histogram(filein, fileout);

	filein = fopen("cameraman_b512.raw", "rb");
	fileout = fopen("HW3_2_a_cameraman_Hist.raw", "wb");
	histogram(filein, fileout);

	filein = fopen("HW3_1_b1.raw", "rb");
	fileout = fopen("HW3_2_a_cameramanPowLaw_Hist.raw", "wb");
	histogram(filein, fileout);

	filein = fopen("HW3_1_b3.raw", "rb");
	fileout = fopen("HW3_2_a_cameramanPiWiLi_Hist.raw", "wb");
	histogram(filein, fileout);

	filein = fopen("livingroom_d512.raw", "rb");
	fileout = fopen("HW3_2_a_livingroom_Hist.raw", "wb");
	histogram(filein, fileout);

	filein = fopen("HW3_1_b2.raw", "rb");
	fileout = fopen("HW3_2_a_livingroomPowLaw_Hist.raw", "wb");
	histogram(filein, fileout);

	filein = fopen("HW3_1_b4.raw", "rb");
	fileout = fopen("HW3_2_a_livingroomPiwiLi_Hist.raw", "wb");
	histogram(filein, fileout);
}