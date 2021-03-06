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

#include "VttWidgetEditor.h"

#include <berryUIException.h>
#include <berryIWorkbenchPage.h>
#include <berryIPreferencesService.h>
#include <berryIPartListener.h>

#include <QWidget>

#include <mitkColorProperty.h>
#include <mitkGlobalInteraction.h>
#include <mitkNodePredicateNot.h>
#include <mitkNodePredicateProperty.h>

#include <mitkDataStorageEditorInput.h>
#include <mitkIDataStorageService.h>

#include <QmitkMouseModeSwitcher.h>
#include <QmitkStdMultiWidget.h>

#include <mbilogo.h>

class VttWidgetEditorPrivate
{
public:

  VttWidgetEditorPrivate();
  ~VttWidgetEditorPrivate();

  QmitkStdMultiWidget* m_StdMultiWidget;
  QmitkMouseModeSwitcher* m_MouseModeToolbar;
  std::string m_FirstBackgroundColor;
  std::string m_SecondBackgroundColor;
  bool m_MenuWidgetsEnabled;
  berry::IPartListener::Pointer m_PartListener;

  QHash<QString, QmitkRenderWindow*> m_RenderWindows;
};

struct VttWidgetPartListener : public berry::IPartListener
{
  berryObjectMacro(VttWidgetPartListener)

  VttWidgetPartListener(VttWidgetEditorPrivate* dd)
    : d(dd)
  {}

  Events::Types GetPartEventTypes() const
  {
    return Events::CLOSED | Events::HIDDEN | Events::VISIBLE;
  }

  void PartClosed (berry::IWorkbenchPartReference::Pointer partRef)
  {
    if (partRef->GetId() == VttWidgetEditor::EDITOR_ID)
    {
      VttWidgetEditor::Pointer stdMultiWidgetEditor = partRef->GetPart(false).Cast<VttWidgetEditor>();

      if (d->m_StdMultiWidget == stdMultiWidgetEditor->GetStdMultiWidget())
      {
        d->m_StdMultiWidget->RemovePlanesFromDataStorage();
        stdMultiWidgetEditor->RequestActivateMenuWidget(false);
      }
    }
  }

  void PartHidden (berry::IWorkbenchPartReference::Pointer partRef)
  {
    if (partRef->GetId() == VttWidgetEditor::EDITOR_ID)
    {
      VttWidgetEditor::Pointer stdMultiWidgetEditor = partRef->GetPart(false).Cast<VttWidgetEditor>();

      if (d->m_StdMultiWidget == stdMultiWidgetEditor->GetStdMultiWidget())
      {
        d->m_StdMultiWidget->RemovePlanesFromDataStorage();
        stdMultiWidgetEditor->RequestActivateMenuWidget(false);
      }
    }
  }

  void PartVisible (berry::IWorkbenchPartReference::Pointer partRef)
  {
    if (partRef->GetId() == VttWidgetEditor::EDITOR_ID)
    {
      VttWidgetEditor::Pointer stdMultiWidgetEditor = partRef->GetPart(false).Cast<VttWidgetEditor>();

      if (d->m_StdMultiWidget == stdMultiWidgetEditor->GetStdMultiWidget())
      {
        d->m_StdMultiWidget->AddPlanesToDataStorage();
        stdMultiWidgetEditor->RequestActivateMenuWidget(true);
      }
    }
  }

private:

  VttWidgetEditorPrivate* const d;
};

VttWidgetEditorPrivate::VttWidgetEditorPrivate()
  : m_StdMultiWidget(0), m_MouseModeToolbar(0)
  , m_MenuWidgetsEnabled(false)
  , m_PartListener(new VttWidgetPartListener(this))
{}

VttWidgetEditorPrivate::~VttWidgetEditorPrivate()
{
}

const std::string VttWidgetEditor::EDITOR_ID = "org.vtt.myeditor";

VttWidgetEditor::VttWidgetEditor()
  : d(new VttWidgetEditorPrivate)
{
	cout<<"creat VttWidgetEditor"<<endl;
}

VttWidgetEditor::~VttWidgetEditor()
{
  this->GetSite()->GetPage()->RemovePartListener(d->m_PartListener);
}

QmitkStdMultiWidget* VttWidgetEditor::GetStdMultiWidget()
{
  return d->m_StdMultiWidget;
}

QmitkRenderWindow *VttWidgetEditor::GetActiveQmitkRenderWindow() const
{
  if (d->m_StdMultiWidget) return d->m_StdMultiWidget->GetRenderWindow1();
  return 0;
}

QHash<QString, QmitkRenderWindow *> VttWidgetEditor::GetQmitkRenderWindows() const
{
  return d->m_RenderWindows;
}

QmitkRenderWindow *VttWidgetEditor::GetQmitkRenderWindow(const QString &id) const
{
  if (d->m_RenderWindows.contains(id))
    return d->m_RenderWindows[id];

  return 0;
}

mitk::Point3D VttWidgetEditor::GetSelectedPosition(const QString & /*id*/) const
{
  return d->m_StdMultiWidget->GetCrossPosition();
}

void VttWidgetEditor::SetSelectedPosition(const mitk::Point3D &pos, const QString &/*id*/)
{
  d->m_StdMultiWidget->MoveCrossToPosition(pos);
}

void VttWidgetEditor::EnableDecorations(bool enable, const QStringList &decorations)
{
  if (decorations.isEmpty() || decorations.contains(DECORATION_BORDER))
  {
    enable ? d->m_StdMultiWidget->EnableColoredRectangles()
           : d->m_StdMultiWidget->DisableColoredRectangles();
  }
  if (decorations.isEmpty() || decorations.contains(DECORATION_LOGO))
  {
    enable ? d->m_StdMultiWidget->EnableDepartmentLogo()
           : d->m_StdMultiWidget->DisableDepartmentLogo();
  }
  if (decorations.isEmpty() || decorations.contains(DECORATION_MENU))
  {
    d->m_StdMultiWidget->ActivateMenuWidget(enable);
  }
  if (decorations.isEmpty() || decorations.contains(DECORATION_BACKGROUND))
  {
    enable ? d->m_StdMultiWidget->EnableGradientBackground()
           : d->m_StdMultiWidget->DisableGradientBackground();
  }
}

bool VttWidgetEditor::IsDecorationEnabled(const QString &decoration) const
{
  if (decoration == DECORATION_BORDER)
  {
    return d->m_StdMultiWidget->IsColoredRectanglesEnabled();
  }
  else if (decoration == DECORATION_LOGO)
  {
    return d->m_StdMultiWidget->IsColoredRectanglesEnabled();
  }
  else if (decoration == DECORATION_MENU)
  {
    return d->m_StdMultiWidget->IsMenuWidgetEnabled();
  }
  else if (decoration == DECORATION_BACKGROUND)
  {
    return d->m_StdMultiWidget->GetGradientBackgroundFlag();
  }
  return false;
}

QStringList VttWidgetEditor::GetDecorations() const
{
  QStringList decorations;
  decorations << DECORATION_BORDER << DECORATION_LOGO << DECORATION_MENU << DECORATION_BACKGROUND;
  return decorations;
}

mitk::SlicesRotator* VttWidgetEditor::GetSlicesRotator() const
{
  return d->m_StdMultiWidget->GetSlicesRotator();
}

mitk::SlicesSwiveller* VttWidgetEditor::GetSlicesSwiveller() const
{
  return d->m_StdMultiWidget->GetSlicesSwiveller();
}

void VttWidgetEditor::EnableSlicingPlanes(bool enable)
{
  d->m_StdMultiWidget->SetWidgetPlanesVisibility(enable);
}

bool VttWidgetEditor::IsSlicingPlanesEnabled() const
{
  mitk::DataNode::Pointer node = this->d->m_StdMultiWidget->GetWidgetPlane1();
  if (node.IsNotNull())
  {
    bool visible = false;
    node->GetVisibility(visible, 0);
    return visible;
  }
  else
  {
    return false;
  }
}

void VttWidgetEditor::EnableLinkedNavigation(bool enable)
{
  enable ? d->m_StdMultiWidget->EnableNavigationControllerEventListening()
         : d->m_StdMultiWidget->DisableNavigationControllerEventListening();
}

bool VttWidgetEditor::IsLinkedNavigationEnabled() const
{
  return d->m_StdMultiWidget->IsCrosshairNavigationEnabled();
}

void VttWidgetEditor::CreateQtPartControl(QWidget* parent)
{
  if (d->m_StdMultiWidget == 0)
  {
    QHBoxLayout* layout = new QHBoxLayout(parent);
    layout->setContentsMargins(0,0,0,0);

    if (d->m_MouseModeToolbar == NULL)
    {
      d->m_MouseModeToolbar = new QmitkMouseModeSwitcher(parent); // delete by Qt via parent
      layout->addWidget(d->m_MouseModeToolbar);
    }

    berry::IPreferences::Pointer prefs = this->GetPreferences();

    mitk::BaseRenderer::RenderingMode::Type renderingMode = static_cast<mitk::BaseRenderer::RenderingMode::Type>(prefs->GetInt( "Rendering Mode" , 0 ));

    d->m_StdMultiWidget = new QmitkStdMultiWidget(parent,0,0,renderingMode);

    d->m_RenderWindows.insert("axial", d->m_StdMultiWidget->GetRenderWindow1());
    d->m_RenderWindows.insert("sagittal", d->m_StdMultiWidget->GetRenderWindow2());
    d->m_RenderWindows.insert("coronal", d->m_StdMultiWidget->GetRenderWindow3());
    d->m_RenderWindows.insert("3d", d->m_StdMultiWidget->GetRenderWindow4());

    d->m_MouseModeToolbar->setMouseModeSwitcher( d->m_StdMultiWidget->GetMouseModeSwitcher() );
    connect( d->m_MouseModeToolbar, SIGNAL( MouseModeSelected(mitk::MouseModeSwitcher::MouseMode) ),
      d->m_StdMultiWidget, SLOT( MouseModeSelected(mitk::MouseModeSwitcher::MouseMode) ) );

    layout->addWidget(d->m_StdMultiWidget);

    mitk::DataStorage::Pointer ds = this->GetDataStorage();

    // Tell the multiWidget which (part of) the tree to render
    d->m_StdMultiWidget->SetDataStorage(ds);

    // Initialize views as axial, sagittal, coronar to all data objects in DataStorage
    // (from top-left to bottom)
    mitk::TimeGeometry::Pointer geo = ds->ComputeBoundingGeometry3D(ds->GetAll());
    mitk::RenderingManager::GetInstance()->InitializeViews(geo);

    // Initialize bottom-right view as 3D view
    d->m_StdMultiWidget->GetRenderWindow4()->GetRenderer()->SetMapperID(
      mitk::BaseRenderer::Standard3D );

    // Enable standard handler for levelwindow-slider
    d->m_StdMultiWidget->EnableStandardLevelWindow();

    // Add the displayed views to the tree to see their positions
    // in 2D and 3D
    d->m_StdMultiWidget->AddDisplayPlaneSubTree();

    d->m_StdMultiWidget->EnableNavigationControllerEventListening();

    // Store the initial visibility status of the menu widget.
    d->m_MenuWidgetsEnabled = d->m_StdMultiWidget->IsMenuWidgetEnabled();

    this->GetSite()->GetPage()->AddPartListener(d->m_PartListener);

    this->OnPreferencesChanged(dynamic_cast<berry::IBerryPreferences*>(prefs.GetPointer()));

    this->RequestUpdate();
  }
}

void VttWidgetEditor::OnPreferencesChanged(const berry::IBerryPreferences* prefs)
{
  // Enable change of logo. If no DepartmentLogo was set explicitly, MBILogo is used.
  // Set new department logo by prefs->Set("DepartmentLogo", "PathToImage");

  // If no logo was set for this plug-in specifically, walk the parent preference nodes
  // and lookup a logo value there.

  const berry::IPreferences* currentNode = prefs;

  while(currentNode)
  {
    std::vector<std::string> keys = currentNode->Keys();

    bool logoFound = false;
    for( std::size_t i = 0; i < keys.size(); ++i )
    {
      if( keys[i] == "DepartmentLogo")
      {
        std::string departmentLogoLocation = currentNode->Get("DepartmentLogo", "");

        if (departmentLogoLocation.empty())
        {
          d->m_StdMultiWidget->DisableDepartmentLogo();
        }
        else
        {
          // we need to disable the logo first, otherwise setting a new logo will have
          // no effect due to how mitkManufacturerLogo works...
          d->m_StdMultiWidget->DisableDepartmentLogo();
          d->m_StdMultiWidget->SetDepartmentLogoPath(departmentLogoLocation.c_str());
          d->m_StdMultiWidget->EnableDepartmentLogo();
        }
        logoFound = true;
        break;
      }
    }

    if (logoFound) break;
    currentNode = currentNode->Parent().GetPointer();
  }

  // preferences for gradient background
  float color = 255.0;
  QString firstColorName = QString::fromStdString (prefs->GetByteArray("first background color", ""));
  QColor firstColor(firstColorName);
  mitk::Color upper;
  if (firstColorName=="") // default values
  {
    upper[0] = 0.1;
    upper[1] = 0.1;
    upper[2] = 0.1;
  }
  else
  {
    upper[0] = firstColor.red() / color;
    upper[1] = firstColor.green() / color;
    upper[2] = firstColor.blue() / color;
  }

  QString secondColorName = QString::fromStdString (prefs->GetByteArray("second background color", ""));
  QColor secondColor(secondColorName);
  mitk::Color lower;
  if (secondColorName=="") // default values
  {
    lower[0] = 0.5;
    lower[1] = 0.5;
    lower[2] = 0.5;
  }
  else
  {
    lower[0] = secondColor.red() / color;
    lower[1] = secondColor.green() / color;
    lower[2] = secondColor.blue() / color;
  }
  d->m_StdMultiWidget->SetGradientBackgroundColors(upper, lower);
  d->m_StdMultiWidget->EnableGradientBackground();

  // Set preferences respecting zooming and padding
  bool constrainedZooming = prefs->GetBool("Use constrained zooming and padding", false);

  mitk::RenderingManager::GetInstance()->SetConstrainedPaddingZooming(constrainedZooming);

  mitk::RenderingManager::GetInstance()->InitializeViewsByBoundingObjects(this->GetDataStorage());

  mitk::RenderingManager::GetInstance()->RequestUpdateAll();

  // level window setting
  bool showLevelWindowWidget = prefs->GetBool("Show level/window widget", true);
  if (showLevelWindowWidget)
  {
    d->m_StdMultiWidget->EnableStandardLevelWindow();
  }
  else
  {
    d->m_StdMultiWidget->DisableStandardLevelWindow();
  }

  // mouse modes toolbar
  bool newMode = prefs->GetBool("PACS like mouse interaction", false);
  d->m_MouseModeToolbar->setVisible( newMode );
  d->m_StdMultiWidget->GetMouseModeSwitcher()->SetInteractionScheme( newMode ? mitk::MouseModeSwitcher::PACS : mitk::MouseModeSwitcher::MITK );
}

void VttWidgetEditor::SetFocus()
{
  if (d->m_StdMultiWidget != 0)
    d->m_StdMultiWidget->setFocus();
}

void VttWidgetEditor::RequestActivateMenuWidget(bool on)
{
  if (d->m_StdMultiWidget)
  {
    if (on)
    {
      d->m_StdMultiWidget->ActivateMenuWidget(d->m_MenuWidgetsEnabled);
    }
    else
    {
      d->m_MenuWidgetsEnabled = d->m_StdMultiWidget->IsMenuWidgetEnabled();
      d->m_StdMultiWidget->ActivateMenuWidget(false);
    }
  }
}
