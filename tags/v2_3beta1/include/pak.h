/***************************************************************************
 *            pak.h
 *
 *  Fri Sep 23 08:58:56 2005
 *  Copyright  2005  Alpher
 *  Email: alpher_zmx@yahoo.com.cn
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
 

#ifndef __PAK_H
#define __PAK_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <gtk/gtk.h>
#include <glib/gi18n.h>

/* PAK file header */
struct sPakHeader	
{
  gchar     szSignature[6]; /* PAK Signature should be 'RWPACK'  */
  gfloat    fVersion;       /* Version of PAK file */
  guint32   dwNumFTEntries; /* Number of file table entries */
  gboolean  bCypherAddition;/* Should the caesar cypher add (or subtract) */
  guint8    iCypherValue;   /* Random value used for the caesar cypher between 0-255 */
  gchar     szUniqueID[10]; /* A unique ID for the file (other programs can check it) */
  guint32   dwReserved;     /* Reserved Value */
};

/* Table Entry per file in the PAK file, for list node type, This should not be saved in pak file */
struct sFileTableEntry_list
{
  gchar     szFileName[30];       /* Name of one file in the PAK */
  guint32   dwFileSize;           /* The size of the file in bytes */
  guint32   dwOffset;             /* Offset of file in the PAK */
  struct sFileTableEntry_list * Next;  /* Next file table entry (is a linked list) */
};
/* This Entry type is used for saving the entry into pak file and read file from pak file
    Because the bits(length) of a pointer is CPU type depended,so there must be no pointer
   in the pak file.
*/
struct sFileTableEntry_tmp
{
  gchar     szFileName[30];       /* Name of one file in the PAK */
  guint32   dwFileSize;           /* The size of the file in bytes */
  guint32   dwOffset;             /* Offset of file in the PAK */
};
gchar       m_szFolderPath[300];     /* Folder to compile in to PAK */
gchar       m_szPakName[300];        /* Output PAK file path and name */
struct sPakHeader  m_Header;                /* The header of the PAK file */
struct sFileTableEntry_list* m_FileTable; /* The master file table for the PAK,
         before creat or unpak,you should set m_FileTable to NULL */

gboolean    GenerateHFT();                          /* Create a Header and File Table */
gboolean    WorkOutOffsets();                       /* Work out the file offsets in the PAK */
gboolean    ClearPAKClass();                        /* Clear current contents */
gboolean    CreatePak( gchar* Path, gchar* Output); /* Create the PAK file */
gboolean    LoadPAKHFT( gchar* PakFile );           /* Load an existing PAK header and file table */
gboolean    ExtractPAK(gchar* Path);                           /* Extract everything from PAK file */
gboolean    ExtractSingleFile( gchar* Filename);    /* Extract a single file from the specified PAK */
gint        GetFileNum(gchar *Firstname, gchar *Lastname);

#endif
