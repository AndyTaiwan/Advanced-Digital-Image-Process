#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat GaussianNoiseMat(Mat IMAGE_IN, float mu, float sigma);

int main()
{
	FILE *filein;
	FILE *fileout;
	Mat image_in;
	Mat image_out3;
	Mat image_out5;
	Mat image_out50;
	Mat image_out100;

	unsigned char image_char[512 * 512];

	/*************************************讀檔*************************************/
	filein = fopen("lena512.raw", "rb");
	fread(image_char, sizeof(image_char), 1, filein);//將影像資訊讀入char
	fclose(filein);
	image_in = Mat(512, 512, CV_8UC1, image_char);//將char轉成Mat
	image_out3 = Mat(512, 512, CV_8UC1, Scalar(0));
	image_out5 = Mat(512, 512, CV_8UC1, Scalar(0));
	image_out50 = Mat(512, 512, CV_8UC1, Scalar(0));
	image_out100 = Mat(512, 512, CV_8UC1, Scalar(0));
	/******************************************************************************/

	/*******************************判斷讀檔是否有誤********************************/
	if (!image_in.data)
	{
		cout << "讀入圖片錯誤！" << endl;
		system("pause");
		return -1;
	}
	/****************************************************************************/

	/*********************************生成高斯雜訊*******************************/
	Mat image_noise;
	image_noise = GaussianNoiseMat(image_in, 0, 50);
	/*************************************k=3************************************/
	for (int i = 0; i < 3; i++)
	{
		Mat image_denoising;
		image_denoising = (double)1 / 3 * GaussianNoiseMat(image_in, 0, 50);
		image_out3 = image_out3 + image_denoising;
	}
	/****************************************************************************/
	/*************************************k=5************************************/
	for (int i = 0; i < 5; i++)
	{
		Mat image_denoising;
		image_denoising = (double)1 / 5 * GaussianNoiseMat(image_in, 0, 50);
		image_out5 = image_out5 + image_denoising;
	}
	/*****************************************************************************/
	/*************************************k=50************************************/
	for (int i = 0; i < 50; i++)
	{
		Mat image_denoising;
		image_denoising = (double)1 / 50 * GaussianNoiseMat(image_in, 0, 50);
		image_out50 = image_out50 + image_denoising;
	}
	/*****************************************************************************/
	/*************************************k=100***********************************/
	for (int i = 0; i < 100; i++)
	{
		Mat image_denoising;
		image_denoising = (double)1 / 100 * GaussianNoiseMat(image_in, 0, 50);
		image_out100 = image_out100 + image_denoising;
	}
	/*****************************************************************************/

	/*************************************寫檔************************************/
	fileout = fopen("HW4_3_b_k=3.raw", "wb");
	fwrite(image_out3.data, image_out3.rows*image_out3.cols, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW4_3_b_k=5.raw", "wb");
	fwrite(image_out5.data, image_out5.rows*image_out5.cols, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW4_3_b_k=50.raw", "wb");
	fwrite(image_out50.data, image_out50.rows*image_out50.cols, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW4_3_b_k=100.raw", "wb");
	fwrite(image_out100.data, image_out100.rows*image_out100.cols, 1, fileout);
	fclose(fileout);
	/******************************************************************************/

	/***********************************顯示影像***********************************/
	imshow("original", image_in);
	imshow("GaussianNoise", image_noise);
	imshow("Denoising_K=3", image_out3);
	imshow("Denoising_K=5", image_out5);
	imshow("Denoising_K=50", image_out50);
	imshow("Denoising_K=100", image_out100);
	waitKey();
	/******************************************************************************/
}
Mat GaussianNoiseMat(Mat IMAGE_IN,float mu,float sigma)
{
	/********************************加入高斯雜訊**********************************/
	Mat noise = Mat(IMAGE_IN.size(), IMAGE_IN.type());//產生一個與原圖格式相同的變數
	randn(noise, mu, sigma);//生成高斯雜訊
	Mat IMAGE_OUT;
	add(IMAGE_IN, noise, IMAGE_OUT);//將原圖與高斯雜訊相加
	return IMAGE_OUT;
	/******************************************************************************/
}

