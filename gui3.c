#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
static void entry_changed    (GtkEditable*, GtkAssistant*);
static void button_toggled   (GtkCheckButton*, GtkAssistant*);
static void button_clicked   (GtkButton*, GtkAssistant*);
static void assistant_cancel (GtkAssistant*, gpointer);
static void assistant_close  (GtkAssistant*, gpointer);
GtkWidget* button;
int node;
typedef struct {
	GtkWidget *widget;
	gint index;
	const gchar *title;
	GtkAssistantPageType type;
	gboolean complete;
} PageInfo;

int main (int argc,
		char *argv[])
{
	GtkWidget *assistant, *entry, *label, *button, *progress, *hbox;
	guint i;
	PageInfo page[6] = {
		{ NULL, -1, "Introduction",                 GTK_ASSISTANT_PAGE_INTRO,    TRUE},
		{ NULL, -1, "Projects",                     GTK_ASSISTANT_PAGE_CONTENT,  TRUE},
		{ NULL, -1, "Profit For Projects",          GTK_ASSISTANT_PAGE_CONTENT,  TRUE},
		{ NULL, -1, "Prerequisites For Projects",   GTK_ASSISTANT_PAGE_CONTENT,  TRUE},
		{ NULL, -1, "Click the Button",             GTK_ASSISTANT_PAGE_PROGRESS, FALSE},
		{ NULL, -1, "Confirmation",                 GTK_ASSISTANT_PAGE_CONFIRM,  TRUE},
	};

	gtk_init (&argc, &argv);

	/* Create a new assistant widget with no pages. */
	assistant = gtk_assistant_new ();
	gtk_widget_set_size_request (assistant, 500, 500);
	gtk_window_set_title (GTK_WINDOW (assistant), "Project Selection Problem");
	g_signal_connect (G_OBJECT (assistant), "destroy",
			G_CALLBACK (gtk_main_quit), NULL);

	page[0].widget = gtk_label_new ("The \"Project Selection Problem\"is to \n"\
			"select a feasible set of projects with \n"\
			"MAXIMUM PROFIT!\n"\
			"It is implemented using 'Max Flow Graphs'\n"\
			"using Ford Fulkerson Algorithm\n");
	page[1].widget = gtk_label_new ("Total no. of projects are 9 ");
	page[2].widget = gtk_label_new ("Profit!");
	page[3].widget = gtk_label_new ("Prerequisites");
	page[4].widget = gtk_alignment_new (0.5, 0.5, 0.0, 0.0);
	page[5].widget = gtk_label_new ("OUTPUT\n"\
			"it is time to leave!");

	/* Create the necessary widgets for the fourth page. The, Attach the progress bar
	 * to the GtkAlignment widget for later access.*/
	button = gtk_button_new_with_label ("Click me!");

	progress = gtk_progress_bar_new ();
	hbox = gtk_hbox_new (FALSE, 5);
	gtk_box_pack_start (GTK_BOX (hbox), progress, TRUE, FALSE, 5);
	gtk_box_pack_start (GTK_BOX (hbox), button, FALSE, FALSE, 5);
	gtk_container_add (GTK_CONTAINER (page[4].widget), hbox);
	g_object_set_data (G_OBJECT (page[4].widget), "pbar", (gpointer) progress);
	
	/* Add six pages to the GtkAssistant dialog. */
	for (i = 0; i < 6; i++)
	{
		page[i].index = gtk_assistant_append_page (GTK_ASSISTANT (assistant),
				page[i].widget);
		gtk_assistant_set_page_title (GTK_ASSISTANT (assistant),
				page[i].widget, page[i].title);
		gtk_assistant_set_page_type (GTK_ASSISTANT (assistant),
				page[i].widget, page[i].type);

		/* Set the introduction and conclusion pages as complete so they can be
		 * incremented or closed. */
		gtk_assistant_set_page_complete (GTK_ASSISTANT (assistant),
				page[i].widget, page[i].complete);
	}

	/* Update whether page 4 are complete based upon whether there is
	   the progress bar
	 * is completely filled. */
	g_signal_connect (G_OBJECT (button), "clicked",
			G_CALLBACK (button_clicked), (gpointer) assistant);
	g_signal_connect (G_OBJECT (assistant), "cancel",
			G_CALLBACK (assistant_cancel), NULL);

	g_signal_connect (G_OBJECT (assistant), "close",
			G_CALLBACK (assistant_close), NULL);
	gtk_widget_show_all (assistant);
	GtkWidget *gtk_check_button_new( void );
	gtk_main ();
	return 0;
}

/* Fill up the progress bar, 10% every second when the button is clicked. Then,
 * set the page as complete when the progress bar is filled. */
	static void
button_clicked (GtkButton *button,
		GtkAssistant *assistant)
{
	GtkProgressBar *progress;
	GtkWidget *page;
	gdouble percent = 0.0;

	gtk_widget_set_sensitive (GTK_WIDGET (button), FALSE);
	page = gtk_assistant_get_nth_page (assistant, 4);
	progress = GTK_PROGRESS_BAR (g_object_get_data (G_OBJECT (page), "pbar"));

	while (percent <= 100.0)
	{
		gchar *message = g_strdup_printf ("%.0f%% Complete", percent);
		gtk_progress_bar_set_fraction (progress, percent / 100.0);
		gtk_progress_bar_set_text (progress, message);

		while (gtk_events_pending ())
			gtk_main_iteration ();

		g_usleep (500000);
		percent += 5.0;
	}

	gtk_assistant_set_page_complete (assistant, page, TRUE);
}

/* If the dialog is cancelled, delete it from memory and then clean up after
 * the Assistant structure. */
 static void assistant_cancel (GtkAssistant *assistant,
		gpointer data)
{
	gtk_widget_destroy (GTK_WIDGET (assistant));
}

/* This function is where you would apply the changes and destroy the assistant. */
static void assistant_close (GtkAssistant *assistant,
		gpointer data)
{
	gtk_widget_destroy (GTK_WIDGET (assistant));
}
