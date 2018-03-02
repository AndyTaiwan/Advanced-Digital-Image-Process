/************************************************************/
/*  程式名稱：Histogram Equalization							*/
/*  作者姓名：卓諭											*/
/*	    學號:106318025										*/
/*  指導教授：Dr.黃正民										*/
/*  電子郵件：t106318025@ntut.org.tw							*/
/*                                                          */
/*  問題描述：利用 Histogram Equalization					*/
/*           處理cameraman_b512.raw、livingroom_d512.raw		*/
/*           存出轉換圖片並畫圖轉換曲線及直方圖				*/
/*                                                          */
/*  輸入檔案：cameraman_b512.raw								*/
/*           HW3_2_b_cameraman_HistoEqual.raw				*/
/*			 livingroom_d512.raw							*/
/*			 HW3_2_b_livingroom_HistoEqual.raw				*/
/*  輸出檔案：HW3_2_b_cameraman_Hist.raw						*/
/*           HW3_2_b_cameraman_HistAdd.raw					*/
/*           HW3_2_b_cameraman_HistoEqual.raw				*/
/*           HW3_2_b_cameraman_HistEqual_Hist.raw			*/
/*           HW3_2_b_livingroom_Hist.raw					*/
/*           HW3_2_b_livingroom_HistAdd.raw					*/
/*           HW3_2_b_livingroom_HistoEqual.raw				*/
/*           HW3_2_b_livingroom_HistEqual_Hist.raw			*/
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
void histoequal(FILE *filein, FILE *fileout, FILE *hist, Mat image, FILE *imagein, FILE *imageout)
{
	int getpix;
	int Cal[256];
	int Cal_h[256];
	int total = 0;
	int MAX = 0;
	int MAX_h = 0;
	unsigned char Accumulate[256][256];
	unsigned char Hist[256][256];
	/*------------------------------初始化矩陣------------------------------*/
	for (int i = 0; i < 256; i++)
	{
		Cal[i] = 0;
		Cal_h[i] = 0;
	}
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			Accumulate[i][j] = 0;
		}
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
			Cal_h[getpix] = Cal_h[getpix] + 1;
		}
	}
	fclose(filein);
	/*------------------------------找最大值Accumulate------------------------------*/
	for (int i = 0; i < 256; i++)
	{
		total = total + Cal[i];
		Cal[i] = total;
		if (Cal[i]>=MAX)
		{
			MAX = Cal[i];
		}
		//printf("像素值=%d，有%d個\n",i ,Cal[i]);
	}
	//printf("Total：%d\n MAX=%d", total,MAX);
	//system("pause");
	/*------------------------------畫像素累加圖------------------------------*/
	for (int i = 0; i < 256; i++)
	{
		Accumulate[255 - Cal[i] * 255 / MAX][i] = 255;
	}
	fwrite(Accumulate, 1, 256 * 256, fileout);
	fclose(fileout);
	/*------------------------------找最大值Histogram------------------------------*/
	for (int i = 0; i < 256; i++)
	{
		if (Cal_h[i]>MAX_h)
		{
			MAX_h = Cal_h[i];
		}
		//printf("像素值=%d，有%d個\n",i ,Cal[i]);
	}
	/*------------------------------畫直方圖------------------------------*/
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < Cal_h[i] * 255 / MAX_h; j++)
		{
			Hist[255 - j][i] = 255;
		}
	}
	fwrite(Hist, 1, 256 * 256, hist);
	fclose(hist);
	/*------------------------------畫equalization圖------------------------------*/
	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			getpix = fgetc(imagein);
			image.data[j + i * 512] = Cal[getpix] * 255 / MAX; 
		}
	}
	fwrite(image.data, 1, 512 * 512, imageout);
	fclose(imagein);
	fclose(imageout);
}
int main()
{
	FILE *filein_hist;
	FILE *filein_image;
	FILE *fileout_hist;
	FILE *fileout_histAdd;
	FILE *fileout_image;
	Mat image1(512, 512, CV_8UC1, Scalar(0));//cameraman
	Mat image2(512, 512, CV_8UC1, Scalar(0));//livingroom

	filein_hist = fopen("cameraman_b512.raw", "rb");
	filein_image = fopen("cameraman_b512.raw", "rb");
	fileout_hist = fopen("HW3_2_b_cameraman_Hist.raw", "wb");
	fileout_histAdd = fopen("HW3_2_b_cameraman_HistAdd.raw", "wb");
	fileout_image = fopen("HW3_2_b_cameraman_HistoEqual.raw", "wb");
	histoequal(filein_hist, fileout_histAdd, fileout_hist, image1, filein_image, fileout_image);
	
	filein_hist = fopen("HW3_2_b_cameraman_HistoEqual.raw", "rb");
	fileout_hist = fopen("HW3_2_b_cameraman_HistEqual_Hist.raw", "wb");
	histogram(filein_hist, fileout_hist);

	filein_hist = fopen("livingroom_d512.raw", "rb");
	filein_image = fopen("livingroom_d512.raw", "rb");
	fileout_hist = fopen("HW3_2_b_livingroom_Hist.raw", "wb");
	fileout_histAdd = fopen("HW3_2_b_livingroom_HistAdd.raw", "wb");
	fileout_image = fopen("HW3_2_b_livingroom_HistoEqual.raw", "wb");
	histoequal(filein_hist, fileout_histAdd, fileout_hist, image2, filein_image, fileout_image);
	
	filein_hist = fopen("HW3_2_b_livingroom_HistoEqual.raw", "rb");
	fileout_hist = fopen("HW3_2_b_livingroom_HistEqual_Hist.raw", "wb");
	histogram(filein_hist, fileout_hist);
}