#include "header.h"

char * getPrio(lvl prio) {
    if (prio == HIGH) {
        return strdup("High");
    } else if (prio == MEDIUM) {
        return strdup("Medium");
    } else if(prio == LOW){ 
        return strdup("Low"); 
    } else { return strdup("NO VALUE"); }
}