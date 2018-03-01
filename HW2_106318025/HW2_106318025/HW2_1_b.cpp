/************************************************************/
/*  �{���W�١G�v��2.75����j                                  */
/*  �@�̩m�W�G����                                           */
/*	    �Ǹ�:106318025                                      */
/*  ���ɱб¡GDr.������                                      */
/*  �q�l�l��Gt106318025@ntut.org.tw                         */
/*                                                          */
/*  ���D�y�z�G�Q��nearest neighbor,bilinear,bicubic��j�v��   */
/*                                                          */
/*  ��J�ɮסGlena_256.raw				                    */
/*  ��X�ɮסGHW2_1_b_nearest.raw                            */
/*           HW2_1_b_bilinear.raw                           */
/*           HW2_1_b_bicubic.raw                            */
/*           HW2_1_b_lena258.raw                            */
/************************************************************/
#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;

void bicubic(float x);
double w;

int main()
{
	/*----------------------------Ū��.RAW��-------------------------------*/
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
	/*----------------------------(Nearest Neighbor Interpolation)-------------------------------*/
	Mat zoomim_1(704, 704, CV_8UC1, Scalar(0));
	FILE *fileout = fopen("HW2_1_b_nearest.raw", "wb");
	//--------------------------zooming2.25------------------------------------
	for (j = 0; j < 704; j++)
	{
		for (i = 0; i < 704; i++)
		{
			m1 = i * 256 / 704; //�������ϤW��x�y��
			n1 = j * 256 / 704; //�������ϤW��y�y��
			zoomim_1.data[i + j * 704] = image.data[m1 + n1 * 256];
		}
	}
	fwrite(zoomim_1.data, 1, 704 * 704, fileout);
	fclose(fileout);
	/*-------------------------------(Bilinear Interpolation)-----------------------------------*/
	Mat zoomim_2(704, 704, CV_8UC1, Scalar(0));
	fileout = fopen("HW2_1_b_bilinear.raw", "wb");
	float a, b;
	//------------------------------zooming2.25-------------------------------
	for (j = 0; j < 704; j++)
	{
		for (i = 0; i < 704; i++)
		{
			m2 = i * (float)256 / 704; //m�������ϤW��x�y��(�B�I��)
			n2 = j * (float)256 / 704; //n�������ϤW��y�y��(�B�I��)
			m1 = m2;//�B�I���ন���
			n1 = n2;
			a = abs(m2 - m1);//�p��alpha��
			b = abs(n2 - n1);//�p��beta��

			//�P�_�b�k��ɤΤU��ɮɪ�����
			int add_m = m1 + 1;
			int add_n = n1 + 1;
			if (m1 == 255 && n1 != 255)
			{
				add_m = m1;
			}
			else if (m1 != 255 && n1 == 255)
			{
				add_n = n1;
			}
			else if (m1 == 255 && n1==255)
			{
				add_m = m1;
				add_n = n1;
			}
			//bilinear ����
			zoomim_2.data[i + j * 704]
				= image.data[m1 + n1 * 256] * (1 - a)*(1 - b)
				+ image.data[add_m + n1 * 256] * a*(1 - b)
				+ image.data[m1 + add_n * 256] * (1 - a)*b
				+ image.data[add_m + add_n * 256] * a*b;
		}
	}
	fwrite(zoomim_2.data, 1, 704 * 704, fileout);
	fclose(fileout);
	/******************************************(Bicubic Interpolation)*********************************************/
	Mat zoomim_3(704, 704, CV_8UC1, Scalar(0));
	Mat lena258(258, 258, CV_8UC1, Scalar(0));
	fileout = fopen("HW2_1_b_bicubic.raw", "wb");//�ŧi��X�ɮ�
	FILE *fileout258 = fopen("HW2_1_b_lena258.raw", "wb");//�Nlena256�V�~�����@�ӹ�����258x258
	/*-------------------------------------�Nlena256�V�~�����@�ӹ�����258x258---------------------------------------*/
	for (j = 0; j < row; j++)
	{
		for (i = 0; i < col; i++)
		{
			lena258.data[(row + 2) + (i + 1) + j*(row + 2)] = image.data[i + j*row];//�N256*256�ϸm����258*258�Ŷ�

			if (i == 0)
			{
				lena258.data[(row + 2) + i + j*(row + 2)] = image.data[i + j*row];//��ɥ��ƪŹ���
				if (j == 0)
				{
					lena258.data[0] = image.data[i + j*row];//��ɥ��W�Ź���
				}
			}
			if (i == 255)
			{
				lena258.data[(row + 2) + (i + 2) + j*(row + 2)] = image.data[i + j*row];//��ɥk�ƪŹ���
				if (j == 255)
				{
					lena258.data[257 + 258 * 257] = image.data[i + j*row];//��ɥk�U�Ź���
				}
			}
			if (j == 0)
			{
				lena258.data[(i + 1) + j*(row + 2)] = image.data[i + j*row];//��ɤW�ƪŹ���
				if (i == 255)
				{
					lena258.data[257 + 258 * 0] = image.data[i + j*row];//��ɥk�W�Ź���
				}
			}
			if (j == 255)
			{
				lena258.data[(row + 3) + (i + 3) + j*(row + 3)] = image.data[i + j*row];//��ɤU�ƪŹ���
				if (i == 0)
				{
					lena258.data[0 + 258 * 257] = image.data[i + j*row];//��ɥ��U�Ź���
				}
			}
		}
	}
	fwrite(lena258.data, 1, 258 * 258, fileout258);
	/*---------------------------------------------------------------------------------------------------------*/
	/*-------------------------------------�N258*258��j��704*704-----------------------------------------------*/
	for (j = 0; j < 704; j++)
	{
		for (i = 0; i < 704; i++)
		{

			float f = 0;
			m2 = abs(i * (float)256 / 704); //m�������ϤW��x�y��(�B�I��) -1��16*16���̥�
			n2 = abs(j * (float)256  / 704); //n�������ϤW��y�y��(�B�I��) -1��16*16���̤W
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
					f = lena258.data[m1 + i1 + 258 * (n1 + j1)] * Wx*Wy + f;
					
				}
			}
			if (f < 0)
				f = 0;
			if (f > 255)
				f = 255;
			zoomim_3.data[i + j * 704] = (int)f;
		}
	}

	fwrite(zoomim_3.data, 1, 704 * 704, fileout);
	fclose(fileout);
	/*---------------------------------------------------------------------------------------------------------*/
	/*----------------------------------------------�e�{�v��----------------------------------------------------*/
	imshow("original", image);
	imshow("lena258", lena258);
	imshow("Nearest Neighbor_zoom", zoomim_1);
	imshow("Bilinear_zoom", zoomim_2);
	imshow("Bicubic_zoom", zoomim_3);
	waitKey(0);
}
/************************************************bicubic����***************************************************/
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