# Bob the text editor!
"Can we build it?"
    
    Derp de der...
    
As long as your computer has a C compiler.

# To build bob:
Download bob.c and (from its directory) enter:

    $ make bob

Put the binary on your $PATH to install bob. Bob is under 15 KB, aiming to be the smallest fully-functional (see below) editor.

# What I wanted:
A minimal console-based text editor like Vim or Nano, written such that a beginning programmer (i.e. me!) can easily read it and understand how it works. Other so-called "minimal" editors still have loads of stuff like search and syntax-highlighting which, while useful, are not part of what I (for the purpose of this project) am considering minimal. Once we have the stupid little core in place with only basic functionality, we can work on adding features as plug-ins, because I always want this core version to exist.

# What I got:
![](https://github.com/porkostomus/bobs-text-editor/blob/master/shot-2018-03-25_23-08-51.png)
Pretty much nailed it.

# How it works
Normally the computer waits for you to type a line and press enter. The first thing we have to do is disable that behavior so the program updates on every key press instead. We call this "raw mode", and is defined by this function:

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
    
We have also disabled Ctrl-C, Ctrl-Z, Ctrl-S, Ctrl-Q, Ctrl-V, and Ctrl-M so those system signals will not interfere with our program. But don't worry, we stored the original settings so that it can put it back to normal on exit.
