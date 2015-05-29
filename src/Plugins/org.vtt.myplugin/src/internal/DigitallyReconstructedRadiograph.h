#pragma once
#include <mitkImage.h>

class CDigitallyReconstructedRadiograph
{
public:
	CDigitallyReconstructedRadiograph(mitk::Image::Pointer image);
	~CDigitallyReconstructedRadiograph(void);

	mitk::Image::Pointer CreatDRR(float res1, float res2,
		int size1, int size2,
		float sid,
		float t1, float t2, float t3,
		float rx, float ry, float rz,
		float normal1, float normal2,
		float cor1, float cor2, float cor3,
		float threshold);
private:
	itk::SmartPointer<mitk::Image> m_image;
};