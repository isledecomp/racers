FROM docker.io/library/debian:stable-slim

# Gather Unix dependencies
RUN dpkg --add-architecture i386
RUN apt-get update -y
RUN apt-get install git unzip wget wine wine32 wine64 -y

# Set up the wineprefix
RUN wine wineboot

# Gather and set up build dependencies (MSVC 6.00 and CMake for Windows)
RUN git clone https://github.com/isledecomp/MSVC600-8168 ~/.wine/drive_c/msvc
RUN wget https://github.com/Kitware/CMake/releases/download/v3.26.6/cmake-3.26.6-windows-i386.zip
RUN unzip cmake-3.26.6-windows-i386.zip -d ~/.wine/drive_c
RUN mv ~/.wine/drive_c/cmake-3.26.6-windows-i386 ~/.wine/drive_c/cmake
RUN rm cmake-3.26.6-windows-i386.zip

# Set up entrypoint script to perform the build
COPY entrypoint.sh entrypoint.sh
RUN chmod +x entrypoint.sh
ENTRYPOINT [ "/bin/bash", "./entrypoint.sh" ]
