inherit "/std/vault";
 
void create() {
  set_short("The Storage Room for the Thief Shop");
  set_long(
"This is the storage room for the Thief shop, containing many valuable "
"items.");
  set_property("light", 2);
  set_property("indoors", 1);
  add_exit("/d/damned/guilds/thief/thief_shop", "east");
  set_door("iron door", "/d/damned/guilds/thief/thief_shop", "east",
     "thief store key");
  set_open("iron door", 0);
  set_locked("iron door", 1);
  set_lock_level("iron door", 22);
  set_property("storage room", 1);
  this_object()->reset();
  return;
}
 
void remove_all(object *inv) {
  int i;
 
  i = sizeof(inv);
  while(i--) if(inv[i] && !living(inv[i]) && environment(inv[i]) == this_object()) inv[i]->remove();
  return;
}
 
void reset() {
  object *inv, ob;
  int i;
 
  seteuid(getuid());
  inv = all_inventory(this_object());
  call_out("remove_all", 5, inv);
  for(i = 1; i <=20; i++) {
    ob = new("/wizards/diewarzau/obj/misc/key_blank");
    ob->move(this_object());
//    ob = new("/wizards/diewarzau/obj/misc/small_vial");
//    ob->move(this_object());
//    ob = new("/wizards/diewarzau/obj/misc/weapon_poison");
//    ob->set_strength(20);
//    ob->move(this_object());
    ob = new("/wizards/diewarzau/obj/misc/lock_pick_case");
    ob->move(this_object());
  }
  for(i = 1; i <= 40; i++) {
     ob = new("/wizards/diewarzau/obj/misc/dagger_belt");
     ob->move(this_object());
     ob = new("/wizards/duridian/poison/empty_poison_vial");
     ob->move(this_object());
  }
  for(i = 1; i <= 15; i++) {
    ob = new("/wizards/duridian/poison/plant_press");
    ob = new("/d/damned/virtual/short-sword_3.weapon");
    ob->move(this_object());
  }
  return;
}
 
void clone_weapons() {
   object ob;
   int i;
 
   for(i=1; i <= 2; i++) {
      ob = new("/d/damned/virtual/short-sword_3.weapon");
      ob->move(this_object());
   }
   return;
}
