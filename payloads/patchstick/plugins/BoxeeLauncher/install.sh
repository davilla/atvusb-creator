#!/bin/bash

# check that staging directory exists
if [ -d /staging ]; then
  echo "       * installing Boxee Launcher"

  # clean staging directory
  rm -rf /staging/*

  # unpack the plugin
  tar -xzf /payloads/patchstick/plugins/BoxeeLauncher/BoxeeLauncher.frappliance.tar.gz -C /staging/

  # move the plugin into location
  if [ -d /OSBoot/System/Library/CoreServices/Finder.app/Contents/Plugins/BoxeeLauncher.frappliance ]; then
    rm -rf /OSBoot/System/Library/CoreServices/Finder.app/Contents/Plugins/BoxeeLauncher.frappliance
  fi
  rsync -r /staging/* /OSBoot/System/Library/CoreServices/Finder.app/Contents/Plugins/

  # always clean staging directory when done
  rm -rf /staging/*
fi