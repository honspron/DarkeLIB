#include "/adm/include/spell.h"
inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","clone");
    set_property("skill","magery");
    set_property("casting time",25);
    set_property("base mp cost",62);
    set_property("dev cost",104);
    set_property("fast dev cost",320);
    set_property("spell level", 20);
    set_property("moon","luna");
    set_property("caster message","You summon a Clone.");
    set_property("target message","");
    set_property("observer message","$C casts clone.");
    set_property("spell type",({  }));
    set_property("duration", 300);
    set_property("no target", 1);
    return;
}

void info() {
message("help",
"This is a truly powerful spell used to summon a clone of yourself.  "
"The clone has ALL the same properties as you.  In addition to being "
"an exact copy of you, the clone will MIRROR ALL OF YOUR ACTIONS!  "
"You heard that right...you cast a spell, the clone will, etc.  "
"Note: in order to read your description correctly, casting this spell "
"will cause most other spells on you to expire immediately.  If your clone "
"is killed, you will lose half of your MAX hit points!  "
"Power affects duration only.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;
//  int roll;

  seteuid(getuid());
  if(!caster->is_player()) {
    message("info", "Only players may cast this spell.",
      caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(caster->query("has clone")) {
    message("info", "You may only clone yourself once.",
      caster);
    if(!flag)
      caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  while(ob=shadow(caster, 0)) ob->external_destruct(ob);
  ob = new("/wizards/diewarzau/obj/mon/clone_ob");
  ob->move(environment(caster));
  ob->copy_player(caster);
  ob->set_dur(props["duration"]);
  message("info", "%^GREEN%^%^BOLD%^A clone of "+
    CQN+" appears.", EC, ({ ob }));
  if(flag) {
    ob->set_fumble();
    message("info", "%^RED%^%^BOLD%^The clone angrily attacks you!", caster);
    message("info", "%^RED%^%^BOLD%^The clone angrily attacks "+
      (string)caster->query_cap_name()+"!", environment(caster), ({ caster }));
    ob->kill_ob(caster, 0);
    remove();
    return;
  } else {
    caster->set("mirror action", ob);
    caster->set("has clone", 1);
    delayed_call("expire_me", props["duration"]+3, caster);
  }
  remove();
  return;
}

void expire_me(object caster) {
  if(caster) {
    caster->set("has clone", 0);
    caster->set("mirror action", 0);
  }
  remove();
  return;
}
