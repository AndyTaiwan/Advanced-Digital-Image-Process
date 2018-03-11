#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void expand(Mat After, Mat Before);
Mat Blurring_3x3(Mat input, int times);

int main()
{
	unsigned char image_char[512 * 512];

	FILE *filein;
	FILE *fileout;
	Mat image_in;
	Mat image_out_3x3_LPF(512, 512, CV_8UC1, Scalar(0));//Blurring mask 3x3 (1 time)
	Mat image_out_Sharpening(512, 512, CV_8UC1, Scalar(0));//Sharpening

	/*************************************Ū��*************************************/
	filein = fopen("lena512.raw", "rb");
	fread(image_char, sizeof(image_char), 1, filein);//�N�v����TŪ�Jchar
	fclose(filein);
	image_in = Mat(512, 512, CV_8UC1, image_char);//�Nchar�নMat

	/**********************************�v���ҽk��*********************************/

	image_out_3x3_LPF = Blurring_3x3(image_in, 5);
	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			double sub
				= (double)image_in.data[j + i * 512] - (double)0.98 * image_out_3x3_LPF.data[j + i * 512];
			if (sub < 0)
				sub = 0;
			if (sub > 255)
				sub = 255;
			image_out_Sharpening.data[j + i * 512] = sub ;
		}
	}
	/*************************************�g��************************************/

	fileout = fopen("HW4_4_c_Sharpening.raw", "wb");
	fwrite(image_out_Sharpening.data, image_out_Sharpening.rows*image_out_Sharpening.cols, 1, fileout);
	fclose(fileout);

	/***********************************��ܼv��***********************************/
	imshow("original", image_in);
	imshow("Image Sharpening_3x3", image_out_Sharpening);

	waitKey();
	/******************************************************************************/
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
Mat Blurring_3x3(Mat input, int times)
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
				double sum
					= (double)expand1.data[(j - 1) + expand1.cols*(i - 1)] * mask_3x3[0][0]
					+ (double)expand1.data[(j)+expand1.cols*(i - 1)] * mask_3x3[0][1]
					+ (double)expand1.data[(j + 1) + expand1.cols*(i - 1)] * mask_3x3[0][2]
					+ (double)expand1.data[(j - 1) + expand1.cols*(i)] * mask_3x3[1][0]
					+ (double)expand1.data[(j)+expand1.cols*(i)] * mask_3x3[1][1]
					+ (double)expand1.data[(j + 1) + expand1.cols*(i)] * mask_3x3[1][2]
					+ (double)expand1.data[(j - 1) + expand1.cols*(i + 1)] * mask_3x3[2][0]
					+ (double)expand1.data[(j)+expand1.cols*(i + 1)] * mask_3x3[2][1]
					+ (double)expand1.data[(j + 1) + expand1.cols*(i + 1)] * mask_3x3[2][2];
				if (sum < 0)
					sum = 0;
				if (sum > 255)
					sum = 255;
				output.data[(j - 1) + output.cols*(i - 1)] = sum;
			}
		}
		times--;
		if (times > 0)//�P�_�Y���y���Ƥj��0�ɫh�N��XMat�����JMat
			input = output;
	} while (times > 0);//�P�_�Y���y���Ƥj��0�ɫh���]while()
	return output;
}