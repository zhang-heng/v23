project(org_vtt_myplugin)

MACRO_CREATE_MITK_CTK_PLUGIN(
  EXPORT_DIRECTIVE MYPLUGIN_EXPORT
  EXPORTED_INCLUDE_SUFFIXES src
  MODULE_DEPENDENCIES MitkQtWidgetsExt
)
