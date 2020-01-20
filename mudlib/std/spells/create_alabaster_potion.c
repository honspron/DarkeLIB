inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","create alabaster potion");
    set_property("skill","prayer");
    set_property("casting time",24);
    set_property("base mp cost", 68);
    set_property("dev cost", 57);
    set_property("fast dev cost", 148);
    set_property("spell level", 12);
    set_property("moon","ankh");
    set_property("caster message","You summon the energies to create a powerful healing potion.");
    set_property("target message","$C summons the energies to create a powerful healing potion.");
    set_property("observer message","");
    set_property("spell type",({ }));
    set_property("no target",1);
    set_property("prereq", "create elixir of healing");
    return;
}

void info() {
message("help",
"This spell is a more powerful version of the 'create elixir of healing' "
"spell (see 'help spell create elixir of healing').  In addition to healing "
"lost hp, this potion will return mp as well as relieving stunning/paralysis "
"and halting damage due to bleeding and other wounds.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;
  int roll, i;

  ob = first_inventory(caster);
  while(ob && !(ob->query_vial() && !ob->query_property("drink func")))
    ob = next_inventory(ob);
  if(!ob) {
    message("info", "You need an empty vial to cast this spell.",
	    caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  roll = 0;
  for(i=1; i<=6; i++) roll += (random(10) +1);
  ob->fill_vial("an alabaster potion", "alabaster_potion", 
		"/wizards/diewarzau/obj/misc/heal_func", 
		power * roll * flag?-1:1);
  message("info", "The vial fills with an unearthly alabaster potion.",
	  caster);
  if(flag)
    message("info", "Despite the fumble, the potion appears okay.",
	    caster);
  remove();
  return;
}

