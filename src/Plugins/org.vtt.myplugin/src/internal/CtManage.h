/*===================================================================
 CT管理类,
 ===================================================================*/

#include <berryISelectionListener.h>
#include <QmitkAbstractView.h>
#include "ui_VttViewControls.h"

#include <QmitkAbstractRenderEditor.h>

class CtestEditor: public QmitkAbstractRenderEditor
{

};

class CCtManage: public QmitkAbstractView
{
Q_OBJECT
public:
	static const std::string VIEW_ID;
	CCtManage(Ui::VttViewControls controls);
public slots:
	void OnCTListCurrentItem(QListWidgetItem* current, QListWidgetItem* previous);
	void OnButtonCTOpen();
	void OnButtonCTImport();

protected:

	virtual void CreateQtPartControl(QWidget *);

	virtual void SetFocus();
	Ui::VttViewControls m_Controls;
};
