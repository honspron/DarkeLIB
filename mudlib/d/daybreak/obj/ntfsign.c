//  Wizard:  Khojem
//  sign
//  sign.c
 
#include <std.h>

inherit OBJECT;

void create() {
  ::create();
    set_name("sign");
    set_id( ({ "sign" }) );
    set_short("sign");
    set_long("A small cardboard sign is tacked to the wall, perhaps you should read it.");
    set_weight(9000);
    set_value(0);
}

