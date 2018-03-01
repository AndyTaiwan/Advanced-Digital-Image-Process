/************************************************************/
/*  程式名稱：影像2.75倍放大                                  */
/*  作者姓名：卓諭                                           */
/*	    學號:106318025                                      */
/*  指導教授：Dr.黃正民                                      */
/*  電子郵件：t106318025@ntut.org.tw                         */
/*                                                          */
/*  問題描述：利用nearest neighbor,bilinear,bicubic放大影像   */
/*                                                          */
/*  輸入檔案：lena_256.raw				                    */
/*  輸出檔案：HW2_1_b_nearest.raw                            */
/*           HW2_1_b_bilinear.raw                           */
/*           HW2_1_b_bicubic.raw                            */
/*           HW2_1_b_lena258.raw                            */
/************************************************************/
#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;

void bicubic(float x);
double w;

int main()
{
	/*----------------------------讀取.RAW檔-------------------------------*/
	int i, j;
	int m1, n1;
	float m2, n2;
	int row = 256;
	int col = 256;
	FILE *filein = fopen("lena_256.raw", "rb");
	Mat image(256, 256, CV_8UC1, Scalar(0));
	for (j = 0; j < row; j++)
	{
		for (i = 0; i < col; i++)
		{
			image.data[i + j*row] = fgetc(filein);
		}
	}
	fclose(filein);
	/*----------------------------(Nearest Neighbor Interpolation)-------------------------------*/
	Mat zoomim_1(704, 704, CV_8UC1, Scalar(0));
	FILE *fileout = fopen("HW2_1_b_nearest.raw", "wb");
	//--------------------------zooming2.25------------------------------------
	for (j = 0; j < 704; j++)
	{
		for (i = 0; i < 704; i++)
		{
			m1 = i * 256 / 704; //對應到原圖上的x座標
			n1 = j * 256 / 704; //對應到原圖上的y座標
			zoomim_1.data[i + j * 704] = image.data[m1 + n1 * 256];
		}
	}
	fwrite(zoomim_1.data, 1, 704 * 704, fileout);
	fclose(fileout);
	/*-------------------------------(Bilinear Interpolation)-----------------------------------*/
	Mat zoomim_2(704, 704, CV_8UC1, Scalar(0));
	fileout = fopen("HW2_1_b_bilinear.raw", "wb");
	float a, b;
	//------------------------------zooming2.25-------------------------------
	for (j = 0; j < 704; j++)
	{
		for (i = 0; i < 704; i++)
		{
			m2 = i * (float)256 / 704; //m對應到原圖上的x座標(浮點數)
			n2 = j * (float)256 / 704; //n對應到原圖上的y座標(浮點數)
			m1 = m2;//浮點數轉成整數
			n1 = n2;
			a = abs(m2 - m1);//計算alpha值
			b = abs(n2 - n1);//計算beta值

			//判斷在右邊界及下邊界時的內插
			int add_m = m1 + 1;
			int add_n = n1 + 1;
			if (m1 == 255 && n1 != 255)
			{
				add_m = m1;
			}
			else if (m1 != 255 && n1 == 255)
			{
				add_n = n1;
			}
			else if (m1 == 255 && n1==255)
			{
				add_m = m1;
				add_n = n1;
			}
			//bilinear 公式
			zoomim_2.data[i + j * 704]
				= image.data[m1 + n1 * 256] * (1 - a)*(1 - b)
				+ image.data[add_m + n1 * 256] * a*(1 - b)
				+ image.data[m1 + add_n * 256] * (1 - a)*b
				+ image.data[add_m + add_n * 256] * a*b;
		}
	}
	fwrite(zoomim_2.data, 1, 704 * 704, fileout);
	fclose(fileout);
	/******************************************(Bicubic Interpolation)*********************************************/
	Mat zoomim_3(704, 704, CV_8UC1, Scalar(0));
	Mat lena258(258, 258, CV_8UC1, Scalar(0));
	fileout = fopen("HW2_1_b_bicubic.raw", "wb");//宣告輸出檔案
	FILE *fileout258 = fopen("HW2_1_b_lena258.raw", "wb");//將lena256向外延伸一個像素變258x258
	/*-------------------------------------將lena256向外延伸一個像素變258x258---------------------------------------*/
	for (j = 0; j < row; j++)
	{
		for (i = 0; i < col; i++)
		{
			lena258.data[(row + 2) + (i + 1) + j*(row + 2)] = image.data[i + j*row];//將256*256圖置中於258*258空間

			if (i == 0)
			{
				lena258.data[(row + 2) + i + j*(row + 2)] = image.data[i + j*row];//填補左排空像素
				if (j == 0)
				{
					lena258.data[0] = image.data[i + j*row];//填補左上空像素
				}
			}
			if (i == 255)
			{
				lena258.data[(row + 2) + (i + 2) + j*(row + 2)] = image.data[i + j*row];//填補右排空像素
				if (j == 255)
				{
					lena258.data[257 + 258 * 257] = image.data[i + j*row];//填補右下空像素
				}
			}
			if (j == 0)
			{
				lena258.data[(i + 1) + j*(row + 2)] = image.data[i + j*row];//填補上排空像素
				if (i == 255)
				{
					lena258.data[257 + 258 * 0] = image.data[i + j*row];//填補右上空像素
				}
			}
			if (j == 255)
			{
				lena258.data[(row + 3) + (i + 3) + j*(row + 3)] = image.data[i + j*row];//填補下排空像素
				if (i == 0)
				{
					lena258.data[0 + 258 * 257] = image.data[i + j*row];//填補左下空像素
				}
			}
		}
	}
	fwrite(lena258.data, 1, 258 * 258, fileout258);
	/*---------------------------------------------------------------------------------------------------------*/
	/*-------------------------------------將258*258放大成704*704-----------------------------------------------*/
	for (j = 0; j < 704; j++)
	{
		for (i = 0; i < 704; i++)
		{

			float f = 0;
			m2 = abs(i * (float)256 / 704); //m對應到原圖上的x座標(浮點數) -1為16*16之最左
			n2 = abs(j * (float)256  / 704); //n對應到原圖上的y座標(浮點數) -1為16*16之最上
			m1 = m2;//浮點數轉成整數
			n1 = n2;

			//做bicubic將對應至舊圖之近鄰16個像素做計算
			for (int j1 = -1; j1 < 3; j1++)
			{
				for (int i1 = -1; i1 < 3; i1++)
				{

					bicubic((m1 - m2) + i1);
					float Wx = w;
					bicubic((n1 - n2) + j1);
					float Wy = w;
					f = lena258.data[m1 + i1 + 258 * (n1 + j1)] * Wx*Wy + f;
					
				}
			}
			if (f < 0)
				f = 0;
			if (f > 255)
				f = 255;
			zoomim_3.data[i + j * 704] = (int)f;
		}
	}

	fwrite(zoomim_3.data, 1, 704 * 704, fileout);
	fclose(fileout);
	/*---------------------------------------------------------------------------------------------------------*/
	/*----------------------------------------------呈現影像----------------------------------------------------*/
	imshow("original", image);
	imshow("lena258", lena258);
	imshow("Nearest Neighbor_zoom", zoomim_1);
	imshow("Bilinear_zoom", zoomim_2);
	imshow("Bicubic_zoom", zoomim_3);
	waitKey(0);
}
/************************************************bicubic公式***************************************************/
void bicubic(float x)
{
	float a = -0.5;
	if (fabs(x) <= 1)
	{
		w = (a + 2)*pow(fabs(x), 3) - (a + 3)*pow(fabs(x), 2) + 1;
	}
	else if (fabs(x) > 1 && fabs(x) < 2)
	{
		w = a*pow(fabs(x), 3) - 5 * a*pow(fabs(x), 2) + 8 * a*fabs(x) - 4 * a;
	}
	else
	{
		w = 0;
	}
}