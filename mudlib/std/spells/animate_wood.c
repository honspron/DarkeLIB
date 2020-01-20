inherit "/std/spells/long_term_spell";

void create() {
    ::create();
    set_property("name","animate wood");
    set_property("skill","woodland lore");
    set_property("duration", "permanent");
    set_property("casting time",4);
    set_property("base mp cost",221);
    set_property("dev cost", 123);
    set_property("fast dev cost", 361);
    set_property("spell level", 25);
    set_property("moon","luna");
    set_property("caster message","You begin to animate the wood.");
    set_property("target message","");
    set_property("observer message","$C begins to animate a wood.");
    set_property("spell type",({ }));
    set_property("target type", "any");
    set_property("must be present", 1);
    return;
}

void info() {
message("help",
"This spells animates a wooden board into a Treant, a powerful, living
tree, who will serve you as any other pet. Treants will serve you by
fighting beside you in combat and can be set to protect rooms. This is a
long-term spell (see help long-term), and it takes very much real tim eto
cast. The spell must be cast on a wooden board at least the size of a
telephone pole, which must be gathered with the 'lumberjack' skill. If you
are interrupted while casting, you may pick up again at a later time.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag)
{
 if(!at->id("wood")) {
    message("info", "You must cast this spell at a wooden board.",
            caster);
    remove();
    return;
  }
   if(at->query_wood() < 7) {
    message("info", "You must cast this spell on a wooden board of a least
telephone pole size.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(flag) {
    message("info", "You misdirect the summoning energies and destroy "+
          "the wooden board!", caster);
    message("info", (string)caster->query_cap_name() +
          " inadvertently splinters a wooden board.",
            environment(caster), ({ caster }) );
    at->remove();
    remove();
    return;
  }
 set_work_message("You animate the wood.");
  start_work(at, caster, 7400+560*power, power);
  return;
}

void finish_work(object caster, object at, int power) {
  object ob;

  if(power <= 0) {
    message("info", "BUG in undead spell....unable to complete.",
            environment(caster));
    remove();
    return;
  }
 message("info", "%^BOLD%^%^GREEN%^The wooden board transforms into a Treent.", caster);
  message("info", (string)caster->query_cap_name() + " utters some "+
         "woodland incantations, and a wooden board "+
        "transforms into a Treant.",
          environment(caster), ({ caster }) );
      message("info", "%^BOLD%^%^GREEN%^The sound of the cracking branchs is heard across the land as a Treant takes it's first step.", users());
  at->remove();
  seteuid(getuid());
   ob = new("/wizards/diewarzau/obj/pet/treant");
  ob->set_up(power);
  ob->set_owner((string)caster->query_name());
  ob->move(environment(caster));
  remove();
  return;
}

