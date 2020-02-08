#include <gtk/gtk.h>

GtkWidget *window;
GtkWidget *label;
gboolean timer_handler();

void destroy(GtkWidget *widget,gpointer data)
{
    gtk_main_quit();
}

gboolean showtime()
{
    GDateTime *date_time;
    gchar *dt_format;
    date_time = g_date_time_new_now_local();
    dt_format = g_date_time_format(date_time, "%H:%M:%S");   
    gtk_label_set_text(GTK_LABEL(label),dt_format);
    g_free (dt_format);
    return TRUE;
}
int main(int argc,char *argv[])
{
    
    gtk_init (&argc, &argv);
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window),800,320);
    
    g_signal_connect(window, "destroy",G_CALLBACK (destroy), NULL);

    GError **err;
    gtk_window_set_icon_from_file (GTK_WINDOW(window),"icon.png",err);

    gtk_window_set_title(GTK_WINDOW(window),"clock");
    gtk_window_set_keep_above(GTK_WINDOW (window), TRUE);
 
    label = gtk_label_new_with_mnemonic ("");

    PangoAttrList *attrls;
    PangoAttribute *attr;
    PangoFontDescription *df;
    
    attrls = pango_attr_list_new ();
    df = pango_font_description_new();
    pango_font_description_set_family(df, "Ani");
    pango_font_description_set_size(df, 100 * PANGO_SCALE);
    pango_font_description_set_weight(df, PANGO_WEIGHT_BOLD);

    attr = pango_attr_font_desc_new(df);
    pango_attr_list_insert(attrls, attr);
    pango_font_description_free(df);

    //font color
    attr = pango_attr_foreground_new(65535,0,0);
    attr->start_index = 6;
    attr->end_index = 8;
    pango_attr_list_change(attrls, attr);
    gtk_label_set_attributes(GTK_LABEL(label), attrls);
    pango_attr_list_unref(attrls);

    gtk_container_add (GTK_CONTAINER (window), label);
    
    gtk_widget_show_all (window);
    gtk_widget_set_opacity (GTK_WIDGET (window), 0.5);
    
    g_timeout_add_seconds (1, (GSourceFunc) showtime,NULL);

    gtk_main ();
    return 0;
}


