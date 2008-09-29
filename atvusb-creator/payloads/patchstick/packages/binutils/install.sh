#!/bin/bash

# check that staging directory exists
if [ -d /staging ]; then
  echo "       * installing binutils"

  # clean staging directory
  rm -rf /staging/*

  # unpack the package
  tar -xzf /payloads/patchstick/packages/binutils/binutils.tar.gz -C /staging/

  # install package
  chown 0:0 /staging/binutils/*
  chmod 755 /staging/binutils/*
  chmod +s  /staging/binutils/top
  rsync /staging/binutils/* /OSBoot/usr/bin/

  # always clean staging directory when done
  rm -rf /staging/*
fi