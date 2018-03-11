/* XF86 Media Keys */
/*#include <X11/XF86keysym.h>*/

/* appearance */
#define NUMCOLORS 12
static const char colors[NUMCOLORS][ColLast][9] = {
  /* border   foreground  background */
  { "#282a2e", "#373b41", "#282a2e" },
  { "#1793D1", "#c5c8c6", "#282a2e" },
  { "#dc322f", "#1d1f21", "#282a2e" },
  { "#282a2e", "#282a2e", "#282a2e" },
  { "#282a2e", "#1d1f21", "#282a2e" },
  { "#282a2e", "#cc6666", "#282a2e" },
  { "#282a2e", "#b5bd68", "#282a2e" },
  { "#282a2e", "#de935f", "#282a2e" },
  { "#282a2e", "#f0c674", "#282a2e" },
  { "#282a2e", "#81a2be", "#282a2e" },
  { "#282a2e", "#b294bb", "#282a2e" },
  { "#282a2e", "#8abeb7", "#282a2e" },
};
static const char font[]            = "Cantarell 9";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int taglinepx = 1;        /* tag underline height   */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const unsigned int gappx     = 5;        /* gap pixel between windows */

/* tagging */
static const char *tags[] = { "web", "dev", "misc" };

static const Rule rules[] = {
    /* class             instance    tags mask    iscentered    isfloating   monitor */
    { "Firefox",         NULL,       1 << 0,      False,        True,        -1 },
    { "Tor Browser",     NULL,       1 << 0,      False,        True,        -1 },
    { "Gimp",            NULL,       1 << 2,      False,        True,        -1 },
    { "URxvt",           NULL,       0,           True,         False,       -1 },
    /*{ "Thunar",          NULL,       0,           True,         True,        -1 },*/
    { "Qbittorrent",     NULL,       1 << 2,      False,        True,        -1 },
    { "Wine",            NULL,       1 << 2,      False,        True,        -1 }
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[T]",      tile },    /* tiling mode */
    { "[F]",      NULL },    /* floating mode */
};

/* key definitions */
#define MODKEY Mod1Mask   /* alt   */
#define MODKEY2 Mod4Mask  /* super */
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/bin/bash", "-c", cmd, NULL } }
#define BASH_EXEC(cmd) { "/usr/bin/bash", "-c", cmd, NULL }
/*#define ALSA_MIXER(plus_minus) BASH_EXEC("amixer --quiet sset Master 5%"plus_minus" unmute")*/

/* commands */
static const char *dmenucmd[]    =   { "dmenu_run", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG], "-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
static const char *thunar[]      =   { "thunar", NULL };
/*static const char *mutt[]        =   BASH_EXEC("sakura --execute=\"mutt -F $HOME/.config/mutt/muttrc\"");*/
static const char *urxvt[]       =   { "urxvtc", NULL };
static const char *torbundle[]   =   BASH_EXEC("tor-browser-en --dir=/tmp");
static const char *qbittorrent[] =   { "qbittorrent", NULL };

/* audio */
/*static const char *vol_up[]      =   ALSA_MIXER("+");*/
/*static const char *vol_down[]    =   ALSA_MIXER("-");*/

static Key keys[] = {
    /* modifier                     key                           function        argument */
    { MODKEY|ControlMask,           XK_j,                         pushdown,       {0} },
    { MODKEY|ControlMask,           XK_k,                         pushup,         {0} },
    /*{ 0,                            XF86XK_AudioRaiseVolume,      spawn,          {.v = vol_up } },*/
    /*{ 0,                            XF86XK_AudioLowerVolume,      spawn,          {.v = vol_down } },*/
    { MODKEY2,                      XK_q,                         spawn,          {.v = qbittorrent } },
    /*{ MODKEY2,                      XK_p,                         spawn,          {.v = pdf2img } },*/
    { MODKEY2,                      XK_s,                         spawn,          {.v = torbundle } },
    /*{ MODKEY2,                      XK_f,                         spawn,          {.v = firefox } },*/
    { MODKEY2,                      XK_x,                         spawn,          {.v = urxvt } },
    /*{ MODKEY2,                      XK_m,                         spawn,          {.v = mutt } },*/
    { MODKEY2,                      XK_t,                         spawn,          {.v = thunar } },
    { MODKEY,                       XK_p,                         spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_b,                         togglebar,      {0} },
    { MODKEY,                       XK_j,                         focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,                         focusstack,     {.i = -1 } },
    { MODKEY,                       XK_i,                         incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,                         incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,                         setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,                         setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_Return,                    zoom,           {0} },
    { MODKEY,                       XK_Tab,                       view,           {0} },
    { MODKEY,                       XK_c,                         killclient,     {0} },
    { MODKEY,                       XK_t,                         setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_f,                         setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_space,                     setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,                     togglefloating, {0} },
    { MODKEY,                       XK_0,                         view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,                         tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,                     focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period,                    focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,                     tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period,                    tagmon,         {.i = +1 } },
    TAGKEYS(                        XK_1,                                         0)
    TAGKEYS(                        XK_2,                                         1)
    TAGKEYS(                        XK_3,                                         2)
    TAGKEYS(                        XK_4,                                         3)
    TAGKEYS(                        XK_5,                                         4)
    TAGKEYS(                        XK_6,                                         5)
    TAGKEYS(                        XK_7,                                         6)
    TAGKEYS(                        XK_8,                                         7)
    TAGKEYS(                        XK_9,                                         8)
    { MODKEY|ShiftMask,             XK_q,                         quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = urxvt } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
