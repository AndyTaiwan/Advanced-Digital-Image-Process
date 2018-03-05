/************************************************************/
/*  �{���W�١G�v���h���T										*/
/*                                                          */
/*  �@�̩m�W�G����											*/
/*	    �Ǹ�:106318025										*/
/*  ���ɱб¡GDr.������										*/
/*  �q�l�l��Gt106318025@ntut.org.tw							*/
/*                                                          */
/*  ���D�y�z�G1.Median Filter denoising						*/
/*           2.Low Pass Filter denoising					*/
/*           ���O�ϥΤ��P�B�n(�ܤ֨��)���B�z					*/
/*                                                          */
/*  ��J�ɮסGlena512_salt&pepper.raw				        */
/*           lena512_gaussianNoise.raw                      */
/*  ��X�ɮסGHW5_1_a_salt&pepper_LPF_3x3.raw                */
/*           HW5_1_a_salt&pepper_LPF_7x7.raw                */
/*           HW5_1_a_salt&pepper_Median_Filter_3x3.raw      */
/*           HW5_1_a_salt&pepper_Median_Filter_7x7.raw      */
/*           HW5_1_a_Gaussian_LPF_3x3.raw                   */
/*           HW5_1_a_Gaussian_LPF_7x7.raw                   */
/*           HW5_1_a_Gaussian_Median_Filter_3x3.raw         */
/*           HW5_1_a_Gaussian_Median_Filter_7x7.raw         */
/************************************************************/
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void expand(Mat After, Mat Before);
Mat LPF_3x3(Mat input, int times);
Mat LPF_7x7(Mat input, int times);
Mat Median_Filter_3x3(Mat input);
Mat Median_Filter_7x7(Mat input);
int main()
{
	unsigned char image_char_salt[512 * 512];
	unsigned char image_char_Gaussian[512 * 512];

	FILE *filein;
	FILE *fileout;
	Mat image_in_salt;
	Mat image_in_Gaussian;
	Mat image_out_S_LPF_3x3;
	Mat image_out_S_LPF_7x7;
	Mat image_out_S_MF_3x3;
	Mat image_out_S_MF_7x7;

	Mat image_out_G_LPF_3x3;
	Mat image_out_G_LPF_7x7;
	Mat image_out_G_MF_3x3;
	Mat image_out_G_MF_7x7;
	/*************************************Ū��*************************************/
	filein = fopen("lena512_salt&pepper.raw", "rb");
	fread(image_char_salt, sizeof(image_char_salt), 1, filein);//�N�v����TŪ�Jchar
	fclose(filein);
	image_in_salt = Mat(512, 512, CV_8UC1, image_char_salt);//�Nchar�নMat
	filein = fopen("lena512_gaussianNoise.raw", "rb");
	fread(image_char_Gaussian, sizeof(image_char_Gaussian), 1, filein);//�N�v����TŪ�Jchar
	fclose(filein);
	image_in_Gaussian = Mat(512, 512, CV_8UC1, image_char_Gaussian);//�Nchar�নMat

	image_out_S_LPF_3x3 = LPF_3x3(image_in_salt, 1);
	image_out_S_LPF_7x7 = LPF_7x7(image_in_salt, 1);
	image_out_S_MF_3x3 = Median_Filter_3x3(image_in_salt);
	image_out_S_MF_7x7 = Median_Filter_7x7(image_in_salt);

	image_out_G_LPF_3x3 = LPF_3x3(image_in_Gaussian, 1);
	image_out_G_LPF_7x7 = LPF_7x7(image_in_Gaussian, 1);
	image_out_G_MF_3x3 = Median_Filter_3x3(image_in_Gaussian);
	image_out_G_MF_7x7 = Median_Filter_7x7(image_in_Gaussian);
	/*************************************�g��************************************/
	fileout = fopen("HW5_1_a_salt&pepper_LPF_3x3.raw", "wb");
	fwrite(image_out_S_LPF_3x3.data, image_out_S_LPF_3x3.rows*image_out_S_LPF_3x3.cols, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW5_1_a_salt&pepper_LPF_7x7.raw", "wb");
	fwrite(image_out_S_LPF_7x7.data, image_out_S_LPF_7x7.rows*image_out_S_LPF_7x7.cols, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW5_1_a_salt&pepper_Median_Filter_3x3.raw", "wb");
	fwrite(image_out_S_MF_3x3.data, image_out_S_MF_3x3.rows*image_out_S_MF_3x3.cols, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW5_1_a_salt&pepper_Median_Filter_7x7.raw", "wb");
	fwrite(image_out_S_MF_7x7.data, image_out_S_MF_7x7.rows*image_out_S_MF_7x7.cols, 1, fileout);
	fclose(fileout);

	fileout = fopen("HW5_1_a_Gaussian_LPF_3x3.raw", "wb");
	fwrite(image_out_G_LPF_3x3.data, image_out_G_LPF_3x3.rows*image_out_G_LPF_3x3.cols, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW5_1_a_Gaussian_LPF_7x7.raw", "wb");
	fwrite(image_out_G_LPF_7x7.data, image_out_G_LPF_7x7.rows*image_out_G_LPF_7x7.cols, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW5_1_a_Gaussian_Median_Filter_3x3.raw", "wb");
	fwrite(image_out_G_MF_3x3.data, image_out_G_MF_3x3.rows*image_out_G_MF_3x3.cols, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW5_1_a_Gaussian_Median_Filter_7x7.raw", "wb");
	fwrite(image_out_G_MF_7x7.data, image_out_G_MF_7x7.rows*image_out_G_MF_7x7.cols, 1, fileout);
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
				output.data[(j - 1) + output.cols*(i - 1)]
					= (double)expand1.data[(j - 1) + expand1.cols*(i - 1)] * mask_3x3[0][0]
					+ (double)expand1.data[(j)+expand1.cols*(i - 1)] * mask_3x3[0][1]
					+ (double)expand1.data[(j + 1) + expand1.cols*(i - 1)] * mask_3x3[0][2]
					+ (double)expand1.data[(j - 1) + expand1.cols*(i)] * mask_3x3[1][0]
					+ (double)expand1.data[(j)+expand1.cols*(i)] * mask_3x3[1][1]
					+ (double)expand1.data[(j + 1) + expand1.cols*(i)] * mask_3x3[1][2]
					+ (double)expand1.data[(j - 1) + expand1.cols*(i + 1)] * mask_3x3[2][0]
					+ (double)expand1.data[(j)+expand1.cols*(i + 1)] * mask_3x3[2][1]
					+ (double)expand1.data[(j + 1) + expand1.cols*(i + 1)] * mask_3x3[2][2];
			}
		}
		times--;
		if (times > 0)//�P�_�Y���y���Ƥj��0�ɫh�N��XMat�����JMat
			input = output;
	} while (times > 0);//�P�_�Y���y���Ƥj��0�ɫh���]while()
	return output;
}
Mat LPF_7x7(Mat input, int times)
{
	Mat output(input.size(), input.type());
	/**********************************Blurring Mask 7x7*********************************/
	double mask_7x7[7][7];
	mask_7x7[0][0] = (double)1 / 49; mask_7x7[0][1] = (double)1 / 49; mask_7x7[0][2] = (double)1 / 49; mask_7x7[0][3] = (double)1 / 49; mask_7x7[0][4] = (double)1 / 49; mask_7x7[0][5] = (double)1 / 49; mask_7x7[0][6] = (double)1 / 49;
	mask_7x7[1][0] = (double)1 / 49; mask_7x7[1][1] = (double)1 / 49; mask_7x7[1][2] = (double)1 / 49; mask_7x7[1][3] = (double)1 / 49; mask_7x7[1][4] = (double)1 / 49; mask_7x7[1][5] = (double)1 / 49; mask_7x7[1][6] = (double)1 / 49;
	mask_7x7[2][0] = (double)1 / 49; mask_7x7[2][1] = (double)1 / 49; mask_7x7[2][2] = (double)1 / 49; mask_7x7[2][3] = (double)1 / 49; mask_7x7[2][4] = (double)1 / 49; mask_7x7[2][5] = (double)1 / 49; mask_7x7[2][6] = (double)1 / 49;
	mask_7x7[3][0] = (double)1 / 49; mask_7x7[3][1] = (double)1 / 49; mask_7x7[3][2] = (double)1 / 49; mask_7x7[3][3] = (double)1 / 49; mask_7x7[3][4] = (double)1 / 49; mask_7x7[3][5] = (double)1 / 49; mask_7x7[3][6] = (double)1 / 49;
	mask_7x7[4][0] = (double)1 / 49; mask_7x7[4][1] = (double)1 / 49; mask_7x7[4][2] = (double)1 / 49; mask_7x7[4][3] = (double)1 / 49; mask_7x7[4][4] = (double)1 / 49; mask_7x7[4][5] = (double)1 / 49; mask_7x7[4][6] = (double)1 / 49;
	mask_7x7[5][0] = (double)1 / 49; mask_7x7[5][1] = (double)1 / 49; mask_7x7[5][2] = (double)1 / 49; mask_7x7[5][3] = (double)1 / 49; mask_7x7[5][4] = (double)1 / 49; mask_7x7[5][5] = (double)1 / 49; mask_7x7[5][6] = (double)1 / 49;
	mask_7x7[6][0] = (double)1 / 49; mask_7x7[6][1] = (double)1 / 49; mask_7x7[6][2] = (double)1 / 49; mask_7x7[6][3] = (double)1 / 49; mask_7x7[6][4] = (double)1 / 49; mask_7x7[6][5] = (double)1 / 49; mask_7x7[6][6] = (double)1 / 49;
	do
	{
		/**********************************�N�v���X�i*********************************/
		Mat expand1(input.rows + 2, input.cols + 2, CV_8UC1, Scalar(0));
		Mat expand2(expand1.rows + 2, expand1.cols + 2, CV_8UC1, Scalar(0));
		Mat expand3(expand2.rows + 2, expand2.cols + 2, CV_8UC1, Scalar(0));
		expand(expand1, input);
		expand(expand2, expand1);
		expand(expand3, expand2);

		for (int i = 3; i < output.rows + 3; i++)
		{
			for (int j = 3; j < output.cols + 3; j++)
			{
				output.data[(j - 3) + output.cols*(i - 3)]
					= (double)expand3.data[(j - 3) + expand3.cols*(i - 3)] * mask_7x7[0][0]
					+ (double)expand3.data[(j - 2) + expand3.cols*(i - 3)] * mask_7x7[0][1]
					+ (double)expand3.data[(j - 1) + expand3.cols*(i - 3)] * mask_7x7[0][2]
					+ (double)expand3.data[(j)+expand3.cols*(i - 3)] * mask_7x7[0][3]
					+ (double)expand3.data[(j + 1) + expand3.cols*(i - 3)] * mask_7x7[0][4]
					+ (double)expand3.data[(j + 2) + expand3.cols*(i - 3)] * mask_7x7[0][5]
					+ (double)expand3.data[(j + 3) + expand3.cols*(i - 3)] * mask_7x7[0][6]

					+ (double)expand3.data[(j - 3) + expand3.cols*(i - 2)] * mask_7x7[1][0]
					+ (double)expand3.data[(j - 2) + expand3.cols*(i - 2)] * mask_7x7[1][1]
					+ (double)expand3.data[(j - 1) + expand3.cols*(i - 2)] * mask_7x7[1][2]
					+ (double)expand3.data[(j)+expand3.cols*(i - 2)] * mask_7x7[1][3]
					+ (double)expand3.data[(j + 1) + expand3.cols*(i - 2)] * mask_7x7[1][4]
					+ (double)expand3.data[(j + 2) + expand3.cols*(i - 2)] * mask_7x7[1][5]
					+ (double)expand3.data[(j + 3) + expand3.cols*(i - 2)] * mask_7x7[1][6]

					+ (double)expand3.data[(j - 3) + expand3.cols*(i - 1)] * mask_7x7[2][0]
					+ (double)expand3.data[(j - 2) + expand3.cols*(i - 1)] * mask_7x7[2][1]
					+ (double)expand3.data[(j - 1) + expand3.cols*(i - 1)] * mask_7x7[2][2]
					+ (double)expand3.data[(j)+expand3.cols*(i - 1)] * mask_7x7[2][3]
					+ (double)expand3.data[(j + 1) + expand3.cols*(i - 1)] * mask_7x7[2][4]
					+ (double)expand3.data[(j + 2) + expand3.cols*(i - 1)] * mask_7x7[2][5]
					+ (double)expand3.data[(j + 3) + expand3.cols*(i - 1)] * mask_7x7[2][6]

					+ (double)expand3.data[(j - 3) + expand3.cols*(i)] * mask_7x7[3][0]
					+ (double)expand3.data[(j - 2) + expand3.cols*(i)] * mask_7x7[3][1]
					+ (double)expand3.data[(j - 1) + expand3.cols*(i)] * mask_7x7[3][2]
					+ (double)expand3.data[(j)+expand3.cols*(i)] * mask_7x7[3][3]
					+ (double)expand3.data[(j + 1) + expand3.cols*(i)] * mask_7x7[3][4]
					+ (double)expand3.data[(j + 2) + expand3.cols*(i)] * mask_7x7[3][5]
					+ (double)expand3.data[(j + 3) + expand3.cols*(i)] * mask_7x7[3][6]

					+ (double)expand3.data[(j - 3) + expand3.cols*(i + 1)] * mask_7x7[4][0]
					+ (double)expand3.data[(j - 2) + expand3.cols*(i + 1)] * mask_7x7[4][1]
					+ (double)expand3.data[(j - 1) + expand3.cols*(i + 1)] * mask_7x7[4][2]
					+ (double)expand3.data[(j)+expand3.cols*(i + 1)] * mask_7x7[4][3]
					+ (double)expand3.data[(j + 1) + expand3.cols*(i + 1)] * mask_7x7[4][4]
					+ (double)expand3.data[(j + 2) + expand3.cols*(i + 1)] * mask_7x7[4][5]
					+ (double)expand3.data[(j + 3) + expand3.cols*(i + 1)] * mask_7x7[4][6]

					+ (double)expand3.data[(j - 3) + expand3.cols*(i + 2)] * mask_7x7[5][0]
					+ (double)expand3.data[(j - 2) + expand3.cols*(i + 2)] * mask_7x7[5][1]
					+ (double)expand3.data[(j - 1) + expand3.cols*(i + 2)] * mask_7x7[5][2]
					+ (double)expand3.data[(j)+expand3.cols*(i + 2)] * mask_7x7[5][3]
					+ (double)expand3.data[(j + 1) + expand3.cols*(i + 2)] * mask_7x7[5][4]
					+ (double)expand3.data[(j + 2) + expand3.cols*(i + 2)] * mask_7x7[5][5]
					+ (double)expand3.data[(j + 3) + expand3.cols*(i + 2)] * mask_7x7[5][6]

					+ (double)expand3.data[(j - 3) + expand3.cols*(i + 3)] * mask_7x7[6][0]
					+ (double)expand3.data[(j - 2) + expand3.cols*(i + 3)] * mask_7x7[6][1]
					+ (double)expand3.data[(j - 1) + expand3.cols*(i + 3)] * mask_7x7[6][2]
					+ (double)expand3.data[(j)+expand3.cols*(i + 3)] * mask_7x7[6][3]
					+ (double)expand3.data[(j + 1) + expand3.cols*(i + 3)] * mask_7x7[6][4]
					+ (double)expand3.data[(j + 2) + expand3.cols*(i + 3)] * mask_7x7[6][5]
					+ (double)expand3.data[(j + 3) + expand3.cols*(i + 3)] * mask_7x7[6][6];
			}
		}
		times--;
		if (times > 0)//�P�_�Y���y���Ƥj��0�ɫh�N��XMat�����JMat
			input = output;
	} while (times > 0);
	return output;
}
Mat Median_Filter_3x3(Mat input)
{
	Mat output(input.size(), input.type());
	Mat expand_MF_3x3(input.rows + 2, input.cols + 2, CV_8UC1, Scalar(0));
	expand(expand_MF_3x3, input);
	for (int i = 1; i < input.rows + 1; i++)
	{
		for (int j = 1; j < input.cols + 1; j++)
		{
			/*****************************mask 3x3 ��Ȧs�Jarr[9]*****************************/
			int len = 9;
			int arr[9];
			for (int m = -1; m < 2; m++)
			{
				for (int n = -1; n < 2; n++)
				{
					arr[(n + 1) + (m + 1) * 3] = expand_MF_3x3.data[(j + n) + (i + m)*expand_MF_3x3.cols];
				}
			}
			/***********************************���J�Ƨ�***********************************/
			for (int a = 1; a < len; a++)
			{
				int insert = arr[a];
				int b = a - 1;
				while (insert< arr[b])
				{
					arr[b + 1] = arr[b];
					b--;
					if (b == -1)
						break;
				}
				arr[b + 1] = insert;
			}
			/************************�N��e�����ȴ������Ƨǫᤤ����************************/
			output.data[(j - 1) + (i - 1)*output.cols] = arr[len / 2];
		}
	}
	return output;
}
Mat Median_Filter_7x7(Mat input)
{
	Mat output(input.size(), input.type());
	Mat expand1(input.rows + 2, input.cols + 2, CV_8UC1, Scalar(0));
	Mat expand2(expand1.rows + 2, expand1.cols + 2, CV_8UC1, Scalar(0));
	Mat expand3(expand2.rows + 2, expand2.cols + 2, CV_8UC1, Scalar(0));
	expand(expand1, input);
	expand(expand2, expand1);
	expand(expand3, expand2);
	for (int i = 3; i < input.rows + 3; i++)
	{
		for (int j = 3; j < input.cols + 3; j++)
		{
			/*****************************mask 7x7 ��Ȧs�Jarr[49]*****************************/
			int len = 49;
			int arr[49];
			for (int m = -3; m < 4; m++)
			{
				for (int n = -3; n < 4; n++)
				{
					arr[(n + 3) + (m + 3) * 7] = expand3.data[(j + n) + (i + m)*expand3.cols];
				}
			}
			/***********************************���J�Ƨ�***********************************/
			for (int a = 1; a < len; a++)
			{
				int insert = arr[a];
				int b = a - 1;
				while (insert< arr[b])
				{
					arr[b + 1] = arr[b];
					b--;
					if (b == -1)
						break;
				}
				arr[b + 1] = insert;
			}
			/************************�N��e�����ȴ������Ƨǫᤤ����************************/
			output.data[(j - 3) + (i - 3)*output.cols] = arr[len / 2 ];
		}
	}
	return output;
}