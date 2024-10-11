# QtApp

This project is a small game I made using the Qt6 framework as well as some external C++ libraries (see [libs/](./libs/)).

Load a MIDI file and play the notes at the right timing to get points. If you play the wrong notes or miss correct ones, you lose points.

# How to Build
- Clone the repo
- `git submodule update --init --recursive`
- Make sure Qt 6.7, QtQuick3D and QtQuick3DPhysics are installed on your system
- Run CMake

# Details
- The app reads the first channel of the MIDI file. 
- MIDI files to load should be placed in the [midi/](./midi/) folder, and can loaded through the UI.

# Demo

https://github.com/user-attachments/assets/ed791f50-30e6-4774-9df6-934d734bae07

