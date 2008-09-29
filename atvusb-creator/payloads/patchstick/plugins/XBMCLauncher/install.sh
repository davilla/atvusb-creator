#!/bin/bash

# check that staging directory exists
if [ -d /staging ]; then
  echo "       * installing XBMCLauncher"

  # clean staging directory
  rm -rf /staging/*

  # unpack the plugin
  tar -xzf /payloads/plugins/xbmc/XBMCLauncher.frappliance.tar.gz -C /staging/

  # move the plugin into location
  rsync -r /staging/* /System/Library/CoreServices/Finder.app/Contents/Plugins/

  # always clean staging directory when done
  rm -rf /staging/*
fi