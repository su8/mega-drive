/* Example plugin for Audacious 3.5 */
/* Will not work with earlier Audacious versions
 * aud_get_string()
sizeof array / sizeof array[0] 
 *             gcc -Wall -O2 -fPIC -shared -z defs `pkg-config --cflags --libs audacious` -o example.so example.c 
 * */

#include <stdio.h>

#include <audacious/drct.h>
#include <audacious/misc.h>
#include <audacious/plugin.h>
#include <audacious/preferences.h>

#include <libaudcore/hook.h>

/* Default values for any configurable settings */
/* Note that Boolean values have to be in ALL CAPS */
const char * const plugin_defaults[] = {
   "print_filenames", "TRUE",
   "custom_string", "I am a custom string",
   NULL
};

/* Define a simple dialog box for those settings */
/* More complex layouts are possible; see <audacious/preferences.h> */
const PreferencesWidget prefs_widgets[] = {
  { WIDGET_CHK_BTN, "Print song filenames",
    .cfg_type = VALUE_BOOLEAN, .csect = "example", .cname = "print_filenames" },
  { WIDGET_ENTRY, "Print custom string",
    .cfg_type = VALUE_STRING, .csect = "example", .cname = "custom_string" }
};

/* Also for the settings dialog; mostly uninteresting */
const PluginPreferences plugin_prefs = {
   .widgets = prefs_widgets,
   .n_widgets = ARRAY_LEN (prefs_widgets)
};

/* Function to be called when the song changes */
void song_changed (void * data1, void * data2)
{
    /* Get some basic info about the currently playing song */
    /* Note the str_unref(); without it we would be leaking memory */
    char * title = aud_drct_get_title ();
    printf ("Title: %s\n", title);
    str_unref (title);

    /* Example use of a configurable Boolean setting */
    if (aud_get_bool ("example", "print_filenames"))
    {
        char * filename = aud_drct_get_filename ();
        printf ("Filename: %s\n", filename);
        str_unref (filename);
    }

    /* Example use of a configurable string setting */
    char * custom = aud_get_str ("example", "custom_string");
    printf ("Custom string: %s\n", custom);
    str_unref (custom);
}

/* Initialization function, called at plugin startup */
bool_t plugin_init (void)
{
    /* Register the default settings declared earlier */
    aud_config_set_defaults ("example", plugin_defaults);

    /* Connect our song-change function to the "playback begin" event */
    hook_associate ("playback begin", song_changed, NULL);

    /* Signify that the plugin was successfully initialized */
    return TRUE;
}

/* Cleanup function, called at plugin shutdown */
void plugin_cleanup (void)
{
    /* Disconnect our song-change function (this is important) */
    hook_dissociate ("playback begin", song_changed);
}

/* Plugin header with various and sundry information */
AUD_GENERAL_PLUGIN
(
    /* Name to be displayed in list of available plugins */
    .name = "Example Plugin",

    /* Text to be displayed in "About Example Plugin" dialog box */
    .about_text = "This is an example plugin",

    /* Pointer to layout for settings dialog */
    .prefs = & plugin_prefs,

    /* Pointer to initialization function */
    .init = plugin_init,

    /* Pointer to cleanup function */
    .cleanup = plugin_cleanup
)
