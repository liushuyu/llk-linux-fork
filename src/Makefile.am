## Process this file with automake to produce Makefile.in

## Created by Anjuta - will be overwritten
## If you don't want it to overwrite it,
## 	Please disable it in the Anjuta project configuration

INCLUDES = \
	$(PACKAGE_CFLAGS)\
	 -I../ -I../include

AM_CFLAGS =\
	`pkg-config --cflags --libs gtk+-2.0`\
	 -Wall\
	 -g

bin_PROGRAMS = llk_linux

llk_linux_SOURCES = \
	main.c\
	llk_about.c\
	llk_algorithm.c\
	llk_inifile.c\
	pak/create_pak.c\
	pak/pak.c\
	eggtrayicon.c\
	tray.c

llk_linux_LDFLAGS = -lX11

llk_linux_LDADD =  \
	$(PACKAGE_LIBS)\
	 -lc

