#ifndef Logbook_h
#define Logbook_h

#include <WString.h>

class Logbook {
    public:
        Logbook();
        void info(String message);
        void warn(String message);
        void error(String message);
};

#endif
