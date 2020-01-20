inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","gate hellion");
    set_property("skill","infernal lore");
    set_property("casting time", 180);
    set_property("base mp cost", 100);
    set_property("dev cost", 31);
    set_property("fast dev cost", 83);
    set_property("spell level", 15);
    set_property("moon","luna");
    set_property("caster message","You open a minor gate to hell.");
    set_property("target message","");
    set_property("observer message","$C opens a minor gate to hell.");
    set_property("spell type",({ }));
    set_property("no target", 1);
    set_property("duration", 1800);
    return;
}

void info() {
message("help",@TEXT
This infernal call will open a minor gate to one of the lesser planes
of Hell.  If the diabolist is willing to pay the price, a hellion will
step through the gate as an infernal companion.  There is a possibility
that no hellion will notice the gate.  It is equally possible that the
hellion that steps through the gate will do so only to reek havok and
not only refuse to aid the diabolist, but may infact attack all those
present.  In any event, no hellion has EVER been known to be friendly
to any but its owner!  The owner may leech life energy from the hellion
(help hellion for details); however, such infernal gifts ALWAYS have a
price...many a diabolist has been known to kill themselves in their
greed and hunger for power.
TEXT
,this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;

  seteuid(getuid());
  ob = new("/wizards/zortek/pet/hellion");
  ob->set_up(power);
  ob->move(environment(caster));
  ob->set_dur(props["duration"]);
  ob->set_owner((string)caster->query_name());
  message("info", "A "+lower_case((string)ob->query_short()) +
          " sees the gate and arrives.", caster);
  message("info", "A "+lower_case((string)ob->query_short()) +
          " arrives through a crackling tear between planes.", environment(caster), ({ caster }));
  ob->force_me("speak devilish");
  if(flag || (int)caster->query_exp() < ((int)ob->query_level()*1500) ) {
    ob->force_me("say I have no desire to give up this opportunity to "+
                 "flex this freedom you have granted me...Alas, since "+
                 "you were such a buffoon for bringing me here, "+
                 "you will be my first tasty treat...");
    message("info", "The creature then begins to cackle and opens up a "+
                    "serious can of whoop-ass on you!", caster);
    message("info", "The creature then begins to cackle and immediately "
                    "suprises "+(string)caster->query_cap_name() +
                    " by suddenly attacking...", environment(caster),
                    ({ caster }));
    ob->set_owner("");
    ob->kill_ob(caster, 0);
    remove();
    return;
  }
  ob->force_me("say "+caster->query_cap_name()+
               ", Are you willing to pay the price for my service???");
  write("The creature glares at you waiting for your answer.\n(HINT: simply type \"yes\" or \"no\")");
  say("The creature glares at "+caster->query_cap_name()+", seeming to wait for something.");
  input_to("hellion_question", ob, caster);
  return;
}

void hellion_question(string answer, object ob, object caster) {
  int prop;
  switch(answer) {
    case "yes": case "y": case "Yes": case "YES":
      break;
    default:
      ob->force_me("say You are a fool to waste my time!  Now you must pay a far greater price for your stupidity.");
      prop = caster->query_property("hellion");
      caster->set_property("hellion", (prop)?prop--:0);
      ob->set_owner("");
      ob->kill_ob(caster, 0);
      remove();
      return;
  }
  ob->force_me("say Very well, consider the price paid...you may command me.");
  ob->set_master((string)caster->query_name());
  caster->add_exp(-1*(int)ob->query_level()*1500);
  prop = caster->query_property("hellion");
  caster->set_property("hellion", (prop)?(prop+(int)caster->query_level()):((int)caster->query_level()));
  remove();
  return;
}
