set(Plugin-Name "MITK StdMultiWidget Editor")
set(Plugin-Version "1.0.0")
set(Plugin-Vendor "DKFZ, Medical and Biological Informatics")
set(Plugin-ContactAddress "http://www.mitk.org")
set(Require-Plugin 
 org.mitk.gui.qt.common
 org.mitk.core.ext # Registers file reader factories
 org.mitk.gui.qt.application # Initializes GlobalInteraction and registers MITK Core factories
 )

