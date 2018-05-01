
Debian
====================
This directory contains files used to package moondexd/moondex-qt
for Debian-based Linux systems. If you compile moondexd/moondex-qt yourself, there are some useful files here.

## moondex: URI support ##


moondex-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install moondex-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your moondex-qt binary to `/usr/bin`
and the `../../share/pixmaps/moondex128.png` to `/usr/share/pixmaps`

moondex-qt.protocol (KDE)

