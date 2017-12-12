#!/bin/bash

if [[ $EUID -eq 0 ]]; then
echo "Unless you only want to run the tracker as root" 1>&2
echo "don't run this script as root." 1>&2
echo "This script will prompt with sudo." 1>&2
echo "" 1>&2

read -p "Continue anyway [not recommended] y/n: " answer
case $answer in
[nN]* ) exit;;
esac

fi

postfix=$1

echo

echo "Dependencies include:"
echo "   ncurses"     #trk
echo "   aplay"       #itp
echo "   inotifywait" #trkdaemon
echo "   flac"        #rend
echo ""

echo "Creating log files"
userName=$USER
primaryGrp=`id -gn`

sudo mkdir /var/tmp/plebtrk 2>/dev/null
sudo chmod 755 /var/tmp/plebtrk
sudo chgrp $primaryGrp /var/tmp/plebtrk
sudo chown $userName /var/tmp/plebtrk

sudo touch /var/tmp/plebtrk/itplog.log
sudo touch /var/tmp/plebtrk/trklog.log

echo "Copying executables into /usr/bin/..."
sudo cp ./plebplay /usr/bin/plebplay$postfix
echo "/usr/bin/plebplay$postfix"
sudo cp ./plebitp /usr/bin/plebitp$postfix
echo "/usr/bin/plebitp$postfix"
sudo cp ./plebrender /usr/bin/plebrender$postfix
echo "/usr/bin/plebrender$postfix"
echo ""

if [ ! -d /usr/local/man ]; then
	sudo mkdir /usr/local/man	
fi
if [ ! -d /usr/local/man/man1 ]; then
	sudo mkdir /usr/local/man/man1/
fi

echo "Copying man pages into /usr/local/man/man1/..."
sudo cp ../doc/plebitp.1 /usr/local/man/man1/
echo "/usr/local/man/man1/plebitp.1"
sudo cp ../doc/plebplay.1 /usr/local/man/man1/
echo "/usr/local/man/man1/plebplay.1"
sudo cp ../doc/plebrender.1 /usr/local/man/man1/
echo "/usr/local/man/man1/plebrender.1"

