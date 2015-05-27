#include "DrrTest.h"

CDrrTest::CDrrTest(QWidget *parent /*= 0*/)
{
	m_ui.setupUi(this);

	m_ui.sx->setRange(-100,100);
	connect(m_ui.sx, SIGNAL(valueChanged(double)), this, SLOT(On_sx(double)));
	m_ui.sy->setRange(-100,100);
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
}

void CDrrTest::On_sx(double i)
{
	cout<<i<<endl;
}

void CDrrTest::On_sy(double i)
{ 
	cout<<i<<endl;
}

void CDrrTest::On_dx(int i)
{
	cout<<i<<endl;
}

void CDrrTest::On_dy(int i)
{
	cout<<i<<endl;
}

void CDrrTest::On_sid(double i)
{
	cout<<i<<endl;
}

void CDrrTest::On_tx(double i)
{
	cout<<i<<endl;
}

void CDrrTest::On_ty(double i)
{
	cout<<i<<endl;
}

void CDrrTest::On_tz(double i)
{
	cout<<i<<endl;
}

void CDrrTest::On_rx(double i)
{
	cout<<i<<endl;
}

void CDrrTest::On_ry(double i)
{
	cout<<i<<endl;
}

void CDrrTest::On_rz(double i)
{
	cout<<i<<endl;
}

void CDrrTest::On_cx(double i)
{
	cout<<i<<endl;
}

void CDrrTest::On_cy(double i)
{
	cout<<i<<endl;
}

void CDrrTest::On_cz(double i)
{
	cout<<i<<endl;
}

void CDrrTest::On_o2Dx(double i)
{
	cout<<i<<endl;
}

void CDrrTest::On_o2Dy(double i)
{
	cout<<i<<endl;
}
void CDrrTest::On_threshold(double i)
{
	cout<<i<<endl;
}