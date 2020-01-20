#include "/adm/include/clock.h"

inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("strength");
    set_dev_cost(10);
    set_fast_dev_cost(27);
    set_property("target type", "any");
    set_property("must be present", 1);
}

void info() {
message("help",
"This skill may be used to skin a corpse and obtain the hide for "
"leather.\n"
"Usage: use skin corpse at corpse 1",
	this_player());
}


void skill_func(object from, object at, string arg) {
  object *weap;
  int i, flag;
   
  if(!at->id("corpse")) {
    message("info", "You must use this skill on a corpse.", from);
    remove();
    return;
  }
  i = sizeof(weap = (object *)from->query_wielded());
  flag = 0;
  while(i--) if((string)weap[i]->query_type() == "knife") flag = 1;
  if(!flag) {
    message("info", "You must wield a knife to use this skill.", from);
    remove();
    return;
  }
  message("info", "%^CYAN%^%^BOLD%^You start skinning the corpse.", from);
  message("info", "%^CYAN%^"+(string)from->query_cap_name() +
      " starts skinning a corpse.", environment(from),
      ({ from }));
  call_out("chop_down", 10, from, at);
  return;
}

void chop_down(object from, object corpse) {
  object ob;
  
  if(!present(corpse, from) && !present(corpse, environment(from))) {
    message("info", "You have lost the corpse.  "+
          "Your skill fails.", from);
    remove();
    return;
  }
  message("info", "%^CYAN%^"+(string)from->query_cap_name() +
      " finishes skinning a corpse.", from);
  corpse->remove();
  if(random(100) >= props["skill level"]) {
    message("info", "The corpse fails to wield any quality skins.", from);
    remove();
    return;
  }
  message("info", "You select a leather swatch which will fashion fine armour.", from);
  seteuid(getuid());
  ob = new("/wizards/diewarzau/obj/misc/leather");
  ob->move(from);
  return;
}

          
