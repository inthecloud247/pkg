/* see LICENSE for copyright and license */

#ifndef CONFIG_H
#define CONFIG_H

/** buttons **/
#define MOD1            Mod1Mask    /* ALT key */
#define CONTROL         ControlMask /* Control key */
#define SHIFT           ShiftMask   /* Shift key */

/** generic settings **/
#define MASTER_SIZE     0.52
#define SHOW_PANEL      False     /* show panel by default on exec */
#define TOP_PANEL       True      /* False mean panel is on bottom */
#define PANEL_HEIGHT    0         /* 0 for no space for panel, thus no panel */
#define DEFAULT_MODE    TILE      /* initial layout/mode: TILE MONOCLE BSTACK GRID FLOAT */
#define ATTACH_ASIDE    False     /* False means new window is master */
#define FOLLOW_WINDOW   False     /* Follow the window when moved to a different desktop */
#define FOLLOW_MOUSE    False     /* Focus the window the mouse just entered */
#define CLICK_TO_FOCUS  False     /* Focus an unfocused window when clicked  */
#define BORDER_WIDTH    2         /* window border width */
#define FOCUS           "#eee8d5" /* focused window border color    */
#define UNFOCUS         "#fdf6e3" /* unfocused window border color  */
#define MINWSZ          50        /* minimum window size in pixels  */
#define DEFAULT_DESKTOP 0         /* the desktop to focus initially */
#define DESKTOPS        6         /* number of desktops - edit DESKTOPCHANGE keys to suit */

/**
 * open applications to specified desktop with specified mode.
 * if desktop is negative, then current is assumed
 */
static const AppRule rules[] = { \
    /*  class     desktop  follow  float */
    { "MPlayer",     -1,    False,  True  },
    { "Gimp",        -1,    False,  True  },
};

/* helper for spawning shell commands */
#define SHCMD(cmd) {.com = (const char*[]){"/bin/sh", "-c", cmd, NULL}}

/**
 * custom commands
 * must always end with '.., NULL };'
 */
static const char *termcmd[] = { "urxvtc",     NULL };

static const char font[]            = "-*-terminus-medium-r-*-*-16-*-*-*-*-*-*-*";
static const char normbgcolor[]     = "#fdf6e3";
static const char normfgcolor[]     = "#657b83";
static const char selbgcolor[]      = "#fdf6e3";
static const char selfgcolor[]      = "#cb4b16";
static const char *menucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };

#define DESKTOPCHANGE(K,N) \
    {  MOD1,             K,              change_desktop, {.i = N}}, \
    {  MOD1|ShiftMask,   K,              client_to_desktop, {.i = N}},

/**
 * keyboard shortcuts
 */
static Key keys[] = {
    /* modifier          key            function           argument */
    {  MOD1,             XK_BackSpace,  focusurgent,       {NULL}},
    {  MOD1|SHIFT,       XK_c,          killclient,        {NULL}},
    {  MOD1,             XK_j,          next_win,          {NULL}},
    {  MOD1,             XK_k,          prev_win,          {NULL}},
    {  MOD1,             XK_h,          resize_master,     {.i = -10}}, /* decrease size in px */
    {  MOD1,             XK_l,          resize_master,     {.i = +10}}, /* increase size in px */
    {  MOD1,             XK_Return,     swap_master,       {NULL}},
    {  MOD1|SHIFT,       XK_j,          move_down,         {NULL}},
    {  MOD1|SHIFT,       XK_k,          move_up,           {NULL}},
    {  MOD1|SHIFT,       XK_t,          switch_mode,       {.i = TILE}},
    {  MOD1|SHIFT,       XK_f,          switch_mode,       {.i = FLOAT}},
    {  MOD1|CONTROL,     XK_r,          quit,              {.i = 0}}, /* quit with exit value 0 */
    {  MOD1|CONTROL,     XK_q,          quit,              {.i = 1}}, /* quit with exit value 1 */
    {  MOD1|SHIFT,       XK_Return,     spawn,             {.com = termcmd}},
    {  MOD1,             XK_p,          spawn,             {.com = menucmd}},
       DESKTOPCHANGE(    XK_1,                             0)
       DESKTOPCHANGE(    XK_2,                             1)
       DESKTOPCHANGE(    XK_3,                             2)
       DESKTOPCHANGE(    XK_4,                             3)
       DESKTOPCHANGE(    XK_5,                             4)
       DESKTOPCHANGE(    XK_6,                             5)
};

/**
 * mouse shortcuts
 */
static Button buttons[] = {
    {  MOD1,             Button1,       mousemotion,       {.i = MOVE}},
    {  MOD1|SHIFT,       Button1,       mousemotion,       {.i = RESIZE}},
};
#endif
