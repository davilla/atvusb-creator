#!/bin/bash

$PACKAGE="dropbear" 

# check that staging directory exists
if [ -d "/staging" ]; then
  echo "       * installing ${PACKAGE}"

  # clean staging directory
  rm -rf /staging/*

  # unpack the package
  tar -xzf /payloads/patchstick/packages/${PACKAGE}/${PACKAGE}.tar.gz -C /staging/

  # begin non-standard install routines
  cp /staging/dropbear/System/Library/LaunchDaemons/com.atvMod.dropbear.plist /OSBoot/System/Library/LaunchDaemons/
  chown 0:0 /OSBoot/System/Library/LaunchDaemons/com.atvMod.dropbear.plist
  chmod 755 /OSBoot/System/Library/LaunchDaemons/com.atvMod.dropbear.plist

  cp /staging/dropbear/usr/bin/{dbclient,dropbear,dropbearconvert,dropbearkey,scp} /OSBoot/usr/bin/
  chown 0:0 /OSBoot/usr/bin/{dbclient,dropbear,dropbearconvert,dropbearkey,scp}
  chmod 755 /OSBoot/usr/bin/{dbclient,dropbear,dropbearconvert,dropbearkey,scp}

  cp /staging/dropbear/usr/lib/libarmfp.dylib /OSBoot/usr/lib/
  chown 0:0 /OSBoot/usr/lib/libarmfp.dylib
  chmod 755 /OSBoot/usr/lib/libarmfp.dylib

  cp /staging/dropbear/Users/frontrow/{.bash_login,.dropbear_banner} /OSBoot/Users/frontrow/
  chown 501:501 /OSBoot/Users/frontrow/{.bash_login,.dropbear_banner}
  chmod 755 /OSBoot/Users/frontrow/{.bash_login,.dropbear_banner}

  cp /staging/dropbear/usr/libexec/{dropbear-keygen-wrapper,sftp-server} /OSBoot/usr/libexec/
  chown 0:0 /OSBoot/usr/libexec/{dropbear-keygen-wrapper,sftp-server}
  chmod 755 /OSBoot/usr/libexec/{dropbear-keygen-wrapper,sftp-server}

  # always clean staging directory when done
  rm -rf /staging/*
fi
