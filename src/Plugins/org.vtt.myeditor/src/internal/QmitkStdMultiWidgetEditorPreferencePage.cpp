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

#include "QmitkStdMultiWidgetEditorPreferencePage.h"
#include "QmitkStdMultiWidgetEditor.h"

#include <QLabel>
#include <QPushButton>
#include <QFormLayout>
#include <QCheckBox>
#include <QColorDialog>
#include <QComboBox>

#include <berryIPreferencesService.h>
#include <berryPlatform.h>

QmitkStdMultiWidgetEditorPreferencePage::QmitkStdMultiWidgetEditorPreferencePage()
: m_MainControl(0)
{
}

void QmitkStdMultiWidgetEditorPreferencePage::Init(berry::IWorkbench::Pointer )
{
}

void QmitkStdMultiWidgetEditorPreferencePage::CreateQtControl(QWidget* parent)
{
  berry::IPreferencesService::Pointer prefService
    = berry::Platform::GetServiceRegistry()
    .GetServiceById<berry::IPreferencesService>(berry::IPreferencesService::ID);

  m_StdMultiWidgetEditorPreferencesNode = prefService->GetSystemPreferences()->Node(VttWidgetEditor::EDITOR_ID);

  m_MainControl = new QWidget(parent);
  m_EnableFlexibleZooming = new QCheckBox;
  m_ShowLevelWindowWidget = new QCheckBox;
  m_PACSLikeMouseMode = new QCheckBox;

  QFormLayout *formLayout = new QFormLayout;
  formLayout->addRow("&Use constrained zooming and padding", m_EnableFlexibleZooming);
  formLayout->addRow("&Show level/window widget", m_ShowLevelWindowWidget);
  formLayout->addRow("&PACS like mouse interactions (select left mouse button action)", m_PACSLikeMouseMode);

  // gradient background
  QLabel* gBName = new QLabel;
  gBName->setText("Gradient background");
  formLayout->addRow(gBName);

  // color
  m_ColorButton1 = new QPushButton;
  m_ColorButton1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
  m_ColorButton2 = new QPushButton;
  m_ColorButton2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
  QPushButton* resetButton = new QPushButton;
  resetButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
  resetButton->setText("Reset");

  QLabel* colorLabel1 = new QLabel("first color : ");
  colorLabel1->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
  QLabel* colorLabel2 = new QLabel("second color: ");
  colorLabel2->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);

  QHBoxLayout* colorWidgetLayout = new QHBoxLayout;
  colorWidgetLayout->setContentsMargins(4,4,4,4);
  colorWidgetLayout->addWidget(colorLabel1);
  colorWidgetLayout->addWidget(m_ColorButton1);
  colorWidgetLayout->addWidget(colorLabel2);
  colorWidgetLayout->addWidget(m_ColorButton2);
  colorWidgetLayout->addWidget(resetButton);

  QWidget* colorWidget = new QWidget;
  colorWidget->setLayout(colorWidgetLayout);

  QLabel* renderLabel = new QLabel;
  renderLabel->setText("Rendering Mode* ");

  m_RenderingMode = new QComboBox;
  m_RenderingMode->addItem("Standard Rendering");
  m_RenderingMode->addItem("Enable Multisampling (Antialiasing)" );
  m_RenderingMode->addItem("Enable Depth Peeling" );

  QLabel* cBHint = new QLabel;
  cBHint->setText("* Changes require restart of MITK. \n Depth Peeling is only supported by Windows. \n For other OS, use Standard Rendering and enable \n the property 'Depth Sorting' in the property list of the surface data node.");

  QSpacerItem *spacer1 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );

  QHBoxLayout* renderingWidgetLayout = new QHBoxLayout;
  renderingWidgetLayout->setContentsMargins(4,4,4,4);
  renderingWidgetLayout->addWidget(renderLabel);
  renderingWidgetLayout->addWidget(m_RenderingMode);
  renderingWidgetLayout->addWidget(cBHint);
  renderingWidgetLayout->addSpacerItem(spacer1);

  QWidget* renderingWidget = new QWidget;
  renderingWidget->setLayout(renderingWidgetLayout);

  //spacer
  QSpacerItem *spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
  QVBoxLayout* vBoxLayout = new QVBoxLayout;
  vBoxLayout->addLayout(formLayout);
  vBoxLayout->addWidget(colorWidget);
  vBoxLayout->addWidget(renderingWidget);
  vBoxLayout->addSpacerItem(spacer);

  m_MainControl->setLayout(vBoxLayout);

  QObject::connect( m_ColorButton1, SIGNAL( clicked() )
    , this, SLOT( FirstColorChanged() ) );

  QObject::connect( m_ColorButton2, SIGNAL( clicked() )
    , this, SLOT( SecondColorChanged() ) );

  QObject::connect( resetButton, SIGNAL( clicked() )
    , this, SLOT( ResetColors() ) );

  QObject::connect( m_RenderingMode, SIGNAL(activated(int) )
    , this, SLOT( ChangeRenderingMode(int) ) );

  this->Update();
}

QWidget* QmitkStdMultiWidgetEditorPreferencePage::GetQtControl() const
{
  return m_MainControl;
}

bool QmitkStdMultiWidgetEditorPreferencePage::PerformOk()
{
  m_StdMultiWidgetEditorPreferencesNode->Put("first background color style sheet", m_FirstColorStyleSheet.toStdString());
  m_StdMultiWidgetEditorPreferencesNode->Put("second background color style sheet", m_SecondColorStyleSheet.toStdString());
  m_StdMultiWidgetEditorPreferencesNode->PutByteArray("first background color", m_FirstColor);
  m_StdMultiWidgetEditorPreferencesNode->PutByteArray("second background color", m_SecondColor);
  m_StdMultiWidgetEditorPreferencesNode->PutBool("Use constrained zooming and padding"
                                        , m_EnableFlexibleZooming->isChecked());
  m_StdMultiWidgetEditorPreferencesNode->PutBool("Show level/window widget", m_ShowLevelWindowWidget->isChecked());
  m_StdMultiWidgetEditorPreferencesNode->PutBool("PACS like mouse interaction", m_PACSLikeMouseMode->isChecked());
  m_StdMultiWidgetEditorPreferencesNode->PutInt("Rendering Mode", m_RenderingMode->currentIndex());

  return true;
}

void QmitkStdMultiWidgetEditorPreferencePage::PerformCancel()
{
}

void QmitkStdMultiWidgetEditorPreferencePage::Update()
{
  m_EnableFlexibleZooming->setChecked(m_StdMultiWidgetEditorPreferencesNode->GetBool("Use constrained zooming and padding", true));
  m_ShowLevelWindowWidget->setChecked(m_StdMultiWidgetEditorPreferencesNode->GetBool("Show level/window widget", true));
  m_PACSLikeMouseMode->setChecked(m_StdMultiWidgetEditorPreferencesNode->GetBool("PACS like mouse interaction", false));
  m_FirstColorStyleSheet = QString::fromStdString(m_StdMultiWidgetEditorPreferencesNode->Get("first background color style sheet", ""));
  m_SecondColorStyleSheet = QString::fromStdString(m_StdMultiWidgetEditorPreferencesNode->Get("second background color style sheet", ""));
  m_FirstColor = m_StdMultiWidgetEditorPreferencesNode->GetByteArray("first background color", "");
  m_SecondColor = m_StdMultiWidgetEditorPreferencesNode->GetByteArray("second background color", "");
  int index=m_StdMultiWidgetEditorPreferencesNode->GetInt("Rendering Mode",0);
  m_RenderingMode->setCurrentIndex(index);

  if (m_FirstColorStyleSheet=="")
  {
    m_FirstColorStyleSheet = "background-color:rgb(25,25,25)";
  }
  if (m_SecondColorStyleSheet=="")
  {
    m_SecondColorStyleSheet = "background-color:rgb(127,127,127)";
  }
  if (m_FirstColor=="")
  {
    m_FirstColor = "#191919";
  }
  if (m_SecondColor=="")
  {
    m_SecondColor = "#7F7F7F";
  }
  m_ColorButton1->setStyleSheet(m_FirstColorStyleSheet);
  m_ColorButton2->setStyleSheet(m_SecondColorStyleSheet);
}

void QmitkStdMultiWidgetEditorPreferencePage::FirstColorChanged()
{
  QColor color = QColorDialog::getColor();
  m_ColorButton1->setAutoFillBackground(true);
  QString styleSheet = "background-color:rgb(";

  styleSheet.append(QString::number(color.red()));
  styleSheet.append(",");
  styleSheet.append(QString::number(color.green()));
  styleSheet.append(",");
  styleSheet.append(QString::number(color.blue()));
  styleSheet.append(")");
  m_ColorButton1->setStyleSheet(styleSheet);

  m_FirstColorStyleSheet = styleSheet;
  QStringList firstColor;
  firstColor << color.name();
  m_FirstColor = firstColor.replaceInStrings(";","\\;").join(";").toStdString();
 }

void QmitkStdMultiWidgetEditorPreferencePage::SecondColorChanged()
{
  QColor color = QColorDialog::getColor();
  m_ColorButton2->setAutoFillBackground(true);
  QString styleSheet = "background-color:rgb(";

  styleSheet.append(QString::number(color.red()));
  styleSheet.append(",");
  styleSheet.append(QString::number(color.green()));
  styleSheet.append(",");
  styleSheet.append(QString::number(color.blue()));
  styleSheet.append(")");
  m_ColorButton2->setStyleSheet(styleSheet);

  m_SecondColorStyleSheet = styleSheet;
  QStringList secondColor;
  secondColor << color.name();
  m_SecondColor = secondColor.replaceInStrings(";","\\;").join(";").toStdString();
 }

void QmitkStdMultiWidgetEditorPreferencePage::ResetColors()
{
  m_FirstColorStyleSheet = "background-color:rgb(25,25,25)";
  m_SecondColorStyleSheet = "background-color:rgb(127,127,127)";
  m_FirstColor = "#191919";
  m_SecondColor = "#7F7F7F";
  m_ColorButton1->setStyleSheet(m_FirstColorStyleSheet);
  m_ColorButton2->setStyleSheet(m_SecondColorStyleSheet);
}

void QmitkStdMultiWidgetEditorPreferencePage::ChangeRenderingMode(int i)
{
  if( i == 0 )
  {
    m_CurrentRenderingMode = "Standard";
  }
  else if( i == 1 )
  {
   m_CurrentRenderingMode = "Multisampling";
  }
  else if( i == 2 )
  {
    m_CurrentRenderingMode = "DepthPeeling";
  }
}

void QmitkStdMultiWidgetEditorPreferencePage::UseGradientBackgroundSelected()
{
}

void QmitkStdMultiWidgetEditorPreferencePage::ColorActionChanged()
{
}