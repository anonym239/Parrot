#!/bin/bash
# Parrot OS - ISO bauen (Debian-Basis, live-build)
# Wird von GitHub Actions UND lokal (Debian 12/13) benutzt.
set -euo pipefail
cd "$(dirname "$0")"

if [ "$(id -u)" -ne 0 ]; then SUDO=sudo; else SUDO=; fi

$SUDO lb clean || true

$SUDO lb config noauto \
  --mode debian \
  --distribution trixie \
  --architectures amd64 \
  --linux-flavours amd64 \
  --archive-areas "main contrib non-free non-free-firmware" \
  --binary-images iso-hybrid \
  --bootloaders "syslinux,grub-efi" \
  --debian-installer none \
  --apt-recommends false \
  --memtest none \
  --iso-application "Parrot OS" \
  --iso-volume "PARROTOS" \
  --iso-publisher "Parrot OS" \
  --bootappend-live "boot=live components quiet splash username=parrot hostname=parrotos locales=de_DE.UTF-8 keyboard-layouts=de timezone=Europe/Berlin"

# Skripte ausführbar machen (ZIP-Dateien verlieren manchmal das x-Bit)
chmod +x config/hooks/live/*.hook.chroot config/includes.chroot/usr/local/bin/* || true

$SUDO lb build

ISO="$(ls -1 *.iso | head -n1)"
mv "$ISO" parrotos.iso
echo "FERTIG: $(pwd)/parrotos.iso"
