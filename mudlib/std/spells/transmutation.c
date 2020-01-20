inherit "/std/spells/spell";

object soul;

void create() {
    ::create();
    set_property("name","transmutation");
    set_property("skill","energy manipulation");
    set_property("casting time",12);
    set_property("base mp cost",30);
    set_property("dev cost", 66);
    set_property("fast dev cost", 195);
    set_property("spell level", 13);
    set_property("moon","luna");
    set_property("caster message","You cast TRANSMUTATION.");
    set_property("target message","");
   set_property("observer message","$C casts TRANSMUTATION.");
    set_property("spell type",({ }));
    set_property("no target", 1);
    set_property("duration", 180);
    return;
}

void info() {
message("help",
"This spell FLIPS your mp and hp totals!  If your hp is higher than "
"your max mp or vice versa, the max values may be exceeded.  At the end "
"of the duration the totals will flip back.  If for some reason, you have "
"0 or negative mp at that time, you WILL die.  If you have EXACTLY the amount "
"of mp it takes to cast the spell (ie, you will have 0 mp after "
"casting), you will ALSO die.  This spell is ONLY "
"self-cast.  Power affects duration only.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  int hp, mp;
  object ob;

  if(caster->query("transmutation")) {
    message("info", "You ay not stack this spell.",
      caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  hp = (int)caster->query_hp();
  mp = (int)caster->query_mp();
  if(flag) {
    message("info", "The spell works as expected, but BOTH totals "
      "are cut in half (round down) as they are flipped!",
      caster);
    hp /= 2;
    mp /= 2;
  }
  hp -= (int)caster->query_mp();
  mp -= (int)caster->query_hp();
  caster->add_hp(mp);
  caster->add_mp(hp);
  ob = new("/wizards/diewarzau/obj/misc/trans_ob");
  ob->set_spell(this_object(), caster);
  ob->move(caster);
  caster->set("transmutation", 1);
  soul = ob;
  delayed_call("remove_trans", props["duration"], caster);
}

void remove_trans(object caster) {
  int hp, mp;

  if(!caster) {
    remove();
    return;
  }
  message("info", "%^CYAN%^Transmutation expires, and "+
    "your totals return to normal.", caster);
  hp = (int)caster->query_hp();
  mp = (int)caster->query_mp();
  hp -= (int)caster->query_mp();
  mp -= (int)caster->query_hp();
  caster->add_hp(mp);
  caster->add_mp(hp);
  if(soul) soul->remove();
  caster->set("transmutation", 0);
  return;
}

int can_exceed_max_mp() { return 1; }

int can_exceed_max_hp() { return 1; }

