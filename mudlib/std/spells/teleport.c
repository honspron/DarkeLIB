#include <clock.h>

inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","teleport");
    set_property("skill","magery");
    set_property("casting time",3);
    set_property("base mp cost",41);
    set_property("dev cost", 62);
    set_property("fast dev cost", 135);
    set_property("spell level",11);
    set_property("moon","luna");
    set_property("caster message","You cast a teleport spell.");
    set_property("target message","");
    set_property("observer message","$C casts a teleport spell.");
    set_property("spell type",({ }));
    set_property("no target", 1);
    set_property("duration", "instantaneous");
    set_property("prereq", "create teleport beacon");
    return;
}

void info() {
message("help",
"This spell teleports you to the last location of your teleport beacon.  "
"You must, of course, have created one to use this spell (see 'help spell "
"create teleport beacon').  If it has been a while since the beacon was cast "
"(a few mud hours or so), or the beacon was cast at a low power, this spell must "
"be cast at a higher power to work.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object room;
  mapping tmp;

  if(flag) {
    message("info", "You get stuck in the warp while teleporting!.", caster);
    caster->move_player("/wizards/diewarzau/room/warp", 0);
    remove();
    return;
  }
  tmp = (mapping)caster->query("teleport beacon");
  if(!tmp || !mapp(tmp)) {
    message("info", "Cannot find your teleport beacon.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  room = find_object_or_load(tmp["room"]);
  if(room->query_property("no teleport")) {
     message("info", "You may not teleport to that location.",
            caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  power += tmp["power"];
  if(power * 2 < (time() - tmp["time"])/HOUR) {
    message("info", "The beacon has faded too much for a teleport spell of that power.",
          caster);
    remove();
    return;
  }
  message("info", "You teleport to the beacon.", caster);
  caster->move_player(room, 0);
  remove();
  return;
}
