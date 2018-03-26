# Bob the UTF-8 Encoder!
"Can we build it?"
    
    "Derp dee derp!"
    
It takes like 2 seconds, all you need is your machine's C compiler.

# Build Bob
Download bob.c and (from its directory) enter:

    $ make bob

# Install Bob
Put the binary on your $PATH to install Bob:

	$ sudo mv bob /usr/bin/bob
	
# Use Bob
	
	$ bob

# What I wanted
To be able to punch people in the face who tell me I should use a certain text editor and say,
	
	"I use BOB, Biotch."
	
A truly minimal console-based text editor that a beginning programmer can easily read, comprehend and modify.

# What I got
![](https://github.com/porkostomus/bobs-text-editor/blob/master/shot-2018-03-25_23-08-51.png)

Here it is inside of [Cool Retro Term](https://github.com/Swordfish90/cool-retro-term), cuz that's how I roll.

# How it works
Normally, the computer waits for you to type a whole line and press enter, and then it does a thing. We need to change the input mode so that our interface can respond to every key in real time instead. We call this "raw mode", and is defined by this function:

    void enableRawMode() {
        if (tcgetattr(STDIN_FILENO, &E.orig_termios) == -1) die("tcgetattr");
        atexit(disableRawMode);
        struct termios raw = E.orig_termios;
        raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
        raw.c_oflag &= ~(OPOST);
        raw.c_cflag |= (CS8);
        raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
        raw.c_cc[VMIN] = 0;
        raw.c_cc[VTIME] = 1;
        if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
    }

    void disableRawMode() {
        if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1)
        die("tcsetattr");
    }
    
We have also disabled Ctrl-C, Ctrl-Z, Ctrl-S, Ctrl-Q, and Ctrl-V so those system signals will not interfere with our program. But don't worry, we stored the original settings so that we can put them back when we're done.

## Define input keys...

    int editorReadKey() {
        int nread;
        char c;
        while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
            if (nread == -1 && errno != EAGAIN) die("read");
        }
        if (c == '\x1b') {
            char seq[3];
            if (read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
            if (read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';
            if (seq[0] == '[') {
                if (seq[1] >= '0' && seq[1] <= '9') {
                    if (read(STDIN_FILENO, &seq[2], 1) != 1) return '\x1b';
                    if (seq[2] == '~') {
                        switch (seq[1]) {
                            case '1': return HOME_KEY;
                            case '3': return DEL_KEY;
                            case '4': return END_KEY;
                            case '5': return PAGE_UP;
                            case '6': return PAGE_DOWN;
                            case '7': return HOME_KEY;
                            case '8': return END_KEY;
                        }
                    }
                } else {
                    switch (seq[1]) {
                        case 'A': return ARROW_UP;
                        case 'B': return ARROW_DOWN;
                        case 'C': return ARROW_RIGHT;
                        case 'D': return ARROW_LEFT;
                        case 'H': return HOME_KEY;
                        case 'F': return END_KEY;
                    }
                }
            } else if (seq[0] == 'O') {
            switch (seq[1]) {
                case 'H': return HOME_KEY;
                case 'F': return END_KEY;
            }
        }
        return '\x1b';
        } else {
            return c;
        }
    }

## ...and how they are processed

    void editorProcessKeypress() {
        static int quit_times = 1;
        int c = editorReadKey();
        switch (c) {
            case '\r':
                editorInsertNewline();
                break;
            case CTRL_KEY('q'):
                if (E.dirty && quit_times > 0) {
                    editorSetStatusMessage("Unsaved changes! Ctrl-Q to confirm.");
                    quit_times--;
                    return;
                }
	            printf("\r\n");
                exit(0);
                break;
            case CTRL_KEY('s'):
                editorSave();
                break;
            case HOME_KEY:
                E.cx = 0;
                break;
            case END_KEY:
                if (E.cy < E.numrows)
                E.cx = E.row[E.cy].size;
                break;
            case BACKSPACE:
            case CTRL_KEY('h'):
            case DEL_KEY:
                if (c == DEL_KEY) editorMoveCursor(ARROW_RIGHT);
                editorDelChar();
                break;
            case PAGE_UP:
            case PAGE_DOWN:
                {
                    if (c == PAGE_UP) {
                        E.cy = E.rowoff;
                    } else if (c == PAGE_DOWN) {
                        E.cy = E.rowoff + E.screenrows - 1;
                        if (E.cy > E.numrows) E.cy = E.numrows;
                    }
                    int times = E.screenrows;
                    while (times--)
                        editorMoveCursor(c == PAGE_UP ? ARROW_UP : ARROW_DOWN);
                }
                break;
            case ARROW_UP:
            case ARROW_DOWN:
            case ARROW_LEFT:
            case ARROW_RIGHT:
                editorMoveCursor(c);
                break;
            case CTRL_KEY('l'):
            case '\x1b':
                break;
            default:
                editorInsertChar(c);
                break;
        }
        quit_times = 1;
    }

# Credits 
[Salvatore Sanfilippo](https://github.com/antirez/kilo)

[Snaptoken]( https://viewsourcecode.org/snaptoken/kilo/)
