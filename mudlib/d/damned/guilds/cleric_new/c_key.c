#include <move.h>
#include <std.h>

inherit "/std/Object";
inherit AUTOLOAD;
  
void create() {
    ::create();
    set("id", ({ "key", "cleric donation box key" }));
    set_name("key");
    set("short", "Cleric donation box key");
    set("long",@TEXT
This is a gem encrusted golden key that safely unlocks the
donation box for the Holy Church.
TEXT
);
    set_weight(25);
    set_value(50000);
   return;
}

int query_always_keep() { return 1; }


