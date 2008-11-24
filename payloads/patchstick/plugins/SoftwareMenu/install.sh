#!/bin/bash

PACKAGE="SoftwareMenu"

# check that staging directory exists
if [ -d "/staging" ]; then
  echo "       * installing ${PACKAGE}"

  # clean staging directory
  rm -rf /staging/*

  # unpack the plugin
  tar -xzf /payloads/patchstick/plugins/${PACKAGE}/${PACKAGE}.frappliance.tar.gz -C /staging/

  # remove existing versions of the plugin
  if [ -d /OSBoot/System/Library/CoreServices/Finder.app/Contents/Plugins/${PACKAGE}.frappliance ]; then
    rm -rf /OSBoot/System/Library/CoreServices/Finder.app/Contents/Plugins/${PACKAGE}.frappliance
  fi
  
  # copy package into location.
  rsync -r /staging/* /OSBoot/System/Library/CoreServices/Finder.app/Contents/Plugins/

  # always clean staging directory when done
  rm -rf /staging/*
fi
