#!/bin/bash
if ! command -v wget &> /dev/null
then
    echo "'wget' could not be found, please install"
    exit
fi

if ! command -v dialog &> /dev/null
then
    echo "'dialog' could not be found, please install"
    exit
fi

if ! command -v 7z &> /dev/null
then
    echo "'7z' could not be found, please install"
    exit
fi

cmd=(dialog --keep-tite --menu "Installing SFML2.5.1. Please, select OS:" 22 76 16)

options=(1 "macOS"
         2 "Linux"
         3 "Windows")

choices=$("${cmd[@]}" "${options[@]}" 2>&1 >/dev/tty)

for choice in $choices
do
    case $choice in
        1)
            wget -O sfml.tar.gz https://github.com/SFML/SFML/releases/download/2.5.1/SFML-2.5.1-macOS-clang.tar.gz
            7z x sfml.tar.gz
            rm sfml.tar.gz
            7z x sfml.tar
            rm sfml.tar
            mkdir bin
            mkdir bin/sfml
            mv -v SFML-2.5.1-macos-clang/* bin/sfml/
            rm -rfv SFML-2.5.1-macos-clang
            cp -r bin/sfml/extlibs/* bin/sfml/Frameworks
            ;;

        2)
            wget -O sfml.tar.gz https://github.com/SFML/SFML/releases/download/2.5.1/SFML-2.5.1-linux-gcc-64-bit.tar.gz
            7z x sfml.tar.gz
            rm sfml.tar.gz
            7z x sfml.tar
            rm sfml.tar
            mkdir bin
            mkdir bin/sfml
            mv -v SFML-2.5.1/* bin/sfml/
            rm -rfv SFML-2.5.1
            ;;
        3)
            wget -O sfml.tar.gz https://github.com/SFML/SFML/releases/download/2.5.1/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit.zip
            7z x sfml.tar.gz
            rm sfml.tar.gz
            7z x sfml.tar
            rm sfml.tar
            mkdir bin
            mkdir bin/sfml
            mv -v SFML-2.5.1/* bin/sfml/
            rm -rfv SFML-2.5.1
            ;;
        4)

    esac
done
