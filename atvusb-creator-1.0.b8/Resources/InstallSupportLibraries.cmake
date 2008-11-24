# ------------------------------------------------------------------------------ 
# This CMake code installs the needed support libraries on NON OSX platforms
# ------------------------------------------------------------------------------ 

INCLUDE (InstallRequiredSystemLibraries)

# ---------- Find/Install the needed Qt4 libraries. 
SET (QTLIBLIST QtCore QtGui)
IF(NOT Q_WS_MAC)
  FOREACH(qtlib ${QTLIBLIST})
    IF (WIN32)
      GET_FILENAME_COMPONENT(QT_DLL_PATH_tmp ${QT_QMAKE_EXECUTABLE} PATH)
      INSTALL(FILES ${QT_DLL_PATH_tmp}/${qtlib}d4.dll 
          DESTINATION bin 
          CONFIGURATIONS Debug 
          COMPONENT Runtime)
      INSTALL(FILES ${QT_DLL_PATH_tmp}/${qtlib}4.dll 
          DESTINATION bin 
          CONFIGURATIONS Release 
          COMPONENT Runtime)
    ENDIF (WIN32)
  ENDFOREACH(qtlib)
ENDIF(NOT Q_WS_MAC)
