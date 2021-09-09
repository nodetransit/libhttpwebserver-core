#ifndef FB_UTILITY_CONSOLELIBRARY__
#define FB_UTILITY_CONSOLELIBRARY__

#include <cstdio>
#include <cstring>
#include <cstdlib>

#define LINUX

#if defined(LOSER)
#    include <conio.h>
#elif defined(LINUX)
#    include <termios.h>
#    include <unistd.h>
#    include <sys/select.h>
#    include <sys/ioctl.h>
#endif

namespace nt { namespace utility { namespace console {

#if defined(LINUX)
int getch();
/**
 * @brief get the number of characters hit on the keyboard
 *
 * @details
 * Unlike `getch()`, this function does not wait until the user presses
 * a key.
 *
 * The pressed key will be placed on the stdout. To reject the pressed
 * key, @see `rejectkbhit()`.
 *
 * @return count of rejected characters
 */
int kbhit();
/**
 * @brief get the number of characters hit on the keyboard
 *
 * @details
 * Unlike `getch()`, this function does not wait until the user presses
 * a key.
 *
 * Th pressed key will not be placed on the stdout.
 *
 * @return count of rejected characters
 */
int rejectkbhit();

/**
 * @brief get the number of characters hit on the keyboard
 *
 * @details
 * Unlike `getch()`, this function does not wait until the user presses
 * a key.
 *
 * @param destination rejected characters
 *
 * @return count of rejected characters
 */
#endif
int rejectkbhit(char*& destination);

}}}

#endif /* FB_UTILITY_STRING_LIBRARY__ */
