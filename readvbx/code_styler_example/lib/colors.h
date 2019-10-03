/*
 * Basso Nicola
 * aka Lince99
 */
/*
 * library dedicated only to define constant string that change text color or background
 * on terminals that support ANSI escape characters
 */
/*
https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences
╔══════════╦════════════════════════════════╦═════════════════════════════════════════════════════════════════════════╗
║  Code    ║             Effect             ║                                   Note                                  ║
╠══════════╬════════════════════════════════╬═════════════════════════════════════════════════════════════════════════╣
║ 0        ║  Reset / Normal                ║  all attributes off                                                     ║
║ 1        ║  Bold or increased intensity   ║                                                                         ║
║ 2        ║  Faint (decreased intensity)   ║  Not widely supported.                                                  ║
║ 3        ║  Italic                        ║  Not widely supported. Sometimes treated as inverse.                    ║
║ 4        ║  Underline                     ║                                                                         ║
║ 5        ║  Slow Blink                    ║  less than 150 per minute                                               ║
║ 6        ║  Rapid Blink                   ║  MS-DOS ANSI.SYS; 150+ per minute; not widely supported                 ║
║ 7        ║  [[reverse video]]             ║  swap foreground and background colors                                  ║
║ 8        ║  Conceal                       ║  Not widely supported.                                                  ║
║ 9        ║  Crossed-out                   ║  Characters legible, but marked for deletion.  Not widely supported.    ║
║ 10       ║  Primary(default) font         ║                                                                         ║
║ 11–19    ║  Alternate font                ║  Select alternate font `n-10`                                           ║
║ 20       ║  Fraktur                       ║  hardly ever supported                                                  ║
║ 21       ║  Bold off or Double Underline  ║  Bold off not widely supported; double underline hardly ever supported. ║
║ 22       ║  Normal color or intensity     ║  Neither bold nor faint                                                 ║
║ 23       ║  Not italic, not Fraktur       ║                                                                         ║
║ 24       ║  Underline off                 ║  Not singly or doubly underlined                                        ║
║ 25       ║  Blink off                     ║                                                                         ║
║ 27       ║  Inverse off                   ║                                                                         ║
║ 28       ║  Reveal                        ║  conceal off                                                            ║
║ 29       ║  Not crossed out               ║                                                                         ║
║ 30–37    ║  Set foreground color          ║  See color table below                                                  ║
║ 38       ║  Set foreground color          ║  Next arguments are `5;n` or `2;r;g;b`, see below                       ║
║ 39       ║  Default foreground color      ║  implementation defined (according to standard)                         ║
║ 40–47    ║  Set background color          ║  See color table below                                                  ║
║ 48       ║  Set background color          ║  Next arguments are `5;n` or `2;r;g;b`, see below                       ║
║ 49       ║  Default background color      ║  implementation defined (according to standard)                         ║
║ 51       ║  Framed                        ║                                                                         ║
║ 52       ║  Encircled                     ║                                                                         ║
║ 53       ║  Overlined                     ║                                                                         ║
║ 54       ║  Not framed or encircled       ║                                                                         ║
║ 55       ║  Not overlined                 ║                                                                         ║
║ 60       ║  ideogram underline            ║  hardly ever supported                                                  ║
║ 61       ║  ideogram double underline     ║  hardly ever supported                                                  ║
║ 62       ║  ideogram overline             ║  hardly ever supported                                                  ║
║ 63       ║  ideogram double overline      ║  hardly ever supported                                                  ║
║ 64       ║  ideogram stress marking       ║  hardly ever supported                                                  ║
║ 65       ║  ideogram attributes off       ║  reset the effects of all of 60-64                                      ║
║ 90–97    ║  Set bright foreground color   ║  aixterm (not in standard)                                              ║
║ 100–107  ║  Set bright background color   ║  aixterm (not in standard)                                              ║
╚══════════╩════════════════════════════════╩═════════════════════════════════════════════════════════════════════════╝
 */
/*
 * \033[38;2;r;g;b
 * \033[48;2;r;g;b
 * for any supported color of text and background
 */

#ifndef COLORS_H
#define COLORS_H



//move cursor
#define gotoxy(x,y) printf("\033[%d;%dH", (x), (y))
/*void gotoxy(int x, int y) {
    printf("\033[%d;%dH", x, y);
}*/

//clear the screen
#ifndef ANSI_CLEAN
    #define ANSI_CLEAN "\x1b[H\x1b[J"
#endif

//font colors (foreground)
#ifndef ANSI_BLACK
    #define ANSI_BLACK "\x1b[30m"
#endif

#ifndef ANSI_RED
    #define ANSI_RED "\x1b[31m"
#endif

#ifndef ANSI_GREEN
    #define ANSI_GREEN  "\x1b[32m"
#endif

#ifndef ANSI_YELLOW
    #define ANSI_YELLOW  "\x1b[33m"
#endif

#ifndef ANSI_BLUE
    #define ANSI_BLUE    "\x1b[34m"
#endif

#ifndef ANSI_MAGENTA
    #define ANSI_MAGENTA "\x1b[35m"
#endif

#ifndef ANSI_CYAN
    #define ANSI_CYAN    "\x1b[36m"
#endif

#ifndef ANSI_WHITE
    #define ANSI_WHITE     "\x1b[37m"
#endif



//background colors
#ifndef ANSI_BG_BLACK
    #define ANSI_BG_BLACK     "\x1b[40m"
#endif

#ifndef ANSI_BG_RED
    #define ANSI_BG_RED     "\x1b[41m"
#endif

#ifndef ANSI_BG_GREEN
    #define ANSI_BG_GREEN   "\x1b[42m"
#endif

#ifndef ANSI_BG_YELLOW
    #define ANSI_BG_YELLOW  "\x1b[43m"
#endif

#ifndef ANSI_BG_BLUE
    #define ANSI_BG_BLUE    "\x1b[44m"
#endif

#ifndef ANSI_BG_MAGENTA
    #define ANSI_BG_MAGENTA "\x1b[45m"
#endif

#ifndef ANSI_BG_CYAN
    #define ANSI_BG_CYAN    "\x1b[46m"
#endif

#ifndef ANSI_BG_WHITE
    #define ANSI_BG_WHITE     "\x1b[47m"
#endif

#ifndef ANSI_REVERSE
    #define ANSI_REVESE     "\x1b[7m"
#endif


//font styles
#ifndef ANSI_BOLD
    #define ANSI_BOLD    "\x1b[1m"
#endif

#ifndef ANSI_ITALIC
    #define ANSI_ITALIC    "\x1b[3m"
#endif

#ifndef ANSI_UNDERLINE
    #define ANSI_UNDERLINE    "\x1b[4m"
#endif

#ifndef ANSI_NOT_OVERLINE
    #define ANSI_NOT_OVERLINE    "\x1b[24m"
#endif

#ifndef ANSI_OVERLINE
    #define ANSI_OVERLINE    "\x1b[53m"
#endif



//restore the original foreground and background colors
#ifndef ANSI_RESET
    #define ANSI_RESET   "\x1b[0m"
#endif

#endif //COLORS_H
