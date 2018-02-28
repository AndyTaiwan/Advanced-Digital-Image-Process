/************************************************************/
/*  �{���W�١G��X�Ϲ������I��T							    */
/*  �@�̩m�W�G����                                           */
/*	    �Ǹ�:106318025                                      */
/*  ���ɱб¡GDr.������                                       */
/*  �q�l�l��Gt106318025@ntut.org.tw                         */
/*                                                          */
/*  ���D�y�z�G�o�ӵ{���N�ھڨϥΪ̿�J��������m�h��o������      */
/*                                                          */
/*  ��J�ɮסGlena256.raw					                 */
/*  ��X�ɮסG�q�зǿ�X�ɿ�X�@�Ӿ�� (�N��@�ӹ�����)          */
/*  �ݨD���ءG�L                                             */
/************************************************************/
#include "stdlib.h"
#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	
	Mat figure(256, 256, CV_8UC1, Scalar(0));//�Q��OpenCV��ܮw�ŧi�@��256*256���x�}�Ŷ�
	FILE *filein;//�Q��C++��ܮw�ŧi�@��filein�H�s��}���ɮ׫᪺��}

	int input_row, input_col;//�ϥΪ̿�J��������m
	int input_pix;//�ϥΪ̿�J���ĴX������
	int i, j;
	int pick;

	filein = fopen("lena256.raw", "rb");
	//fopen()�|�Ǧ^�@��FILE��ڪ���}�Ȩ�filein�A"rb"��uŪ���@�ӤG�i����

	for (j = 0; j < 256; j++)
	{
		for (i = 0; i < 256; i++)
		{
			figure.data[i + j*256] = fgetc(filein);
			//fgetc()�ǤJFILE��Ҫ���}�ȡA�C����@���N�|�q�ɮפ�Ū���@�Ӧr���A����Ū���ɧ�(End of File, EOF)����
		}
	}
	fclose(filein);//�� fclose() ��ƨӱN�}�Ҫ��ɮ������A�o�˸�Ƥ~�|�u���g�J
	/*-------------------����n�ϥΪ�������m��F�覡�ÿ�X���I������-----------------*/

	while (1)
	{
		printf(" 1.position of pixel\n ");
		printf("2.The number of the pixel\n ");
		printf(" Please choose a number : ");
		scanf("%d", &pick);
		switch (pick)
		{
		case 1:
			printf("input row :");
			scanf("%d", &input_row);
			printf("input col :");
			scanf("%d", &input_col);
			printf("The intensity value of the %dth row & %dth colum is :%d\n", input_row, input_col, figure.data[input_row * 256 + input_col]);
			system("pause");
			break;
		case 2:
			printf("The number of the pixel :");
			scanf("%d", &input_pix);
			printf("The intensity value of the %d th pixel is :%d\n", input_pix, figure.data[input_pix-1]);
			system("pause");
			break;
		default:
			printf("Are you an illiteracy ? \n");
			system("pause");
			printf("Such a poor guy\n");
			system("pause");
			break;
		}
	}
}
