#define UNITY_INTERFACE_API __stdcall
#define UNITY_INTERFACE_EXPORT __declspec(dllexport)

#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <vector>

using namespace cv;
using namespace std;

extern "C"
{

	UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API GetNumber()
	{
		return 12356;
	}

	//ライブラリを追加の依存ファイルに追加する。

	UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API CalcHomography(const double* src, const double* dst, double* homography )
	{
		Mat mHomography;

		Point2f inX;

		vector<Point2f> srcPoints, dstPoints;
		srcPoints.push_back(Point2f(src[0], src[1]));
		srcPoints.push_back(Point2f(src[2], src[3]));
		srcPoints.push_back(Point2f(src[4], src[5]));
		srcPoints.push_back(Point2f(src[6], src[7]));

		dstPoints.push_back(Point2f(dst[0], dst[1]));
		dstPoints.push_back(Point2f(dst[2], dst[3]));
		dstPoints.push_back(Point2f(dst[4], dst[5]));
		dstPoints.push_back(Point2f(dst[6], dst[7]));

		// calc homography
		if (srcPoints.size() != 4 || dstPoints.size() != 4)
		{
			return -1;	// error
		}

		// generate a homography from input points
		mHomography = findHomography(Mat(srcPoints), Mat(dstPoints));

		homography[0] = mHomography.at<double>(0);
		homography[1] = mHomography.at<double>(1);
		homography[2] = mHomography.at<double>(2);
		homography[3] = mHomography.at<double>(3);
		homography[4] = mHomography.at<double>(4);
		homography[5] = mHomography.at<double>(5);
		homography[6] = mHomography.at<double>(6);
		homography[7] = mHomography.at<double>(7);
		homography[8] = mHomography.at<double>(8);

		return 234;
	}

	UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API HomographyTransform(const double* src, double* dst, const double* homogrphy)
	{
		// calc transform point
		//Mat inputMat = (Mat_<double>(3, 1) << input.x, input.y, input.z);
		//Mat tmpMat = mHomography * inputMat;
		//float dst_x = tmpMat.at<double>(0, 0) / tmpMat.at<double>(2, 0);
		//float dst_y = tmpMat.at<double>(1, 0) / tmpMat.at<double>(2, 0);
		//return ofPoint(dst_x, dst_y);

		return 0;
	}

	UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API CalcHomographyPoint(const double* input, double* output, const double* src, const double* dst)
	{
		Mat mHomography;

		//double output[2];

		vector<Point2f> srcPoints, dstPoints;
		srcPoints.push_back(Point2f(src[0], src[1]));
		srcPoints.push_back(Point2f(src[2], src[3]));
		srcPoints.push_back(Point2f(src[4], src[5]));
		srcPoints.push_back(Point2f(src[6], src[7]));

		dstPoints.push_back(Point2f(dst[0], dst[1]));
		dstPoints.push_back(Point2f(dst[2], dst[3]));
		dstPoints.push_back(Point2f(dst[4], dst[5]));
		dstPoints.push_back(Point2f(dst[6], dst[7]));

		// generate a homography from input points
		mHomography = findHomography(Mat(srcPoints), Mat(dstPoints));

		// calc transform point
		Mat inputMat = (Mat_<double>(3, 1) << input[0], input[1], input[2]);
		Mat tmpMat = mHomography * inputMat;
		float dst_x = tmpMat.at<double>(0, 0) / tmpMat.at<double>(2, 0);
		float dst_y = tmpMat.at<double>(1, 0) / tmpMat.at<double>(2, 0);

		output[0] = dst_x;
		output[1] = dst_y;
		output[2] = 1;

		return 567;
	}

}