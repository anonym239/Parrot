# Parrot OS

Dein eigenes Betriebssystem mit eigenem Look, eigener Boot-Animation, eigenem Dock,
eigener Willkommens-App und Installer. Unter der Haube arbeitet Linux (Debian 13) –
alles Sichtbare ist Parrot OS.

Das ISO wird **in der Cloud gebaut (GitHub Actions)**. Du musst dafür weder Linux
installieren noch irgendetwas auf deinem PC einrichten.

---------------------------------------------------------------------------
## 1. ISO bauen lassen (einmalig, ca. 30–60 Minuten Wartezeit)

1. Auf https://github.com ein Konto anlegen bzw. einloggen.
2. Oben rechts **+ → New repository**. Name: `parrotos`, **Public** wählen, **Create repository**.
3. Dieses ZIP auf deinem PC entpacken.
4. Im neuen Repository auf **uploading an existing file** klicken und den **gesamten Inhalt**
   des entpackten Ordners per Drag & Drop hineinziehen (auch die versteckten Ordner
   `.github` und `config` – am besten den Ordnerinhalt mit Strg+A markieren).
   Unten **Commit changes** klicken.
   Tipp: Falls `.github` nicht mitgezogen wird: Repository → **Add file → Create new file**,
   Dateiname `.github/workflows/build-iso.yml` eintippen und den Inhalt aus der ZIP einfügen.
5. Oben auf **Actions** klicken → links **Parrot OS ISO bauen** → rechts **Run workflow**.
   (Falls GitHub fragt, ob Workflows aktiviert werden sollen: bestätigen.)
6. Warten, bis der Eintrag einen grünen Haken hat.
7. Auf den fertigen Eintrag klicken → ganz unten bei **Artifacts** auf **ParrotOS-ISO**
   klicken. Du bekommst eine ZIP-Datei, in der **parrotos.iso** steckt. Entpacken.

Wenn der Lauf rot wird: Auf den roten Eintrag klicken, den Fehlertext am Ende kopieren
und mir schicken – dann behebe ich es.

---------------------------------------------------------------------------
## 2. In Oracle VirtualBox ausprobieren

1. VirtualBox öffnen → **Neu** (New).
2. Name: `Parrot OS` · ISO-Image: `parrotos.iso` auswählen.
3. **Haken bei „Skip Unattended Installation" / „Unbeaufsichtigte Installation
   überspringen" setzen!** Typ: Linux · Version: Debian (64-bit).
4. Hardware: Arbeitsspeicher **4096 MB**, Prozessoren **2**.
5. Festplatte: **Neue virtuelle Festplatte erstellen**, **30 GB**.
6. Fertigstellen. Dann die VM markieren → **Ändern → Anzeige**:
   Videospeicher **128 MB**, Grafikcontroller **VMSVGA**.
7. **Starten.** Im Boot-Menü Enter drücken. Nach der Boot-Animation erscheint der Desktop
   samt Willkommens-Fenster.
8. Zum **Fest-Installieren in die VM**: auf das Icon **Parrot OS installieren**
   (Desktop oder Willkommens-Fenster) klicken, den Assistenten durchklicken
   („Festplatte löschen" ist in der VM sicher – es betrifft nur die virtuelle Platte).
9. Danach VM ausschalten → **Ändern → Massenspeicher** → ISO entfernen → neu starten.

Bildschirmgröße: Mit den Gast-Erweiterungen (im Image enthalten, falls verfügbar) passt sich
das Fenster automatisch an. Sonst: Anzeige → Auflösung im Parrot-Menü einstellen.

---------------------------------------------------------------------------
## 3. Auf dem echten Laptop (leere SSD)

1. Einen USB-Stick (mindestens 4 GB, wird gelöscht!) bereithalten.
2. Auf einem anderen PC **Rufus** (Windows) oder **Balena Etcher** laden, `parrotos.iso`
   und den Stick auswählen, **Start**. (Rufus: bei Nachfrage „Im ISO-Image-Modus schreiben".)
3. Stick in den Laptop stecken, einschalten und sofort die Boot-Menü-Taste drücken
   (meist **F12**, **Esc**, **F9** oder **F2** – je nach Hersteller).
4. USB-Stick wählen. Falls der Stick nicht startet: im BIOS **Secure Boot** ausschalten.
5. Parrot OS startet im Live-Modus (testen, nichts wird verändert).
6. **Parrot OS installieren** klicken → Assistent → „Festplatte löschen" → Benutzer anlegen
   → Installieren. Stick entfernen, neu starten. Fertig.

---------------------------------------------------------------------------
## 4. Benutzen wie ein richtiges System

- **Browser:** Firefox ESR, Startseite Google, mit uBlock Origin. YouTube, Logins, Downloads wie gewohnt.
- **Netzwerk:** WLAN-/LAN-Symbol oben rechts im Panel (NetworkManager): WLAN, VPN, feste IP.
- **Dateien:** Thunar mit echten Ordnern, USB-Sticks, Festplatten. Mit der Maus einen
  Rahmen aufziehen markiert mehrere Dateien (auch auf dem Desktop).
- **Apps installieren:**
  - **Software** (Dock): grafischer Store für Debian-Programme und Flathub.
  - Doppelklick auf eine heruntergeladene `.deb`-Datei installiert sie über „Software".
  - Terminal: `sudo apt install <paket>` oder `flatpak install flathub <app>`.
- **Von GitHub installieren:** Menü → „Von GitHub installieren" (oder Willkommens-Fenster)
  und Link einfügen. Es wird die neueste `.deb`/`.AppImage` installiert; gibt es keine,
  wird das Projekt nach `~/GitHub` geklont und nach Rückfrage gebaut.
  Im Terminal: `parrot-github https://github.com/BESITZER/PROJEKT`. `git`, `npm`, `pip`,
  `cmake`, `make` sind vorinstalliert.
- **Eigene Hintergrundbilder:** Rechtsklick auf den Desktop → *Desktop-Einstellungen* →
  eigenes Bild wählen. Oder Bild im Bildbetrachter öffnen → „Als Hintergrund setzen".
- **System aktualisieren:** `sudo apt update && sudo apt full-upgrade`

---------------------------------------------------------------------------
## 5. Anpassen – hier steckt dein eigener Style

| Was                    | Datei                                                              |
|------------------------|--------------------------------------------------------------------|
| Hintergrundbild        | `config/includes.chroot/usr/share/backgrounds/parrotos/wallpaper.png` |
| Boot-Animation         | `config/includes.chroot/usr/share/plymouth/themes/parrotos/`      |
| Willkommens-App        | `config/includes.chroot/usr/local/bin/parrot-welcome` (Python/GTK) |
| Dock-Symbole           | `config/includes.chroot/etc/skel/.config/plank/dock1/launchers/`  |
| Farben/Theme           | `config/includes.chroot/etc/skel/.config/xfce4/…/xsettings.xml`   |
| Terminal-Farben        | `config/includes.chroot/etc/skel/.config/xfce4/terminal/terminalrc` |
| Programme im System    | `config/package-lists/parrotos.list.chroot`                        |
| Name/Boot-Optionen     | `build.sh`                                                         |

Datei ändern → ins GitHub-Repository hochladen (ersetzen) → **Run workflow** → neues ISO.

---------------------------------------------------------------------------
## 6. Login-Daten im Live-Modus
Benutzer `parrot`, Passwort `live` (nur im Live-Modus; nach der Installation gilt dein
eigener Benutzer).

## 7. Lokal bauen (optional, nur auf Debian 13 / Debian-VM)
`sudo apt install live-build` → `./build.sh` → `parrotos.iso` entsteht im Ordner.

## 8. Kernel-Labor (Bonus)
Im Ordner `kernel-labor/` liegt ein winziger, komplett selbst geschriebener Kernel
(ohne Linux) mit Textshell. Zum Lernen, wie ein OS von Grund auf entsteht.
Bauen unter Linux: `sudo apt install build-essential gcc-multilib grub-pc-bin xorriso mtools`
dann `make` und `make run`.

## 9. Hinweis zum Namen
„Parrot OS/Parrot Security" ist ein bestehendes Projekt. Für den privaten Gebrauch
kein Problem; vor einer öffentlichen Veröffentlichung besser umbenennen.
