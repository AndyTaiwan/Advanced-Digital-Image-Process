/************************************************************/
/*  �{���W�١G1.�v��2.75����j�A2.2���Y�p                      */
/*           2.�v��2.2���Y�p�A2.75����j                      */
/*           3.�v��1.25����j                                */
/*  �@�̩m�W�G����                                           */
/*	    �Ǹ�:106318025                                      */
/*  ���ɱб¡GDr.������                                       */
/*  �q�l�l��Gt106318025@ntut.org.tw                         */
/*                                                          */
/*  ���D�y�z�G�Q��nearest neighbor,bilinear,bicubic���O�B�z   */
/*           1.�v��2.75����j�A2.2���Y�p                      */
/*           2.�v��2.2���Y�p�A2.75����j                      */
/*           3.�v��1.25����j                                */
/*                                                          */
/*  ��J�ɮסGlena_256.raw				                    */
/*  ��X�ɮסGHW2_1_d_nearest1.raw                           */
/*           HW2_1_d_nearest2.raw                           */
/*           HW2_1_d_nearest3.raw                           */
/*           HW2_1_d_bilinear1.raw                          */
/*           HW2_1_d_bilinear2.raw                          */
/*           HW2_1_d_bilinear3.raw                          */
/*           HW2_1_d_bicubic1.raw                           */
/*           HW2_1_d_bicubic1.raw                           */
/*           HW2_1_d_bicubic1.raw                           */
/************************************************************/
#include <cstdio>
#include <opencv2/opencv.hpp>
#include <time.h>


using namespace cv;

double w;
int i, j;
int m1, n1;
float m2, n2;
clock_t time0, time1;

void expand(Mat After, Mat Before)
{
	for (j = 0; j < Before.rows; j++)
	{
		for (i = 0; i < Before.cols; i++)
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
			if (i == Before.cols-1)
			{
				After.data[(Before.rows + 2) + (i + 2) + j*(Before.rows + 2)] = Before.data[i + j*Before.rows];//��ɥk�ƪŹ���
				if (j == Before.rows-1)
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
void nearest_sizechange(Mat After,Mat Before)
{
	for (j = 0; j < After.rows; j++)
	{
		for (i = 0; i < After.cols; i++)
		{
			m1 = i * Before.rows / After.rows; //�������ϤW��x�y��
			n1 = j * Before.rows / After.rows; //�������ϤW��y�y��
			After.data[i + j * After.rows] = Before.data[m1 + n1 * Before.rows];
		}
	}
}
void bilinear_sizechange(Mat After, Mat Before)
{
	for (j = 0; j < After.rows; j++)
	{
		for (i = 0; i < After.rows; i++)
		{
			m2 = i * (float)Before.rows / After.rows; //m�������ϤW��x�y��(�B�I��)
			n2 = j * (float)Before.rows / After.rows; //n�������ϤW��y�y��(�B�I��)
			m1 = m2;//�B�I���ন���
			n1 = n2;
			float a = abs(m2 - m1);//�p��alpha��
			float b = abs(n2 - n1);//�p��beta��

			//�P�_�b�k��ɤΤU��ɮɪ�����
			int add_m = m1 + 1;
			int add_n = n1 + 1;
			if (m1 == Before.rows - 1 && n1 != Before.rows - 1)
			{
				add_m = m1;
			}
			else if (m1 != Before.rows - 1 && n1 == Before.rows - 1)
			{
				add_n = n1;
			}
			else if (m1 == Before.rows - 1 && n1 == Before.rows - 1)
			{
				add_m = m1;
				add_n = n1;
			}
			//bilinear ����
			After.data[i + j * After.rows]
				= Before.data[m1 + n1 * Before.rows] * (1 - a)*(1 - b)
				+ Before.data[add_m + n1 * Before.rows] * a*(1 - b)
				+ Before.data[m1 + add_n * Before.rows] * (1 - a)*b
				+ Before.data[add_m + add_n * Before.rows] * a*b;
		}
	}
}
void bicubic_sizechange(Mat After, Mat Before)
{
	for (j = 0; j < After.rows; j++)
	{
		for (i = 0; i < After.rows; i++)
		{

			float f = 0;
			m2 = abs(i * (float)(Before.rows-2) / After.rows); //m�������ϤW��x�y��(�B�I��) -1��16*16���̥�
			n2 = abs(j * (float)(Before.rows-2) / After.rows); //n�������ϤW��y�y��(�B�I��) -1��16*16���̤W
			m1 = m2;//�B�I���ন���
			n1 = n2;

			//��bicubic�N�������¹Ϥ���F16�ӹ������p��
			for (int j1 = -1; j1 < 3; j1++)
			{
				for (int i1 = -1; i1 < 3; i1++)
				{
					bicubic((m1 - m2) + i1);
					float Wx = w;
					bicubic((n1 - n2) + j1);
					float Wy = w;
					f = Before.data[m1 + i1 + Before.cols * (n1 + j1)] * Wx*Wy + f;
				}
			}
			if (f < 0)
				f = 0;
			if (f > 255)
				f = 255;
			After.data[i + j * After.rows] = (int)f;
		}
	}
}

int main()
{
	/**************************************Ū��.RAW��**************************************/
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
	/*******************************(Nearest Neighbor Interpolation)*********************************/
	Mat zoomim_NNI_1(704, 704, CV_8UC1, Scalar(0));//����j�A�Y�p
	Mat zoomim_NNI_2(320, 320, CV_8UC1, Scalar(0));//���Y�p�A��j
	Mat zoomim_NNI_3(320, 320, CV_8UC1, Scalar(0));//������j
	Mat shrinkim_NNI_1(320, 320, CV_8UC1, Scalar(0));//����j�A�Y�p
	Mat shrinkim_NNI_2(116, 116, CV_8UC1, Scalar(0));//���Y�p�A��j
	FILE *fileout_1 = fopen("HW2_1_d_nearest1.raw", "wb");
	FILE *fileout_2 = fopen("HW2_1_d_nearest2.raw", "wb");
	FILE *fileout_3 = fopen("HW2_1_d_nearest3.raw", "wb");
	printf("Nearest Neighbor Interpolation\n");
	/*--------------------------------zoom 2.75 then shrink 2.2------------------------------------*/
	time0 = clock();
	nearest_sizechange(zoomim_NNI_1, image);
	nearest_sizechange(shrinkim_NNI_1, zoomim_NNI_1);
	time1 = clock();
	fwrite(shrinkim_NNI_1.data, 1, 320 * 320, fileout_1);
	imshow("nearest1", shrinkim_NNI_1);
	fclose(fileout_1);
	
	printf("zoom 2.75 then shrink 2.2 = %d ms\n",time1-time0);
	/*--------------------------------shrink 2.2 then zoom 2.75------------------------------------*/
	time0 = clock();
	nearest_sizechange(shrinkim_NNI_2, image);
	nearest_sizechange(zoomim_NNI_2, shrinkim_NNI_2);
	time1 = clock();
	fwrite(zoomim_NNI_2.data, 1, 320 * 320, fileout_2);
	imshow("nearest2", zoomim_NNI_2);
	fclose(fileout_2);

	printf("shrink 2.2 then zoom 2.75 = %d ms\n", time1 - time0);
	/*-----------------------------------------zoom 1.25------------------------------------------*/
	time0 = clock();
	nearest_sizechange(zoomim_NNI_3, image);
	time1 = clock();
	fwrite(zoomim_NNI_2.data, 1, 320 * 320, fileout_3);
	imshow("nearest3", zoomim_NNI_3);
	fclose(fileout_3);

	printf("zoom 1.25 = %d ms\n\n\n", time1 - time0);
	waitKey();
	/**********************************************************************************************/
	/***********************************(Bilinear Interpolation)***********************************/
	Mat zoomim_Bilinear_1(704, 704, CV_8UC1, Scalar(0));//����j�A�Y�p
	Mat zoomim_Bilinear_2(320, 320, CV_8UC1, Scalar(0));//���Y�p�A��j
	Mat zoomim_Bilinear_3(320, 320, CV_8UC1, Scalar(0));//������j
	Mat shrinkim_Bilinear_1(320, 320, CV_8UC1, Scalar(0));//����j�A�Y�p
	Mat shrinkim_Bilinear_2(116, 116, CV_8UC1, Scalar(0));//���Y�p�A��j
	fileout_1 = fopen("HW2_1_d_bilinear1.raw", "wb");
	fileout_2 = fopen("HW2_1_d_bilinear2.raw", "wb");
	fileout_3 = fopen("HW2_1_d_bilinear3.raw", "wb");
	printf("Bilinear Interpolation\n");
	/*--------------------------------zoom 2.75 then shrink 2.2------------------------------------*/
	time0 = clock();
	bilinear_sizechange(zoomim_Bilinear_1,image);
	bilinear_sizechange(shrinkim_Bilinear_1, zoomim_Bilinear_1);
	time1 = clock();
	fwrite(shrinkim_Bilinear_1.data, 1, 320 * 320, fileout_1);
	imshow("bilinear1", shrinkim_Bilinear_1);
	fclose(fileout_1);
	printf("zoom 2.75 then shrink 2.2 = %d ms\n", time1 - time0);
	/*--------------------------------shrink 2.2 then zoom 2.75------------------------------------*/
	time0 = clock();
	bilinear_sizechange(shrinkim_Bilinear_2, image);
	bilinear_sizechange(zoomim_Bilinear_2, shrinkim_Bilinear_2);
	time1 = clock();
	fwrite(zoomim_Bilinear_2.data, 1, 320 * 320, fileout_2);
	imshow("bilinear2", zoomim_Bilinear_2);
	fclose(fileout_2);
	printf("shrink 2.2 then zoom 2.75 = %d ms\n", time1 - time0);
	/*-----------------------------------------zoom 1.25------------------------------------------*/
	time0 = clock();
	bilinear_sizechange(zoomim_Bilinear_3, image);
	time1 = clock();
	fwrite(zoomim_Bilinear_3.data, 1, 320 * 320, fileout_3);
	imshow("bilinear3", zoomim_Bilinear_3);
	fclose(fileout_3);
	printf("zoom 1.25= %d ms\n\n\n", time1 - time0);
	waitKey();
	/**********************************************************************************************/
	/***********************************(Bicubic Interpolation)************************************/
	Mat zoomim_Bicubic_1(704, 704, CV_8UC1, Scalar(0));//����j�A�Y�p
	Mat zoomim_Bicubic_2(320, 320, CV_8UC1, Scalar(0));//���Y�p�A��j
	Mat zoomim_Bicubic_3(320, 320, CV_8UC1, Scalar(0));//������j
	Mat shrinkim_Bicubic_1(320, 320, CV_8UC1, Scalar(0));//����j�A�Y�p
	Mat shrinkim_Bicubic_2(116, 116, CV_8UC1, Scalar(0));//���Y�p�A��j
	Mat lena258(258, 258, CV_8UC1, Scalar(0));
	Mat lena706(706, 706, CV_8UC1, Scalar(0));
	Mat lena118(118, 118, CV_8UC1, Scalar(0));
	fileout_1 = fopen("HW2_1_d_bicubic1.raw", "wb");
	fileout_2 = fopen("HW2_1_d_bicubic2.raw", "wb");
	fileout_3 = fopen("HW2_1_d_bicubic3.raw", "wb");
	printf("Bicubic Interpolation\n");
	/*--------------------------------zoom 2.75 then shrink 2.2------------------------------------*/
	time0 = clock();
	expand(lena258, image);
	bicubic_sizechange(zoomim_Bicubic_1, lena258);
	expand(lena706, zoomim_Bicubic_1);
	bicubic_sizechange(shrinkim_Bicubic_1, lena706);
	time1 = clock();
	fwrite(shrinkim_Bicubic_1.data, 1, 320 * 320, fileout_1);
	imshow("bicubic1", shrinkim_Bicubic_1);
	fclose(fileout_1);
	printf("zoom 2.75 then shrink 2.2 = %d ms\n", time1 - time0);
	/*--------------------------------shrink 2.2 then zoom 2.75------------------------------------*/
	time0 = clock();
	bicubic_sizechange(shrinkim_Bicubic_2, lena258);
	expand(lena118, shrinkim_Bicubic_2);
	bicubic_sizechange(zoomim_Bicubic_2, lena118);
	time1 = clock();
	fwrite(zoomim_Bicubic_2.data, 1, 320 * 320, fileout_2);
	imshow("bicubic2", zoomim_Bicubic_2);
	fclose(fileout_2);
	printf("shrink 2.2 then zoom 2.75 = %d ms\n", time1 - time0);
	/*-----------------------------------------zoom 1.25------------------------------------------*/
	time0 = clock();
	bicubic_sizechange(zoomim_Bicubic_3, lena258);
	time1 = clock();
	fwrite(zoomim_Bicubic_3.data, 1, 320 * 320, fileout_3);
	imshow("bicubic3", zoomim_Bicubic_3);
	fclose(fileout_3);
	printf("zoom 1.25 = %d ms\n", time1 - time0);
	waitKey();
	/**********************************************************************************************/
}