/***************************************************************************
 *            pak.c
 *
 *  Fri Sep 23 08:57:35 2005
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

#include <pak.h>

gchar m_szFolderPath[300];  /* Folder to compile in to PAK */
gchar m_szPakName[300];     /* Output PAK file path and name */
struct sPakHeader m_Header; /* The header of the PAK file */
struct sFileTableEntry_list *m_FileTable;

gboolean GenerateHFT() {
  /* Declare local variables */
  gint iRandom = 0;        /* Recieves a random number */
  guint32 dwFileCount = 0; /* Number of files in compile directory */
  DIR *dp;
  struct dirent *entry;
  struct stat statbuf;
  gint i;
  gchar Buffer[300] = {0}; /* All purpose buffer */

  /* Seed the timer with the clock */
  srand((unsigned)time(NULL));

  /* Create the header signature */
  memcpy(m_Header.szSignature, "LLKPAK", 6);

  /* Set the file version */
  m_Header.fVersion = 2.3;

  /* Get a random 1 or 0 (TRUE or FALSE) and set cypher direction */
  iRandom = rand() % 2;
  m_Header.bCypherAddition = (gboolean)iRandom;

  /* Get the caesar cypher value */
  iRandom = rand() % 256;
  m_Header.iCypherValue = (guint8)iRandom;

  /* Create a unique ID */
  for (i = 0; i < 10; i++) {
    iRandom = rand() % 256;
    m_Header.szUniqueID[i] = (gchar)iRandom;
  }

  /* Get a local copy of the compilation folder name so that the one
     in the class isn't altered */
  if (strlen(m_szFolderPath) == 0) {
    return FALSE;
  }
  memcpy(Buffer, m_szFolderPath, 300);
  if ((dp = opendir(Buffer)) == NULL) { /* can not open directory */
    return FALSE;
  }
  chdir(Buffer);
  /* Start filling in the file table */
  while ((entry = readdir(dp)) != NULL) {
    lstat(entry->d_name, &statbuf);
    if (S_ISDIR(statbuf.st_mode)) {
      if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        continue;
      else { /* ignore directory */
        continue;
      }
    } else {
      /* Create a node entry for the file table */
      struct sFileTableEntry_list *TempEntry =
          (struct sFileTableEntry_list *)g_malloc(
              sizeof(struct sFileTableEntry_list));
      /* Store the file name */
      memcpy(TempEntry->szFileName, entry->d_name, 30);
      /* Store the file size */
      TempEntry->dwFileSize = (guint32)statbuf.st_size;
      /* Default the offset value (worked out later) */
      TempEntry->dwOffset = 0;
      /* Add this to the file table,add to the front */
      TempEntry->Next = m_FileTable;
      m_FileTable = TempEntry;
      /* Increment the files counter */
      dwFileCount++;
    }
  }
  chdir("..");
  /* Close the search handle */
  closedir(dp);

  /* Mark the number of files added in the header */
  m_Header.dwNumFTEntries = dwFileCount;
  return TRUE;
}

gboolean WorkOutOffsets() {
  /* Declare local variables */
  guint32 dwFileHFTData = 0; /* Size of header and file table */
  guint32 dwOffset = 0;      /* Individual files offset in to the PAK */
  struct sFileTableEntry_list *Current;
  /* Work out the size, in bytes, of the header and FT ,this place should use
   * sFileTableEntry_tmp, because the Next pointer is not saved in pak file*/
  dwFileHFTData =
      sizeof(struct sPakHeader) +
      (m_Header.dwNumFTEntries * sizeof(struct sFileTableEntry_tmp));

  /* Create a temporary node and make it the head of the linked list */

  Current = m_FileTable;

  /* Get the first offset */
  dwOffset = dwFileHFTData + 1;

  while (Current != NULL) {
    /* Set the offset */
    Current->dwOffset = dwOffset;

    /* Update the offset */
    dwOffset = dwOffset + Current->dwFileSize;

    /* Update the current variable */
    Current = Current->Next;
  }

  return TRUE;
}

gboolean CreatePak(gchar *Path, gchar *Output) {
  /* Declare local variables */
  FILE *PAKStream;   /* File pointer for writing to the PAK */
  FILE *InputStream; /* For reading in each file to be added */
  fpos_t Pos;        /* Position in the PAK file,fpos_t,defined in stdio.h */
  gchar Buffer[300] = {0}; /* General purpose buffer */
  gint iStringLength = 0;  /* String length */
  struct sFileTableEntry_list *Current;

  memset(&m_Header, 0, sizeof(struct sPakHeader));
  memset(m_szFolderPath, 0, 300);
  memset(m_szPakName, 0, 300);
  m_FileTable = NULL;
  /* Error check */
  if ((Path == NULL) || (Output == NULL)) {
    return FALSE;
  }

  /* Store the function paramaters in the class */
  iStringLength = strlen(Path);
  memcpy(m_szFolderPath, Path, iStringLength);
  iStringLength = strlen(Output);
  memcpy(m_szPakName, Output, iStringLength);

  /* Create the header and file table */
  if (!GenerateHFT()) {
    g_print("%s\n", _("GenerateHFT() failed."));
    return FALSE;
  }

  /* Work out the offsets */
  if (!WorkOutOffsets()) {
    g_print("%s\n", _("WorkOutOffsets() failed."));
    return FALSE;
  }

  /* Open the file stream for writing the PAK */
  PAKStream = fopen(Output, "wb");
  if (!PAKStream) {
    return FALSE;
  }

  /* Write the PAK header */
  fwrite(&m_Header, sizeof(struct sPakHeader), 1, PAKStream);

  /* Get a local copy of the file table head */
  Current = m_FileTable;

  /* Encrypt and write out each file table entry */
  while (Current != NULL) {
    /* Create a BYTE pointer for byte access to a file table entry */
    guint8 *Ptr = NULL;
    gint i;

    /* Create a BYTE array the same size as a file table entry */
    Ptr = (guint8 *)g_malloc(sizeof(struct sFileTableEntry_tmp));
    /* Store the file name */
    memcpy(((struct sFileTableEntry_tmp *)Ptr)->szFileName, Current->szFileName,
           30);
    ((struct sFileTableEntry_tmp *)Ptr)->dwFileSize = Current->dwFileSize;
    ((struct sFileTableEntry_tmp *)Ptr)->dwOffset = Current->dwOffset;

    for (i = 0; i < sizeof(struct sFileTableEntry_tmp); i++) {
      /* Temporary BYTE variable */
      guint8 Temp = 0;

      /* Make equal to the relevant byte of the FT entry */
      Temp = Ptr[i];

      /* Encrypt BYTE according to the caesar cypher */
      if (m_Header.bCypherAddition == TRUE)
        Temp += m_Header.iCypherValue;
      else
        Temp -= m_Header.iCypherValue;

      /* Write the FT encrypted BYTE value */
      fwrite(&Temp, sizeof(guint8), 1, PAKStream);
    }

    /* Move on to the next file table entry */
    Current = Current->Next;

    /* Delete the temporary BYTE pointer */
    g_free(Ptr);
  }

  /* Close the stream used for the header and file table */
  fclose(PAKStream);

  /* Reset variable to be the head of the file table */
  Current = m_FileTable;

  /* Read in each file at a time, encrypt it using the cypher and add to PAK */
  while (Current != NULL) {
    /* Declare local variables */
    guint8 DataBuffer = 0;
    guint32 i;

    /* Open the PAK file for writing
     * g_print("%s\n%s\n",m_szFolderPath,m_szPakName);*/
    PAKStream = fopen(Output, "r+b");
    if (!PAKStream) {
      return FALSE;
    }

    /* Create the absolute path of the file to be added to the PAK */
    memcpy(Buffer, m_szFolderPath, 300);
    strcat(Buffer,
           "/"); /* if in windows system,this should be strcat(Buffer,"\\"); */
    strcat(Buffer, Current->szFileName);

    /* Open the data stream for reading in a file to be added to the PAK */
    InputStream = fopen(Buffer, "rb");
    if (!InputStream) {
      fclose(PAKStream);
      return FALSE;
    }

    /* Set the position in the PAK file for this file to be written at */
    /* If not GNU system,this should be Pos = Current->dwOffset */
#ifdef WIN32
    Pos = Current->dwOffset;
#else
    Pos.__pos = Current->dwOffset;
#endif
    fsetpos(PAKStream, &Pos);

    /* Read in the file a byte at a time, encrypt it and write to PAK */
    for (i = 0; i < Current->dwFileSize; i++) {
      /* Get the first BYTE from the file to be added */
      DataBuffer = fgetc(InputStream);

      /* Encrypt the file accordingly */
      if (m_Header.bCypherAddition == TRUE)
        DataBuffer += m_Header.iCypherValue;
      else
        DataBuffer -= m_Header.iCypherValue;

      /* Write to the PAK file starting at the offset */
      fwrite(&DataBuffer, sizeof(guint8), 1, PAKStream);
    }

    /* Close both the file streams */
    fclose(InputStream);
    fclose(PAKStream);

    /* Advance to the next file to be written according to the FT */
    Current = Current->Next;
  }

  return TRUE;
}

gboolean ClearPAKClass() {
  guint32 i;
  /* Default the path variables */
  memset(m_szFolderPath, 0, sizeof(m_szFolderPath));
  memset(m_szPakName, 0, sizeof(m_szPakName));

  /* Check if there is data in the FT */
  if (m_FileTable != NULL) {
    /* Loop through each file table entry and delete it */
    for (i = 0; i < m_Header.dwNumFTEntries; i++) {
      /* Create a temporary FT node */
      struct sFileTableEntry_list *Temp = m_FileTable;
      /* Make head node point to it's child */
      m_FileTable = Temp->Next;
      /* Free the temp pointer */
      free(Temp);
    }
  }
  /* Clear the PAK header */
  memset(&m_Header, 0, sizeof(struct sPakHeader));
  return TRUE;
}

gboolean LoadPAKHFT(gchar *PakFile) {
  /* Declare local variables */
  FILE *InputStream;
  struct sFileTableEntry_list *NewEntry;
  guint32 i, z;

  /* Clear previous data if there is any */
  ClearPAKClass();
  /* Error check */
  if (strlen(PakFile) == 0) {
    return FALSE;
  }

  /* Store the PAK name in the class */
  memcpy(m_szPakName, PakFile, 300);

  /* Open the specified file */
  InputStream = fopen(PakFile, "rb");
  if (!InputStream) {
    return FALSE;
  }

  /* Read in the file header */
  fread(&m_Header, sizeof(struct sPakHeader), 1, InputStream);

  /* Read in the file table */
  for (i = 0; i < m_Header.dwNumFTEntries; i++) {
    /* Create a BYTE array the size of a file table entry */
    guint8 *Ptr = NULL;
    Ptr = (guint8 *)g_malloc(sizeof(struct sFileTableEntry_tmp));

    /* Read in the entry a BYTE at a time */
    for (z = 0; z < sizeof(struct sFileTableEntry_tmp); z++) {
      /* Read a BYTE at a time */
      Ptr[z] = fgetc(InputStream);

      /* Perform decryption using the caesar cypher (reversed to decrypt) */
      if (m_Header.bCypherAddition == TRUE)
        Ptr[z] -= m_Header.iCypherValue;
      else
        Ptr[z] += m_Header.iCypherValue;
    }

    /* Create the file entry to add to the list */
    NewEntry = (struct sFileTableEntry_list *)g_malloc(
        sizeof(struct sFileTableEntry_list));

    /* Copy the contents of the BYTE array to the entry */
    // memcpy( NewEntry, Ptr, sizeof(struct sFileTableEntry_list) );
    memcpy(NewEntry->szFileName,
           ((struct sFileTableEntry_tmp *)Ptr)->szFileName, 30);
    NewEntry->dwFileSize = ((struct sFileTableEntry_tmp *)Ptr)->dwFileSize;
    NewEntry->dwOffset = ((struct sFileTableEntry_tmp *)Ptr)->dwOffset;

    /* Add this to the linked list, file table member variable */
    NewEntry->Next = m_FileTable;
    m_FileTable = NewEntry;

    /* Free the BYTE array */
    g_free(Ptr);
    Ptr = NULL;
  }

  /* Close the file stream */
  fclose(InputStream);

  return TRUE;
}

gboolean ExtractPAK(gchar *Path) {
  /* Declare local variables */
  FILE *ReadStream;  /* A read data stream */
  FILE *WriteStream; /* A write data stream */
  fpos_t Pos;        /* Offset in to file */
  struct sFileTableEntry_list *Current;
  gchar *extract_to_name = NULL;

  /* Error check the PAK name that is acquired in LoadPAKHFT() */
  if (strlen(m_szPakName) == 0) {
    return FALSE;
  }

  /* Make it the head of the file table */
  Current = m_FileTable;

  while (Current != NULL) {
    /* Declare local variables */
    guchar Buffer = 0;
    guint32 Count;

    /* Open PAK file stream (to read from) */
    ReadStream = fopen(m_szPakName, "rb");
    if (!ReadStream)
      return FALSE;

    /* Attempt to open the write stream for creating the file */
    extract_to_name = g_strdup_printf("%s/%s", Path, Current->szFileName);
    WriteStream = fopen(extract_to_name, "wb");
    g_free(extract_to_name);
    if (!WriteStream) {
      fclose(ReadStream);
      return FALSE;
    }

    /* Set the offset in PAK to the beginning of this particular file
       to be extracted */
    /* If not GNU system,this should be Pos = Current->dwOffset */
#ifdef WIN32
    Pos = Current->dwOffset;
#else
    Pos.__pos = Current->dwOffset;
#endif
    fsetpos(ReadStream, &Pos);

    /* Loop through the file by it's size and read from the PAK
       followed by write to file */
    for (Count = 0; Count < Current->dwFileSize; Count++) {
      /* Read in the char */
      Buffer = fgetc(ReadStream);

      /* Perform decryption using the caesar cypher (reversed to decrypt) */
      if (m_Header.bCypherAddition == TRUE)
        Buffer -= m_Header.iCypherValue;
      else
        Buffer += m_Header.iCypherValue;

      /* Write to the file */
      fwrite(&Buffer, sizeof(guchar), 1, WriteStream);
    }

    /* Close the file streams */
    fclose(WriteStream);
    fclose(ReadStream);

    /* Move on the the next file to extract */
    Current = Current->Next;
  }

  return TRUE;
}

gboolean ExtractSingleFile(gchar *Filename) {
  /* Declare local variables */
  FILE *ReadStream = NULL;  /* A read data stream */
  FILE *WriteStream = NULL; /* A write data stream */
  fpos_t Pos;               /* Offset in to file */
  guchar Buffer = 0;        /* A read buffer */
  guint32 Count;
  /* Declare a temporary file table node to work from */
  struct sFileTableEntry_list *Current;

  /* Error check the method parameters and PAK file acquired from LoadPAKHFT()
   */
  if (strlen(m_szPakName) == 0) {
    return FALSE;
  }
  if (strlen(Filename) == 0) {
    return FALSE;
  }

  /* Make it the top of the file table */
  Current = m_FileTable;

  /* Iterate through Current until it is the entry specified in the method
   * parameters */
  while (Current != NULL && strcmp(Current->szFileName, Filename) != 0) {
    /* Advance Current to the next entry */
    Current = Current->Next;
  }
  if (Current == NULL)
    return FALSE; /* No such file name in these entries */

  /* Open PAK file stream (to read from) */
  ReadStream = fopen(m_szPakName, "rb");
  if (!ReadStream)
    return FALSE;
  /* Attempt to open the write stream for creating the file */
  gchar *tmpstr = NULL;
  tmpstr = g_strdup_printf("/tmp/llk_%s", Current->szFileName);
  WriteStream = fopen(tmpstr, "wb");
  g_free(tmpstr);
  if (!WriteStream) {
    fclose(ReadStream);
    return FALSE;
  }

  /* Set the offset in PAK to the beginning of this particular file
     to be extracted */
  /* If not GNU system,this should be Pos = Current->dwOffset */
#ifdef WIN32
  Pos = Current->dwOffset;
#else
  Pos.__pos = Current->dwOffset;
#endif
  fsetpos(ReadStream, &Pos);

  /* Loop through the file by it's size and read from the PAK
     followed by write to file */
  for (Count = 0; Count < Current->dwFileSize; Count++) {
    /* Read in the char */
    Buffer = fgetc(ReadStream);

    /* Perform decryption using the caesar cypher (reversed to decrypt) */
    if (m_Header.bCypherAddition == TRUE)
      Buffer -= m_Header.iCypherValue;
    else
      Buffer += m_Header.iCypherValue;
    /* Write to the file */
    fwrite(&Buffer, sizeof(guchar), 1, WriteStream);
  }

  /* Close the file streams */
  fclose(ReadStream);
  fclose(WriteStream);

  return TRUE;
}

gboolean FindFile(gchar *filename) {
  struct sFileTableEntry_list *Current;
  Current = m_FileTable;
  while (Current != NULL) {
    if (!strcasecmp(Current->szFileName, filename))
      return TRUE;
    Current = Current->Next;
  }
  return FALSE;
}
gint GetFileNum(gchar *Firstname, gchar *Lastname) {
  gint Count = 0;
  gchar *str =
      g_malloc(sizeof(gchar) * (strlen(Firstname) + strlen(Lastname) + 5));
  /* Count should be within 999 */
  while (TRUE) {
    sprintf(str, "%s%d.%s", Firstname, Count, Lastname);
    if (FindFile(str))
      Count++;
    else {
      g_free(str);
      return Count;
    }
  }
}
