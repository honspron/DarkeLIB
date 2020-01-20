inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","call divine plate");
    set_property("skill","worship of k'thach");
    set_property("casting time",10);
    set_property("base mp cost",18);
    set_property("dev cost", 5);
    set_property("fast dev cost", 14);
    set_property("spell level", 1);
    set_property("moon","luna");
    set_property("caster message","You call a suit of Divine Plate Mail to your hands.");
    set_property("target message","");
    set_property("observer message","$C calls a suit of Divine Plate Mail into creation.");
    set_property("spell type",({ }));
    set_property("no target", 1);
    set_property("duration", 420);
    return;
}

void info() {
message("help",
"This spell summons a suit of holy plate into existence.  "
"It is about as effective as regular plate mail, but is much "
"lighter.  It will disappear if you remove it or when the "
"duration expires.  Note that, depending on your race, you may not "
"be able to wear the entire suit.\n"
	"NOTE: Casting this spell causes you to unequip "
"weapons AND armour!",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;
  object *armours;

  if(flag) {
    message("info", "The fumble causes you to be drained of "
      "half of your remaining mp!", caster);
    caster->add_mp(-1 * (int)caster->query_mp() / 2);
    remove();
    return;
  }
  caster->force_me("unequip");
  armours = allocate(6);
  ob = new("/wizards/diewarzau/obj/armour/wbrstplt");
  ob->move(caster);
  armours[0] = ob;
  ob = new("/wizards/diewarzau/obj/armour/wleggin");
  ob->move(caster);
  armours[1] = ob;
  ob = new("/wizards/diewarzau/obj/armour/wgaunt");
  ob->move(caster);
  armours[2] = ob;
  ob = new("/wizards/diewarzau/obj/armour/wboots");
  ob->move(caster);
  armours[3] = ob;
  ob = new("/wizards/diewarzau/obj/armour/wbracers");
  ob->move(caster);
  armours[4] = ob;
  ob = new("/wizards/diewarzau/obj/armour/whelmet");
  ob->move(caster);
  armours[5] = ob;
  map_array(armours, (: call_other :), "set_caster", caster);
  caster->force_me("wear breast-plate");
  caster->force_me("wear boots");
  caster->force_me("wear helmet");
  caster->force_me("wear leggings");
  caster->force_me("wear gauntlets");
  caster->force_me("wear bracers");
  delayed_call("remove_all", props["duration"], caster, armours);
  return;
}

void remove_all(object caster, object *armours) {
  object ob;

  if(caster) {
    message("info", "%^CYAN%^The divine plate disappears.",
      caster);
  } else return;
  foreach(ob in armours) {
    if(!ob) continue;
    ob->remove();
  }
  return;
}

