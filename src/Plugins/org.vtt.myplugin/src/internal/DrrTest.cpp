#include "DrrTest.h"

#include <mitkDataNodeFactory.h>



CDrrTest::CDrrTest(QWidget *parent /*= 0*/)
{
	m_ui.setupUi(this);

	m_ui.sx->setRange(-100,100);
	m_ui.sx->setValue(1);
	connect(m_ui.sx, SIGNAL(valueChanged(double)), this, SLOT(On_sx(double)));
	m_ui.sy->setRange(-100,100);
	m_ui.sy->setValue(1);
	connect(m_ui.sy, SIGNAL(valueChanged(double)), this, SLOT(On_sy(double)));

	m_ui.dx->setRange(1,1000);
	m_ui.dx->setValue(501);
	connect(m_ui.dx, SIGNAL(valueChanged(int)), this, SLOT(On_dx(int)));
	m_ui.dy->setRange(1,1000);
	m_ui.dy->setValue(501);
	connect(m_ui.dy, SIGNAL(valueChanged(int)), this, SLOT(On_dy(int)));

	m_ui.sid->setRange(1,1000);
	m_ui.sid->setValue(400);
	connect(m_ui.sid, SIGNAL(valueChanged(double)), this, SLOT(On_sid(double)));

	m_ui.tx->setRange(-300,300);
	connect(m_ui.tx, SIGNAL(valueChanged(double)), this, SLOT(On_tx(double)));
	m_ui.ty->setRange(-300,300);
	connect(m_ui.ty, SIGNAL(valueChanged(double)), this, SLOT(On_ty(double)));
	m_ui.tz->setRange(-300,300);
	connect(m_ui.tz, SIGNAL(valueChanged(double)), this, SLOT(On_tz(double)));

	m_ui.rx->setRange(-300,300);
	connect(m_ui.rx, SIGNAL(valueChanged(double)), this, SLOT(On_rx(double)));
	m_ui.ry->setRange(-300,300);
	connect(m_ui.ry, SIGNAL(valueChanged(double)), this, SLOT(On_ry(double)));
	m_ui.rz->setRange(-300,300);
	connect(m_ui.rz, SIGNAL(valueChanged(double)), this, SLOT(On_rz(double)));

	m_ui.cx->setRange(-300,300);
	connect(m_ui.cx, SIGNAL(valueChanged(double)), this, SLOT(On_cx(double)));
	m_ui.cy->setRange(-300,300);
	connect(m_ui.cy, SIGNAL(valueChanged(double)), this, SLOT(On_cy(double)));
	m_ui.cz->setRange(-300,300);
	connect(m_ui.cz, SIGNAL(valueChanged(double)), this, SLOT(On_cz(double)));

	m_ui.o2Dx->setRange(-300,300);
	connect(m_ui.o2Dx, SIGNAL(valueChanged(double)), this, SLOT(On_o2Dx(double)));
	m_ui.o2Dy->setRange(-300,300);
	connect(m_ui.o2Dy, SIGNAL(valueChanged(double)), this, SLOT(On_o2Dy(double)));

	m_ui.threshold->setRange(-300,300);
	connect(m_ui.threshold, SIGNAL(valueChanged(double)), this, SLOT(On_threshold(double)));

	initData();
}

void CDrrTest::On_sx(double i)
{
	cout<<i<<endl;
	ShowDRR();
}

void CDrrTest::On_sy(double i)
{ 
	cout<<i<<endl;
	ShowDRR();
}

void CDrrTest::On_dx(int i)
{
	cout<<i<<endl;
	ShowDRR();
}

void CDrrTest::On_dy(int i)
{
	cout<<i<<endl;
	ShowDRR();
}

void CDrrTest::On_sid(double i)
{
	cout<<i<<endl;
	ShowDRR();
}

void CDrrTest::On_tx(double i)
{
	cout<<i<<endl;
	ShowDRR();
}

void CDrrTest::On_ty(double i)
{
	cout<<i<<endl;
	ShowDRR();
}

void CDrrTest::On_tz(double i)
{
	cout<<i<<endl;
	ShowDRR();
}

void CDrrTest::On_rx(double i)
{
	cout<<i<<endl;
	ShowDRR();
}

void CDrrTest::On_ry(double i)
{
	cout<<i<<endl;
	ShowDRR();
}

void CDrrTest::On_rz(double i)
{
	cout<<i<<endl;
	ShowDRR();
}

void CDrrTest::On_cx(double i)
{
	cout<<i<<endl;
	ShowDRR();
}

void CDrrTest::On_cy(double i)
{
	cout<<i<<endl;
	ShowDRR();
}

void CDrrTest::On_cz(double i)
{
	cout<<i<<endl;
	ShowDRR();
}

void CDrrTest::On_o2Dx(double i)
{
	cout<<i<<endl;
	ShowDRR();
}

void CDrrTest::On_o2Dy(double i)
{
	cout<<i<<endl;
	ShowDRR();
}
void CDrrTest::On_threshold(double i)
{
	cout<<i<<endl;
	ShowDRR();
}

void CDrrTest::setCloser(std::function<void ()> f)
{ 
	m_closer = f;
} 

void CDrrTest::closeEvent( QCloseEvent * ce )
{
	m_closer();
}

#define V(C) m_ui.C->value()

#define MODLE_PATH "D:\\kuaipan\\Work\\MITK\\phantom.mha"

#include <mitkImagePixelReadAccessor.h>
#include <mitkImagePixelWriteAccessor.h>

#include <mitkImageReadAccessor.h>
#include <mitkImageWriteAccessor.h>

#include <mitkImageWriter.h>
#include <mitkSurface.h>
#include <mitkSurfaceToImageFilter.h>

void CDrrTest::initData()
{
	////生成实验体数据
	//mitk::DataNodeFactory::Pointer reader=mitk::DataNodeFactory::New();
	//reader->SetFileName("C:\\Users\\kay\\Downloads\\test\\sphere.stl");
	//reader->Update();
	//auto node = reader->GetOutput();
	//mitk::Surface::Pointer surface = dynamic_cast<mitk::Surface*>(node->GetData());

	//reader->SetFileName("C:\\Users\\kay\\Downloads\\test\\phantom.nrrd");
	//reader->Update();
	//auto node2 = reader->GetOutput();
	//mitk::Image::Pointer image = dynamic_cast<mitk::Image*>(node2->GetData());

	//mitk::SurfaceToImageFilter::Pointer surfaceToImageFilter = mitk::SurfaceToImageFilter::New();
	//surfaceToImageFilter->MakeOutputBinaryOn();
	//surfaceToImageFilter->SetInput(surface);
	//surfaceToImageFilter->SetImage(image);
	//surfaceToImageFilter->Update();
	//auto image2 = surfaceToImageFilter->GetOutput();

	//for (int iz =0; iz <image->GetDimension(2); iz++)
	//{
	//	mitk::ImagePixelWriteAccessor<float,2> writeAccess(image,image->GetSliceData(iz));
	//	mitk::ImagePixelReadAccessor<unsigned char,2> readAccess(image2, image2->GetSliceData(iz));
	//	for(int ix = 0; ix<image2->GetDimension(0); ix++)
	//	{
	//		for(int iy = 0; iy<image2->GetDimension(1); iy++)
	//		{
	//			itk::Index<2> idx = {{ ix, iy }};
	//			auto v = readAccess.GetPixelByIndex(idx);
	//			if (v>0)
	//			{
	//				writeAccess.SetPixelByIndex(idx, 0x0fff);
	//			}
	//		}
	//	}
	//}
	//mitk::ImageWriter::Pointer writer = mitk::ImageWriter::New();
	//writer->SetInput(image);
	//writer->SetFileName("C:\\Users\\kay\\Downloads\\test\\phantom2.nrrd");
	//writer->Update();
	//return;




	////drrTest
	//mitk::ImageGenerator::GenerateRandomImage<float>(dimX,dimY);
	//auto dataNode = mitk::DataNode::New();
	//dataNode->SetName("node");
	//auto dn = mitk::Image::New();
	//dataNode->SetData(dn);
	//ds = mitk::StandaloneDataStorage::New();
	//ds->Add(dataNode);
	//mitk::DataNodeFactory::Pointer reader=mitk::DataNodeFactory::New();
	//try
	//{
	//	reader->SetFileName(MODLE_PATH);
	//	reader->Update();
	//	auto node = reader->GetOutput();
	//	auto image = dynamic_cast<mitk::Image*>(node->GetData());
	//	m_drr = new CDigitallyReconstructedRadiograph(image);
	//}
	//catch(...)
	//{
	//	return;
	//}
	//renderWindow.GetRenderer()->SetDataStorage(ds);
	//mitk::TimeGeometry::Pointer geo = ds->ComputeBoundingGeometry3D(ds->GetAll());
	//mitk::RenderingManager::GetInstance()->InitializeViews( geo );
	//mitk::SliceNavigationController::Pointer sliceNaviController = renderWindow.GetSliceNavigationController();
	//if (sliceNaviController)
	//	sliceNaviController->GetSlice()->SetPos( 0 );
	//renderWindow.show();
	//renderWindow.resize( 512, 512 );
}

void CDrrTest::ShowDRR()
{
	auto image = m_drr->CreatDRR(V(sx),V(sy),
		V(dx),V(dy),
		V(sid),
		V(tx),V(ty),V(tz),
		V(rx),V(ry),V(rz),
		V(cx),V(cy),V(cz),
		V(o2Dx),V(o2Dy),
		V(threshold));
	auto node = ds->GetNamedNode("node");
	node->SetData(image);

	//mitk::DataNodeFactory::Pointer reader=mitk::DataNodeFactory::New();
	//reader->SetFileName("d://xxx.png");
	//reader->Update();
	//auto nodxe = reader->GetOutput(); 
	//node->SetData(nodxe->GetData());

	renderWindow.GetRenderer()->SetDataStorage(ds);
	mitk::TimeGeometry::Pointer geo = ds->ComputeBoundingGeometry3D(ds->GetAll());
	mitk::RenderingManager::GetInstance()->InitializeViews( geo );
	mitk::SliceNavigationController::Pointer sliceNaviController = renderWindow.GetSliceNavigationController();
	if (sliceNaviController)
		sliceNaviController->GetSlice()->SetPos( 0 );
}