/*===================================================================

 The Medical Imaging Interaction Toolkit (MITK)

 Copyright (c) German Cancer Research Center,
 Division of Medical and Biological Informatics.
 All rights reserved.

 This software is distributed WITHOUT ANY WARRANTY; without
 even the implied warranty of MERCHANTABILITY or FITNESS FOR
 A PARTICULAR PURPOSE.

 See LICENSE.txt or http://www.mitk.org for details.

 ===================================================================*/

#ifndef VttView_h
#define VttView_h

#include <berryISelectionListener.h>

#include <QmitkAbstractView.h>

#include "ui_VttViewControls.h"

#include "XrayManage.h"
#include "CtManage.h"
#include "VNavigation.h"

/**
 \brief VttView

 \warning  This class is not yet documented. Use "git blame" and ask the author to provide basic documentation.

 \sa QmitkAbstractView
 \ingroup ${plugin_target}_internal
 */
class VttView: public QmitkAbstractView
{
	// this is needed for all Qt objects that should have a Qt meta-object
	// (everything that derives from QObject and wants to have signal/slots)
Q_OBJECT

public:
	static const std::string VIEW_ID;

protected slots:
	void DoImageProcessing();
	void OnStepsChanged(const int &step);
	void OnButtonPrev();
	void OnButtonNext();

protected:

	virtual void CreateQtPartControl(QWidget *parent);

	virtual void SetFocus();

	/// \brief called by QmitkFunctionality when DataManager's selection has changed
	virtual void OnSelectionChanged(berry::IWorkbenchPart::Pointer source, const QList<mitk::DataNode::Pointer>& nodes);

	Ui::VttViewControls m_Controls;

	CCtManage * CtManage;
};

#endif // VttView_h
