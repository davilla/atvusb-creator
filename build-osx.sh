#!/bin/bash

#
#pyuic4 data/atvusb.ui -o liveusb/dialog.py

#
pyrcc4 data/resources.qrc -o liveusb/resources_rc.py

#
#python setup_osx.py py2app --includes sip --no-strip
python setup_osx.py py2app --includes sip

#
#mv dist/atvusb-creator.app dist/tmp.app
#ditto --rsrc --arch i386 dist/tmp.app dist/atvusb-creator.app
#rm -rf dist/tmp.app

# to get the icon to show
touch dist/atvusb-creator.app