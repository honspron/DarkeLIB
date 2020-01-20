inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","delay rune");
    set_property("skill","enchantment");
    set_property("casting time",9);
    set_property("base mp cost",41);
    set_property("dev cost", 62);
    set_property("fast dev cost", 183);
    set_property("spell level", 12);
    set_property("moon","luna");
    set_property("caster message","You cast delay rune at $T.");
    set_property("target message","");
    set_property("observer message","$C casts delay rune at $T.");
    set_property("spell type",({ }));
    set_property("target type", "any");
    set_property("must be present", 1);
    set_property("can be in room", 1);
    set_property("can be in room", 1);
    set_property("duration", "variable (see below)");
    return;
}

void info() {
message("help",
"This spell allows you to delay the effect of a rune, allowing it to "
"go off, affecting everyone in the room (including you if you are there).  "
"After casting this spell on a rune, it will not affect eople coming into "
"the room, and the rune will disappear after the delay goes off.\n"
"Syntax: cast *3 delay rune at <rune> with <time>\n"
"Ex: cast *3 delay rune at poison rune with 75\n"
"The above will delay the rune for 75 sec.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  int time;
  
  if(!at->is_rune()) {
    message("info", "You must cast this spell at a rune.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(at->query("delay")) {
    message("info", "That rune is already delayed.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(flag) {
    message("info", "You cause the rune to go off immediately!",
        caster);
    at->delay_action();
    remove();
    return;
  }
  if(!sscanf(args, "%d", time)) {
    message("info", "Incorrect syntax.  See 'help spell delay rune'.",
        caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  at->delay_rune(time);
  remove();
  return;
}
