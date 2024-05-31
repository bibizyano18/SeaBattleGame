#include <ncurses.h>
#include <ApplicationServices/ApplicationServices.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

// всё, что связано с улавливанием нажатия на клавиши

void setTerminalRawMode(bool enable) {
    static struct termios oldt, newt;
    if (enable) {
        tcgetattr(STDIN_FILENO, &oldt); // Save current terminal settings
        newt = oldt;
        cfmakeraw(&newt); // Set terminal to raw mode
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore terminal settings
    }
}
int kbhit() { // if button pressed
    struct termios oldt, newt;
    int ch;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    
    return 0;
}
int ButtonPressed() {
    char key;

    setTerminalRawMode(true); // Enable raw mode
    while (true) {
        if (kbhit()) { // Check if a key was pressed
            key = getchar(); // Get the pressed key
            
            if (key == 27) { // Escape character for special keys
                getchar(); // Skip the '[' character
                key = getchar();
                switch (key) {
                    case 'A': // Arrow up
                        setTerminalRawMode(false); // Restore terminal mode
                        return 0;
                    case 'B': // Arrow down
                        setTerminalRawMode(false); // Restore terminal mode
                        return 1;
                    case 'D': // Arrow left
                        setTerminalRawMode(false); // Restore terminal mode
                        return 2;
                    case 'C': // Arrow right
                        setTerminalRawMode(false); // Restore terminal mode
                        return 3;
                }
            } else if (key == 13) { // Enter
                setTerminalRawMode(false); // Restore terminal mode
                return 4;
            } else if (key == 'r' || key == 'R') { // R
                setTerminalRawMode(false); // Restore terminal mode
                return 5;
            }
        }
    }
}
int ButtonPressedNum() {
    char key;

    setTerminalRawMode(true); // Enable raw mode
    while (true) {
        if (kbhit()) { // Check if a key was pressed
            key = getchar(); // Get the pressed key
            switch (key) {
                case '0':
                    setTerminalRawMode(false); // Restore terminal mode
                    return 0;
                case '1':
                    setTerminalRawMode(false); // Restore terminal mode
                    return 1;
                case '2':
                    setTerminalRawMode(false); // Restore terminal mode
                    return 2;
                case '3':
                    setTerminalRawMode(false); // Restore terminal mode
                    return 3;
                case '4':
                    setTerminalRawMode(false); // Restore terminal mode
                    return 4;
            }
        }
    }
}