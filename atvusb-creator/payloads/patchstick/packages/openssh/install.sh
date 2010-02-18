#!/bin/bash

PACKAGE="openssh" 

# check that staging directory exists
if [ -d "/staging" ]; then  
  echo "       * installing ${PACKAGE}"

  # clean staging directory
  rm -rf /staging/*

  # unpack the package
  tar xjf /payloads/patchstick/packages/openssh/OpenSSH-56.root.tar.bz2 -C /staging/

  # begin install routines
  chown 0:0 /staging/private/etc/{moduli,ssh_config,sshd_config}
  cp /staging/private/etc/{moduli,ssh_config,sshd_config} /OSBoot/private/etc/
  rsync -ar /staging/System/* /OSBoot/System/
  rsync -ar /staging/usr/* /OSBoot/usr/

  # install the replacement ssh.plist that enables it
  cp /payloads/patchstick/packages/openssh/ssh.plist /OSBoot/System/Library/LaunchDaemons
  chown 0:0 /OSBoot/System/Library/LaunchDaemons/ssh.plist

  # turn off PAM
  sed -i"" -e 's/#UsePAM/UsePAM/g' "/OSBoot/etc/sshd_config"

  # always clean staging directory when done
  rm -rf /staging/*
fi
