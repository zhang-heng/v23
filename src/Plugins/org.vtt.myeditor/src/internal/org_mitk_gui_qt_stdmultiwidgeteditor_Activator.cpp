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

#include "org_mitk_gui_qt_stdmultiwidgeteditor_Activator.h"

#include "../VttWidgetEditor.h"
#include "QmitkStdMultiWidgetEditorPreferencePage.h"


void
org_mitk_gui_qt_stdmultiwidgeteditor_Activator::start(ctkPluginContext* context)
{
  Q_UNUSED(context)

  BERRY_REGISTER_EXTENSION_CLASS(VttWidgetEditor, context)
  BERRY_REGISTER_EXTENSION_CLASS(QmitkStdMultiWidgetEditorPreferencePage, context)
}

void
org_mitk_gui_qt_stdmultiwidgeteditor_Activator::stop(ctkPluginContext* context)
{
  Q_UNUSED(context)
}

Q_EXPORT_PLUGIN2(org_mitk_gui_qt_stdmultiwidgeteditor, org_mitk_gui_qt_stdmultiwidgeteditor_Activator)
