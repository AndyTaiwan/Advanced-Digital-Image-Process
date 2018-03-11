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

	/*************************************Ū��*************************************/
	filein = fopen("lena512.raw", "rb");
	fread(image_char, sizeof(image_char), 1, filein);//�N�v����TŪ�Jchar
	fclose(filein);
	image_in = Mat(512, 512, CV_8UC1, image_char);//�Nchar�নMat
	image_out3 = Mat(512, 512, CV_8UC1, Scalar(0));
	image_out5 = Mat(512, 512, CV_8UC1, Scalar(0));
	image_out50 = Mat(512, 512, CV_8UC1, Scalar(0));
	image_out100 = Mat(512, 512, CV_8UC1, Scalar(0));
	/******************************************************************************/

	/*******************************�P�_Ū�ɬO�_���~********************************/
	if (!image_in.data)
	{
		cout << "Ū�J�Ϥ����~�I" << endl;
		system("pause");
		return -1;
	}
	/****************************************************************************/

	/*********************************�ͦ��������T*******************************/
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

	/*************************************�g��************************************/
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

	/***********************************��ܼv��***********************************/
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
	/********************************�[�J�������T**********************************/
	Mat noise = Mat(IMAGE_IN.size(), IMAGE_IN.type());//���ͤ@�ӻP��Ϯ榡�ۦP���ܼ�
	randn(noise, mu, sigma);//�ͦ��������T
	Mat IMAGE_OUT;
	add(IMAGE_IN, noise, IMAGE_OUT);//�N��ϻP�������T�ۥ[
	return IMAGE_OUT;
	/******************************************************************************/
}

