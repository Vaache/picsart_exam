#include "header.h"

char * getPrio(lvl prio) {
    if (prio == HIGH) {
        return strdup("Hight");
    } else if (prio == MEDIUM) {
        return strdup("Medium");
    } else { return strdup("Low"); }
}