/************************************************************/
/*  程式名稱：Enhance the image								*/
/*  作者姓名：卓諭											*/
/*	    學號:106318025										*/
/*  指導教授：Dr.黃正民										*/
/*  電子郵件：t106318025@ntut.org.tw							*/
/*                                                          */
/*  問題描述：利用1.Power-Law transformation					*/
/*              2.Piecewise-Linear transformation			*/
/*           處理cameraman_b512.raw、livingroom_d512.raw		*/
/*           存出轉換圖片並畫圖轉換曲線						*/
/*                                                          */
/*  輸入檔案：cameraman_b512.raw				                */
/*           livingroom_d512.raw                            */
/*  輸出檔案：HW3_1_b1.raw									*/
/*           HW3_1_b2.raw									*/
/*           HW3_1_b3.raw									*/
/*           HW3_1_b4.raw									*/
/*           HW3_1_b1_curve.raw								*/
/*           HW3_1_b2_curve.raw								*/
/*           HW3_1_b3_curve.raw								*/
/*           HW3_1_b4_curve.raw								*/
/************************************************************/
#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	FILE *filein1;
	FILE *filein2;
	FILE *fileout1 = fopen("HW3_1_b1.raw", "wb");//宣告輸出檔案
	FILE *fileout2 = fopen("HW3_1_b2.raw", "wb");//宣告輸出檔案
	FILE *fileout3 = fopen("HW3_1_b3.raw", "wb");//宣告輸出檔案
	FILE *fileout4 = fopen("HW3_1_b4.raw", "wb");//宣告輸出檔案
	FILE *fileout5 = fopen("HW3_1_b1_curve.raw", "wb");//宣告輸出檔案
	FILE *fileout6 = fopen("HW3_1_b2_curve.raw", "wb");//宣告輸出檔案
	FILE *fileout7 = fopen("HW3_1_b3_curve.raw", "wb");//宣告輸出檔案
	FILE *fileout8 = fopen("HW3_1_b4_curve.raw", "wb");//宣告輸出檔案
	Mat image1(512, 512, CV_8UC1, Scalar(0));//Power-Law cameraman
	Mat image2(512, 512, CV_8UC1, Scalar(0));//Power-Law livingroom
	Mat image3(512, 512, CV_8UC1, Scalar(0));//Piecewise-linear cameraman
	Mat image4(512, 512, CV_8UC1, Scalar(0));//Piecewise-linear livingroom
	unsigned char powlaw1[256][256];
	unsigned char powlaw2[256][256];
	unsigned char piwili1[256][256];
	unsigned char piwili2[256][256];
	int getpix;
	/*----------------------------Power-Law cameraman_b512.raw-------------------------------*/
	float r11 = 15;
	float c1 = 1;
	float in1, out1;
	filein1 = fopen("cameraman_b512.raw", "rb");
	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			getpix = fgetc(filein1);
			in1 = (float)getpix / 255;
			out1 = c1*(float)pow(in1, r11);
			image1.data[j + i * 512] = out1 * 255; //Gamma Transformation
		}
	}
	fwrite(image1.data, 1, 512 * 512, fileout1);
	imshow("HW3_1_b1", image1);
	//imshow("Histogram", Hist);
	fclose(filein1);
	fclose(fileout1);
	/*------------------------------------初始化曲線圖------------------------------------*/
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			powlaw1[i][j] = 0;
		}
	}
	/*------------------------------------繪製曲線------------------------------------*/
	for (int i = 0; i < 256; i++)
	{
		in1 = (float)i / 255;
		out1 = c1*(float)pow(in1, r11);
		int j = (int)255 * out1;

		powlaw1[255-j][i] = 255;

	}
	fwrite(powlaw1, 1, 256*256, fileout5);
	fclose(fileout5);
	/*----------------------------Power-Law livingroom_d512.raw-------------------------------*/
	float r22 = 0.95;
	float c2 = 6;
	float in2, out2;
	filein2 = fopen("livingroom_d512.raw", "rb");
	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			in2 = (float)fgetc(filein2) / 255;
			out2 = c2*(float)pow(in2, r22);
			if (out2 >= 1)
				out2 = 1;
			if (out2 <= 0)
				out2 = 0;

			image2.data[j + i * 512] = out2 * 255; //Gamma Transformation
		}
	}
	fwrite(image2.data, 1, 512 * 512, fileout2);
	imshow("HW3_1_b2", image2);
	//waitKey();
	fclose(filein2);
	fclose(fileout2);
	/*------------------------------------初始化曲線圖------------------------------------*/
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			powlaw2[i][j] = 0;
		}
	}
	/*------------------------------------繪製曲線------------------------------------*/
	for (int i = 0; i < 256; i++)
	{
		in2 = (float)i / 255;
		out2 = c2*(float)pow(in2, r22);
		int j = (int)255 * out2;
		if (j > 255)
			j = 255;
		powlaw2[255 - j][i] = 255;
	}
	fwrite(powlaw2, 1, 256*256, fileout6);
	fclose(fileout6);

	/*----------------------------Piecewise-linear cameraman_b512.raw-------------------------------*/
	int r1 = 80, r2 = 204;
	int s1 = 45, s2 = 60;
	filein1 = fopen("cameraman_b512.raw", "rb");
	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			getpix = fgetc(filein1);
			if (getpix < r1)
			{
				getpix = (getpix - 0)*s1 / r1;
			}
			else if (getpix >= r1 && getpix <= r2)
			{
				getpix = (getpix - r1)*(s2 - s1) / (r2 - r1) + s1;
			}
			else if (getpix >= r2)
			{
				getpix = (getpix - r2)*(255 - s2) / (255 - r2) + s2;
			}
			if (getpix >= 255)
			{
				getpix = 255;
			}
			if (getpix <= 0)
			{
				getpix = 0;
			}
			image3.data[j + i * 512] = getpix; 
		}
	}
	fwrite(image3.data, 1, 512 * 512, fileout3);
	imshow("HW3_1_b3", image3);
	//imshow("Histogram", Hist);
	//waitKey();
	fclose(filein1);
	fclose(fileout3);
	/*------------------------------------初始化曲線圖------------------------------------*/
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			piwili1[i][j] = 0;
		}
	}
	/*------------------------------------繪製曲線------------------------------------*/
	for (int i = 0; i < 256; i++)
	{
		int j;
		if (i < r1)
		{
			j = (float)(i - 0)*s1 / r1;
		}
		if (i >= r1 && i <= r2)
		{
			j = (float)(i - r1)*(s2 - s1) / (r2 - r1) + s1;
		}
		if (i >= r2)
		{
			j = (float)(i - r2)*(255 - s2) / (255 - r2) + s2;
		}
		if (j >= 255)
		{
			j = 255;
		}
		if (j <= 0)
		{
			j = 0;
		}
		piwili1[255 - j][i] = 255;

	}
	fwrite(piwili1, 1, 256 * 256, fileout7);
	fclose(fileout7);

	/*----------------------------Piecewise-linear livingroom_d512.raw------------------------------*/
	int rr1 = 15, rr2 = 25;
	int ss1 = 5, ss2 = 240;
	filein2 = fopen("livingroom_d512.raw", "rb");
	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			getpix = fgetc(filein2);
			if (getpix < rr1)
			{
				getpix = (float)(getpix - 0)*ss1 / rr1;
			}
			else if (getpix >= rr1 && getpix <= rr2)
			{
				getpix = (float)(getpix - rr1)*(ss2 - ss1) / (rr2 - rr1) + ss1;
			}
			else if (getpix >= rr2)
			{
				getpix = (float)(getpix - rr2)*(255 - ss2) / (255 - rr2) + ss2;
			}
			if (getpix >= 255)
			{
				getpix = 255;
			}
			if (getpix <= 0)
			{
				getpix = 0;
			}
			image4.data[j + i * 512] = getpix;
			//for (int k = 0; k < 512; k++)
			//{
			//	if (Hist.data[(getpix)+(256 * (256 ,  - 1 - k))] == 0)
			//	{
			//		Hist.data[(getpix)+(256 * (512  - 1 - k))] = 255;
			//		break;
			//	}
			//}
		}
	}
	fwrite(image4.data, 1, 512 * 512, fileout4);
	imshow("HW3_1_b4", image4);
	//imshow("Histogram", Hist);
	waitKey();
	fclose(filein2);
	fclose(fileout4);
	/*------------------------------------初始化曲線圖------------------------------------*/
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			piwili2[i][j] = 0;
		}
	}
	/*------------------------------------繪製曲線------------------------------------*/
	for (int i = 0; i < 256; i++)
	{
		int j;
		if (i < rr1)
		{
			j = (float)(i - 0)*ss1 / rr1;
		}
		if (i >= rr1 && i <= rr2)
		{
			j = (float)(i - rr1)*(ss2 - ss1) / (rr2 - rr1) + ss1;
		}
		if (i >= rr2)
		{
			j = (float)(i - rr2)*(255 - ss2) / (255 - rr2) + ss2;
		}
		if (j >= 255)
		{
			j = 255;
		}
		if (j <= 0)
		{
			j = 0;
		}
		piwili2[255 - j][i] = 255;
	}
	fwrite(piwili2, 1, 256 * 256, fileout8);
	fclose(fileout8);
}