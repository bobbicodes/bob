# Bob the Editor!

![Repl](2018-10-18-033538_1366x768_scrot.png)

[Watch screencast](https://youtu.be/f_1ZLgQtaWg)

## "Can we build it?"
    
>"Derp de derrrrr!"
    
It takes like 2 seconds, all you need is a C compiler. To check if it's there type:

	$ cc --version

Install it (if needed) with:

    $ sudo apt-get install gcc make

# Build Bob

Download bob.c and (from its directory) enter:

    $ make bob

# Install Bob

Put the binary on your $PATH to install Bob:

	$ mv bob ~/bin/bob
	
# Use Bob
	
	$ bob [FILENAME]

# Clojure evaluation

* Run the `repl` script (set to executable with `chmod +x repl`) to connect to a Clojurescript REPL via JavaScriptCore.
You must have `inotifywait` installed on your machine, as well as [Planck](http://planck-repl.org/).

* Pressing **Ctrl+e** evaluates the whole buffer and prints the result of the last expression.

# What I wanted

A truly minimal console-based text editor that a beginning programmer can easily read, comprehend and modify.

## What I actually wanted

When people tell me to use a certain text editor - to be able to punch them in the face and say,
	
>"I use BOB, Biotch."

# TODO:

Figure out how to use pREPL and show results right in status bar.
