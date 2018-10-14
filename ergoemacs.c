// Alt+ijkl cursor movement

int editorReadKey() {
  int nread;
  char c;
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    if (nread == -1 && errno != EAGAIN) die("read");
  }
  if (c == '\x1b') {
    char seq[3];
    if (read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
    /* editorSetStatusMessage("%c", seq[0]); */

    switch (seq[0]) {
    case 'i': return ARROW_UP;
    case 'k': return ARROW_DOWN;
    case 'l': return ARROW_RIGHT;
    case 'j': return ARROW_LEFT;
    case 'h': return HOME_KEY;
    case ';': return END_KEY;
    }

    if (read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';

// etc
