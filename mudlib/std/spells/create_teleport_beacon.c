inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","create teleport beacon");
    set_property("skill","magery");
    set_property("casting time",24);
    set_property("base mp cost",24);
    set_property("dev cost", 62);
    set_property("fast dev cost", 159);
   set_property("spell level", 11);
    set_property("moon","luna");
    set_property("caster message","You create a teleport beacon.");
    set_property("target message","");
    set_property("observer message","$C casts create teleport beacon.");
    set_property("spell type",({ }));
    set_property("no target", 1);
    set_property("duration", "until logout");
    return;
}

void info() {
message("help",
"This spell creates an invisible teleport beacon in the room where you "
"stand.  You may later cast teleport or mass teleport, and you will be "
"transported to the beacon's location.  After casting, the energy of the "
"beacon fades very slowly.  Higher power levels cause slower fading.  "
"If the beacon had faded, you must cas teleport at a higher power to "
"compensate.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  
  if(flag) {
    message("info", "Despite the fumble, you seem okay.", caster);
    caster->set("teleport beacon",
      ([ "room" : "/wizards/diewarzau/room/warp",
          "power" : power, "time" : time() ]) );
    remove();
    return;
  }
  if(environment(caster)->query_property("no teleport")) {
     message("info", "You may not create a teleport beacon here.",
            caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  caster->set("teleport beacon",
      ([ "room" : base_name(environment(caster)),
          "power" : power, "time" : time() ]) );
  message("info", "You may now teleport to this location.", caster);
  remove();
  return;
}
