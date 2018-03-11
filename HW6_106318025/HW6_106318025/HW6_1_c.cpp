#include <cstdio>
#include <opencv2/opencv.hpp>
#include <time.h>

using namespace cv;
clock_t time0, time1;
Mat shift(Mat &in);
Mat DFT(Mat &in, Mat &complexI, Mat &DFT_magnitude, Mat &DFT_phase);
Mat IDFT(Mat &in);
int main()
{
	FILE *filein;
	FILE *fileout;
	Mat blackwhite256;
	Mat blackwhite256_rotate;
	unsigned char blackwhite256_char[256 * 256];
	unsigned char blackwhite256_rotate_char[256 * 256];
	/*********************************************read image*********************************************/
	filein = fopen("blackwhite256.raw", "rb");
	fread(blackwhite256_char, sizeof(blackwhite256_char), 1, filein);//將影像資訊讀入char
	fclose(filein);
	blackwhite256 = Mat(256, 256, CV_8UC1, blackwhite256_char);//將char轉成Mat
	filein = fopen("blackwhite256_rotate.raw", "rb");
	fread(blackwhite256_rotate_char, sizeof(blackwhite256_rotate_char), 1, filein);//將影像資訊讀入char
	fclose(filein);
	blackwhite256_rotate = Mat(256, 256, CV_8UC1, blackwhite256_rotate_char);
	/*****************************************Fourier Transform*****************************************/
	Mat complexImg1;//Complex plane to contain the DFT coefficients {[0]-Real,[1]-Img}
	Mat complexImg2;
	Mat DFT_blackwhite256_mag;
	Mat DFT_blackwhite256_phase;
	Mat DFT_blackwhite256_rotate_mag;
	Mat DFT_blackwhite256_rotate_phase;
	time0 = clock();//execution time
	DFT(blackwhite256, complexImg1, DFT_blackwhite256_mag, DFT_blackwhite256_phase);
	time1 = clock();//execution time
	printf("DFT execution time (blackwhite256) = %d ms\n", time1 - time0);//execution time
	time0 = clock();//execution time
	DFT(blackwhite256_rotate, complexImg2, DFT_blackwhite256_rotate_mag, DFT_blackwhite256_rotate_phase);
	time1 = clock();//execution time
	printf("DFT execution time (blackwhite256_rotate) = %d ms\n", time1 - time0);//execution time
	/*---------------------------------show image---------------------------------*/
	imshow("blackwhite256", blackwhite256);                                  //原圖
	imshow("blackwhite256_rotate", blackwhite256_rotate);                    //原圖
	waitKey();
	imshow("DFT_blackwhite256_mag", DFT_blackwhite256_mag);                  //magnitude
	imshow("DFT_blackwhite256_rotate_mag", DFT_blackwhite256_rotate_mag);	 //magnitude
	waitKey();
	imshow("DFT_blackwhite256_phase", DFT_blackwhite256_phase);				 //phase
	imshow("DFT_blackwhite256_rotate_phase", DFT_blackwhite256_rotate_phase);//phase
	waitKey();
	/*----------------------------------write image-----------------------------------*/
	fileout = fopen("HW6_1_c_blackwhite256_DFT_magnitude.raw", "wb");
	fwrite(DFT_blackwhite256_mag.data, DFT_blackwhite256_mag.rows*DFT_blackwhite256_mag.cols, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW6_1_c_blackwhite256_rotate_DFT_magnitude.raw", "wb");
	fwrite(DFT_blackwhite256_rotate_mag.data, DFT_blackwhite256_rotate_mag.rows*DFT_blackwhite256_rotate_mag.cols, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW6_1_c_blackwhite256_DFT_phase.raw", "wb");
	fwrite(DFT_blackwhite256_phase.data, DFT_blackwhite256_phase.rows*DFT_blackwhite256_phase.cols, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW6_1_c_blackwhite256_rotate_DFT_phase.raw", "wb");
	fwrite(DFT_blackwhite256_rotate_phase.data, DFT_blackwhite256_rotate_phase.rows*DFT_blackwhite256_rotate_phase.cols, 1, fileout);
	fclose(fileout);
	/*****************************************Inverse Fourier Transform*****************************************/
	Mat IDFT_blackwhite256;
	Mat IDFT_blackwhite256_rotate;
	time0 = clock();//execution time
	IDFT_blackwhite256 = IDFT(complexImg1);
	time1 = clock();//execution time
	printf("IDFT execution time (blackwhite256_rotate) = %d ms\n", time1 - time0);//execution time
	time0 = clock();//execution time
	IDFT_blackwhite256_rotate = IDFT(complexImg2);
	time1 = clock();//execution time
	printf("IDFT execution time (blackwhite256_rotate) = %d ms\n", time1 - time0);//execution time
	/*--------------------------------------show image--------------------------------------*/
	imshow("IDFT_blackwhite256", IDFT_blackwhite256);                                     //IDFT
	imshow("IDFT_blackwhite256_rotate", IDFT_blackwhite256_rotate);						  //IDFT
	waitKey();
	/*--------------------------------------write image--------------------------------------*/
	fileout = fopen("HW6_1_c_blackwhite256_IDFT.raw", "wb");
	fwrite(IDFT_blackwhite256.data, IDFT_blackwhite256.rows*IDFT_blackwhite256.cols, 1, fileout);
	fclose(fileout);
	fileout = fopen("HW6_1_c_blackwhite256_rotate_IDFT.raw", "wb");
	fwrite(IDFT_blackwhite256_rotate.data, IDFT_blackwhite256_rotate.rows*IDFT_blackwhite256_rotate.cols, 1, fileout);
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
Mat DFT(Mat &in, Mat &complexI, Mat &DFT_magnitude, Mat &DFT_phase)
{
	Mat planes1[] = { Mat_<float>(in), Mat::zeros(in.size(), CV_32F) };
	merge(planes1, 2, complexI);
	dft(complexI, complexI);  // Applying DFT

	// Reconstructing original image from the DFT coefficients
	Mat planes2[] = { Mat_<float>(complexI), Mat::zeros(complexI.size(), CV_32F) };
	split(complexI, planes2);
	/*-------------------計算magnitude, phase-------------------*/
	Mat mag;
	Mat ph;
	cartToPolar(planes2[0], planes2[1], mag, ph);//得到magnitude, phase
	/*-------------------magnitude contrast enhancement-------------------*/
	Mat magI = mag;
	magI += Scalar::all(1);                     //magI = log(1+planes[0])
	log(magI, magI);
	/*---------------將區塊重排，讓原點在影像的中央---------------*/
	mag = shift(magI);
	ph = shift(ph);
	/*---------------正規化 magnitude & phase---------------*/
	normalize(mag, mag, 1, 0, CV_MINMAX);
	normalize(ph, ph, 1, 0, CV_MINMAX);
	/*----------------將32F轉回8UC1才能正確存取---------------*/
	mag.convertTo(DFT_magnitude, CV_8U, 255);
	ph.convertTo(DFT_phase, CV_8U, 255);
	return DFT_magnitude, DFT_phase;
}
Mat IDFT(Mat &in)
{
	Mat IDFT;
	Mat ifft;
	idft(in, ifft, DFT_SCALE | DFT_REAL_OUTPUT);// Applying IDFT
	normalize(ifft, ifft, 0, 1, CV_MINMAX);//正規化IDFT結果
	ifft.convertTo(IDFT, CV_8U, 255);//將32F轉回8UC1才能正確存取
	return IDFT;
}