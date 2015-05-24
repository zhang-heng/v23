set(SRC_CPP_FILES
)

set(INTERNAL_CPP_FILES
  DigitallyReconstructedRadiograph.cpp
  org_vtt_myplugin_Activator.cpp
  VttView.cpp 
  CtManage.cpp
  CNavEditor.cpp
  FocusPoint.cpp
  VNavigation.cpp
  XrayManage.cpp
)

set(UI_FILES
  src/internal/VttViewControls.ui
)

set(MOC_H_FILES
  src/internal/DigitallyReconstructedRadiograph.h
  src/internal/org_vtt_myplugin_Activator.h
  src/internal/VttView.h 
  src/internal/CtManage.h 
  src/internal/CNavEditor.h
  src/internal/FocusPoint.h
  src/internal/VNavigation.h
  src/internal/XrayManage.h
)

# list of resource files which can be used by the plug-in
# system without loading the plug-ins shared library,
# for example the icon used in the menu and tabs for the
# plug-in views in the workbench
set(CACHED_RESOURCE_FILES
  plugin.xml
  resources/logo.png
)

# list of Qt .qrc files which contain additional resources
# specific to this plugin
set(QRC_FILES
  resources/myplugin.qrc
)

set(CPP_FILES )

foreach(file ${SRC_CPP_FILES})
  set(CPP_FILES ${CPP_FILES} src/${file})
endforeach(file ${SRC_CPP_FILES})

foreach(file ${INTERNAL_CPP_FILES})
  set(CPP_FILES ${CPP_FILES} src/internal/${file})
endforeach(file ${INTERNAL_CPP_FILES})
