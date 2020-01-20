inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","undead dimension");
    set_property("skill","necromancy");
    set_property("casting time",45);
    set_property("base mp cost",57);
    set_property("dev cost", 16);
    set_property("fast dev cost", 49);
    set_property("spell level", 3);
    set_property("moon","luna");
    set_property("caster message","You transport to your undead dimension.");
    set_property("target message","");
    set_property("observer message","$C casts undead dimension.");
    set_property("spell type",({ }));
    set_property("no target", 1);
    set_property("duration", 30);
    return;
}

void info() {
message("help",
"This spell allows you to transport to your undead dimension so that "
"you may retrieve the creatures therein.  There will be one exit from "
"the dimension leading to the room in which you cast the spell.  When "
"the spell expires, you will be forced through the exit and the dimension "
"will close.",
this_player());
}

int undead_filter(object who, object caster) {
  if(!living(who)) return 0;
  if((string)who->query_owner() != (string)caster->query_name()) return 0;
  return 1;
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object room, *inv;
  object ob;

  room = find_object_or_load(sprintf("/d/damned/virtual/%s.undead", (string)caster->query_name()));
  if(flag) {
    room->remove_out();
    inv = filter_array(all_inventory(room), "undead_filter", this_object(), caster);
    if(inv && sizeof(inv))
      ob = inv[random(sizeof(inv))]->remove();
    else ob = 0;
    if(ob) {
      message("info", "You have convoluted the forces surrounding your dimension!\n"+
          "You accidentally destroy "+(string)ob->query_short()+"!", caster);
      ob->remove();
    } else
      message("info", "Your attempt at transport is unsuccessful.", caster);
    remove();
    return;
  }
  room->open_exit(environment(caster), props["duration"]);
  caster->move_player(base_name(room), 0);
  remove();
  return;
}

