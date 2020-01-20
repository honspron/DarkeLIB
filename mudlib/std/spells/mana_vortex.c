#include <spell.h>
inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","mana vortex");
    set_property("skill","sorcery");
    set_property("casting time",55);
    set_property("base mp cost",25);
    set_property("dev cost", 61);
    set_property("fast dev cost", 185);
    set_property("spell level", 12);
    set_property("moon","luna");
    set_property("caster message","You cast Mana Vortex!");
    set_property("target message","");
    set_property("observer message","$C seems to concentrate with intensity.");
    set_property("spell type",({ }));
    set_property("no target", 1);
    set_property("prereq", "mana drain");
    set_property("duration", "instantaneous");
    return;
}

void info() {
message("help",
"This extremely powerful spell creates a vortex of magical power "
"over the entire mud, taking magic points from all players.  "
"Their loss will be small, but your gain large, depending on power level "
"of course.  The disadvantage is that higher level magi will be able to "
"sense that you have cast this spell (spell sense or detect magic / 2), "
"and in some cases divine your EXACT LOCATION, which will function like an "
"automatic scry.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object *inv;
  object ob;
  int mp, tot;

  if(flag) {
    message("info", "You accidentally rob yourself of all mp, sending "
	    "the mana inot the void!", caster);
    caster->add_mp(-1 * (int)caster->query_mp());
    remove();
    return;
  }
  tot = 0;
  inv = filter_array(users(), (: !(wizardp($1)) :));
  foreach(ob in inv) {
    if(ob == caster) continue;
    mp = (10+random(10)+random(10)) * power;
    if(mp > (int)ob->query_mp()) mp = (int)ob->query_mp();
    ob->add_mp(-1*mp);
    caster->add_mp(mp);
    if((random(100) >= (int)ob->query_skill("spell sense")) &&
       (random(100) >= ((int)ob->query_skill("detect magic")/2)))
      continue;
    message("info", "%^MAGENTA%^%^BOLD%^"
	    "You sense "+CQN+" draining mana from you with a mana vortex!",
	    ob);
    if(random(100) >= (2*(int)ob->query_skill("spell sense")/3))
      continue;
    message("info", "%^CYAN%^You sense "+possessive(caster)+
	    " location as "+(string)environment(caster)->query_short()+
	    " AND receive an AUTOMATIC scry to "+possessive(caster)+
	    " location!", ob);
    ob->set("scry", caster);
    ob->set("scry time", time()+240*power);
  }
  message("info", "%^GREEN%^%^BOLD%^"
	  "You have successfully drained mana from "+
	  sizeof(inv)+
	  " individuals.", caster);
  remove();
  return;
}
