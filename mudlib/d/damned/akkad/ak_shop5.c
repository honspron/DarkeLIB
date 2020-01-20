inherit "/std/vault";

private int open;

void reset() {
   ::reset();
   seteuid(getuid());
   if (!present("karsten") && open) {
      new("/d/damned/akkad/obj/mon/karsten")->move(this_object());
   }
}

void create() {
   ::create();
   set_property("indoors",1);
   set_property("light",3);
   add_exit("/d/damned/akkad/ak_markse", "north");
   add_exit("/d/damned/akkad/shops/shop5_store", "west");
   set_door("wooden door", "/d/damned/akkad/shops/shop5_store", "west",
	    "ak shop5 store");
   set_open("wooden door", 0);
   set_locked("wooden door", 1);
   open = 1;
   set_door("south door", "/d/damned/akkad/ak_markse", "north",
	    "ak shop5");
    set_open("south door", 1);
   set_locked("south door", 0);
   set_lock_level("wooden door", 22);
   set("short","The Magic Shop");
   set("long",
"This is the Magic Shop.  Several magical wares can be seen "
"lying about.  There is a sign on the wall\n"
"To the west is a sturdy wooden door.");
   set_items( (["sign": (: call_other, this_object(), "read_sign" :),
              "wooden door" : "It looks very sturdy.",
              "south door" : "It is a large wooden door.",
              "door" : "There is an south door and a wooden door" ]) );
   set_open_function("open_door", "5:30:00");
   set_close_function("close_door", "16:30:00");
}

void open_door() {
  set_locked("south door", 0);
  set_open("south door", 1);
  call_other("/d/damned/akkad/ak_markse", "set_locked",
	     "south door", 0);
  call_other("/d/damned/akkad/ak_markse", "set_open",
	     "south door", 1);
  open = 1;
  this_object()->reset();
  return;
}

int read_sign() {
  write("Welcome to Karsten's World o' Magic!\n"
  "\nHere, you may buy figurines for summoning spells and vials for "
  "potion spells.\n\n"
  "Also, if you are too lazy to make a potion yourself, we offer two "
  "varieties of healing potions here!\n");
  write("White potion - 100hp heal.\nAlabaster potion - 200 hp + remove poison\n"+
      "Purple potion - helps regen magic points but lowers casting chance temporarily.");
  return 1;
}

void close_door() {
  object ob, *inv;
  int i;
  
  ob = present("karsten", this_object());
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
  set_open("south door", 0);
  set_locked("south door", 1);
  call_other("/d/damned/akkad/ak_markse", "set_open", 
		"south door", 0);
  call_other("/d/damned/akkad/ak_markse", "set_locked", 
		"south door", 1);
   open = 0;
}
