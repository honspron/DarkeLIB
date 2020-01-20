inherit "/std/Object";

int picks_left;

void create() {
  ::create();
  set_name("lock picks");
  set_id( ({ "case", "picks", "lock picks", "case of lock picks" }) );
  set_short("A case of 10 lock picks");
  picks_left = 10;
  set_long("This is a case of lock picks.  You must 'take' one from the "
"case before using it.");
  set_weight(50);
  set_value(230);
  return;
}

void init() {
  ::init();
  add_action("get_pick", "take");
  add_action("get_pick", "get");
  return;
}

int get_pick(string str) {
  string tmp1, tmp2;
  object ob;

  if(sscanf(str, "%s from %s", tmp1, tmp2) != 2) return 0;
  if(present(tmp2, this_player()) != this_object()) return 0;
  seteuid(getuid());
  ob = new("/wizards/diewarzau/obj/misc/lock_picks");
  if(!ob->id(tmp1)) {
    ob->remove();
    write("There is no '"+str+"' in the case.");
    return 1;
  }
  picks_left--;
  write("Ok.");
  ob->move(this_player());
  if(picks_left > 1)
    set_short(sprintf("A case of %d lock picks", picks_left));
  else if(picks_left == 1)
    set_short("A case with 1 lock pick in it");
  else {
    write("Having taken the last lock pick, you discard the case.");
    remove();
  }
  set_value(query_value() - 23);
  return 1;
}
