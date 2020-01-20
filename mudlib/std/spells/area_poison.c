#include "/adm/include/party.h"

inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","area poison");
    set_property("skill","body alteration");
    set_property("casting time",6);
    set_property("base mp cost",37);
    set_property("dev cost", 36);
    set_property("fast dev cost", 145);
    set_property("spell level", 7);
    set_property("moon","warzau");
    set_property("caster message","You cast area poison.");
    set_property("target message","$C casts area poison!");
    set_property("observer message","$C casts area poison.");
    set_property("damage multiplier", 4);
    set_property("combat spell", 1);
    set_property("must be present", 1);
    set_property("save mod", "constitution");
    set_property("no target", 1);
    set_property("target type", "living");
    set_property("prereq", "instill poison");
    return;
}

void info() {
message("help",
"This spell creates a poison cloud, poisoning all not in your party!.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object *inv;
  string hit;
  int i;

  inv = filter_array(all_inventory(environment(caster)), (: living :));
  inv = filter_array(inv, "not_party",
          this_object(), caster);
  i = sizeof(inv);
  hit = "";
  while(i--) {
    if(i < sizeof(inv)-1) hit += ", ";
    hit += (string)inv[i]->query_cap_name();
    message("info", "%^CYAN%^A killing cloud hits you!", inv[i]);
    inv[i]->add_poisoning((20 + random(20)) * power);
    inv[i]->kill_ob(caster, 0);
  }
  hit += ".";
  message("info", "%^CYAN%^Your spell hits: "+hit, caster);
  remove();
  return;
}

