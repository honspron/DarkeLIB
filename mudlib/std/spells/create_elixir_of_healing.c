inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","create elixir of healing");
    set_property("skill","prayer");
    set_property("casting time",24);
    set_property("base mp cost", 37);
    set_property("dev cost", 42);
    set_property("fast dev cost", 119);
    set_property("spell level", 9);
    set_property("moon","ankh");
    set_property("caster message","You summon the energies to create a healing potion.");
    set_property("target message","$C summons the energies to create a healing potion.");
    set_property("observer message","");
    set_property("spell type",({ }));
    set_property("no target",1);
    return;
}

void info() {
message("help",
"This spell is used to create healing potions which may be imbibed at a "
"later time.  Once the potion is created, it may be saved for as long as "
"you want.  In order to create the potion, you must have a vial ready.",
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
  for(i=1; i<=6; i++) roll += (random(6) +1);
  ob->fill_vial("a white potion", "healing_potion", 
		"/wizards/diewarzau/obj/misc/heal_func", 
	    	(flag?-1:1) * power * roll);
  message("info", "The vial fills with an unearthly white potion.",
	  caster);
  /*
   * succesful casts will no longer get the fumble message
   *   Nevin 09/30/96
   */  
  
  if(flag) {
    message("info", "The potion appears fine despite the fumble...", caster);
  }
  remove();
  return;
}
