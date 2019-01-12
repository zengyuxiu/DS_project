#=============================================================================
#
# Author: Zeng Yuxiu
#
# Copyright (C) 2018 All rights reserved.
#
# Last modified:	2019-01-12 18:06
#
# Filename:		Biotaxomy.sh
#
# Description: 
#
#==============================================================================
#!/bin/bash
exec 3>OUT
if [ -n  "$1" ]
then 
	while getopts :p:af:mho opt
	do 
		case "$opt" in
			p)	./Call/Call $OPTAGE >&3;;
			a)	./Call/Call >&3;;
			f)  ./Find/SingleFind $2 >&3;;
			m)	./Find/MutiFind  >&3;;
			h)  cat ./INFO | more;;
			*)  cat ./INFO | more;;
		esac
	done
else
	cat ./INFO | more
fi

