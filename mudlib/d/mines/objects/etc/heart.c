//    Maxwell's Underground Mudlib
//    Heart of Jenkarb

#include <std.h>
#define UNDER "/wizards/maxwell/underzone/"
inherit OBJECT;

create() {
    ::create();
   set_id(({"heart","Jenkarb's heart","jheart"}));
   set_name("heart");
   set_short("a bloody heart");
   set("long", "This heart is covered in dark red blood and bits of "
      "flesh.\n");
   set_weight(5);
   set_value(10);
}

