#include "CtManage.h"

// Qt
#include <QtGui>
#include <QmitkAboutDialog/QmitkAboutDialog.h>

//mitk
#include <mitkCoreObjectFactory.h>
#include <berryPlatform.h>
#include <berryPlatformUI.h>
#include <berryIWorkbenchWindow.h>
#include <berryIWorkbenchPage.h>
#include <berryIViewDescriptor.h>
#include <mitkDataStorageEditorInput.h>

const std::string CCtManage::VIEW_ID = "org.mitk.views.vttview";

CCtManage::CCtManage(Ui::VttViewControls controls)
{
	m_Controls = controls;
	controls.ButtonCTImport->setIcon(QIcon(":/org.vtt.myplugin/Load_48.png"));
	controls.ButtonCTOpen->setIcon(QIcon(":/org.vtt.myplugin/DataManager_48.png"));

	connect(m_Controls.ButtonCTOpen, SIGNAL(clicked()), this, SLOT(OnButtonCTOpen()));
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

void CCtManage::OnButtonCTOpen()
{
	//org.mitk.editors.stdmultiwidget
	berry::IWorkbenchPage::Pointer page = this->GetSite()->GetPage();
	mitk::DataStorageEditorInput::Pointer input(new mitk::DataStorageEditorInput(GetDataStorageReference()));
	page->OpenEditor(input,"org.mitk.editors.stdmultiwidget");

	//this->GetRenderWindowPart(QmitkAbstractView::BRING_TO_FRONT | QmitkAbstractView::OPEN);

//	berry::IWorkbench* currentWorkbench = berry::PlatformUI::GetWorkbench();
//	berry::IWorkbenchWindow::Pointer currentWorkbenchWindow = currentWorkbench->GetActiveWorkbenchWindow();
//	berry::IWorkbenchPage::Pointer currentPage = currentWorkbenchWindow->GetActivePage();
//	//CtestEditor * view = new CtestEditor();
//
//	//currentPage->Activate();
//	berry::IEditorPart::Pointer editor = currentPage->GetActiveEditor();
//	berry::IWorkbenchPart::Pointer currentPart = currentPage->GetActivePart();
//	MITK_INFO<< currentPart->GetSite()->GetPluginId();

//打开帮助页面
//berry::PlatformUI::GetWorkbench()->GetIntroManager()->ShowIntro(berry::PlatformUI::GetWorkbench()->GetActiveWorkbenchWindow(), false);
//新增view页面，Perspective
//berry::PlatformUI::GetWorkbench()->ShowPerspective("org.blueberry.perspectives.help", berry::PlatformUI::GetWorkbench()->GetActiveWorkbenchWindow());
//QmitkAboutDialog* aboutDialog = new QmitkAboutDialog(QApplication::activeWindow(), NULL);
//aboutDialog->open();
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
