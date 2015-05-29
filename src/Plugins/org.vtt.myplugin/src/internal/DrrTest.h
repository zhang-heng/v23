#ifndef DrrTest_h
#define DrrTest_h

#include <berryISelectionListener.h>
#include <QmitkAbstractView.h>
#include "ui_DrrTest.h"
#include <QDialog>
#include <QmitkAbstractRenderEditor.h>
#include <mitkStandaloneDataStorage.h>
#include <QmitkRenderWindow.h>

#include "DigitallyReconstructedRadiograph.h"
class CDrrTest: public QDialog
{
	Q_OBJECT
public:
	CDrrTest(QWidget *parent = 0);
	static const std::string VIEW_ID;
	void setCloser(std::function<void ()> f);
private:
	std::function<void ()> m_closer;
protected slots:
	void On_sx(double i);
	void On_sy(double i);
	void On_dx(int i);
	void On_dy(int i);
	void On_sid(double i);
	void On_tx(double i);
	void On_ty(double i);
	void On_tz(double i);
	void On_rx(double i);
	void On_ry(double i);
	void On_rz(double i);
	void On_cx(double i);
	void On_cy(double i);
	void On_cz(double i);
	void On_o2Dx(double i);
	void On_o2Dy(double i);
	void On_threshold(double i);
protected:
	Ui::DrrTest m_ui;
	void closeEvent(QCloseEvent * ce);
	void initData();
	void ShowDRR();
	mitk::StandaloneDataStorage::Pointer ds;
	QmitkRenderWindow renderWindow; 
	CDigitallyReconstructedRadiograph *m_drr;
};

#endif // DrrTest_h