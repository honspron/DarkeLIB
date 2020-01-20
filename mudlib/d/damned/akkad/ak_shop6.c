inherit "/std/vault";

private int open;

void reset() {
   ::reset();
   seteuid(getuid());
   if (!present("gil") && open) {
      new("/d/damned/akkad/obj/mon/gil")->move(this_object());
   }
}

void create() {
   ::create();
   set_property("indoors",1);
   set_property("light",3);
   add_exit("/d/damned/akkad/ak_markse", "west");
   add_exit("/d/damned/akkad/shops/shop6_store", "north");
   add_exit("/d/damned/akkad/shops/locksmith", "south");
   set_door("wooden door", "/d/damned/akkad/shops/shop6_store", "north",
	    "ak shop6 store");
   set_open("wooden door", 0);
   set_locked("wooden door", 1);
   open = 1;
   set_door("east door", "/d/damned/akkad/ak_markse", "west",
	    "ak shop6");
    set_open("east door", 1);
   set_locked("east door", 0);
   set_lock_level("wooden door", 35);
   set("short","The Chest Shop");
   set("long",
"This is the Chest Shop.  Here you may buy chests and the like "
"to store your items past the daily reboots.  You must store "
"the chests in special rooms that save items, such as rooms at "
"the inn.  Chests must be closed to store items.  There is a sign on the wall\n"
"To the north is a sturdy wooden door.\n"
"To the south is the Locksmith.");
   set_items( (["sign": (: call_other, this_object(), "read_sign" :),
              "wooden door" : "It looks very sturdy.",
              "east door" : "It is a large wooden door.",
              "door" : "There is an east door and a wooden door" ]) );
   set_open_function("open_door", "5:30:00");
     set_close_function("close_door", "20:00:00");
}

int read_sign() {
  string msg;

  msg =
"The following chests are available:\n"
"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"
"Small Chest          Stores 5 items (2000 coins weight)\n"
"Large Chest          Stores 8 items (3200 coins weight)\n"
"Storage Locker       Stores 25 items (15000 coins weight)\n"
"                     Can be used to store inventory of shops\n"
"Safe                 Can store about 100,000 coins (money only)\n"
"\n'say gil, help' for assistance.\n";
  this_player()->more(explode(msg, "\n"));
  return 1;
}

void open_door() {
  set_locked("east door", 0);
  set_open("east door", 1);
  call_other("/d/damned/akkad/ak_markse", "set_locked",
	     "east door", 0);
  call_other("/d/damned/akkad/ak_markse", "set_open",
	     "east door", 1);
  open = 1;
  this_object()->reset();
  return;
}

void close_door() {
  object ob, *inv;
  int i;
  
  ob = present("gil", this_object());
  if(ob) {
    ob->move(find_object_or_load("/d/standard/void"));
    ob->remove();
  }
  inv = all_inventory(this_object());
  i = sizeof(inv);
  while(i--) {
    if(living(inv[i])) {
      message("info", "The shop is closing now.  You must leave.", inv[i]);
      inv[i]->move(find_object_or_load("/d/damned/akkad/ak_markse"));
    }
  }
  set_open("east door", 0);
  set_locked("east door", 1);
  call_other("/d/damned/akkad/ak_markse", "set_open", 
		"east door", 0);
  call_other("/d/damned/akkad/ak_markse", "set_locked", 
		"east door", 1);
   open = 0;
}
