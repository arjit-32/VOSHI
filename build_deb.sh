#!/bin/bash

set -e

echo "[*] Cleaning..."
make clean

echo "[*] Compiling voshi..."
make

echo "[*] Preparing package structure..."
mkdir -p package/usr/local/bin
cp voshi package/usr/local/bin/voshi

echo "[*] Setting permissions..."
chmod 755 package/usr/local/bin/voshi
chmod 755 package/DEBIAN

echo "[*] Building .deb package..."
dpkg-deb --build package voshi_1.0.0_amd64.deb

echo "✅ Done! Install with: sudo dpkg -i voshi_1.0.0_amd64.deb"
