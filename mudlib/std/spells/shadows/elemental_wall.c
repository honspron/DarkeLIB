#include <spell.h>

inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","elemental wall");
    set_property("skill","elementalism");
    set_property("elemental spell", 1);
    set_property("casting time",12);
    set_property("base mp cost",38);
    set_property("dev cost", 29);
    set_property("fast dev cost", 105);
    set_property("spell level", 6);
    set_property("moon","luna");
    set_property("caster message","You create an elemental wall.");
    set_property("target message","");
    set_property("observer message","$C creates an elemental wall.");
    set_property("spell type",({ }));
    set_property("no target", 1);
    set_property("duration", 180);
    return;
}

void info() {
message("help",
"This spell creates a wall over an exit in a room.  If a player or monster, "
"including you, passes the wall, he/she will take damage and critical "
"hit(s) according to the element.  It is useful for covering your tracks.\n"
"Syntax: cast *3 elemental wall at <exit>\n"
"Ex: cast *3 elemental wall at north\n",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob, room;
  string recip;

  if(flag) {
    message("info", "You suffer no ill effects, but the mp "+
      "cost is doubled.", caster);
    caster->add_mp(-1 * props["mp cost"]);
    remove();
    return;
  }
  if(!args) {
    message("info", "See 'help spell illusionary wall' for syntax.",
      caster);
    caster->add_mp(-props["mp cost"]);
    remove();
    return;
  }
  if(member_array(args, (string *)environment(caster)->query_exits()) < 0) {
    message("info", "There is no '"+args+"' exit from the room.",
      caster);
    caster->add_mp(-props["mp cost"]);
    remove();
    return;
  }
  if(!catch(room=find_object_or_load((string)environment(caster)->
    query_exit(args)))) {
    recip = (string)room->query_direction(file_name(environment(caster)));
    if(member_array(recip, (string *)room->query_exits()) > 0) {
      ob = new("/wizards/diewarzau/obj/misc/ele_wall");
      ob->set_caster(caster);
      ob->set_pow(power);
      ob->set_verb(recip);
      ob->set_elements(props["element types"]);
      ob->set_ele_name(props["element"]);
      ob->set_dur(props["duration"]);
      ob->move(room);
    }
    else recip = 0;
  }
  else recip = 0;
  ob = new("/wizards/diewarzau/obj/misc/ill_wall");
  ob->set_caster(caster);
  ob->set_pow(power);
  ob->set_verb(args);
  ob->set_dur(props["duration"]);
  ob->move(environment(caster));
  message("info", "%^CYAN%^%^BOLD%^A wall of "+props["element"]+" appears over the "+args+
    " exit.", EC);
  if(recip && room)
    message("info", "%^CYAN%^%^BOLD%^A wall of "+props["element"]+" appears over the "+recip+
      " exit.", room);
  remove();
  return;
}
