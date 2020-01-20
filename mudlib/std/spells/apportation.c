#include "/adm/include/spell.h"

inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","apportation");
    set_property("skill","magery");
    set_property("casting time",10);
    set_property("base mp cost",41);
    set_property("dev cost", 51);
    set_property("fast dev cost", 160);
    set_property("spell level", 10);
    set_property("moon","luna");
    set_property("caster message","You cast apportation at $T.");
    set_property("target message","You feel a magical force tugging at your possessions!");
    set_property("observer message","$C casts apportation at $T.");
    set_property("spell type",({ }));
    set_property("target type", "player");
    set_property("must be present", 1);
    set_property("can resist", 1);
    set_property("save mod", "strength");
    return;
}

void info() {
message("help",
"This spell is a telekenetic variant which can transport someone's "
"possessions into your grasp.  The player will ALWAYS know it was you who "
"did it, but you may use this spell with wielded weapons or worn armour!  "
"The player may use his/her strength to resist the spell.  Power level overcomes "
"this effect.\n"
"Syntax: cast *3 apportation at <player> with <item>\n"
"Ex: cast *3 apportation at diewarzau with sword",
this_player());
}

int steal_filter(object what) {
  if(what->query_wielded()) return 0;
  if(what->query_worn()) return 0;
  if(what->query_property("no steal")) return 0;
  return 1;
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob, *inv;
  int i, bucka;
  string *currs;

  if(flag) {
    message("info", "Oops!  You transport all possessions and money "+
      "into "+TQN+"'s hands!", caster);
    message("info", CQN+" must be feeling generous, for "+
      nominative(caster)+" magically transports all of "+
      possessive(caster)+" worldly possessions into you hands.",
      at);
//    inv = all_inventory(caster);
      inv = filter_array(all_inventory(at), "steal_filter", this_object());
    i = sizeof(inv);
    while(i--) {
      if(inv[i]->drop()) continue;
      inv[i]->move(at);
    }
    currs = (string *)caster->query_currencies();
    i = sizeof(currs);
    while(i--) {
      bucka = (int)caster->query_money(currs[i]);
      if(bucka <= 0) continue;
      caster->add_money(currs[i], -1*bucka);
      at->add_money(currs[i], bucka);
    }
    remove();
    return;
  }
  if(!args) {
    message("info", "See 'help spell apportation' for syntax.",
      caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(!ob=present(args, at)) {
    message("info", TQN+" isn't carrying '"+args+"'.",
      caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  ob->move(caster);
  message("info", "You magically transport "+(string)ob->query_short()+
    " into your hands!", caster);
  message("info", CQN+" magically transports "+(string)ob->query_short()+
    " from your hands into "+possessive(caster)+"!", at);
  message("info", CQN+" transports "+(string)ob->query_short()+
    " from "+TQN+"'s grasp into "+possessive(caster)+" own.",
    EC, ({ at, caster }));
  remove();
  return;
}
