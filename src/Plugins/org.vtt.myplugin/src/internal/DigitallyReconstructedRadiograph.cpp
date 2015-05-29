#include "DigitallyReconstructedRadiograph.h"

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkResampleImageFilter.h"
#include "itkCenteredEuler3DTransform.h"
#include "itkNearestNeighborInterpolateImageFunction.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkRayCastInterpolateImageFunction.h"

#include <mitkDataNodeFactory.h>
#include <mitkImageCast.h>
#include <mitkITKImageImport.h>

CDigitallyReconstructedRadiograph::CDigitallyReconstructedRadiograph(mitk::Image::Pointer image)
{
	const     unsigned int  Dimension = 3;
	typedef   short         InputPixelType;
	typedef   unsigned char OutputPixelType;
	typedef itk::Image< InputPixelType,  Dimension >   InputImageType; 
	InputImageType::Pointer itkImage;
	m_image = image;
}

mitk::Image::Pointer CDigitallyReconstructedRadiograph::CreatDRR
	(float sx, float sy,                      //输出的像素间距
	int dx = 501, int dy = 501,               //输出尺寸
	float sid = 400,                          //射线源距离 1000?
	float tx = 0, float ty = 0, float tz = 0, //相机的变换参数
	float rx = 0, float ry = 0, float rz = 0, //轴的变换
	float cx = 0, float cy = 0, float cz = 0, //相对物体的旋转中心
	float o2Dx = 0, float o2Dy = 0,           //默认的2d投影位置 512 512
	float threshold = 0)                      //阈值
{
	char *input_name = NULL;
	char *output_name = NULL; 
	bool verbose = true; // -v

	const     unsigned int  Dimension = 3;
	typedef   short         InputPixelType;
	typedef   unsigned char OutputPixelType;
	typedef itk::Image< InputPixelType,  Dimension >   InputImageType;
	typedef itk::Image< OutputPixelType, Dimension >   OutputImageType;
	InputImageType::Pointer image;
	mitk::CastToItkImage(m_image, image);

	if (verbose)
	{
		unsigned int i;
		const InputImageType::SpacingType spacing = image->GetSpacing();
		std::cout << std::endl << "Input ";
		InputImageType::RegionType region = image->GetBufferedRegion();
		region.Print(std::cout);
		std::cout << "  Resolution: [";
		for (i=0; i<Dimension; i++)
		{
			std::cout << spacing[i];
			if (i < Dimension-1) std::cout << ", ";
		}
		std::cout << "]" << std::endl;
		const InputImageType::PointType origin = image->GetOrigin();
		std::cout << "  Origin: [";
		for (i=0; i<Dimension; i++)
		{
			std::cout << origin[i];
			if (i < Dimension-1) std::cout << ", ";
		}
		std::cout << "]" << std::endl<< std::endl;
	}

	// Creation of a \code{ResampleImageFilter} enables coordinates for
	// each of the pixels in the DRR image to be generated. These
	// coordinates are used by the \code{RayCastInterpolateImageFunction}
	// to determine the equation of each corresponding ray which is cast
	// through the input volume.

	typedef itk::ResampleImageFilter<InputImageType, InputImageType > FilterType;
	FilterType::Pointer filter = FilterType::New();
	filter->SetInput( image );
	filter->SetDefaultPixelValue( 0 );

	// An Euler transformation is defined to position the input volume.
	// The \code{ResampleImageFilter} uses this transform to position the
	// output DRR image for the desired view.

	typedef itk::CenteredEuler3DTransform< double >  TransformType;
	TransformType::Pointer transform = TransformType::New();
	transform->SetComputeZYX(true);
	TransformType::OutputVectorType translation;
	translation[0] = tx;
	translation[1] = ty;
	translation[2] = tz;
	// constant for converting degrees into radians
	const double dtr = ( vcl_atan(1.0) * 4.0 ) / 180.0;
	transform->SetTranslation( translation );
	transform->SetRotation( dtr*rx, dtr*ry, dtr*rz );
	InputImageType::PointType   imOrigin = image->GetOrigin();
	InputImageType::SpacingType imRes    = image->GetSpacing();
	typedef InputImageType::RegionType     InputImageRegionType;
	typedef InputImageRegionType::SizeType InputImageSizeType;
	InputImageRegionType imRegion = image->GetBufferedRegion();
	InputImageSizeType   imSize   = imRegion.GetSize();
	imOrigin[0] += imRes[0] * static_cast<double>( imSize[0] ) / 2.0;
	imOrigin[1] += imRes[1] * static_cast<double>( imSize[1] ) / 2.0;
	imOrigin[2] += imRes[2] * static_cast<double>( imSize[2] ) / 2.0;
	TransformType::InputPointType center;
	center[0] = cx + imOrigin[0];
	center[1] = cy + imOrigin[1];
	center[2] = cz + imOrigin[2];
	transform->SetCenter(center);
	if (verbose)
	{
		std::cout << "Image size: "
			<< imSize[0] << ", " << imSize[1] << ", " << imSize[2]
		<< std::endl << "   resolution: "
			<< imRes[0] << ", " << imRes[1] << ", " << imRes[2]
		<< std::endl << "   origin: "
			<< imOrigin[0] << ", " << imOrigin[1] << ", " << imOrigin[2]
		<< std::endl << "   center: "
			<< center[0] << ", " << center[1] << ", " << center[2]
		<< std::endl << "Transform: " << transform << std::endl;
	}

	// The \code{RayCastInterpolateImageFunction} is instantiated and passed the transform
	// object. The \code{RayCastInterpolateImageFunction} uses this
	// transform to reposition the x-ray source such that the DRR image
	// and x-ray source move as one around the input volume. This coupling
	// mimics the rigid geometry of the x-ray gantry.

	typedef itk::RayCastInterpolateImageFunction<InputImageType,double>
		InterpolatorType;
	InterpolatorType::Pointer interpolator = InterpolatorType::New();
	interpolator->SetTransform(transform);

	// We can then specify a threshold above which the volume's
	// intensities will be integrated.

	interpolator->SetThreshold(threshold);

	// The ray-cast interpolator needs to know the initial position of the
	// ray source or focal point. In this example we place the input
	// volume at the origin and halfway between the ray source and the
	// screen. The distance between the ray source and the screen
	// is the "source to image distance" \code{sid} and is specified by
	// the user.

	InterpolatorType::InputPointType focalpoint;
	focalpoint[0]= imOrigin[0];
	focalpoint[1]= imOrigin[1];
	focalpoint[2]= imOrigin[2] - sid/2.;
	interpolator->SetFocalPoint(focalpoint);
	// Software Guide : EndCodeSnippet
	if (verbose)
	{
		std::cout << "Focal Point: "
			<< focalpoint[0] << ", "
			<< focalpoint[1] << ", "
			<< focalpoint[2] << std::endl;
	}

	// Having initialised the interpolator we pass the object to the
	// resample filter.

	interpolator->Print (std::cout);
	filter->SetInterpolator( interpolator );
	filter->SetTransform( transform );

	// The size and resolution of the output DRR image is specified via the
	// resample filter.

	// setup the scene
	InputImageType::SizeType   size;
	size[0] = dx;  // number of pixels along X of the 2D DRR image
	size[1] = dy;  // number of pixels along Y of the 2D DRR image
	size[2] = 1;   // only one slice
	filter->SetSize( size );
	InputImageType::SpacingType spacing;
	spacing[0] = sx;  // pixel spacing along X of the 2D DRR image [mm]
	spacing[1] = sy;  // pixel spacing along Y of the 2D DRR image [mm]
	spacing[2] = 1.0; // slice thickness of the 2D DRR image [mm]
	filter->SetOutputSpacing( spacing );

	if (verbose)
	{
		std::cout << "Output image size: "
			<< size[0] << ", "
			<< size[1] << ", "
			<< size[2] << std::endl;
		std::cout << "Output image spacing: "
			<< spacing[0] << ", "
			<< spacing[1] << ", "
			<< spacing[2] << std::endl;
	}

	// In addition the position of the DRR is specified. The default
	// position of the input volume, prior to its transformation is
	// half-way between the ray source and screen and unless specified
	// otherwise the normal from the "screen" to the ray source passes
	// directly through the centre of the DRR.

	double origin[ Dimension ];
	origin[0] = imOrigin[0] + o2Dx - sx*((double) dx - 1.)/2.;
	origin[1] = imOrigin[1] + o2Dy - sy*((double) dy - 1.)/2.;
	origin[2] = imOrigin[2] + sid/2.;
	filter->SetOutputOrigin( origin );

	if (verbose)
	{
		std::cout << "Output image origin: "
			<< origin[0] << ", "
			<< origin[1] << ", "
			<< origin[2] << std::endl;
	}
	// create writer

	// The output of the resample filter can then be passed to a writer to
	// save the DRR image to a file.

	typedef itk::RescaleIntensityImageFilter<InputImageType, OutputImageType> RescaleFilterType;
	RescaleFilterType::Pointer rescaler = RescaleFilterType::New();
	rescaler->SetOutputMinimum(   0 );
	rescaler->SetOutputMaximum( 255 );
	rescaler->SetInput( filter->GetOutput() );
	typedef itk::ImageFileWriter< OutputImageType >  WriterType;
	WriterType::Pointer writer = WriterType::New();
	try
	{ 
		rescaler->Update();
		auto mitkImage =mitk::Image::New();
		mitk::CastToMitkImage(rescaler->GetOutput(),mitkImage);
		return mitkImage;
	}
	catch( itk::ExceptionObject & err )
	{
		std::cerr << "ERROR: ExceptionObject caught !" << std::endl;
		std::cerr << err << std::endl;
	}

	return nullptr;//EXIT_SUCCESS;
}


CDigitallyReconstructedRadiograph::~CDigitallyReconstructedRadiograph(void)
{
}