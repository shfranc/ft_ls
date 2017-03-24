#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>

int	main(int argc, char **argv)
{

    struct winsize w;
    // struct termios settings;
    char *s;
    
    // tcgetattr(0, &settings);

	// settings.c_oflag |= (OPOST | ONOCR);

	// tcsetattr(0, 1, &settings);

    ioctl(0, TIOCGWINSZ, &w);
    // ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    
    printf ("lines %d\n", w.ws_row);
    printf ("columns %d\n", w.ws_col);

    s = malloc(w.ws_col + 1 +1);
    bzero(s, w.ws_col + 1);
    memset(s, 'a', w.ws_col);
    printf("%s", s);




	return 0;
}

// int tcgetattr(int fildes, struct termios *termios_p);

139
long_format_details_part2.c = 27
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
classic_display.c		long_display.o			main.c				parsing_options.c
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
installer.failurerequests = 25
tty.BoseAE2SoundLink-SPPDev-1 = 29
==> 4 colonnes + vide

standalone = 10

=> 5 colonnes + vide
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

installer.failurerequests
un_nom_de_fichier_particulierement_long_et_plus_encore_et_encore_et_encore = 74
resources_ft_ls.pdf
fillit_reference

/usr/bin/wall
116/14 = 8.2 -1 = 7.2
2 fil

ft_putchar_fd.c 16
E9E04EAB-C17D-45B7-AA9F-09DA476D50AB_OUT
