inherit "/std/spells/long_term_spell";



void create() {

    ::create();

    set_property("name","self power");

    set_property("skill","enchantment");

    set_property("duration", "permanent");

    set_property("casting time",4);

    set_property("base mp cost",66);

    set_property("dev cost", 87);

    set_property("fast dev cost", 290);

    set_property("spell level", 17);

    set_property("moon","luna");

    set_property("caster message","You begin to power the scroll.");

    set_property("target message","");

    set_property("observer message","$C begins writing on a scroll.");

    set_property("spell type",({ }));

    set_property("target type", "any");

    set_property("prereq", "scribe scroll");
    set_property("must be present", 1);

    return;

}



void info() {

message("help",

"This spell must be cast on a scroll which has had 'scribe scroll' successfully "

"cast upon it.  It reduces the mp cost of casting the spell to 1/2 normal cost "

"(for power 1) up to 1/4 normal (for power 3).  Casting at power 4-6 has the "

"same effect as power 1-3 except it takes half the time.  "

"This is a long-term spell (see help long-term), and it takes very much real "

"time to cast.  If you are interrupted while casting, "

"you may pick up again at a later time.  If you are continuing the spell, no arguements need to "

"be supplied.  If the scroll already has that spell written on it, it will be replaced by the new "

"casting, even if it is lower.\n\n"

"Syntax: cast *3 self power at <scroll>\n"

"NOTE: If the spell is cast more than once on a scroll, it is not cumulative...the newer spell "

"will replace the old.",

this_player());

}



void spell_func(object caster, object at, int power, string args, int flag) {

  int idx, mult, time, mod;

  string file;

  

  if(!at->id("parchment scroll") || !at->query_spell()) {

    message("info", "You must cast this spell on a spell scroll which has "+

      "had 'scribe scroll' successfully cast upon it.",

	    caster);

	  caster->add_mp(props["mp cost"]);

    remove();

    return;

  }

  if(flag) {

    message("info", "You misdirect the summoning energies and disintegrate "+

	    "the scroll!", caster);

    message("info", (string)caster->query_cap_name() +

	    " inadvertently disintigrates the scroll.",

	    environment(caster), ({ caster }) );

    at->remove();

    remove();

    return;

  }

  seteuid(getuid());

  file = "/std/spells/"+replace_string((string)at->query_spell(), " ", "_");

  if(!file_exists(file+".c")) {

    message("info", "Cannot find the spell file...this is a BUG.", caster);

    caster->add_mp(props["mp cost"]);

    remove();

    return;

  }

  idx = (int)file->query_property("spell level");

  set_work_message("%^CYAN%^You power the scroll.");

  if(power > 3) {

    power -= 3;

    mult = 2;

  } else

    mult = 1;

  time = idx *(90 + power*120)/mult;

  mod = 40+2*props["spell level"];

  if(!start_work(at, caster, (time*mod)/caster->query_skill("enchantment"), power) &&

    (int)at->query_property("self power") > 1)

    message("info", "Replacing old casting...", caster);

  return;

}



void finish_work(object caster, object at, int power) {

//  int ench;



  if(power <= 0) {

    message("info", "BUG in Enchanter spell....unable to complete.",

	    environment(caster));

    remove();

    return;

  }

  message("info", "You are finished powering.", caster);

  message("info", (string)caster->query_cap_name() + " concludes scribing the scroll.",

	  environment(caster), ({ caster }) );

	at->set_property("self power", 1+power);

  remove();

  return;

}



