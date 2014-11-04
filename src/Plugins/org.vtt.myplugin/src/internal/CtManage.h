/*===================================================================
 CT管理类,
 ===================================================================*/

#include <berryISelectionListener.h>
#include <QmitkAbstractView.h>
#include "ui_VttViewControls.h"

class CCtManage: public QmitkAbstractView
{
Q_OBJECT
public:
	CCtManage(Ui::VttViewControls controls);
public slots:
	void OnCTListCurrentItem(QListWidgetItem* current, QListWidgetItem* previous);
	void OnButtonCTImport();

protected:

	virtual void CreateQtPartControl(QWidget *);

	virtual void SetFocus();
	Ui::VttViewControls m_Controls;
};
