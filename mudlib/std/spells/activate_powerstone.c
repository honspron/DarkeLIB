inherit "/std/spells/long_term_spell";

void create() {
    ::create();
    set_property("name","activate powerstone");
    set_property("skill","enchantment");
    set_property("duration", "permanent");
    set_property("casting time",4);
    set_property("base mp cost",95);
    set_property("dev cost", 85);
    set_property("fast dev cost", 261);
   set_property("spell level", 10);
    set_property("moon","luna");
    set_property("caster message","You begin to charge the stone.");
    set_property("target message","");
    set_property("observer message","$C begins to magically charge a power stone.");
    set_property("spell type",({ }));
    set_property("target type", "any");
    set_property("must be present", 1);
    return;
}

void info() {
message("help",
"This spell allows you to charge a power stone.  The powerstone may then be used for "
"extra magic points.  Blank powerstones of various sizes are available at the "
"magic shop.  You must cast this spell at a power equal to the size of the "
"powerstone divided by 10 (size 40 stone = power 4).  That means powerstones bigger "
"than 60 will require MULTIPLE CASTINGS.   "
"This is a long-term spell (see help long-term), and it takes very much real "
"time to cast.  The spell must be cast on a clay figurine, which is "
"available at most magical shops.  If you are interrupted while casting, "
"you may pick up again at a later time.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  int time, mod;
  if(!at->id("power stone") || at->is_active()) {
    message("info", "You must cast this spell at a blank powerstone.",
	    caster);
    remove();
    return;
  }
  if(flag) {
    message("info", "You misdirect the summoning energies and shatter "+
	    "the stone!", caster);
    message("info", (string)caster->query_cap_name() +
	    " inadvertently shatters the powerstone.",
	    environment(caster), ({ caster }) );
    at->remove();
    remove();
    return;
  }
  set_work_message("%^CYAN%^You charge the stone.");
  time = 550*power;
  mod = 40+2*props["spell level"];
  start_work(at, caster, (time*mod)/caster->query_skill("enchantment"), power);
  return;
}

void finish_work(object caster, object at, int power) {
  int so_far;
  int to_go;

  if(power <= 0) {
    message("info", "BUG in powerstone spell....unable to complete.",
	    environment(caster));
    remove();
    return;
  }
  message("info", "You complete the spell.", caster);
  message("info", (string)caster->query_cap_name() +
    " finishes charging a power stone.",
	  environment(caster), ({ caster }) );
  so_far = (int)at->query_property("total casting");
  if(!so_far) so_far = 0;
  so_far += power * 10;
  if(so_far >= (int)at->query_size()) {
    message("info", "The powerstone is fully charged and ready for use.",
      caster);
    at->activate_me();
  } else {
    at->set_property("total casting", so_far);
    so_far = (int)at->query_size() - so_far;
    to_go = so_far/10;
    if(so_far%10 > 0) to_go++;
    message("info", "This powerstone still needs "+to_go+" power level(s) "+
      "worth of casting before it is charged.", caster);
  }
  remove();
  return;
}

