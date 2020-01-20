#include "../../daybreak.h"
#include <daemons.h>
#define CURRS ({ "mithril", "gold", "electrum", "copper", \
                "silver" })

inherit "/std/vault";

private int open;

void init() {
   add_action("read", "read");
   ::init();
}
void reset() {
   ::reset();
   seteuid(getuid());
   if (!present("silas")) {
      new(MON+"silas")->move(this_object());
   }
}

void create() {
   ::create();
   set_property("indoors",1);
   set_property("light",3);
   add_exit(ROOMS+"dbcc8", "east");
   add_exit(ROOMS+"money_store", "north");
   set_door("vault door", ROOMS+"money_store", "north","ak shop1 store");
   set_open("vault door", 0);
   set_locked("vault door", 1);
   set_lock_level("vault door", 27);
   set("short","The Money Changer");
   set("long",
"This is the office of the Money Changer.  A thin, pensive-looking "
"half-elf eyes you from behind a desk laiden with parchments.  "
"There is a large sign on the west wall, and a huge vault door "
"crafted of fine metal is seen to the north.");
   set_items( (["sign": (: call_other, this_object(), "money_rates" :),
              "vault door" : "It looks almost impregnable."]) );}

void money_rates() {
  int i, tmp;
  string line;
  float rate;

  write("The sign is titled 'Current Exchange Rates of Major "+
        "Currencies'.  It reads:\n");
  for(i=0; i<sizeof(CURRS); i++) {
    rate = ECONOMY_D->__Query(CURRS[i], "rate");
    if(rate < (float)ECONOMY_D->__Query("gold", "rate"))
      line = sprintf("%-30'.'s%-5.1f gold", capitalize(CURRS[i])+":",
                     (float)ECONOMY_D->__Query("gold", "rate")/rate);
    else
      line = sprintf("%-30'.'s%-5.1f copper", capitalize(CURRS[i])+":",
                     (float)ECONOMY_D->__Query("copper", "rate")/rate);
    write(line);
  }
   write("\nType 'help money' for help on exchanging.\n"
   "NOTE: Due to the flooded market, platinum is no "+
   "longer carried here.");
  return;
}


int read(string str) {
   if(str == "sign") {
      money_rates();
      return 1;
   }
   else
      return 0;
}
