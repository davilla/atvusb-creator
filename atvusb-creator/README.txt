atvusb-creator
===============
This tool installs a AppleTV patchstick on to a USB stick.

Forked
======
This project was forked https://fedorahosted.org/liveusb-creator

Using
=====


Developing
==========

  In OSX
  ----------
  o Get the latest code

  o Install Python2.5, PyQt4, and py2app

  o Compiling an app:

	# developing
        python setup_osx.py py2app --alias 

	# distribution
        python setup_osx.py py2app

  o If you change the QtDesigner ui file, you can compile it by doing:

        pyuic4 data/atvusb.ui -o liveusb/dialog.py

  o If you add more PyQt resources (pixmaps, icons, etc), you can rebuild
    the resources module by running:

        pyrcc4 data/resources.qrc -o liveusb/resources_rc.py

 In Linux
  ----------
  o Get the latest code

  o Install Python2.5, PyQt4

  o Compiling an app:

  o If you change the QtDesigner ui file, you can compile it by doing:

        pyuic4 data/atvusb.ui -o liveusb/dialog.py

  o If you add more PyQt resources (pixmaps, icons, etc), you can rebuild
    the resources module by running:

        pyrcc4 data/resources.qrc -o liveusb/resources_rc.py

  In Windows
  ----------
  o Get the latest code

  o Install Python2.5, PyQt4, and py2exe

  o Compiling an exe:

        python -OO setup_win.py py2exe

  o If you change the QtDesigner ui file, you can compile it by doing:

        pyuic4 data\atvusb.ui -o liveusb\dialog.py

  o If you add more PyQt resources (pixmaps, icons, etc), you can rebuild
    the resources module by running:

        pyrcc4 data\resources.qrc -o liveusb\resources_rc.py

================================================================================

This tool is distributed with the following open source software

   7-Zip
   http://www.7-zip.org
   Copyright (C) 1999-2007 Igor Pavlov.
   7-Zip is free software distributed under the GNU LGPL 
   (except for unRar code and AES code).

   SYSLINUX
   http://syslinux.zytor.com/
   Copyright 1994-2008 H. Peter Anvin - All Rights Reserved
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, Inc., 53 Temple Place Ste 330,
   Boston MA 02111-1307, USA; either version 2 of the License, or
   (at your option) any later version; incorporated herein by reference.

   dd for Windows
   http://www.chrysocome.net/dd
   dd is owned and copyright by Chrysocome and John Newbigin.
   It is made available under the terms of the GPLv2
