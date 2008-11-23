#!/bin/bash

PACKAGE="binutils"

# check that staging directory exists
if [ -d "/staging" ]; then
  echo "       * installing ${PACKAGE}"

  # clean staging directory
  rm -rf /staging/*

  # unpack the package
  tar -xzf /payloads/patchstick/packages/${PACKAGE}/${PACKAGE}.tar.gz -C /staging/

  # install package
  chown 0:0 /staging/${PACKAGE}/*
  chmod 755 /staging/${PACKAGE}/*
  chmod +s  /staging/${PACKAGE}/top
  rsync /staging/${PACKAGE}/* /OSBoot/usr/bin/

  # always clean staging directory when done
  rm -rf /staging/*
fi
