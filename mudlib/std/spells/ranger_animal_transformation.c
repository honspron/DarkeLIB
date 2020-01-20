#include <rooms.h>
inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","ranger animal transformation");
    set_property("skill","woodland lore");
    set_property("casting time",20);
    set_property("base mp cost",35);
    set_property("dev cost", 31);
    set_property("fast dev cost", 90);
    set_property("spell level", 9);
    set_property("moon","luna");
    set_property("caster message","You cast animal transformation.");
    set_property("target message","");
    set_property("observer message","$C casts animal transformation.");
    set_property("spell type",({ }));
    set_property("no target", 1);
    set_property("duration", 240);
    return;
}

void info() {
message("help",
"This spell will transform you into an animal resembling those "
"indiginous to DarkeMUD, allowing both the advantages of disguise and "
"any advantaged which may accompany the particular animal.  The animal into
"
"which you transform is random, and power level affects only duration.\n"
"'remove transformation' will cause the spell to be dispelled on command.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag)
{
  object ob, *inv, shad;
  int i;

  if(flag) {
    message("info", "You accidentally summon a large panther!", caster);
    seteuid(getuid());
    ob = new("/d/damned/world/obj/mon/panther");
    ob->move(ROOM_VOID);
    ob->move_player(base_name(environment(caster)), 0);
    remove();
    return;
  }
  if(caster->query_lyc_status()) {
    message("info", "You cannot cast this spell while transformed by
lycanthropy.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  seteuid(getuid());
  message("info", "You drop your whole inventory on the ground.",
    caster);
  inv = all_inventory(caster);
  i = sizeof(inv);
  while(i--) if(inv[i]->query_short() && !inv[i]->drop())
inv[i]->move(environment(caster));

  message("info", (string)caster->query_cap_name()+" drops "+
    possessive(caster)+" whole inventory on the ground.",
    environment(caster), ({ caster }));
  ob = new("/std/spells/shadows/a_trans_shadow");
  shad = ob;
  switch(random(4)) {
  case 0:
    message("info", "You transform into a jackrabbit.", caster);
    message("info", ""+(string)caster->query_cap_name()+
      " transforms into a jackrabbit.", environment(caster),
      ({ caster }));
    ob->set_new_short("A jackrabbit");
    ob->set_atrans_mods(([ "strength" : -50, "dexterity" : 20,
      "intelligence" : -30 ]));
    ob->set_new_melee(([ "crushing" : -10 ]));
    ob->set_new_cap("Rabbit");
    break;
  case 1:
    message("info", "You transform into a mountain lion.", caster);
    message("info", ""+(string)caster->query_cap_name()+
      " transforms into a mountain lion.", environment(caster),
      ({ caster }));
    ob->set_new_short("A ferocious mountain lion");
    ob->set_atrans_mods(([ "strength" : 20, "dexterity" : 30,
      "intelligence" : -50 ]));
    ob->set_new_melee(([ "cutting" : 20 ]));
    ob->set_new_cap("Lion");
    break;
  case 2:
    message("info", "You transform into a timber wolf.", caster);
    message("info", ""+(string)caster->query_cap_name()+
      " transforms into a jackrabbit.", environment(caster),
      ({ caster }));
    ob->set_new_short("A menacing timber wolf");
    ob->set_atrans_mods(([ "strength" : 30, "dexterity" : 30,
      "intelligence" : -50 ]));
    ob->set_new_melee(([ "cutting" : 20 ]));
    ob->set_new_cap("Wolf");
    break;
  case 3:
  default:
    message("info", "You transform into a lizard.", caster);
    message("info", ""+(string)caster->query_cap_name()+
      " transforms into a lizard.", environment(caster),
      ({ caster }));
    ob->set_new_short("A lizard");
    ob->set_atrans_mods(([ "strength" : -50, "dexterity" : 20,
      "intelligence" : -30 ]));
    ob->set_new_melee(([ "crushing" : -10 ]));
    ob->set_new_cap("Lizard");
    break;
  }
  ob->start_shadow(caster, props["duration"], "%^BOLD%^%^CYAN%^Animal transformation wears
off.");
  ob = new("/wizards/diewarzau/obj/misc/a_trans_ob");
  ob->move(caster);
  ob->set_shadow(shad);
  call_out("remove_ob", props["duration"], ob);
  return;
}

void remove_ob(object ob) {
  if(ob) ob->remove();
  return;
}
