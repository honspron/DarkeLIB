//    Maxwell's Underground Mudlib 
//          Rug Key for Desk Lock
#include <std.h>
inherit OBJECT;

void create() {
  ::create();
    set_name("fenton key");
    set_id( ({ "key","brass key","brass fenton key","fenton key"}));
    set_short("a small brass fenton key" );
    set_long("The key is made from a solid piece of brass. Engraved into "
             "the shaft of the key is 'Frenton LockSmith'.");
    set_weight(10);
    set_value(0);
}

