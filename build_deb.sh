#!/bin/bash

set -e

echo "[*] Compiling voshi..."
make

echo "[*] Copying binary to package structure..."
mkdir -p package/usr/local/bin
cp voshi package/usr/local/bin/voshi

echo "[*] Building .deb package..."
dpkg-deb --build package voshi_1.0.0_amd64.deb

echo "✅ Done! Install with: sudo dpkg -i voshi_1.0.0_amd64.deb"
