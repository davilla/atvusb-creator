#!/bin/bash

# check that staging directory exists
if [ -d /Users/Frontrow/atv-install/xbmc]; then
  PW="frontrow"

  # install xbmc app
  echo $PW | sudo -S hdiutil attach /Users/Frontrow/atv-install/xbmc/xbmc.dmg
  echo $PW | sudo -S install -pkg /Volumes/XBMC/"XBMC Media Center.mpkg" -target /
  echo $PW | sudo -S hdiutil detach /Volumes/XBMC


  # clean up
  echo $PW | sudo -S rm -rf /Users/Frontrow/atv-install/xbmc
fi