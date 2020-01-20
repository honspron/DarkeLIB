inherit "/std/spells/spell";



void create() {

    ::create();

    set_property("name","soul gate");

    set_property("skill","prayer");

    set_property("casting time",60);

    set_property("base mp cost",170);

    set_property("dev cost", 81);

    set_property("fast dev cost", 250);

    set_property("spell level", 17);

    set_property("moon","ankh");

    set_property("caster message","You cast soul gate at $T.");

    set_property("target message","$C casts soul gate at you.");

    set_property("observer message","$C casts soul gate at $T.");

    set_property("spell type",({ }));

    set_property("target type", "player");

    set_property("must be present",1);

    set_property("prereq", "resurrect");
    return;

}



int res_spell() { return 1; }



void info() {

message("help",

"This spell is extremely similar to the resurrect spell (see 'help spell "

"resurrect'), except that it is more powerful.  If a player's corpse has "

"decayed, or the player has logged off since he or she died, soul gate "

"opens a gate to the astral plane which allows the player's soul to "

"return to the prime material without the usual penalty.",

this_player());

}



void spell_func(object caster, object at, int power, string args, int flag) {

  int lvl_diff, c_level, a_level;

  object ob;



  if(flag) {

    message("my_action", "You accidently mangle your soul.",

	    caster);

    message("other_action", (string)caster->query_cap_name() + 

	    " accidently mangles "+

	    possessive(caster) + " own soul!", environment(caster),

	    ({ caster }) );

    caster->add_hp(-1 * ((int)caster->query_hp()) + 5 - power);

    remove();

    return;

  }

  if(!at->query_ghost()) {

    message("info", at->query_cap_name()+" isn't dead...are you stoopid?", caster);

    return;

  }

  a_level = (int)at->query_level();

  c_level = (int)caster->query_level();

  if(a_level < c_level) {

    lvl_diff = a_level - c_level;

    if(lvl_diff - power > 4) {

      message("my_action", "The spell is not powerful enough to soul gate that "+

	    "player.", caster);

      message("other_action", (string)caster->query_cap_name() + "'s "+

	    "spell was insufficient to soul gate "+

	    (string)at->query_cap_name() + ".", environment(caster),

	    ({ caster, at }) );

      message("other_action", (string)caster->query_cap_name() + "'s "+

            "spell was insufficient to soul gate you.", at);

      remove();

      return;

    }

  }

  if(!objectp(at->query("corpse ob"))) {

    seteuid(getuid());

    ob = new("/std/Object");

    ob->set_name("gate");

    ob->set_id( ({ "gate" }) );

    ob->set_weight(100000000);

    ob->set_short("A soul gate");

    ob->set_long("This is a magical one-way portal out of the astral plane.");

    ob->move(environment(at));

    at->set("corpse ob", ob);

    call_out("kill_gate", 30, ob);

  }

  at->revive();

  caster->add_exp2((int)at->query_level()* 500);

  return;

}



void kill_gate(object what) {

  if(!objectp(what)) return;

  what->remove();

  remove();

  return;

}

