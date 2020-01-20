inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","summon demon lord");
    set_property("skill","chaos magic");
    set_property("casting time",81);
    set_property("base mp cost", 161);
    set_property("dev cost",146);
    set_property("fast dev cost",430);
    set_property("spell level", 27);
    set_property("moon","luna");
    set_property("caster message","You summon a Demon Lord.");
    set_property("target message","");
    set_property("observer message","$C sumons a Demon Lord.");
    set_property("spell type",({  }));
    set_property("duration", 240);
    set_property("no target", 1);
    set_property("prereq", "summon greater demon");
    return;
}

void info() {
message("help",
"This spell is used to summon a DEMON LORD!  You must make a successful "
"control roll at -50 ('help skill control demon'), or he may simply disappear, "
"or ATTACK!  Once summoned, he may be bound to your skin as armour or "
"your sword to increase damage.  Other spells are necessary to do these, "
"however.  The demon, if controlled, may be used additionally to fight at "
"your side.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;
  int roll;

  seteuid(getuid());
  ob = new("/wizards/diewarzau/obj/pet/demon_lord");
  ob->set_dur(props["duration"]);
  ob->set_owner("asskicker");
  ob->set_up(power);
  ob->move(environment(caster));
  if(flag) {
    message("info", "%^RED%^%^BOLD%^The demon angrily attacks you!", caster);
    message("info", "%^RED%^%^BOLD%^The demon angrily attacks "+
      (string)caster->query_cap_name()+"!", environment(caster), ({ caster }));
    ob->kill_ob(caster, 0);
    ob->set_following(caster);
    caster->add_follower(ob);
    remove();
    return;
  }
  roll = random(100);
  if(roll < (int)caster->query_skill("control demon")-50) {
    message("info", "The demon is successfully contolled.", caster);
    ob->set_owner((string)caster->query_name());
    remove();
    return;
  } else if(roll - ((int)caster->query_skill("control demon")-50) < 15) {
    message("info", "The demon is not controlled, and he goes in search of bigger and better things.",
        caster);
    ob->set_moving(1);
    ob->set_speed(60);
    ob->move_around();
    ob->set_aggr_status(1);
    ob->set_owner("asskicker");
    remove();
    return;
  } else if(roll - ((int)caster->query_skill("control demon")-50) < 30) {
    message("info", "The demon is not controlled.  Annoyed, he returns to his plane.",
        caster);
    ob->remove();
    remove();
    return;
  } else {
    message("info", "The demon is not controlled.  He angrily attacks you!",
         caster);
    ob->kill_ob(caster, 0);
    ob->set_following(caster);
    caster->add_follower(ob);
    remove();
    return;
  }
  remove();
  return;
}

