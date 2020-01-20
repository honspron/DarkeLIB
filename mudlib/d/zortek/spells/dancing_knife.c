inherit "/std/spells/long_term_spell";

void create() {
    ::create();
    set_property("name","dancing knife");
    set_property("skill","mentalism");
    set_property("duration", "permanent");
    set_property("casting time",4);
    set_property("base mp cost",38);
    set_property("dev cost", 10);
    set_property("fast dev cost", 38);
    set_property("spell level", 1);
    set_property("moon","luna");
    set_property("caster message","You begin to add energy and focus to a knife.");
    set_property("target message","");
    set_property("observer message","$C begins to concentrate intently on a knife.");
    set_property("spell type",({ }));
    set_property("target type", "any");
    set_property("must be present", 1);
    return;
}

void info() {
message("help", @TEXT
This focus will animate a knife that will serve you by fighting
beside you in combat.  This is a long-term spell (see help long-term),
and it takes very much real time to cast.  The spell must be cast on
a knife of exceptional quality and make which must be prepared with
the "prepare item" skill.  If you are interrupted while concentrating,
you may resume again at a later time.
TEXT
,this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  if((string)at->query_type() != "knife") {
    message("info", "In order to animate a knife you must first HAVE one!",
      caster);
    remove();
    return;
  }
  if(!at->query_property("prepared") ||
      (int)at->query_property("prepared") < 
      query_property("spell level")*power ) {
    message("info", "This knife has not been sufficiently prepared to receive this focus.",
	    caster);
    remove();
    return;
  }
  if(flag) {
    message("info", "You lose your concentration and accidently desentigrate the knife!!!", caster);
    message("info", (string)caster->query_cap_name() +
      " disentigrates a knife.",
	    environment(caster), ({ caster }) );
    at->remove();
    remove();
    return;
  }
  set_work_message("%^GREEN%^You concentrate intently on your knife.");
  start_work(at, caster, 50 + 90*power, power);
  return;
}

void finish_work(object caster, object at, int power) {
  object ob;
  string *old_short;
  string new_short;

  if(power <= 0) {
    message("info", "BUG in animate spell....unable to complete.",
	    environment(caster));
    remove();
    return;
  }
  message("info", "The knife begins to float and hover before you.", caster);
  message("info", (string)caster->query_cap_name() + " looks up from "+
    caster->query_possessive()+" knife and watches as it begins to hover and dance in the air.",
    environment(caster), ({ caster }) );
  seteuid(getuid());
  ob = new("/wizards/zortek/pet/knife");
  ob->set_up(power);
  ob->set_owner((string)caster->query_name());
  ob->set_name((string)at->query_name());
  ob->set_id( (string *)at->query_id());
  ob->set_property("melee damage", (mapping)at->query_all_wc());
  old_short = explode(at->query_short(), " ");
  switch ( old_short[0] ){
    case "a" :
    case "A" :
    case "an" :
    case "An" :
      old_short -= ({ old_short[0] });
      break;
    default:
  }
  new_short = implode(old_short, " ");    
  ob->set_short(new_short+" (%^CYAN%^Dancing%^RED%^)");
  ob->set_long(at->query_long());
  ob->move(environment(caster));
  at->remove();
  remove();
  return;
}
