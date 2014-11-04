#include "CtManage.h"

//mitk
#include <mitkCoreObjectFactory.h>
// Qt
#include <QtGui>

CCtManage::CCtManage(Ui::VttViewControls controls)
{
	m_Controls = controls;
	controls.ButtonCTImport->setIcon(QIcon(":/org.vtt.myplugin/Load_48.png"));
	controls.ButtonCTOpen->setIcon(QIcon(":/org.vtt.myplugin/DataManager_48.png"));

	connect(m_Controls.ButtonCTImport, SIGNAL(clicked()), this, SLOT(OnButtonCTImport()));
	connect(m_Controls.CTListWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this,
			SLOT(OnCTListCurrentItem(QListWidgetItem*,QListWidgetItem*)));

	//test
	m_Controls.CTListWidget->addItem(new QListWidgetItem(QIcon(":/org.vtt.myplugin/Load_48.png"), "111111"));
	m_Controls.CTListWidget->addItem(new QListWidgetItem(QIcon(":/org.vtt.myplugin/Load_48.png"), "222222"));
}

//响应CT列表点击消息
void CCtManage::OnCTListCurrentItem(QListWidgetItem* current, QListWidgetItem*)
{
	MITK_INFO<<"ct: "<< current->text().toStdString();
}

void CCtManage::OnButtonCTImport()
{
	QStringList fileNames = QFileDialog::getOpenFileNames(NULL, "load CT image", "", mitk::CoreObjectFactory::GetInstance()->GetFileExtensions());
	QString str = fileNames.join(",\n");
	MITK_INFO<< str.toStdString();
}

void CCtManage::CreateQtPartControl(QWidget *)
{
}

void CCtManage::SetFocus()
{
}
