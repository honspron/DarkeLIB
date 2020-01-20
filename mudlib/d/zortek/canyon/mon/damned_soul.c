#include <std.h>

inherit MONSTER;

create() {
  object ob;
  object gem;
  string *dir_list;
  string *letters = ({"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"});
  string pname;
  int x,y,z;
  ::create();
  x = sizeof(letters);
  y = random(x);
  dir_list = get_dir("/adm/save/users/"+letters[y]+"/*.o");
  z = random(sizeof(dir_list));
  pname = dir_list[z];
  pname = replace_string(pname, ".o", "");
  set_name("soul");
  set_id( ({ "soul", "damned soul", pname }) );
  set_short("Damned Soul of "+capitalize(pname));
  set_gender("neuter");
  set_level(random(10)+15);
  set_overall_ac(random(50)+50);
  set_property("enhance criticals", -3);
  set("race", "devil");
  set_body_type("devil");
  set_property("melee damage", ([ "infernal" : 25, ]));
  gem = new("/wizards/zortek/canyon/obj/soul_gem");
  gem->set_devil_name(capitalize(pname));
  gem->move(this_object());
}

void init() {
  ::init();
}

void die(object ob) {
  
  ::die(ob);
  return;
}
