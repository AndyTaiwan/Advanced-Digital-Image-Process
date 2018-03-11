#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;

void shift(Mat& in)
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
}

/******************************************************************************/
// return a floating point spectrum magnitude image scaled for user viewing
// complexImg- input dft (2 channel floating point, Real + Imaginary fourier image)
// rearrange - perform rearrangement of DFT quadrants if true

// return value - pointer to output spectrum magnitude image scaled for user viewing

Mat spectrum_magnitude(Mat& complexImg, bool rearrange)
{
	Mat planes[2];

	// compute magnitude spectrum
	// compute log(1 + sqrt(Re(DFT(img))**2 + Im(DFT(img))**2))

	split(complexImg, planes);
	magnitude(planes[0], planes[1], planes[0]);

	Mat mag = (planes[0]).clone();
	mag += Scalar::all(1);
	log(mag, mag);

	if (rearrange)
	{
		// re-arrange the quaderants
		shift(mag);
	}

	normalize(mag, mag, 0, 1, CV_MINMAX);

	Mat convert_mag;
	mag.convertTo(convert_mag, CV_8U, 255);
	return convert_mag;

}
/******************************************************************************/
// create a 2-channel butterworth low-pass filter with radius D, order n
// (assumes pre-aollocated size of dft_Filter specifies dimensions)

void ideal_lowpass_filter(Mat &dft_Filter, int D)
{
	Mat tmp = Mat(dft_Filter.rows, dft_Filter.cols, CV_32F);

	Point centre = Point(dft_Filter.rows / 2, dft_Filter.cols / 2);
	double radius;

	for (int i = 0; i < dft_Filter.rows; i++)
	{
		float *data = tmp.ptr<float>(i);
		for (int j = 0; j < dft_Filter.cols; j++)
		{
			radius = (double)sqrt(pow((i - centre.x), 2.0) + pow((double)(j - centre.y), 2.0));
			if (radius <= D)
			{
				data[j] = 1.0;
			}
			if (radius > D)
			{
				data[j] = 0.0;
			}
		}
	}

	Mat Merge[] = { tmp, tmp };
	merge(Merge, 2, dft_Filter);
}

void ideal_highpass_filter(Mat &dft_Filter, int D)
{
	Mat tmp = Mat(dft_Filter.rows, dft_Filter.cols, CV_32F);

	Point centre = Point(dft_Filter.rows / 2, dft_Filter.cols / 2);
	double radius;

	for (int i = 0; i < dft_Filter.rows; i++)
	{
		float *data = tmp.ptr<float>(i);
		for (int j = 0; j < dft_Filter.cols; j++)
		{
			radius = (double)sqrt(pow((i - centre.x), 2.0) + pow((double)(j - centre.y), 2.0));
			if (radius <= D)
			{
				data[j] = 0.0;
			}
			if (radius > D)
			{
				data[j] = 1.0;
			}
		}
	}

	Mat Merge[] = { tmp, tmp };
	merge(Merge, 2, dft_Filter);
}

void frequency_filtering(Mat &in, int radius, bool HPF_LPF, Mat &in_filter_magnitude, Mat &convert_in_filter_image, Mat &convert_filter_Output)//(HPF)bool HPF_LPF = true,(LPF)bool HPF_LPF = false
{

	Mat padded;					// fourier image objects and arrays
	Mat planes[2];
	Mat complexImage;
	Mat in_filter_image, filter, filter_Output;

	int N, M;					// fourier image sizes

	// setup the DFT image sizes

	M = getOptimalDFTSize(in.rows);
	N = getOptimalDFTSize(in.cols);

	// setup the DFT images

	copyMakeBorder(in, padded, 0, M - in.rows, 0, N - in.cols, BORDER_CONSTANT, Scalar::all(0));
	planes[0] = Mat_<float>(padded);
	planes[1] = Mat::zeros(padded.size(), CV_32F);

	merge(planes, 2, complexImage);

	// do the DFT

	dft(complexImage, complexImage);

	// construct the filter (same size as complex image)

	filter = complexImage.clone();
	if (HPF_LPF == true)
	{
		ideal_highpass_filter(filter, radius);//HPF is DC component
	}
	if (HPF_LPF == false)
	{
		ideal_lowpass_filter(filter, radius);//LPF is DC component
	}

	// apply filter
	shift(complexImage);//because LPF is already DC component ,so the dft result has to shift to the centre
	mulSpectrums(complexImage, filter, complexImage, 0);//F(u,v) x H(u,v)
	shift(complexImage);//because the idft operation isn't use DC component result

	// create magnitude spectrum for display

	in_filter_magnitude = spectrum_magnitude(complexImage, true);

	// do inverse DFT on filtered image

	idft(complexImage, complexImage);

	// split into planes and extract plane 0 as output image

	split(complexImage, planes);
	normalize(planes[0], in_filter_image, 0, 1, CV_MINMAX);
	/*Mat convert_in_filter_image;*/
	in_filter_image.convertTo(convert_in_filter_image, CV_8U, 255);

	// do the same with the filter image

	split(filter, planes);
	normalize(planes[0], filter_Output, 0, 1, CV_MINMAX);
	/*Mat convert_filter_Output;*/
	filter_Output.convertTo(convert_filter_Output, CV_8U, 255);
}
/******************************************************************************/
int main()
{
	FILE *filein;
	FILE *fileout;
	Mat Cat512;
	unsigned char Cat512_char[512 * 512];
	/*********************************************read image*********************************************/
	filein = fopen("Cat512.raw", "rb");
	fread(Cat512_char, sizeof(Cat512_char), 1, filein);//read the image to the data type unsigned char
	fclose(filein);
	Cat512 = Mat(512, 512, CV_8UC1, Cat512_char);//unsigned char to Mat

	/******************************************************************************************/
	int radius[3] = { 3, 15, 50 };			// filter parameter

	for (int flag = 0; flag < 2; flag++)
	{
		for (int i = 0; i < 3; i++)
		{
			if (flag == 0)
			{
				switch (i + 1)
				{
				case 1:
				{
					Mat Cat512_LPF_magnitude, Cat512_LPF_image, LPF_Output;
					frequency_filtering(Cat512, radius[i], false, Cat512_LPF_magnitude, Cat512_LPF_image, LPF_Output);
					/*imshow("original", Cat512);
					imshow("spectrumMag", Cat512_LPF_magnitude);
					imshow("lowPass", Cat512_LPF_image);
					imshow("filter", LPF_Output);
					waitKey();*/

					fileout = fopen("HW6_2_a_LPF_D0=3_magnitude.raw", "wb");
					fwrite(Cat512_LPF_magnitude.data, Cat512_LPF_magnitude.rows*Cat512_LPF_magnitude.cols, 1, fileout);
					fclose(fileout);
					fileout = fopen("HW6_2_a_LPF_D0=3_image.raw", "wb");
					fwrite(Cat512_LPF_image.data, Cat512_LPF_image.rows*Cat512_LPF_image.cols, 1, fileout);
					fclose(fileout);
					fileout = fopen("HW6_2_a_LPF_D0=3_filter.raw", "wb");
					fwrite(LPF_Output.data, LPF_Output.rows*LPF_Output.cols, 1, fileout);
					fclose(fileout);
				}
				case 2:
				{
					Mat Cat512_LPF_magnitude, Cat512_LPF_image, LPF_Output;
					frequency_filtering(Cat512, radius[i], false, Cat512_LPF_magnitude, Cat512_LPF_image, LPF_Output);
					/*imshow("original", Cat512);
					imshow("spectrumMag", Cat512_LPF_magnitude);
					imshow("lowPass", Cat512_LPF_image);
					imshow("filter", LPF_Output);
					waitKey();*/

					fileout = fopen("HW6_2_a_LPF_D0=15_magnitude.raw", "wb");
					fwrite(Cat512_LPF_magnitude.data, Cat512_LPF_magnitude.rows*Cat512_LPF_magnitude.cols, 1, fileout);
					fclose(fileout);
					fileout = fopen("HW6_2_a_LPF_D0=15_image.raw", "wb");
					fwrite(Cat512_LPF_image.data, Cat512_LPF_image.rows*Cat512_LPF_image.cols, 1, fileout);
					fclose(fileout);
					fileout = fopen("HW6_2_a_LPF_D0=15_filter.raw", "wb");
					fwrite(LPF_Output.data, LPF_Output.rows*LPF_Output.cols, 1, fileout);
					fclose(fileout);
				}
				case 3:
				{
					Mat Cat512_LPF_magnitude, Cat512_LPF_image, LPF_Output;
					frequency_filtering(Cat512, radius[i], false, Cat512_LPF_magnitude, Cat512_LPF_image, LPF_Output);
					/*imshow("original", Cat512);
					imshow("spectrumMag", Cat512_LPF_magnitude);
					imshow("lowPass", Cat512_LPF_image);
					imshow("filter", LPF_Output);
					waitKey();*/

					fileout = fopen("HW6_2_a_LPF_D0=50_magnitude.raw", "wb");
					fwrite(Cat512_LPF_magnitude.data, Cat512_LPF_magnitude.rows*Cat512_LPF_magnitude.cols, 1, fileout);
					fclose(fileout);
					fileout = fopen("HW6_2_a_LPF_D0=50_image.raw", "wb");
					fwrite(Cat512_LPF_image.data, Cat512_LPF_image.rows*Cat512_LPF_image.cols, 1, fileout);
					fclose(fileout);
					fileout = fopen("HW6_2_a_LPF_D0=50_filter.raw", "wb");
					fwrite(LPF_Output.data, LPF_Output.rows*LPF_Output.cols, 1, fileout);
					fclose(fileout);
				}
				default:
					break;
				}
			}
			if (flag == 1)
			{
				switch (i + 1)
				{
				case 1:
				{
					Mat Cat512_HPF_magnitude, Cat512_HPF_image, HPF_Output;
					frequency_filtering(Cat512, radius[i], true, Cat512_HPF_magnitude, Cat512_HPF_image, HPF_Output);
					/*imshow("original", Cat512);
					imshow("spectrumMag", Cat512_LPF_magnitude);
					imshow("lowPass", Cat512_LPF_image);
					imshow("filter", LPF_Output);
					waitKey();*/

					fileout = fopen("HW6_2_a_HPF_D0=3_magnitude.raw", "wb");
					fwrite(Cat512_HPF_magnitude.data, Cat512_HPF_magnitude.rows*Cat512_HPF_magnitude.cols, 1, fileout);
					fclose(fileout);
					fileout = fopen("HW6_2_a_HPF_D0=3_image.raw", "wb");
					fwrite(Cat512_HPF_image.data, Cat512_HPF_image.rows*Cat512_HPF_image.cols, 1, fileout);
					fclose(fileout);
					fileout = fopen("HW6_2_a_HPF_D0=3_filter.raw", "wb");
					fwrite(HPF_Output.data, HPF_Output.rows*HPF_Output.cols, 1, fileout);
					fclose(fileout);
				}
				case 2:
				{
					Mat Cat512_HPF_magnitude, Cat512_HPF_image, HPF_Output;
					frequency_filtering(Cat512, radius[i], true, Cat512_HPF_magnitude, Cat512_HPF_image, HPF_Output);
					/*imshow("original", Cat512);
					imshow("spectrumMag", Cat512_LPF_magnitude);
					imshow("lowPass", Cat512_LPF_image);
					imshow("filter", LPF_Output);
					waitKey();*/

					fileout = fopen("HW6_2_a_HPF_D0=15_magnitude.raw", "wb");
					fwrite(Cat512_HPF_magnitude.data, Cat512_HPF_magnitude.rows*Cat512_HPF_magnitude.cols, 1, fileout);
					fclose(fileout);
					fileout = fopen("HW6_2_a_HPF_D0=15_image.raw", "wb");
					fwrite(Cat512_HPF_image.data, Cat512_HPF_image.rows*Cat512_HPF_image.cols, 1, fileout);
					fclose(fileout);
					fileout = fopen("HW6_2_a_HPF_D0=15_filter.raw", "wb");
					fwrite(HPF_Output.data, HPF_Output.rows*HPF_Output.cols, 1, fileout);
					fclose(fileout);
				}
				case 3:
				{
					Mat Cat512_HPF_magnitude, Cat512_HPF_image, HPF_Output;
					frequency_filtering(Cat512, radius[i], true, Cat512_HPF_magnitude, Cat512_HPF_image, HPF_Output);
					/*imshow("original", Cat512);
					imshow("spectrumMag", Cat512_LPF_magnitude);
					imshow("lowPass", Cat512_LPF_image);
					imshow("filter", LPF_Output);
					waitKey();*/

					fileout = fopen("HW6_2_a_HPF_D0=50_magnitude.raw", "wb");
					fwrite(Cat512_HPF_magnitude.data, Cat512_HPF_magnitude.rows*Cat512_HPF_magnitude.cols, 1, fileout);
					fclose(fileout);
					fileout = fopen("HW6_2_a_HPF_D0=50_image.raw", "wb");
					fwrite(Cat512_HPF_image.data, Cat512_HPF_image.rows*Cat512_HPF_image.cols, 1, fileout);
					fclose(fileout);
					fileout = fopen("HW6_2_a_HPF_D0=50_filter.raw", "wb");
					fwrite(HPF_Output.data, HPF_Output.rows*HPF_Output.cols, 1, fileout);
					fclose(fileout);
				}
				default:
					break;
				}
			}
		}
	}

}