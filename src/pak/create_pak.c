/***************************************************************************
 *            create_pak.c
 *
 *  Fri Sep 23 09:00:37 2005
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
 
#include <create_pak.h>

GtkWidget *pak_dialog,*pak_entry_compilation,*pak_entry_output,*pak_entry_input,*pak_entry_extract;

void create_pak_dialog(void)
{
  GtkWidget *frame_compilation,*frame_extract;
  GtkWidget *button_compilation,*button_output,*button_input,*button_extract;
  GtkWidget *hbox_compilation,*vbox_compilation,*hbox_extract,*vbox_extract,*button;
  pak_dialog = gtk_dialog_new();
  gtk_window_set_title(GTK_WINDOW(pak_dialog),_("PAK File Compiler"));
  gtk_container_border_width(GTK_CONTAINER(pak_dialog), 5);
  frame_compilation = gtk_frame_new(_("Compilation / Output"));
  gtk_box_pack_start (GTK_BOX (GTK_DIALOG(pak_dialog)->vbox),frame_compilation,FALSE,TRUE,20);
    vbox_compilation = gtk_vbox_new(FALSE,5);
    gtk_container_add (GTK_CONTAINER(frame_compilation),vbox_compilation);
      hbox_compilation = gtk_hbox_new(FALSE,10);  
      gtk_box_pack_start (GTK_BOX (vbox_compilation),hbox_compilation,FALSE,TRUE,5);
        pak_entry_compilation = gtk_entry_new_with_max_length(300);
        gtk_box_pack_start (GTK_BOX(hbox_compilation),pak_entry_compilation,FALSE,TRUE,5);
        button_compilation = gtk_button_new_with_label(_(" Input Directory "));
        gtk_widget_set_size_request(button_compilation,140,30);
        gtk_signal_connect_object(GTK_OBJECT(button_compilation),"clicked",GTK_SIGNAL_FUNC(on_browse),GINT_TO_POINTER(0));
        gtk_box_pack_start (GTK_BOX(hbox_compilation),button_compilation,FALSE,FALSE,10);
      hbox_compilation = gtk_hbox_new(FALSE,10);
      gtk_box_pack_start (GTK_BOX(vbox_compilation),hbox_compilation,FALSE,TRUE,5);
        pak_entry_output = gtk_entry_new_with_max_length(300);
        gtk_box_pack_start (GTK_BOX(hbox_compilation),pak_entry_output,FALSE,TRUE,5);
        button_output = gtk_button_new_with_label(_(" Output PAK Name "));
        gtk_widget_set_size_request(button_output,140,30);
        gtk_signal_connect_object(GTK_OBJECT(button_output),"clicked",GTK_SIGNAL_FUNC(on_browse),GINT_TO_POINTER(1));
        gtk_box_pack_start (GTK_BOX(hbox_compilation),button_output,FALSE,FALSE,10);      
  frame_extract = gtk_frame_new(_("Extract PAK File"));
  gtk_box_pack_start (GTK_BOX (GTK_DIALOG(pak_dialog)->vbox),frame_extract,FALSE,TRUE,20);
    vbox_extract = gtk_vbox_new(FALSE,10);
    gtk_container_add (GTK_CONTAINER(frame_extract),vbox_extract);
      hbox_extract = gtk_hbox_new(FALSE,10);
      gtk_box_pack_start (GTK_BOX (vbox_extract),hbox_extract,FALSE,TRUE,5);
        pak_entry_input = gtk_entry_new_with_max_length(300);
        gtk_box_pack_start (GTK_BOX (hbox_extract),pak_entry_input,FALSE,TRUE,5);
        button_input = gtk_button_new_with_label(_(" Choose PAK File "));
        gtk_widget_set_size_request(button_input,140,30);
        gtk_signal_connect_object(GTK_OBJECT(button_input),"clicked",GTK_SIGNAL_FUNC(on_browse),GINT_TO_POINTER(2));
        gtk_box_pack_start (GTK_BOX (hbox_extract),button_input,FALSE,TRUE,5);
      hbox_extract = gtk_hbox_new(FALSE,10);
      gtk_box_pack_start (GTK_BOX (vbox_extract),hbox_extract,FALSE,TRUE,5);
        pak_entry_extract = gtk_entry_new_with_max_length(300);
        gtk_box_pack_start (GTK_BOX(hbox_extract),pak_entry_extract,FALSE,TRUE,5);
        button_extract = gtk_button_new_with_label(_(" Output Directory "));
        gtk_widget_set_size_request(button_extract,140,30);
        gtk_signal_connect_object(GTK_OBJECT(button_extract),"clicked",GTK_SIGNAL_FUNC(on_browse),GINT_TO_POINTER(3));
        gtk_box_pack_start (GTK_BOX(hbox_extract),button_extract,FALSE,FALSE,10);  
  
  /*Button area*/
  button = gtk_button_new_with_label(_(" Compilation "));
  gtk_signal_connect_object(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(on_ok_clicked), GINT_TO_POINTER(0));
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pak_dialog)->action_area), button, FALSE, FALSE, 0);
  button = gtk_button_new_with_label(_(" Extract All "));
  gtk_signal_connect_object(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(on_ok_clicked), GINT_TO_POINTER(1));
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pak_dialog)->action_area), button, FALSE, FALSE, 0);
  button = gtk_button_new_with_label(_(" Cancel "));
  gtk_signal_connect_object(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(gtk_widget_destroy), GTK_OBJECT(pak_dialog));
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pak_dialog)->action_area), button, FALSE, FALSE, 0);

  gtk_widget_show_all(pak_dialog);
  //gtk_widget_grab_focus(button);
}
void on_browse(gpointer data)
{
  GtkWidget *dialog;
  switch(GPOINTER_TO_INT(data))
  {
    case 0:
      dialog = gtk_file_chooser_dialog_new (_("Select Folder To Compile"),
                                          GTK_WINDOW(pak_dialog),
                                          GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
                                          GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                          NULL);
      break;
    case 1:
      dialog = gtk_file_chooser_dialog_new (_("Select Output PAK File Name"),
                                          GTK_WINDOW(pak_dialog),
                                          GTK_FILE_CHOOSER_ACTION_SAVE,
                                          GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                          NULL);
      break;
    case 2:
      dialog = gtk_file_chooser_dialog_new (_("Select A PAK File To Extract"),
                                          GTK_WINDOW(pak_dialog),
                                          GTK_FILE_CHOOSER_ACTION_OPEN,
                                          GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                          NULL);
      break;
    case 3:
      dialog = gtk_file_chooser_dialog_new (_("Select Folder Where To Extract The PAK File"),
                                          GTK_WINDOW(pak_dialog),
                                          GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
                                          GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                          NULL);
      break;
    default:
      dialog = NULL;
      break;
  }
  if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
  {
    char *filename;
    filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
    switch(GPOINTER_TO_INT(data))
    {
      case 0:
        gtk_entry_set_text(GTK_ENTRY(pak_entry_compilation),filename);
        break;
      case 1:
        gtk_entry_set_text(GTK_ENTRY(pak_entry_output),filename);
        break;
      case 2:
        gtk_entry_set_text(GTK_ENTRY(pak_entry_input),filename);
        break;
      case 3:
        gtk_entry_set_text(GTK_ENTRY(pak_entry_extract),filename);
        break;
    }
    g_free (filename);
  }
  gtk_widget_destroy (dialog);
}
void on_ok_clicked(gpointer data)
{
  char *str1 = NULL, *str2 = NULL;

  switch(GPOINTER_TO_INT(data))
  {
    case 0: /* Compilation */
      str1 = g_strdup_printf("%s",gtk_entry_get_text(GTK_ENTRY(pak_entry_compilation)));
      str2 = g_strdup_printf("%s",gtk_entry_get_text(GTK_ENTRY(pak_entry_output)));
      if(CreatePak(str1,str2))
      {
         GtkWidget *dialog = gtk_message_dialog_new (GTK_WINDOW(pak_dialog),
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  GTK_MESSAGE_INFO,
                                  GTK_BUTTONS_CLOSE,
                                  _("Compile Fold to PAK Successfully."));
        gtk_dialog_run (GTK_DIALOG (dialog));
        gtk_widget_destroy (dialog);
      }
      else
      {
        GtkWidget *dialog = gtk_message_dialog_new (GTK_WINDOW(pak_dialog),
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  GTK_MESSAGE_ERROR,
                                  GTK_BUTTONS_CLOSE,
                                  _("Compile Fold to PAK Failed,Check the folder/file name if you have right to access them"));
        gtk_dialog_run (GTK_DIALOG (dialog));
        gtk_widget_destroy (dialog);
      }
	  g_free (str1); g_free (str2);
      break;
    case 1: /* Extract all */
      str1 = g_strdup_printf("%s",gtk_entry_get_text(GTK_ENTRY(pak_entry_input)));
      str2 = g_strdup_printf("%s",gtk_entry_get_text(GTK_ENTRY(pak_entry_extract)));
      if(LoadPAKHFT(str1) && ExtractPAK(str2))
      {
         GtkWidget *dialog = gtk_message_dialog_new (GTK_WINDOW(pak_dialog),
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  GTK_MESSAGE_INFO,
                                  GTK_BUTTONS_CLOSE,
                                  _("Extract PAK Successfully."));
        gtk_dialog_run (GTK_DIALOG (dialog));
        gtk_widget_destroy (dialog);
      }
      else
      {
        GtkWidget *dialog = gtk_message_dialog_new (GTK_WINDOW(pak_dialog),
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  GTK_MESSAGE_ERROR,
                                  GTK_BUTTONS_CLOSE,
                                  _("Extract PAK File Failed,Check if you have right to access the file/folder."));
        gtk_dialog_run (GTK_DIALOG (dialog));
        gtk_widget_destroy (dialog);
      }
	  g_free (str1); g_free (str2);
      break;
    default:
      break;
  }
}
