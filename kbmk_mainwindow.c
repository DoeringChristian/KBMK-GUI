#include "kbmk_mainwindow.h"

const gint EvMask = GDK_BUTTON_PRESS_MASK | GDK_BUTTON1_MOTION_MASK;
const char parser_alph_numb[] = "0123456789";
const char parser_alph_letter[] =  "!\"#$%&\\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
const char kbmk_mainwindow_btn_lock_label_locked[] = " Locked ";
const char kbmk_mainwindow_btn_lock_label_unlocked[] = "Unlocked";
const char kbmk_mainwindow_keybord_idpath[] = "/dev/input/by-id/";

SLL_DEFINE_C(kbmk_keybutton_p);
SLL_DEFINE_C(kbmk_keyboard_p);

kbmk_mainwindow_t *kbmk_mainwindow_new(){

    kbmk_mainwindow_t *mainwindow = malloc(sizeof(kbmk_mainwindow_t));

    mainwindow->win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width (GTK_CONTAINER (mainwindow->win), 0);
    gtk_widget_realize(mainwindow->win);
    g_signal_connect(mainwindow->win, "destroy", gtk_main_quit, NULL);

    mainwindow->box_main = gtk_vbox_new(FALSE, 0);
    mainwindow->box_chose = gtk_hbox_new(FALSE, 0);
    mainwindow->box_bottom = gtk_hbox_new(FALSE, 0);
    mainwindow->box_middle = gtk_hbox_new(FALSE, 0);
    mainwindow->box_menu = gtk_vbox_new(FALSE, 0);

    mainwindow->ch_layout = gtk_combo_box_new();
    //mainwindow->ch_keyboard = gtk_combo_box_new();
    mainwindow->ch_keyboard = gtk_combo_box_text_new();

    mainwindow->btn_load = gtk_button_new();
    mainwindow->btn_save = gtk_button_new();
    mainwindow->btn_add = gtk_button_new();
    mainwindow->btn_export = gtk_button_new();
    mainwindow->btn_lock = gtk_toggle_button_new();

    mainwindow->grd_layout = gtk_fixed_new();

    mainwindow->configwindow = NULL;
    mainwindow->layout = SLL_LIST_NEW(kbmk_keybutton_p)();
    mainwindow->moved_keybutton = NULL;
    mainwindow->keyboards = SLL_LIST_NEW(kbmk_keyboard_p)();
    mainwindow->locked = 0;


    gtk_widget_add_events(mainwindow->win,  gtk_widget_get_events(mainwindow->win) | GDK_POINTER_MOTION_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON1_MOTION_MASK);
    gtk_widget_add_events(mainwindow->grd_layout,  gtk_widget_get_events(mainwindow->grd_layout) | GDK_POINTER_MOTION_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON1_MOTION_MASK);
    gtk_window_set_default_size(GTK_WINDOW(mainwindow->win), 800, 600);

    g_signal_connect(G_OBJECT(mainwindow->btn_load), "clicked", G_CALLBACK(btn_load_clicked), (gpointer)mainwindow);
    g_signal_connect(G_OBJECT(mainwindow->btn_save), "clicked", G_CALLBACK(btn_save_clicked), (gpointer)mainwindow);
    g_signal_connect(G_OBJECT(mainwindow->btn_add), "clicked", G_CALLBACK(btn_add_clicked), (gpointer)mainwindow);
    g_signal_connect(G_OBJECT(mainwindow->btn_export), "clicked", G_CALLBACK(btn_export_clicked), (gpointer)mainwindow);
    g_signal_connect(G_OBJECT(mainwindow->btn_lock), "clicked", G_CALLBACK(btn_lock_clicked), (gpointer)mainwindow);

    g_signal_connect(G_OBJECT(mainwindow->ch_layout), "changed", G_CALLBACK(ch_layout_changed), (gpointer)mainwindow);
    g_signal_connect(G_OBJECT(mainwindow->ch_keyboard), "changed", G_CALLBACK(ch_keyboard_changed), (gpointer)mainwindow);

    g_signal_connect(G_OBJECT(mainwindow->win), "motion_notify_event", G_CALLBACK(grd_layout_motion_event), (gpointer)mainwindow);

    gtk_container_add(GTK_CONTAINER(mainwindow->win), mainwindow->box_main);
    gtk_box_pack_start(GTK_BOX(mainwindow->box_main), mainwindow->box_chose, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(mainwindow->box_main), mainwindow->box_middle, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(mainwindow->box_main), mainwindow->box_bottom, FALSE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(mainwindow->box_chose), mainwindow->ch_keyboard, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(mainwindow->box_chose), mainwindow->ch_layout, TRUE, TRUE, 0);

    gtk_box_pack_end(GTK_BOX(mainwindow->box_bottom), mainwindow->btn_save, FALSE, TRUE, 0);
    gtk_box_pack_end(GTK_BOX(mainwindow->box_bottom), mainwindow->btn_load, FALSE, TRUE, 0);
    gtk_box_pack_end(GTK_BOX(mainwindow->box_bottom), mainwindow->btn_export, FALSE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(mainwindow->box_middle), mainwindow->box_menu, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(mainwindow->box_middle), mainwindow->grd_layout, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(mainwindow->box_menu), mainwindow->btn_add, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(mainwindow->box_menu), mainwindow->btn_lock, FALSE, TRUE, 0);

    gtk_button_set_label(GTK_BUTTON(mainwindow->btn_load), "Load");
    gtk_button_set_label(GTK_BUTTON(mainwindow->btn_save), "Save");
    gtk_button_set_label(GTK_BUTTON(mainwindow->btn_add), "Add +");
    gtk_button_set_label(GTK_BUTTON(mainwindow->btn_export), "Export");
    gtk_button_set_label(GTK_BUTTON(mainwindow->btn_lock), kbmk_mainwindow_btn_lock_label_locked);

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(mainwindow->btn_lock), TRUE);

    gtk_box_set_spacing(GTK_BOX(mainwindow->box_menu), 5);
    gtk_box_set_spacing(GTK_BOX(mainwindow->box_main), 5);
    gtk_box_set_spacing(GTK_BOX(mainwindow->box_chose), 5);
    gtk_box_set_spacing(GTK_BOX(mainwindow->box_middle), 5);
    gtk_box_set_spacing(GTK_BOX(mainwindow->box_bottom), 5);

    kbmk_mainwindow_list_keyboard(mainwindow);

    return mainwindow;
}

void kbmk_mainwindow_delete(kbmk_mainwindow_t *win){
    kbmk_configwindow_delete(win->configwindow);
    SLL_FOR_EACH(button IN win->layout){
        kbmk_keybutton_delete(button);
    }
    gtk_widget_destroy(win->win);
    free(win);
}

static void btn_load_clicked(GtkWidget *wid, kbmk_mainwindow_t *win){
    GtkWidget *dialog;

    dialog = gtk_file_chooser_dialog_new ("Load File",
                                      win->win,
                                      GTK_FILE_CHOOSER_ACTION_OPEN,
                                      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                      NULL);

    if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT){
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        kbmk_mainwindow_load_file(win, filename);
        g_free(filename);
    }
    gtk_widget_destroy(dialog);

    //kbmk_mainwindow_load_file(win, "test.txt");
}
static void btn_save_clicked(GtkWidget *wid, kbmk_mainwindow_t *win){
    GtkWidget *dialog;

    dialog = gtk_file_chooser_dialog_new ("Save File",
                                          win->win,
                                          GTK_FILE_CHOOSER_ACTION_SAVE,
                                          GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
                                          NULL);
    gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (dialog), TRUE);
    gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (dialog), "Untitled document");

    if(gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT){
        char *filename;

        filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
        kbmk_mainwindow_save_file(win, filename);
        g_free (filename);
    }

    gtk_widget_destroy (dialog);
}
static void btn_add_clicked(GtkWidget *wid, kbmk_mainwindow_t *win){
    g_print("test");
    kbmk_keybutton_t *current_keybutton = kbmk_keybutton_new(win);

    SLL_LIST_PUSH_BACK(kbmk_keybutton_p)(win->layout, current_keybutton);

    gtk_fixed_put(GTK_FIXED(win->grd_layout), current_keybutton->box_outline, 10, 10);
    gtk_widget_show_all(win->win);

    kbmk_configwindow_delete(win->configwindow);
    win->configwindow = kbmk_configwindow_new(win, current_keybutton);
    gtk_widget_show_all(win->configwindow->win_config);
}
static void ch_keyboard_changed(GtkComboBox *widget, kbmk_mainwindow_t *win){
    //printf("%i\n", gtk_combo_box_get_active(widget));
    unsigned int index = gtk_combo_box_get_active(widget);
    kbmk_keyboard_p *active = SLL_LIST_ELEMENT_AT(kbmk_keyboard_p)(win->keyboards, index);
    SLL_NODE(kbmk_keyboard_p) *active_node = SLL_LIST_NODE_AT(kbmk_keyboard_p)(win->keyboards, index);
    printf("%s\n", (*active)->event);
}
static void ch_layout_changed(GtkComboBox *widget, kbmk_mainwindow_t *win){}

static void grd_layout_motion_event(GtkWidget *wid, GdkEvent *event, kbmk_mainwindow_t *win){
    if(win->moved_keybutton != NULL){
        GdkEventMotion* e=(GdkEventMotion*)event;
        g_print("x, y: %i, %i", (int)e->x, (int)e->y);
        gint grd_layout_x, grd_layout_y;
        gint btn_config_w, btn_config_h;

        btn_config_w = 50;
        btn_config_h = 50;
        gtk_widget_translate_coordinates(win->win, win->grd_layout, (int)e->x, (int)e->y, &grd_layout_x, &grd_layout_y);

        gint total_x = grd_layout_x-btn_config_w/2, total_y = grd_layout_y-btn_config_h/2;

        if(total_x >= 0 && total_y >= 0)
            kbmk_keybutton_set_position(win->moved_keybutton, total_x, total_y);
        else if(total_x >= 0 && total_y < 0)
            kbmk_keybutton_set_position(win->moved_keybutton, total_x, 0);
        else if(total_x < 0 && total_y >= 0)
            kbmk_keybutton_set_position(win->moved_keybutton, 0, total_y);
        gtk_widget_show_all(win->win);
    }
}

void kbmk_mainwindow_load_file(kbmk_mainwindow_t *mainwindow, char *filename){
    FILE *fp = fopen(filename, "r");

    uint8_t state = PARSER_DASH;
    char buffer[1024];
    uint64_t buffercount = 0;
    kbmk_keybutton_t *current_button = NULL;
    int c = 0;
    while(c != EOF){
        c = getc(fp);
        switch(state){
        case PARSER_BEGIN:
            if(c == '-')
                state = PARSER_DASH;
            else
                state = PARSER_BEGIN;
            break;
        case PARSER_DASH:
            if(c == '-'){
                current_button = kbmk_keybutton_new(mainwindow);
                SLL_LIST_PUSH_BACK(kbmk_keybutton_p)(&mainwindow->layout, current_button);
                state = PARSER_NAME;
            }
            else
                state = PARSER_DASH;
            break;
        case PARSER_NAME:
            if(c == '\n'){
                buffer[buffercount] = 0;
                buffercount++;
                kbmk_keybutton_set_keyname(current_button, buffer);
                buffercount = 0;
                state = PARSER_KEYCODE;
            }
            else{
                buffer[buffercount] = c;
                buffercount++;
                state = PARSER_NAME;
            }
            break;
        case PARSER_KEYCODE:
            if(strchr(parser_alph_numb, c) != NULL){
                buffer[buffercount] = c;
                buffercount++;
                state = PARSER_KEYCODE;
            }
            else if(c == '\n'){
                buffer[buffercount] = 0;
                buffercount++;
                int i;
                sscanf(buffer, "%i", &i);
                kbmk_keybutton_set_keycode(current_button, i);
                buffercount = 0;
                state = PARSER_COMMAND;
            }
            else
                state = PARSER_ERROR;
            break;
        case PARSER_COMMAND:
            if(c == '\n'){
                buffer[buffercount] = 0;
                buffercount++;
                kbmk_keybutton_set_command(current_button, buffer);
                buffercount = 0;
                state = PARSER_POSITION;
            }
            else{
                buffer[buffercount] = c;
                buffercount++;
                state = PARSER_COMMAND;
            }
            break;
        case PARSER_POSITION:
            if(c == '\n'){
                buffer[buffercount] = 0;
                buffercount++;
                int x, y;
                sscanf(buffer, "%i %i", &x, &y);
                current_button->x = x;
                current_button->y = y;

                gtk_fixed_put(GTK_FIXED(mainwindow->grd_layout), current_button->box_outline, x, y);
                gtk_widget_show_all(mainwindow->win);

                buffercount = 0;
                state = PARSER_DASH;
            }
            else{
                buffer[buffercount] = c;
                buffercount++;
                state = PARSER_POSITION;
            }
            break;
        case PARSER_ERROR:
        default:
            break;
        }
    }



    fclose(fp);
}

void kbmk_mainwindow_save_file(kbmk_mainwindow_t *mainwindow, char *filename){
    FILE *fp = fopen(filename, "w");

    //list_node_kbmk_keybutton_p *tmp = mainwindow->layout;
    SLL_FOR_EACH(tmp IN mainwindow->layout){
        fprintf(fp, "-");
        fprintf(fp, "%s\n", tmp->element->keyname);
        fprintf(fp, "%i\n", tmp->element->keycode);
        fprintf(fp, "%s\n", tmp->element->command);
        fprintf(fp, "%i %i\n", tmp->element->x, tmp->element->y);
    }
    /*
    for(int i = 0;i < list_size_kbmk_keybutton_p(&mainwindow->keybuttons); i++){
        kbmk_keybutton_t *element = list_element_at_kbmk_keybutton_p(&mainwindow->keybuttons, i);
        fprintf(fp, "-\n");
        fprintf(fp, "%s\n", element->keyname);
        fprintf(fp, "%i\n", element->keycode);
        fprintf(fp, "%s\n", element->command);
        fprintf(fp, "%i %i\n", element->x, element->y);
    }*/

    fclose(fp);
}

static void btn_export_clicked(GtkWidget *wid, kbmk_mainwindow_t *win){
    GtkWidget *dialog;

    dialog = gtk_file_chooser_dialog_new ("Export File",
                                          win->win,
                                          GTK_FILE_CHOOSER_ACTION_SAVE,
                                          GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
                                          NULL);
    gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (dialog), TRUE);
    gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (dialog), "Untitled document");

    if(gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT){
        char *filename;

        filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
        kbmk_mainwindow_export_file(win, filename);
        g_free (filename);
    }

    gtk_widget_destroy (dialog);
}

void kbmk_mainwindow_export_file(kbmk_mainwindow_t *mainwindow, char *filename){
    FILE *fp = fopen(filename, "w");
    int index = gtk_combo_box_get_active(mainwindow->ch_keyboard);
    if(index == -1)
        fprintf(fp, "-event\n");
    else{
        fprintf(fp, "-%s\n", (*SLL_LIST_ELEMENT_AT(kbmk_keyboard_p)(mainwindow->keyboards, index))->event);
    }

    SLL_FOR_EACH(tmp IN mainwindow->layout){
                fprintf(fp, "%04i %s # %s\n", tmp->element->keycode, tmp->element->command, tmp->element->keyname);
    }

    fclose(fp);

}

static void btn_lock_clicked(GtkWidget *wid, kbmk_mainwindow_t *win){
    if(win->locked != 0){
        win->locked = 0;
        //gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(win->btn_lock), FALSE);
        gtk_button_set_label(GTK_BUTTON(win->btn_lock), kbmk_mainwindow_btn_lock_label_unlocked);
    }
    else{
        win->locked = 1;
        //gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(win->btn_lock), TRUE);
        gtk_button_set_label(GTK_BUTTON(win->btn_lock), kbmk_mainwindow_btn_lock_label_locked);
    }
}

void kbmk_mainwindow_list_keyboard(kbmk_mainwindow_t *mainwindow){
    DIR *dp;
    dp = opendir(kbmk_mainwindow_keybord_idpath);
    struct dirent *de;
    if(dp){
        while((de = readdir(dp)) != NULL){
            if(strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0){
                kbmk_keyboard_t *keyboard = kbmk_keyboard_new(de->d_name);
                SLL_LIST_PUSH_BACK(kbmk_keyboard_p)(mainwindow->keyboards, keyboard);
                if(keyboard->event != NULL){
                    g_print("%s\n", keyboard->event);
                    gtk_combo_box_append_text(GTK_COMBO_BOX(mainwindow->ch_keyboard), keyboard->name);
                }
            }
        }
    }
}
