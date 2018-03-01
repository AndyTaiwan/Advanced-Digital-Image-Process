/************************************************************/
/*  程式名稱：Distance and Path                              */
/*  作者姓名：卓諭                                           */
/*	    學號:106318025                                      */
/*  指導教授：Dr.黃正民                                       */
/*  電子郵件：t106318025@ntut.org.tw                         */
/*                                                          */
/*  問題描述：起點(25,89)終點(235,187)                        */
/*           找出對短路徑之距離以及畫出路徑                    */
/*                                                          */
/*  輸入檔案：maze_256.raw				                    */
/*  輸出檔案：HW2_5_D4.raw                                   */
/*           HW2_5_D8.raw                                   */
/************************************************************/
#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	FILE *filein = fopen("maze_256.raw", "rb");//宣告輸入檔案
	FILE *fileout;//宣告輸出檔案
	Mat image(256, 256, CV_8UC1, Scalar(0));
	int i, j;
	/*----------------------------讀取.RAW檔-------------------------------*/
	for (i = 0; i < 256; i++)
	{
		for (j = 0; j < 256; j++)
		{
			image.data[j + i * 256] = fgetc(filein);
		}
	}
	fclose(filein);
	/******************************************D4 distance******************************************/
	/*---------------------------初始化距離矩陣---------------------------*/
	int distance[256][256];
	for (i = 0; i < 256; i++)
	{
		for (j = 0; j < 256; j++)
		{
			distance[i][j] = 256*256;
		}
	}
	int a=0;//設定初始距離數
	distance[89][35] = a;
	int x = 35;
	int y = 89;
	bool flag_1 = 1;
	bool flag_2 = 1;
	while (flag_1)
	{
		for (i = 0; i < 256; i++)
		{
			for (j = 0; j < 256; j++)
			{
				if (distance[i][j]/*逐行掃*/ == a)
				{
					x = j;
					y = i;
					
					if (image.data[(x)+256 * (y - 1)] == 0 && distance[y - 1][x] == 256*256)//判斷上是否有路且沒走過
					{
						distance[y - 1][x] = distance[y][x] + 1;
						if (y - 1 == 187 && x == 235)//判斷是否到達終點
							flag_1 = 0;
					}
					if (image.data[(x)+256 * (y + 1)] == 0 && distance[y + 1][x] == 256 * 256)//判斷下是否有路且沒走過
					{
						distance[y + 1][x] = distance[y][x] + 1;
						if (y + 1 == 187 && x == 235)//判斷是否到達終點
							flag_1 = 0;
					}
					if (image.data[(x - 1) + 256 * (y)] == 0 && distance[y][x - 1] == 256 * 256)//判斷左是否有路且沒走過
					{
						distance[y][x - 1] = distance[y][x] + 1;
						if (y == 187 && x - 1 == 235)//判斷是否到達終點
							flag_1 = 0;
					}
					if (image.data[(x + 1) + 256 * (y)] == 0 && distance[y][x + 1] == 256 * 256)//判斷右是否有路且沒走過
					{
						distance[y][x + 1] = distance[y][x] + 1;
						if (y == 187 && x + 1 == 235)//判斷是否到達終點
							flag_1 = 0;
					}
				}		
			}
		}
		a = a + 1;
	}
	imshow("maze256", image);
	waitKey();
	printf("D4 distance shortest path = %d\n", distance[187][235]);
	system("pause");



	Mat New_image_1(256, 256, CV_8UC1, Scalar(0));
	fileout = fopen("HW2_5_D4.raw", "wb");
	int b = 1;
	New_image_1.data[235 + 256 * 187] = 255;
	while (flag_2)
	{
		for (i = 0; i < 256; i++)
		{
			for (j = 0; j < 256; j++)
			{
				if (distance[i][j] == (distance[187][235] - b) && (New_image_1.data[(j) + (i - 1) * 256] == 255 || New_image_1.data[(j) + (i + 1) * 256] == 255 || New_image_1.data[(j - 1) + (i) * 256] == 255 || New_image_1.data[(j + 1) + (i) * 256] == 255))
				{
					New_image_1.data[j + 256 * i] = 255;
					if (distance[i][j] == 0)
					{
						flag_2 = 0;
					}
				}
			}
		}b = b + 1;
	}
	fwrite(New_image_1.data, 1, 256 * 256, fileout);
	imshow("New_image_1", New_image_1);
	fclose(fileout);
	waitKey();
	/******************************************D8 distance******************************************/
	/*---------------------------初始化距離矩陣---------------------------*/
	int distance8[256][256];
	for (i = 0; i < 256; i++)
	{
		for (j = 0; j < 256; j++)
		{
			distance8[i][j] = 256 * 256;
		}
	}
	int aa = 0;//設定初始距離數
	distance8[89][35] = aa;
	x = 35;
	y = 89;
	bool flag_11 = 1;
	bool flag_22 = 1;

	while (flag_11)
	{
		for (i = 0; i < 256; i++)
		{
			for (j = 0; j < 256; j++)
			{
				if (distance8[i][j]/*逐行掃*/ == aa)
				{
					x = j;
					y = i;

					if (image.data[(x)+256 * (y - 1)] == 0 && distance8[y - 1][x] == 256 * 256)//判斷上是否有路且沒走過
					{
						distance8[y - 1][x] = distance8[y][x] + 1;
						if (y - 1 == 187 && x == 235)//判斷是否到達終點
							flag_11 = 0;
					}
					if (image.data[(x)+256 * (y + 1)] == 0 && distance8[y + 1][x] == 256 * 256)//判斷下是否有路且沒走過
					{
						distance8[y + 1][x] = distance8[y][x] + 1;
						if (y + 1 == 187 && x == 235)//判斷是否到達終點
							flag_11 = 0;
					}
					if (image.data[(x - 1) + 256 * (y)] == 0 && distance8[y][x - 1] == 256 * 256)//判斷左是否有路且沒走過
					{
						distance8[y][x - 1] = distance8[y][x] + 1;
						if (y == 187 && x - 1 == 235)//判斷是否到達終點
							flag_11 = 0;
					}
					if (image.data[(x + 1) + 256 * (y)] == 0 && distance8[y][x + 1] == 256 * 256)//判斷右是否有路且沒走過
					{
						distance8[y][x + 1] = distance8[y][x] + 1;
						if (y == 187 && x + 1 == 235)//判斷是否到達終點
							flag_11 = 0;
					}
					if (image.data[(x - 1) + 256 * (y - 1)] == 0 && distance8[y - 1][x - 1] == 256 * 256)//判斷左上是否有路且沒走過
					{
						distance8[y - 1][x - 1] = distance8[y][x] + 1;
						if (y - 1 == 187 && x - 1 == 235)//判斷是否到達終點
							flag_11 = 0;
					}
					if (image.data[(x - 1) + 256 * (y + 1)] == 0 && distance8[y + 1][x - 1] == 256 * 256)//判斷左下是否有路且沒走過
					{
						distance8[y + 1][x - 1] = distance8[y][x] + 1;
						if (y + 1 == 187 && x - 1 == 235)//判斷是否到達終點
							flag_11 = 0;
					}
					if (image.data[(x + 1) + 256 * (y - 1)] == 0 && distance8[y - 1][x + 1] == 256 * 256)//判斷右上是否有路且沒走過
					{
						distance8[y - 1][x + 1] = distance8[y][x] + 1;
						if (y - 1 == 187 && x + 1 == 235)//判斷是否到達終點
							flag_11 = 0;
					}
					if (image.data[(x + 1) + 256 * (y + 1)] == 0 && distance8[y + 1][x + 1] == 256 * 256)//判斷右下是否有路且沒走過
					{
						distance8[y + 1][x + 1] = distance8[y][x] + 1;
						if (y + 1 == 187 && x + 1 == 235)//判斷是否到達終點
							flag_11 = 0;
					}
				}
			}
		}
		aa = aa + 1;
	}
	printf("D8 distance shortest path = %d\n", distance8[187][235]);
	system("pause");

	Mat New_image_2(256, 256, CV_8UC1, Scalar(0));
	fileout = fopen("HW2_5_D8.raw", "wb");
	int bb = 1;
	New_image_2.data[235 + 256 * 187] = 255;
	while (flag_22)
	{
		for (i = 0; i < 256; i++)
		{
			for (j = 0; j < 256; j++)
			{
				if (distance8[i][j] == (distance8[187][235] - bb) && (New_image_2.data[(j)+(i - 1) * 256] == 255 || New_image_2.data[(j)+(i + 1) * 256] == 255 || New_image_2.data[(j - 1) + (i)* 256] == 255 || New_image_2.data[(j + 1) + (i)* 256] == 255 || New_image_2.data[(j + 1) + (i + 1) * 256] == 255 || New_image_2.data[(j + 1) + (i - 1) * 256] == 255 || New_image_2.data[(j - 1) + (i - 1) * 256] == 255 || New_image_2.data[(j - 1) + (i + 1)* 256] == 255))
				{
					New_image_2.data[j + 256 * i] = 255;
					if (distance8[i][j] == 0)
					{
						flag_22 = 0;
					}
				}
			}
		}bb = bb + 1;
	}
	fwrite(New_image_2.data, 1, 256 * 256, fileout);
	imshow("New_image_2", New_image_2);
	fclose(fileout);
	waitKey();
}