﻿/*===================================================================
CT管理类,
===================================================================*/

#include <berryISelectionListener.h>
#include <QmitkAbstractView.h>
#include "ui_VttViewControls.h"

#include <QmitkAbstractRenderEditor.h>

class CCtManage: public QObject
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
	Ui::VttViewControls m_Controls;
};
