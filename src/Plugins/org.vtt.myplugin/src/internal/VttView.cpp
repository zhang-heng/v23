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

// Blueberry
#include <berryISelectionService.h>
#include <berryIWorkbenchWindow.h>

//mitk
#include <mitkCoreObjectFactory.h>

// Qmitk
#include "VttView.h"

// Qt
#include <QtGui>

const std::string VttView::VIEW_ID = "org.mitk.views.vttview";

void VttView::SetFocus() {
  //m_Controls.buttonPerformImageProcessing->setFocus();
}

void VttView::CreateQtPartControl(QWidget *parent) {
  // create GUI widgets from the Qt Designer's .ui file
  m_Controls.setupUi(parent);
  //connect( m_Controls.buttonPerformImageProcessing, SIGNAL(clicked()), this, SLOT(DoImageProcessing()) );
  connect(m_Controls.comboBoxSteps, SIGNAL(currentIndexChanged(const int &)),
          this, SLOT(OnStepsChanged(const int &)));
  connect(m_Controls.ButtonPrev, SIGNAL(clicked()), this,
          SLOT(OnButtonPrev()));
  connect(m_Controls.ButtonNext, SIGNAL(clicked()), this,
          SLOT(OnButtonNext()));
  connect(m_Controls.ButtonCTImport, SIGNAL(clicked()), this,
          SLOT(OnButtonCTImport()));

  m_Controls.comboBoxSteps->setCurrentIndex(0);
  this->OnStepsChanged(0);
  m_Controls.ButtonPrev->setIcon(QIcon(":/org.vtt.myplugin/go-previous.png"));
  m_Controls.ButtonNext->setIcon(QIcon(":/org.vtt.myplugin/go-next.png"));
  m_Controls.ButtonCTImport->setIcon(QIcon(":/org.vtt.myplugin/Load_48.png"));
  m_Controls.ButtonCTOpen->setIcon(
                                   QIcon(":/org.vtt.myplugin/DataManager_48.png"));
}

void VttView::OpenFile() {

}

void VttView::OnButtonCTImport() {
  QStringList fileNames = QFileDialog::getOpenFileNames(NULL, "load CT image",
                                                        "", mitk::CoreObjectFactory::GetInstance()->GetFileExtensions());
  QString str = fileNames.join(",\n");
  MITK_INFO<< str.toStdString();
}

void VttView::OnStepsChanged(const int &step) {
  if (step > 0)
    m_Controls.ButtonPrev->setEnabled(true);
  else
    m_Controls.ButtonPrev->setEnabled(false);
  if (step + 1 < m_Controls.comboBoxSteps->count())
    m_Controls.ButtonNext->setEnabled(true);
  else
    m_Controls.ButtonNext->setEnabled(false);
  m_Controls.stackedWidget->setCurrentIndex(step);
}

void VttView::OnButtonPrev() {
  int currentIndex = m_Controls.comboBoxSteps->currentIndex();
  currentIndex--;
  if (currentIndex >= 0)
    m_Controls.comboBoxSteps->setCurrentIndex(currentIndex);
}

void VttView::OnButtonNext() {
  int currentIndex = m_Controls.comboBoxSteps->currentIndex();
  currentIndex++;
  if (currentIndex < m_Controls.comboBoxSteps->count())
    m_Controls.comboBoxSteps->setCurrentIndex(currentIndex);
}

void VttView::OnSelectionChanged(berry::IWorkbenchPart::Pointer /*source*/,
                                 const QList<mitk::DataNode::Pointer>& nodes) {
  // m_Controls.buttonPerformImageProcessing->setEnabled( true );
  // return;

  // // iterate all selected objects, adjust warning visibility
  // foreach( mitk::DataNode::Pointer node, nodes )
  //   {
  //     if( node.IsNotNull() && dynamic_cast<mitk::Image*>(node->GetData()) )
  //       {
  //         m_Controls.labelWarning->setVisible( false );
  //         m_Controls.buttonPerformImageProcessing->setEnabled( true );
  //         return;
  //       }
  //   }

  // //m_Controls.labelWarning->setVisible( true );
  // //m_Controls.buttonPerformImageProcessing->setEnabled( false );
}

void VttView::DoImageProcessing() {
  // mitk::IRenderWindowPart* renderWindow = this->GetRenderWindowPart();
  // if (renderWindow == NULL){
  //   renderWindow = this->GetRenderWindowPart(QmitkAbstractView::BRING_TO_FRONT | QmitkAbstractView::OPEN);
  // }else{
  //   mitk::IDataStorageReference::Pointer pds = this->GetDataStorageReference();

  // }
  // if (renderWindow == NULL) return;

  // QList<mitk::DataNode::Pointer> nodes = this->GetDataManagerSelection();
  // if (nodes.empty()) return;

  // mitk::DataNode* node = nodes.front();

  // if (!node)
  //   {
  //     // Nothing selected. Inform the user and return
  //     QMessageBox::information( NULL, "Template", "Please load and select an image before starting image processing.");
  //     return;
  //   }

  // // here we have a valid mitk::DataNode

  // // a node itself is not very useful, we need its data item (the image)
  // mitk::BaseData* data = node->GetData();
  // if (data)
  //   {
  //     // test if this data item is an image or not (could also be a surface or soething totally different)
  //     mitk::Image* image = dynamic_cast<mitk::Image*>( data );
  //     if (image)
  //       {
  //         std::stringstream message;
  //         std::string name;
  //         message << "Performing image processing for image ";
  //         if (node->GetName(name))
  //           {
  //             // a property called "name" was found for this DataNode
  //             message << "'" << name << "'";
  //           }
  //         message << ".";
  //         MITK_INFO << message.str();

  //         // actually do something here...

  //       }
  //   }
}
