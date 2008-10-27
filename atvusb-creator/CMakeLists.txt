cmake_minimum_required(VERSION 2.6)

PROJECT( atvusb-creator )

SET (PROJECT_RESOURCES_DIR ${PROJECT_SOURCE_DIR}/Resources)

#------ Setup the Executable output Directory ---------------------------------
SET (EXECUTABLE_OUTPUT_PATH
	${PROJECT_BINARY_DIR}/bin
	CACHE PATH
	"Single Directory for all Executables."
)

#--------------------------------------------------------------------------------
# This sets the windows build that will need the special winmain@16 call. Qt provides
#  this for us in the qtmain.lib file. Using this cmake code will ensure we have it
#  linked into our build. Not needed on Unix/OS X/Linux which is why we have the 
#  IF(WIN32) conditional.
IF (WIN32)
    SET (QT_USE_QTMAIN TRUE)
ENDIF (WIN32)

#setup qt4
find_package(Qt4 REQUIRED)
SET(QT_USE_QTNETWORK 1)

IF(NOT WIN32 AND NOT APPLE)
#we're using QDbus on linux
SET(QT_USE_QTDBUS 1)
ENDIF(NOT WIN32 AND NOT APPLE)

include(${QT_USE_FILE})

#--------------------------------------------------------------------------------
#add include directories
INCLUDE_DIRECTORIES (
  ${QT_INCLUDE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR} # Look in the cmake build directory
  src
)

#--------------------------------------------------------------------------------
#gather source
SET(atvusb-creator_SRCS
	src/main.cpp 
	src/aucdialog.h 
	src/aucdialog.cpp 
	src/atvusbcreatorbase.h 
	src/atvusbcreatorbase.cpp
	src/aucthread.h 
	src/aucthread.cpp 
	src/aucprogressthread.h 
	src/aucprogressthread.cpp 
	src/aucreleasedownloader.h
	src/aucreleasedownloader.cpp
	src/lists.h
	src/lists.cpp
	src/default_list.h
	)

#--------------------------------------------------------------------------------
#add platform specific sources
IF(WIN32)
ELSE(WIN32)
	IF(APPLE)
		SET(atvusb-creator_SRCS ${atvusb-creator_SRCS} src/osx/atvusbcreatorosx.h src/osx/atvusbcreatorosx.cpp)
	ELSE(APPLE)
    #linux
    SET(atvusb-creator_SRCS ${atvusb-creator_SRCS} src/linux/atvusbcreatorlinux.h src/linux/atvusbcreatorlinux.cpp)
	ENDIF(APPLE) 
ENDIF(WIN32)

#--------------------------------------------------------------------------------
# Sets a variable that signals CMake with a keyword appropriate for each platform
#  that will create the proper executable.
SET(GUI_TYPE)
IF(WIN32)
	 SET(GUI_TYPE WIN32)
ELSE(WIN32)
	IF(APPLE)
	 SET(CMAKE_OSX_ARCHITECTURES "ppc;i386" CACHE STRING "Build architectures for OSX" FORCE)
	 SET(GUI_TYPE MACOSX_BUNDLE)
	 SET(atvusb-creator_SRCS ${atvusb-creator_SRCS} ${CMAKE_CURRENT_SOURCE_DIR}/data/atvusb.icns)
	 SET(MACOSX_BUNDLE_ICON_FILE ${CMAKE_CURRENT_SOURCE_DIR}/data/atvusb.icns)
	 SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_SOURCE_DIR}/data/atvusb.icns PROPERTIES
	   MACOSX_PACKAGE_LOCATION Resources)	
	ELSE(APPLE)
		#linux
	ENDIF(APPLE)
ENDIF(WIN32)

#--------------------------------------------------------------------------------
#gather uis
SET(atvusb-creator_UIS data/atvusb.ui)
QT4_WRAP_UI(atvusb-creator_UIS_H ${atvusb-creator_UIS})

#--------------------------------------------------------------------------------
#moc the headers
SET(atvusb-creator_MOC_HDRS 
	src/aucdialog.h
	src/aucthread.h 
	src/aucprogressthread.h 
	src/aucreleasedownloader.h
	)	
QT4_WRAP_CPP(atvusb-creator_MOC_SRCS ${atvusb-creator_MOC_HDRS})

#--------------------------------------------------------------------------------
#add resources
QT4_ADD_RESOURCES(atvusb-creator_RES_SRCS data/resources.qrc)

#--------------------------------------------------------------------------------
#finally build executable
add_executable( atvusb-creator ${GUI_TYPE} ${atvusb-creator_SRCS} ${atvusb-creator_MOC_SRCS} ${atvusb-creator_UIS_H} ${atvusb-creator_RES_SRCS})

IF(APPLE)
	#add our own Info.plist
 	set_target_properties(atvusb-creator PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${PROJECT_SOURCE_DIR}/data/Info.plist")
ENDIF(APPLE)

#--------------------------------------------------------------------------------
#and tell which libraries to link
target_link_libraries(atvusb-creator ${QT_LIBRARIES})

#--------------------------------------------------------------------------------
# Install the Qt Libraries on NON Apple Platforms
#--------------------------------------------------------------------------------
IF (NOT APPLE)
    INCLUDE (${PROJECT_SOURCE_DIR}/Resources/InstallSupportLibraries.cmake)
ENDIF (NOT APPLE)

# --- If we are on OS X copy all the embedded libraries to the app bundle
IF (APPLE)
  # -------- Function to build OS X Stand Alone Bundles -----------------
  function(MakeOSXBundleApp target binary_dir)
	  SET (OSX_MAKE_STANDALONE_BUNDLE_CMAKE_SCRIPT "${binary_dir}/${target}_OSX_MakeStandAloneBundle.cmake")
	  SET (OSX_MAKE_STANDALONE_BUNDLE_BASH_SCRIPT "${binary_dir}/${target}_OSX_MakeStandAloneBundle.sh")
	
	  CONFIGURE_FILE("${PROJECT_RESOURCES_DIR}/OSX_Tools/CompleteBundle.cmake.in"
	      "${OSX_MAKE_STANDALONE_BUNDLE_CMAKE_SCRIPT}" @ONLY IMMEDIATE)
	  CONFIGURE_FILE("${PROJECT_RESOURCES_DIR}/OSX_Tools/CreateBundle.sh.in"
	      "${OSX_MAKE_STANDALONE_BUNDLE_BASH_SCRIPT}" @ONLY IMMEDIATE)
	 
	  install(SCRIPT "${OSX_MAKE_STANDALONE_BUNDLE_CMAKE_SCRIPT}")
  endfunction(MakeOSXBundleApp)

  MakeOSXBundleApp(atvusb-creator ${PROJECT_BINARY_DIR})
ENDIF (APPLE)

IF (WIN32)
  INSTALL(TARGETS atvusb-creator
      LIBRARY DESTINATION lib 
      ARCHIVE DESTINATION lib
      RUNTIME DESTINATION bin
      COMPONENT Runtime
  )   
ENDIF (WIN32)
