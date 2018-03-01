/************************************************************/
/*  程式名稱：Quatize the gray-level resolution              */
/*           from 1bit to 8bits                             */
/*  作者姓名：卓諭                                           */
/*	    學號:106318025                                      */
/*  指導教授：Dr.黃正民                                       */
/*  電子郵件：t106318025@ntut.org.tw                         */
/*                                                          */
/*  問題描述：將lena_256.raw及baboon_256.raw                  */
/*           個別顯示當影像灰階值從8bits到1bits的輸出影像       */
/*           並輸出每張影像之MSE                              */
/*                                                          */
/*  輸入檔案：lena_256.raw				                    */
/*           baboon_256.raw                                 */
/*  輸出檔案：lena1bits.raw                                  */
/*           lena2bits.raw                                  */
/*           lena3bits.raw                                  */
/*           lena4bits.raw                                  */
/*           lena5bits.raw                                  */
/*           lena6bits.raw                                  */
/*           lena7bits.raw                                  */
/*           lena8bits.raw                                  */
/*           baboon1bits.raw                                */
/*           baboon2bits.raw                                */
/*           baboon3bits.raw                                */
/*           baboon4bits.raw                                */
/*           baboon5bits.raw                                */
/*           baboon6bits.raw                                */        
/*           baboon7bits.raw                                */
/*           baboon8bits.raw                                */
/************************************************************/
#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	FILE *filein;
	FILE *fileout_1 = fopen("lena1bits.raw", "wb");
	FILE *fileout_2 = fopen("lena2bits.raw", "wb");
	FILE *fileout_3 = fopen("lena3bits.raw", "wb");
	FILE *fileout_4 = fopen("lena4bits.raw", "wb");
	FILE *fileout_5 = fopen("lena5bits.raw", "wb");
	FILE *fileout_6 = fopen("lena6bits.raw", "wb");
	FILE *fileout_7 = fopen("lena7bits.raw", "wb");
	FILE *fileout_8 = fopen("lena8bits.raw", "wb");
	Mat lena(256, 256, CV_8UC1, Scalar(0));
	FILE *fileout_11 = fopen("baboon1bits.raw", "wb");
	FILE *fileout_22 = fopen("baboon2bits.raw", "wb");
	FILE *fileout_33 = fopen("baboon3bits.raw", "wb");
	FILE *fileout_44 = fopen("baboon4bits.raw", "wb");
	FILE *fileout_55 = fopen("baboon5bits.raw", "wb");
	FILE *fileout_66 = fopen("baboon6bits.raw", "wb");
	FILE *fileout_77 = fopen("baboon7bits.raw", "wb");
	FILE *fileout_88 = fopen("baboon8bits.raw", "wb");
	Mat baboon(256, 256, CV_8UC1, Scalar(0));

	int k, j, i;
	int a, b;
	unsigned int total,MSE;

	for (k = 1; k < 9; k++)
	{
		total = 0;
		filein = fopen("lena_256.raw", "rb");
		for (j = 0; j < 256; j++)
		{
			for (i = 0; i < 256; i++)
			{
				a = fgetc(filein);
				b = a * pow(2, k) / 256;
				lena.data[i + j * 256] = 256 / pow(2, k)*b;
				
				total = pow((a - lena.data[i + j * 256]),2) +total;//計算MSE
			}
		}
		MSE = total /(256 * 256 * 1);//計算MSE
		fclose(filein);

		switch (k)
		{
		case 1:
		
			fwrite(lena.data, 1, 256 * 256, fileout_1);
			printf("MSE lena1bits :%d\n", MSE);
			imshow("lena1bits", lena);
			waitKey();
			break;
		
		case 2:
		
			fwrite(lena.data, 1, 256 * 256, fileout_2);
			printf("MSE lena2bits :%d\n", MSE);
			imshow("lena2bits", lena);
			waitKey();
			break;
		
		case 3:
		
			fwrite(lena.data, 1, 256 * 256, fileout_3);
			printf("MSE lena3bits :%d\n", MSE);
			imshow("lena3bits", lena);
			waitKey();
			break;
		
		case 4:
		
			fwrite(lena.data, 1, 256 * 256, fileout_4);
			printf("MSE lena4bits :%d\n", MSE);
			imshow("lena4bits", lena);
			waitKey();
			break;
		
		case 5:
		
			fwrite(lena.data, 1, 256 * 256, fileout_5);
			printf("MSE lena5bits :%d\n", MSE);
			imshow("lena5bits", lena);
			waitKey();
			break;
		
		case 6:
		
			fwrite(lena.data, 1, 256 * 256, fileout_6);
			printf("MSE lena6bits :%d\n", MSE);
			imshow("lena6bits", lena);
			waitKey();
			break;
		
		case 7:
		
			fwrite(lena.data, 1, 256 * 256, fileout_7);
			printf("MSE lena7bits :%d\n", MSE);
			imshow("lena7bits", lena);
			waitKey();
			break;
		
		case 8:
		
  			fwrite(lena.data, 1, 256 * 256, fileout_8);
			printf("MSE lena8 bits :%d\n", MSE);
			imshow("lena8bits", lena);
 			waitKey();
			break;
			
		}
	}
	fclose(fileout_1);
	fclose(fileout_2);
	fclose(fileout_3);
	fclose(fileout_4);
	fclose(fileout_5);
	fclose(fileout_6);
	fclose(fileout_7);
	fclose(fileout_8);

	for (k = 1; k < 9; k++)
	{
		total = 0; 
		filein = fopen("baboon_256.raw", "rb");
		for (j = 0; j < 256; j++)
		{
			for (i = 0; i < 256; i++)
			{
				a = fgetc(filein);
				b = a * pow(2, k) / 256;
				baboon.data[i + j * 256] = 256 / pow(2, k)*b;

				total = pow((a - baboon.data[i + j * 256]), 2) + total;//計算MSE
			}
		}
		MSE = total / (256 * 256 * 1);//計算MSE
		fclose(filein);

		switch (k)
		{
		case 1:

			fwrite(baboon.data, 1, 256 * 256, fileout_11);
			printf("MSE baboon1bits :%d\n", MSE);
			imshow("baboon1bits", baboon);
			waitKey();
			break;

		case 2:

			fwrite(baboon.data, 1, 256 * 256, fileout_22);
			printf("MSE baboon2bits :%d\n", MSE);
			imshow("baboon2bits", baboon);
			waitKey();
			break;

		case 3:

			fwrite(baboon.data, 1, 256 * 256, fileout_33);
			printf("MSE baboon3bits :%d\n", MSE);
			imshow("baboon3bits", baboon);
			waitKey();
			break;

		case 4:

			fwrite(baboon.data, 1, 256 * 256, fileout_44);
			printf("MSE baboon4bits :%d\n", MSE);
			imshow("baboon4bits", baboon);
			waitKey();
			break;

		case 5:

			fwrite(baboon.data, 1, 256 * 256, fileout_55);
			printf("MSE baboon5bits :%d\n", MSE);
			imshow("baboon5bits", baboon);
			waitKey();
			break;

		case 6:

			fwrite(baboon.data, 1, 256 * 256, fileout_66);
			printf("MSE baboon6bits :%d\n", MSE);
			imshow("baboon6bits", baboon);
			waitKey();
			break;

		case 7:

			fwrite(baboon.data, 1, 256 * 256, fileout_77);
			printf("MSE baboon7bits :%d\n", MSE);
			imshow("baboon7bits", baboon);
			waitKey();
			break;

		case 8:

			fwrite(baboon.data, 1, 256 * 256, fileout_88);
			printf("MSE baboon8bits :%d\n", MSE);
			imshow("baboon8bits", baboon);
			waitKey();
			break;

		}
	}
	fclose(fileout_11);
	fclose(fileout_22);
	fclose(fileout_33);
	fclose(fileout_44);
	fclose(fileout_55);
	fclose(fileout_66);
	fclose(fileout_77);
	fclose(fileout_88);
}