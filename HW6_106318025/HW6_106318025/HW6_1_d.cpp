#define _USE_MATH_DEFINES
#include <cstdio>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace cv;
Mat IDFT(Mat &in);
Mat shift(Mat &in);
int main()
{
	FILE *filein;
	FILE *fileout;
	Mat circle256_1;
	Mat circle256_2;
	unsigned char circle256_char_1[256 * 256];
	unsigned char circle256_char_2[256 * 256];
	/*********************************************讀檔*********************************************/
	filein = fopen("circle256_1.raw", "rb");
	fread(circle256_char_1, sizeof(circle256_char_1), 1, filein);//將影像資訊讀入char
	fclose(filein);
	circle256_1 = Mat(256, 256, CV_8UC1, circle256_char_1);//將char轉成Mat

	filein = fopen("circle256_2.raw", "rb");
	fread(circle256_char_2, sizeof(circle256_char_2), 1, filein);//將影像資訊讀入char
	fclose(filein);
	circle256_2 = Mat(256, 256, CV_8UC1, circle256_char_2);

	/*****************************************反傅立葉轉換*****************************************/
	
	Mat IDFT_circle_1;
	Mat IDFT_circle_2;
	IDFT_circle_1 = IDFT(circle256_1);
	IDFT_circle_2 = IDFT(circle256_2);
	imshow("IDFT_circle_1", IDFT_circle_1);
	imshow("IDFT_circle_2", IDFT_circle_2);
	waitKey();
	/*************************************寫檔************************************/
	fileout = fopen("HW6_1_d_circle_1_IDFT.raw", "wb");
	fwrite(IDFT_circle_1.data, IDFT_circle_1.rows*IDFT_circle_1.cols, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW6_1_d_circle_2_IDFT.raw", "wb");
	fwrite(IDFT_circle_2.data, IDFT_circle_2.rows*IDFT_circle_2.cols, 1, fileout);
	fclose(fileout);
}
Mat shift(Mat &in)
{
	int cx1 = in.cols / 2;
	int cy1 = in.rows / 2;

	Mat q0_1(in, Rect(0, 0, cx1, cy1));
	Mat q1_1(in, Rect(cx1, 0, cx1, cy1));
	Mat q2_1(in, Rect(0, cy1, cx1, cy1));
	Mat q3_1(in, Rect(cx1, cy1, cx1, cy1));

	Mat tmp1, tmp2;
	q0_1.copyTo(tmp1);
	q3_1.copyTo(q0_1);
	tmp1.copyTo(q3_1);
	q1_1.copyTo(tmp1);
	q2_1.copyTo(q1_1);
	tmp1.copyTo(q2_1);

	return in;
}
Mat IDFT(Mat &in)
{
	Mat ifft;
	Mat convert_ifft;
	in = shift(in);
	Mat planes[] = { Mat_<float>(in), Mat::zeros(in.size(), CV_32F) };
	Mat complexI;    //Complex plane to contain the DFT coefficients {[0]-Real,[1]-Img}
	merge(planes, 2, complexI);
	idft(complexI, ifft, DFT_SCALE | DFT_REAL_OUTPUT);// Applying IDFT
	normalize(ifft, ifft, 0, 1, CV_MINMAX);//正規化IDFT結果
	ifft.convertTo(convert_ifft, CV_8U, 255);//將32F轉回8UC1才能正確存取
	/*convert_ifft = shift(convert_ifft);*/
	return convert_ifft;
}