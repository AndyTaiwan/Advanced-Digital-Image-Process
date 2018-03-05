/************************************************************/
/*  程式名稱：影像邊緣偵測(解決雜訊問題)						*/
/*															*/
/*  作者姓名：卓諭											*/
/*	    學號:106318025										*/
/*  指導教授：Dr.黃正民										*/
/*  電子郵件：t106318025@ntut.org.tw							*/
/*															*/
/*  問題描述：使用Sobel Edge Detector							*/
/*           分別對雜訊影像進行模糊化及不做模糊化影像做邊緣偵測	*/
/*															*/
/*  輸入檔案：aerialcity512_gaussianNoise.raw				*/
/*  輸出檔案：HW5_2_b_aerialcity512_Blurring.raw				*/
/*           HW5_2_b_with_Blurring_Sobel.raw				*/
/*           HW5_2_b_without_Blurring_Sobel.raw				*/
/************************************************************/
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void expand(Mat After, Mat Before);
Mat LPF_3x3(Mat input, int times);
Mat Sobel_Filter_3x3(Mat input);

int main()
{
	unsigned char image_char_Gaussian[512 * 512];
	FILE *filein;
	FILE *fileout;
	Mat image_in_gaussian;
	Mat image_out_with_Blurring;
	Mat image_out_with_Blurring_Sobel;
	Mat image_out_without_Blurring_Sobel;
	/*************************************讀檔*************************************/
	filein = fopen("aerialcity512_gaussianNoise.raw", "rb");
	fread(image_char_Gaussian, sizeof(image_char_Gaussian), 1, filein);//將影像資訊讀入char
	fclose(filein);
	image_in_gaussian = Mat(512, 512, CV_8UC1, image_char_Gaussian);//將char轉成Mat
	/*********************************Blurring**********************************/
	image_out_with_Blurring = LPF_3x3(image_in_gaussian, 3);//加模糊化
	/*********************************Sobel Edge**********************************/
	image_out_with_Blurring_Sobel = Sobel_Filter_3x3(image_out_with_Blurring);//加模糊化取邊緣
	image_out_without_Blurring_Sobel = Sobel_Filter_3x3(image_in_gaussian);//未加模糊化取邊緣

	/**********************************顯示影像***********************************/
	imshow("Original", image_in_gaussian);
	imshow("Blurring", image_out_with_Blurring);
	imshow("With_Blurring_Sobel", image_out_with_Blurring_Sobel);
	imshow("Without_Blurring_Sobel", image_out_without_Blurring_Sobel);
	waitKey();
	/*************************************寫檔************************************/
	fileout = fopen("HW5_2_b_aerialcity512_Blurring.raw", "wb");
	fwrite(image_out_with_Blurring.data, image_out_with_Blurring.rows*image_out_with_Blurring.cols, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW5_2_b_with_Blurring_Sobel.raw", "wb");
	fwrite(image_out_with_Blurring_Sobel.data, image_out_with_Blurring_Sobel.rows*image_out_with_Blurring_Sobel.cols, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW5_2_b_without_Blurring_Sobel.raw", "wb");
	fwrite(image_out_without_Blurring_Sobel.data, image_out_without_Blurring_Sobel.rows*image_out_without_Blurring_Sobel.cols, 1, fileout);
	fclose(fileout);
}
void expand(Mat After, Mat Before)
{
	for (int j = 0; j < Before.rows; j++)
	{
		for (int i = 0; i < Before.cols; i++)
		{
			After.data[(Before.rows + 2) + (i + 1) + j*(Before.rows + 2)] = Before.data[i + j*Before.rows];//將原圖置中於擴展圖空間

			if (i == 0)
			{
				After.data[(Before.rows + 2) + i + j*(Before.rows + 2)] = Before.data[i + j*Before.rows];//填補左排空像素
				if (j == 0)
				{
					After.data[0] = Before.data[i + j*Before.rows];//填補左上空像素
				}
			}
			if (i == Before.cols - 1)
			{
				After.data[(Before.rows + 2) + (i + 2) + j*(Before.rows + 2)] = Before.data[i + j*Before.rows];//填補右排空像素
				if (j == Before.rows - 1)
				{
					After.data[Before.cols + 1 + (Before.rows + 2) * (Before.cols + 1)] = Before.data[i + j*Before.rows];//填補右下空像素
				}
			}
			if (j == 0)
			{
				After.data[(i + 1) + j*(Before.rows + 2)] = Before.data[i + j*Before.rows];//填補上排空像素
				if (i == Before.cols - 1)
				{
					After.data[Before.cols + 1 + (Before.rows + 2) * 0] = Before.data[i + j*Before.rows];//填補右上空像素
				}
			}
			if (j == Before.rows - 1)
			{
				After.data[(Before.rows + 3) + (i + 3) + j*(Before.rows + 3)] = Before.data[i + j*Before.rows];//填補下排空像素
				if (i == 0)
				{
					After.data[0 + (Before.rows + 2) * Before.cols + 1] = Before.data[i + j*Before.rows];//填補左下空像素
				}
			}
		}
	}
}
Mat LPF_3x3(Mat input, int times)
{
	Mat output(input.size(), input.type());
	/**********************************Blurring Mask 3x3*********************************/
	double mask_3x3[3][3];
	mask_3x3[0][0] = (double)1 / 9; mask_3x3[0][1] = (double)1 / 9; mask_3x3[0][2] = (double)1 / 9;
	mask_3x3[1][0] = (double)1 / 9; mask_3x3[1][1] = (double)1 / 9; mask_3x3[1][2] = (double)1 / 9;
	mask_3x3[2][0] = (double)1 / 9; mask_3x3[2][1] = (double)1 / 9; mask_3x3[2][2] = (double)1 / 9;
	do
	{
		/**********************************將影像擴展*********************************/
		Mat expand1(input.rows + 2, input.cols + 2, CV_8UC1, Scalar(0));
		expand(expand1, input);
		/*******************************Mask逐行逐列掃描******************************/
		for (int i = 1; i < output.rows + 1; i++)
		{
			for (int j = 1; j < output.cols + 1; j++)
			{
				double total = 0;
				for (int m = -1; m < 2; m++)
				{
					for (int n = -1; n < 2; n++)
					{
						total = total + (double)expand1.data[(j + n) + (i + m)*expand1.cols] * mask_3x3[m + 1][n + 1];
					}
				}
				output.data[(j - 1) + output.cols*(i - 1)] = total;
			}
		}
		times--;
		if (times > 0)//判斷若掃描次數大於0時則將輸出Mat等於輸入Mat
			input = output;
	} while (times > 0);//判斷若掃描次數大於0時則重跑while()
	return output;
}
Mat Sobel_Filter_3x3(Mat input)
{
	Mat output(input.size(), input.type());
	Mat expand1(input.rows + 2, input.cols + 2, CV_8UC1, Scalar(0));
	expand(expand1, input);
	int max = 0, min = INT_MAX;
	int Gx[9], Gy[9];
	Gx[0] = -1; Gx[1] = -2; Gx[2] = -1;
	Gx[3] =  0; Gx[4] =  0; Gx[5] =  0;
	Gx[6] =  1; Gx[7] =  2; Gx[8] =  1;
	Gy[0] = -1; Gy[1] =  0; Gy[2] =  1;
	Gy[3] = -2; Gy[4] =  0; Gy[5] =  2;
	Gy[6] = -1; Gy[7] =  0; Gy[8] =  1;
	/*****************************找出Sobel合成量的極大值及小值(正規化)*****************************/
	for (int i = 1; i < input.rows + 1; i++)
	{
		for (int j = 1; j < input.cols + 1; j++)
		{

			int total_Gx = 0;
			int total_Gy = 0;
			for (int m = -1; m < 2; m++)
			{
				for (int n = -1; n < 2; n++)
				{
					total_Gx = total_Gx + Gx[(n + 1) + (m + 1) * 3] * expand1.data[(j + n) + (i + m)*expand1.cols];
					total_Gy = total_Gy + Gy[(n + 1) + (m + 1) * 3] * expand1.data[(j + n) + (i + m)*expand1.cols];
				}
			}
			total_Gx = abs(total_Gx);
			total_Gy = abs(total_Gy);

			if (total_Gx + total_Gy > max)
			{
				max = total_Gx + total_Gy;//極大值
			}
			if (total_Gx + total_Gy < min)
			{
				min = total_Gx + total_Gy;//極小值
			}
		}
	}
	for (int i = 1; i < input.rows + 1; i++)
	{
		for (int j = 1; j < input.cols + 1; j++)
		{
			/*****************************Mask Sobel*****************************/
			int total_Gx = 0;
			int total_Gy = 0;
			for (int m = -1; m < 2; m++)
			{
				for (int n = -1; n < 2; n++)
				{
					total_Gx = total_Gx + Gx[(n + 1) + (m + 1) * 3] * expand1.data[(j + n) + (i + m)*expand1.cols];
					total_Gy = total_Gy + Gy[(n + 1) + (m + 1) * 3] * expand1.data[(j + n) + (i + m)*expand1.cols];
				}
			}
			total_Gx = abs(total_Gx);
			total_Gy = abs(total_Gy);
			/************************************將計算後的值存回原像素位置************************************/
			output.data[(j - 1) + (i - 1)*output.cols] = 255 * (total_Gx + total_Gy - min) / (max - min);//正規化
		}
	}
	return output;
}