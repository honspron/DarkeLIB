#include <security.h>
#define NO_SUGGEST ({ "reincarnate","quit", "chfn", "passwd", "snoopable", "suicide" })

inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","suggestion");
    set_property("skill","magery");
    set_property("casting time",7);
    set_property("base mp cost",45);
    set_property("dev cost", 62);
    set_property("fast dev cost", 181);
    set_property("spell level", 12);
    set_property("moon","luna");
    set_property("caster message","You cast suggestion at $T.");
    set_property("target message","$C attempts to suggest something to you.");
    set_property("observer message","$C casts suggestion at $T.");
    set_property("spell type",({ }));
    set_property("target type", "player");
    set_property("must be present", 1);
    set_property("duration", "instant");
    set_property("can resist", 1);
    set_property("save mod", "intelligence");
    return;
}

void info() {
message("help",
"This spell allows you to force other players to do commands as if they "
"had typed them in themselves!  It is more difficult to suggest to higher "
"level players, but higher spell power can offset this penalty.  You may not "
"suggest that another player quit or change his or her password.\n"
"Syntax: cast *3 suggestion at <player> with <command>\n"
"Ex: cast *3 suggestion at diewarzau with drop all\n",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  string *words;
  object *inv;
  int i, chance;

  seteuid(UID_FORCE);
  if(flag) {
    message("info", "Oops, you force youself to give your whole "+
      "inventory to "+(string)at->query_cap_name()+"!", caster);
    inv = all_inventory(caster);
    i = sizeof(inv);
    while(i--) {
      words = (string *)inv[i]->query_id();
      if(!pointerp(words) || !sizeof(words)) continue;
      caster->force_me("give "+words[0]+" to "+(string)at->query_name());
    }
    remove();
    return;
  }
  if(!args || !stringp(args)) {
    message("info", "See 'help spell suggestion' for syntax.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  while(strlen(args) && args[0] == ' ') args = replace_string(args, " ", "", 1);
  words = explode(args, " ");
  if(sizeof(words) && member_array(words[0], NO_SUGGEST) >= 0) {
    message("info", "You may not suggest that command.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  i = (int)caster->query_level() - (int)at->query_level();
  chance = 10 + i*2;
  if(chance < 1) chance = 1;
  if(i < -5 || random(100) >= (chance*power)) {
    message("info", "You fail to suggest the command.", caster);
    message("info", (string)caster->query_cap_name() +
      " fails to suggest you to '"+args+"'.", at);
    remove();
    return;
  }
  seteuid(UID_FORCE);
  at->force_me(args);
  seteuid(getuid());
  remove();
  return;
}
