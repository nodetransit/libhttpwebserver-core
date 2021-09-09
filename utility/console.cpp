#include "console.hpp"

namespace nt { namespace utility { namespace console {

#if defined(LOSER)
int
rejectkbhit(char*& destination)
{
    size_t count;

    while (!(count = kbhit()));

    destination = (char*)calloc(count + 1, sizeof(char));
    char* tmp = destination;

    while (count-- > 0) {
        char c = getch();

        strncpy(tmp++, &c, 1);
    }

    return count;
}


#elif defined(LINUX)
int
getch()
{
    termios oldt = {0};

    tcgetattr(STDIN_FILENO, &oldt);

    termios newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

int
kbhit()
{
    static bool initialized = false;

    if (! initialized) {
        termios term = {0};

        tcgetattr(STDIN_FILENO, &term);

        term.c_lflag &= ~ICANON;

        tcsetattr(STDIN_FILENO, TCSANOW, &term);
        setbuf(stdin, nullptr);

        initialized = true;
    }

    int bytesWaiting;

    ioctl(STDIN_FILENO, FIONREAD, &bytesWaiting);

    return bytesWaiting;
}

int
rejectkbhit()
{
    termios oldt = {0};

    tcgetattr(STDIN_FILENO, &oldt);

    termios newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    size_t count;

    while (!(count = kbhit()));

    while (count-- > 0) {
        getch();
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return count;
}

int
rejectkbhit(char*& destination)
{
    termios oldt = {0};

    tcgetattr(STDIN_FILENO, &oldt);

    termios newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    size_t count;

    while (!(count = kbhit()));

    destination = (char*)calloc(count + 1, sizeof(char));

    char* tmp = destination;

    while (count-- > 0) {
        char c = getch();

        strncpy(tmp++, &c, 1);
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return count;
}

#endif

}}}

