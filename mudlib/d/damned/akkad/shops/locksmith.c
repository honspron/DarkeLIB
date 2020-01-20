inherit "/std/room";

private int pay(object tp, int amt, string curr);

void reset() {
   ::reset();
   seteuid(getuid());
   if (!present("raz")) {
      new("/d/damned/akkad/obj/mon/raz")->move(this_object());
   }
   if(!present("key rack"))
      new("/d/damned/akkad/obj/misc/key_rack")->move(this_object());
}

void create() {
   ::create();
   set_property("indoors",1);
   set_property("light",3);
   add_exit("/d/damned/akkad/ak_shop6","north");
   set("short","The Trap Shop");
   set("long",
"This is the Trap Shop.  Here you may have traps "
"installed on your chests.  There is a sign on the wall.");
   set_items( (["sign": (: call_other, this_object(), "read_sign" :) ]) );
}

int read_sign() {
  string msg;

  msg =
"The following chest traps are available:\n"
"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n"
"poison trap          poisons a would-be thief (360 gold)\n"
"fire trap            magical fireball trap! (1400 gold)\n"
"gate trap            transports victim to the warp to be\n"
"                     DEVOURED by warp creatures! (15000 gold\n"
"\n"
"To get a trap: trap <chest-name> with <trap-name>\n";
  this_player()->more(explode(msg, "\n"));
  return 1;
}

void init() {
  ::init();
  add_action("trap_chest", "trap");
}

int pay(object tp, int amt, string curr) {
  if((int)tp->query_money(curr) < amt) {
    message("info", "You don't have enough "+curr+".", tp);
    return 0;
  }
  tp->add_money(curr, -1 * amt);
  return 1;
}
/*
int lock_chest(string str) {
  string chest, lock;
  object ob;

  if(sscanf(str, "%s on %s", lock, chest) != 2)
    return notify_fail("Usage: install <lock-name> on <chest-name>\n");
  ob = present(chest, this_player());
  if(!ob) {
    write("You don't have a '"+chest+"'.");
    return 1;
  }
  lock = lower_case(lock);
  switch(lock) {
  case "cheap lock":
    if(!pay(this_player(), 300, "gold")) return 1;
    ob->set_key((string)this_player()->query_name() + " chest key");
    ob->set_lock("unlocked");
    ob->set_lock_level(5);
    write("Lock installed on "+(string)ob->query_short()+".");
    return 1;
  case "standard lock":
    if(!pay(this_player(), 800, "gold")) return 1;
    ob->set_key((string)this_player()->query_name() + " chest key");
    ob->set_lock("unlocked");
    ob->set_lock_level(10);
    write("Lock installed on "+(string)ob->query_short()+".");
    return 1;
  case "fine lock":
    if(!pay(this_player(), 2000, "gold")) return 1;
    ob->set_key((string)this_player()->query_name() + " chest key");
    ob->set_lock("unlocked");
    ob->set_lock_level(16);
    write("Lock installed on "+(string)ob->query_short()+".");
    return 1;
  case "industrial lock":
    if(!pay(this_player(), 8000, "gold")) return 1;
    ob->set_key((string)this_player()->query_name() + " chest key");
    ob->set_lock("unlocked");
    ob->set_lock_level(23);
    write("Lock installed on "+(string)ob->query_short()+".");
    return 1;
  case "wizard lock":
    if(!pay(this_player(), 19000, "gold")) return 1;
    ob->set_key((string)this_player()->query_name() + " chest key");
    ob->set_lock("unlocked");
    ob->set_lock_level(32);
    write("Lock installed on "+(string)ob->query_short()+".");
    return 1;
  default:
    write("We don't have a lock of the type: '"+lock+"'.");
    return 1;
  }
}
*/
int trap_chest(string str) {
  string chest, trap;
  object ob;

  if(sscanf(str, "%s with %s", chest, trap) != 2)
    return notify_fail("Usage: trap <chest-name> with <trap-name>\n");
  ob = present(chest, this_player());
  if(!ob) {
    write("You don't have a '"+chest+"'.");
    return 1;
  }
  trap = lower_case(trap);
  switch(trap) {
  case "poison trap":
    if(!pay(this_player(), 360, "gold")) return 1;
    ob->set_trap_func("/std/diewarzau/obj/misc/trap_func",
            "poison_trap");
    ob->set_trap_level(10);
    write("Trap installed.\n");
    return 1;
  case "fire trap":
    if(!pay(this_player(), 1400, "gold")) return 1;
    ob->set_trap_func("/std/diewarzau/obj/misc/trap_func",
            "fire_trap");
    ob->set_trap_level(16);
    write("Trap installed.\n");
    return 1;
  case "gate trap":
    if(!pay(this_player(), 15000, "gold")) return 1;
    ob->set_trap_func("/std/diewarzau/obj/misc/trap_func",
            "gate_trap");
    ob->set_trap_level(30);
    write("Trap installed.\n");
    return 1;
  default:
    write("We don't have that trap.");
    return 1;
  }
}

