#include <spell.h>
inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","word of recall");
    set_property("skill","prayer");
    set_property("casting time",60);
    set_property("base mp cost",45);
    set_property("dev cost", 155);
    set_property("fast dev cost", 460);
    set_property("spell level", 19);
    set_property("moon","luna");
    set_property("caster message","You mark this location for Recall.");
    set_property("target message","You feel a wash of tingling pass over your body.");
    set_property("observer message","$C sprinkles some water and prays.");
    set_property("target observer message", "A holy aura enshrouds $T.");
    set_property("spell type",({ }));
    set_property("target type", "living");
    return;
}

void info() {
  message("help",@TEXT
This prayer will mark the caster's location as the destination for the
target's Recall action.  If the room will not allow magic, combat, or is
proof against teleport, scry, or summons--the spell will fail.

The spell is not 100% guaranteed to succeed (even when it appears
to have been successful...occationally, the gods will randomly
changes the destination, the trick is to know when and why.
TEXT
,this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  int diff;
  object ob;

#if 0
  if(wizardp(at)) {
    message("info", "You may not apply a recall to wizards.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
#endif
  if(at->is_player() && !interactive(at)) {
    message("info", "You may not apply a recall to link-dead players.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(environment(at)->query_property("no summon")) {
    message("info", "You may not apply a recall to anyone from "+
            (string)at->query_cap_name()+"'s location.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(environment(caster)->query_property("no teleport")) {
     message("info", "You may not apply a recall to anyone at this location.",
            caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  diff = (int)at->query_level() - (int)caster->query_level();
  diff += 23 - (power * 4);
  if(random(20) <= diff) {
    message("info", "Your attempt to apply a recall was insufficiently powered for "+
            (string)at->query_cap_name()+".", caster);
    message("info", (string)caster->query_cap_name() +
            " tried unsuccessfully to apply a recall to you.", at);
    remove();
    return;
  }
  message("info","%^BLUE%^%^BOLD%^"+(string)caster->query_cap_name()+
    " has successfully applied a RECALL to you at "+(string)environment(caster)->query_short()+".", at);
  ob = new("/wizards/zortek/obj/recall_ob");
  ob->set_dest(file_name(environment(caster)));
  ob->set_creator((string)caster->query_cap_name());
  ob->set_rtime(time()+(900*power));
  ob->set_success(caster->query_level());
  ob->move(at);
  remove();
  return;
}
