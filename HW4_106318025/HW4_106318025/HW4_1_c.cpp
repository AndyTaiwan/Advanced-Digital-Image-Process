#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;

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
		if (Cal[i] >= MAX)
		{
			MAX = Cal[i];
		}
		//printf("像素值=%d，有%d個\n",i ,Cal[i]);
	}
	//printf("Total：%d\n MAX=%d", total,MAX);
	//system("pause");
	/*------------------------------畫像素累加圖------------------------------*/
	/*for (int i = 0; i < 256; i++)
	{
		Accumulate[255 - Cal[i] * 255 / MAX][i] = 255;
	}*/
	/*fwrite(Accumulate, 1, 256 * 256, fileout);
	fclose(fileout);*/
	///*------------------------------找最大值Histogram------------------------------*/
	//for (int i = 0; i < 256; i++)
	//{
	//	if (Cal_h[i]>MAX_h)
	//	{
	//		MAX_h = Cal_h[i];
	//	}
	//	//printf("像素值=%d，有%d個\n",i ,Cal[i]);
	//}
	///*------------------------------畫直方圖------------------------------*/
	//for (int i = 0; i < 256; i++)
	//{
	//	for (int j = 0; j < Cal_h[i] * 255 / MAX_h; j++)
	//	{
	//		Hist[255 - j][i] = 255;
	//	}
	//}
	//fwrite(Hist, 1, 256 * 256, hist);
	//fclose(hist);
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
	Mat image1(512, 512, CV_8UC1, Scalar(0));//house512

	filein_hist = fopen("house512.raw", "rb");
	filein_image = fopen("house512.raw", "rb");
	fileout_hist = fopen("HW4_1_a_house512_Hist.raw", "wb");
	fileout_histAdd = fopen("HW4_1_a_house512_HistAdd.raw", "wb");
	fileout_image = fopen("HW4_1_a_house512_HistoEqual.raw", "wb");
	histoequal(filein_hist, fileout_histAdd, fileout_hist, image1, filein_image, fileout_image);
}