// This file is part of the TMI Mudlib distribution.

// Please include this header if you use this code.

// Written by Sulam(Jan 19, 1991)

// Modifed by Buddha(2-18-92)



#include <config.h>



// This is there because I noticed /bin modules weren't going away...



void clean_up() { destruct(this_object()); }



// This gets used a lot.



void create() { seteuid(ROOT_UID); }





int query_prevent_shadow() { return 1; }

