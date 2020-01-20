// /wizards/excelsior/cape/rooms


#include <daemons.h>
#define CURRS ({ "mithril", "gold", "electrum", "copper", \
                "silver" })

inherit "/std/vault";

private int open;

void reset() {
   ::reset();
   seteuid(getuid());
   if (!present("bob") && open) {
      new("/wizards/excelsior/cape/mon/bob")->move(this_object());
   }
}

void create() {
   ::create();
   set_property("indoors",1);
   set_property("light",3);
   add_exit("/wizards/excelsior/cape/rooms/town3", "south"); 
   open = 1;
   set_door("south door", "/wizards/excelsior/cape/rooms/town3", "south",
	    "ms out");
   set_open("south door", 1);
   set_locked("south door", 0);
   set("short","Bob the Money Changer");
   set("long",
"This is the fine money changing establishment of Bob the Money Changer. "+
"Bob, having opened a successful general store with chains all over, decided "+
"to go into the business of money changing as well. This is not a very "+
"lucurative business, as he makes no profit off any of his transactions. Hrm. "+
"Bob himself stands behind a high counter ready to serve you.");
   set_items( (["sign": (: call_other, this_object(), "money_rates" :),
              "counter" : "It is a high counter with slots for tellers."]) );
   set_open_function("open_door", "1:00:00");
   set_close_function("close_door", "17:00:00");
}

void money_rates() {
  int i, tmp;
  string line;
  float rate;

  write("%^BOLD%^%^BLUE%^Current Exchange Rates of Major Currencies%^RESET%^\n");
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
   "NOTE: Due to the flooded market, platinum is no longer carried or excepted here.");
  return;
}

void open_door() {
  set_locked("south door", 0);
  set_open("south door", 1);
  call_other("/wizards/excelsior/cape/rooms/town3", "set_locked",
	     "south door", 0);
  call_other("/wizards/excelsior/cape/rooms/town3", "set_open",
	     "south door", 1);
  open = 1;
  this_object()->reset();
  return;
}

void close_door() {
  object ob, *inv;
  int i;
  
  ob = present("silas", this_object());
  if(ob) ob->remove();
  inv = all_inventory(this_object());
  i = sizeof(inv);
  while(i--) {
    if(living(inv[i])) {
      message("info", "The shop is closing now.  Get outta here.", inv[i]);
      inv[i]->move(find_object_or_load("/wizards/excelsior/cape/rooms/town3"));
    }
  }
  set_open("south door", 0);
  set_locked("south door", 1);
  call_other("/wizards/excelsior/cape/rooms/town3", "set_open", 
		"south door", 0);
  call_other("/wizards/excelsior/cape/rooms/town3", "set_locked", 
		"south door", 1);
   open = 0;
}
