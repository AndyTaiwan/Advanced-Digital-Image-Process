/************************************************************/
/*  �{���W�١G�v����t����(�ѨM���T���D)						*/
/*															*/
/*  �@�̩m�W�G����											*/
/*	    �Ǹ�:106318025										*/
/*  ���ɱб¡GDr.������										*/
/*  �q�l�l��Gt106318025@ntut.org.tw							*/
/*															*/
/*  ���D�y�z�G�ϥ�Sobel Edge Detector							*/
/*           ���O�����T�v���i��ҽk�ƤΤ����ҽk�Ƽv������t����	*/
/*															*/
/*  ��J�ɮסGaerialcity512_gaussianNoise.raw				*/
/*  ��X�ɮסGHW5_2_b_aerialcity512_Blurring.raw				*/
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
	/*************************************Ū��*************************************/
	filein = fopen("aerialcity512_gaussianNoise.raw", "rb");
	fread(image_char_Gaussian, sizeof(image_char_Gaussian), 1, filein);//�N�v����TŪ�Jchar
	fclose(filein);
	image_in_gaussian = Mat(512, 512, CV_8UC1, image_char_Gaussian);//�Nchar�নMat
	/*********************************Blurring**********************************/
	image_out_with_Blurring = LPF_3x3(image_in_gaussian, 3);//�[�ҽk��
	/*********************************Sobel Edge**********************************/
	image_out_with_Blurring_Sobel = Sobel_Filter_3x3(image_out_with_Blurring);//�[�ҽk�ƨ���t
	image_out_without_Blurring_Sobel = Sobel_Filter_3x3(image_in_gaussian);//���[�ҽk�ƨ���t

	/**********************************��ܼv��***********************************/
	imshow("Original", image_in_gaussian);
	imshow("Blurring", image_out_with_Blurring);
	imshow("With_Blurring_Sobel", image_out_with_Blurring_Sobel);
	imshow("Without_Blurring_Sobel", image_out_without_Blurring_Sobel);
	waitKey();
	/*************************************�g��************************************/
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
			After.data[(Before.rows + 2) + (i + 1) + j*(Before.rows + 2)] = Before.data[i + j*Before.rows];//�N��ϸm�����X�i�ϪŶ�

			if (i == 0)
			{
				After.data[(Before.rows + 2) + i + j*(Before.rows + 2)] = Before.data[i + j*Before.rows];//��ɥ��ƪŹ���
				if (j == 0)
				{
					After.data[0] = Before.data[i + j*Before.rows];//��ɥ��W�Ź���
				}
			}
			if (i == Before.cols - 1)
			{
				After.data[(Before.rows + 2) + (i + 2) + j*(Before.rows + 2)] = Before.data[i + j*Before.rows];//��ɥk�ƪŹ���
				if (j == Before.rows - 1)
				{
					After.data[Before.cols + 1 + (Before.rows + 2) * (Before.cols + 1)] = Before.data[i + j*Before.rows];//��ɥk�U�Ź���
				}
			}
			if (j == 0)
			{
				After.data[(i + 1) + j*(Before.rows + 2)] = Before.data[i + j*Before.rows];//��ɤW�ƪŹ���
				if (i == Before.cols - 1)
				{
					After.data[Before.cols + 1 + (Before.rows + 2) * 0] = Before.data[i + j*Before.rows];//��ɥk�W�Ź���
				}
			}
			if (j == Before.rows - 1)
			{
				After.data[(Before.rows + 3) + (i + 3) + j*(Before.rows + 3)] = Before.data[i + j*Before.rows];//��ɤU�ƪŹ���
				if (i == 0)
				{
					After.data[0 + (Before.rows + 2) * Before.cols + 1] = Before.data[i + j*Before.rows];//��ɥ��U�Ź���
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
		/**********************************�N�v���X�i*********************************/
		Mat expand1(input.rows + 2, input.cols + 2, CV_8UC1, Scalar(0));
		expand(expand1, input);
		/*******************************Mask�v��v�C���y******************************/
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
		if (times > 0)//�P�_�Y���y���Ƥj��0�ɫh�N��XMat�����JMat
			input = output;
	} while (times > 0);//�P�_�Y���y���Ƥj��0�ɫh���]while()
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
	/*****************************��XSobel�X���q�����j�ȤΤp��(���W��)*****************************/
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
				max = total_Gx + total_Gy;//���j��
			}
			if (total_Gx + total_Gy < min)
			{
				min = total_Gx + total_Gy;//���p��
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
			/************************************�N�p��᪺�Ȧs�^�칳����m************************************/
			output.data[(j - 1) + (i - 1)*output.cols] = 255 * (total_Gx + total_Gy - min) / (max - min);//���W��
		}
	}
	return output;
}