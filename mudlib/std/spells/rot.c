inherit "/std/spells/spell";

int sp_pow;
object cas;

void create() {
    ::create();
    set_property("name","rot");
    set_property("skill","necromancy");
    set_property("casting time",12);
    set_property("base mp cost",64);
    set_property("dev cost", 75);
    set_property("fast dev cost", 223);
    set_property("spell level", 14);
    set_property("moon","luna");
    set_property("caster message","You cast rot upon this room!");
    set_property("target message","");
    set_property("observer message","$C casts rot upon this room!");
    set_property("spell type",({ }));
    set_property("no target", 1);
    set_property("duration", 30);
    set_property("prereq", "decay");
    return;
}

void info() {
message("help",
"This is a truly powerful spell which damages all in the room "
"(except you) periodically for the length of the duration.  "

"If you leave the room, the spell will not 'follow' you.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  sp_pow = power;
  if(flag) {
    message("info", "%^GREEN%^You accidentally rot away half of your hit points!",
      caster);
    caster->add_hp(-1 * (int)caster->query_hp()/2);
    remove();
    return;
  }
  cas = caster;
  call_out("damage_all", 5, base_name(environment(caster)), props["duration"]/5);
}

int filter_living(object who) { return living(who); }

void damage_all(string room, int times) {
  object *inv, env;
  int i;

  env = find_object_or_load(room);
  times--;
  inv = filter_array(all_inventory(env), "filter_living", this_object());
  i = sizeof(inv);
  while(i--) {
    if(inv[i] == cas) continue;
    message("info", "%^GREEN%^You take damage from ROT.", inv[i]);
    inv[i]->add_hp(-1 * sp_pow * (int)inv[i]->query_hp() /100 );
    if(cas)
      inv[i]->kill_ob(cas, 1);
  }
  if(times <= 0) {
    message("info", "%^CYAN%^%^BOLD%^A rot spell wears off.",
        env);
    remove();
    return;
  }
  call_out("damage_all", 5, room, times);
  return;
}

