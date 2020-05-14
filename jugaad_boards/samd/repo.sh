#!/bin/bash
##################################################################################
#
# Juaad-Board's Repository Cloning Script
#
###############################################
# Copyright (C) 2006-2020 Abhijit Bose <https://boseji.com>. All right reserved.
#
# This program is free software; you can redistribute it and/or modify it under 
# the terms of the GNU General Public License as published by the 
# Free Software Foundation; version 2.
#
# This program is distributed in the hope that it will be useful, 
# but WITHOUT ANY WARRANTY; without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License 
# along with this program; if not, write to the Free Software Foundation, Inc., 
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA. 
#
# SPDX-License-Identifier: GPL-2.0-only
# https://spdx.org/licenses/GPL-2.0-only.html
#
##################################################################################
echo
echo "  Juaad-Board's Repository Cloning Script"
echo "-------------------------------------------"
echo
# Variables
USER="arduino"
REPO="ArduinoCore-samd"
BUILD_DIR="build"
REPO_DIR="samd"
# Find the Latest Tag
TAG=`curl -s https://api.github.com/repos/$USER/$REPO/releases/latest | grep -oP '"tag_name": "\K(.*)(?=")'`

echo
echo "1.  Clonning into $REPO Latest Tag: $TAG ..."
echo

# Create the build Directory
if [[ -d "${BUILD_DIR}" ]] ; then
    rm -rf $BUILD_DIR
fi
mkdir $BUILD_DIR
cd $BUILD_DIR

# Perfrom the Actual Cloning
git clone -b $TAG --depth 1 https://github.com/$USER/$REPO.git $REPO_DIR

# Restore
cd ..