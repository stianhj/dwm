/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "D2Coding:size=9" };
static const char dmenufont[]       = "D2Coding:size=9";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_white[]       = "#ffffff";
static const char col_blueish[]     = "#aaaaff";
static const char col_red[]         = "#cf4c66";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_white, col_gray1, col_red  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "X", "Y", "Z" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered   isfloating   monitor */
	{ "Sxiv",     NULL,       NULL,       0,            1,		 1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int decorhints  = 1;    /* 1 means respect decoration hints */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "urxvt", NULL };
static const char *term_samedir_cmd[] = { "urxvt-same-dir.sh", NULL };
static const char *ncmpcppcmd[]  = { "urxvt", "-e", "ncmpcpp", NULL };
static const char *muttcmd[]  = { "urxvt", "-e", "mutt", NULL };

static const char *maimscmd[]  = { "maims", NULL };
static const char *maimfcmd[]  = { "maimf", NULL };

static const char scratchpadname[] = "scratchpad";
static const char *mathtermcmd[] = { "xterm", "-class", "mathterm", "-title", scratchpadname, "-e", "qalc", NULL };

static const char *vol_up[] =     { "/home/x/.local/bin/vol.sh", "up", NULL };
static const char *vol_down[] =   { "/home/x/.local/bin/vol.sh", "down", NULL };
static const char *vol_toggle[] = { "/home/x/.local/bin/vol.sh", "toggle", NULL };
static const char *backlight_toggle[]  = { "/home/x/.local/bin/toggle-backlight.sh", NULL };

static const char *mpc_toggle[] = { "mpc", "toggle", NULL };
static const char *mpc_next[] =   { "mpc", "next", NULL };
static const char *mpc_prev[] =   { "mpc", "prev", NULL };
static const char *mpc_seek_forward[] = { "mpc", "seek", "+0:10", NULL };
static const char *mpc_seek_back[] =    { "mpc", "seek", "-0:10", NULL };
static const char *mpc_seek_start[] =   { "mpc", "seek",  "0:00", NULL };

static const char *rofi_emoji[] = { "rofi", "-show", "emoji", "-modi", "emoji", "-theme", "dracula_emoji", "-matching", "normal", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ ControlMask|ShiftMask,        XK_Return, spawn,          {.v = term_samedir_cmd } },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = ncmpcppcmd } },
	{ MODKEY|ControlMask,           XK_m,      spawn,          {.v = muttcmd } },

	{ MODKEY,                       XK_a,      togglescratch,  {.v = mathtermcmd } },

	{ MODKEY,                       XK_F1,     spawn,          {.v = vol_toggle } },
	{ MODKEY,                       XK_F2,     spawn,          {.v = vol_down } },
	{ MODKEY,                       XK_F3,     spawn,          {.v = vol_up } },

	{ MODKEY,                       XK_F5,     spawn,          {.v = mpc_toggle } },
	{ MODKEY,                       XK_F6,     spawn,          {.v = mpc_prev } },
	{ MODKEY,                       XK_F7,     spawn,          {.v = mpc_next } },
	{ MODKEY|ShiftMask,             XK_F5,     spawn,          {.v = mpc_seek_start } },
	{ MODKEY|ShiftMask,             XK_F6,     spawn,          {.v = mpc_seek_back } },
	{ MODKEY|ShiftMask,             XK_F7,     spawn,          {.v = mpc_seek_forward } },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = backlight_toggle } },

	{ MODKEY|ShiftMask,             XK_e,      spawn,          {.v = rofi_emoji } },

	{ 0,                            XK_Print,  spawn,          {.v = maimscmd } },
	{ ShiftMask,                    XK_Print,  spawn,          {.v = maimfcmd } },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	//{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	//{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_0,                      9)
	TAGKEYS(                        XK_y,                      10)
	TAGKEYS(                        XK_z,                      11)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

