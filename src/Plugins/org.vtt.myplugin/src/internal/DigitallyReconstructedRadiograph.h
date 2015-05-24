#pragma once
class CDigitallyReconstructedRadiograph
{
public:
	CDigitallyReconstructedRadiograph(float res1, float res2,
		int size1, int size2,
		float sid,
		float t1, float t2, float t3,
		float rx, float ry, float rz,
		float normal1, float normal2,
		float cor1, float cor2, float cor3,
		float threshold);
	~CDigitallyReconstructedRadiograph(void);
};