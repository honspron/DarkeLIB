#include <daemons.h>

inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","regeneration");
    set_property("skill","prayer");
    set_property("casting time", 25);
    set_property("base mp cost",75);
    set_property("dev cost", 61);
    set_property("fast dev cost", 135);
    set_property("spell level", 12);
    set_property("moon","ankh");
    set_property("caster message","You cast regeneration at $T.");
    set_property("target message","$C casts regeneration at you.");
    set_property("observer message","$C casts regeneration at $T.");
    set_property("must be present",1);
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This spell regenerates lost limbs.  The limb must be supplied as an argument, "
"or a random limb will be regenerated.  Note that you cannot regenerate a limb "
"to which another limb is connected, meaning you cold not, for instance, "
"regenerate someone's hand if they are missing the entire arm.  If the spell "
"is cast at power level 4 or more, however, regenerating the arm will CAUSE "
"the hand to grow back.  Higher power level also increases the amount of "
"hit points returned to the regenerated limb and decreases the time taken for "
"it to grow back.\n"
"	example: cast *3 regeneration at bob with right hand",
this_player());
}

void spell_func(object from, object at, int pow, string args, int flag)
{
  mapping limb_info;
  string *missing, *there, limb;

  limb = args;
  there = (string *)at->query_limbs();
  missing = (string *)at->query_severed_limbs();
  if(!missing || !sizeof(missing)) {
    message("info", (string)at->query_cap_name() +
	    " is not missing any limbs!", from);
    from->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(!limb && !strlen(limb)) limb = missing[random(sizeof(missing))];
  if(member_array(limb, missing) == -1) {
    message("info", (string)at->query_cap_name() +
            " is not missing that limb.", from);
    from->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(member_array(limb, there) != -1) {
    message("info", (string)at->query_cap_name() +
            " already has that limb.", from);
    from->add_mp(props["mp cost"]);
    remove();
    return;
  }
  limb_info= (mapping)RACE_D->query_limb_info(limb,(string)at->query("race"));
  if(!limb_info) {
    message("info", "That limb cannot be regenerated.", from);
    from->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(limb_info["attach"] != "0") {
    if(member_array(limb_info["attach"], there) == -1) {
      message("info", (string)at->query_cap_name() +
	      " needs a "+ limb_info["attach"] + " first.", from);
      from->add_mp(props["mp cost"]);
      remove();
      return;
    }
  }
  message("my_action", "The limb begins to grow back.", from);
  message("info", "Your "+ limb + " begins to grow back.", at);
  call_out("regen_limb", (600 / pow), limb, limb_info,
	   at, pow);
  return;
}

void regen_limb(string limb, mapping limb_info, object at, int pow) {

  at->add_limb(limb, limb_info["ref"], (int)at->query_max_hp()/
	       limb_info["max"], 
	       ((int)at->query_max_hp()/limb_info["max"]) / (7 - pow), 0);
  if(member_array(limb, (string *)RACE_D->
		  query_wielding_limbs((string)at->query("race"))) != -1)
    at->add_wielding_limb(limb);
  message("info", "Your " + limb + " has fully regrown.", at);
  if(!limb_info["ref"] || !strlen(limb_info["ref"]) || pow <= 3) {
    remove();
    return;
  }
  limb = limb_info["ref"];
  limb_info= (mapping)RACE_D->query_limb_info(limb,(string)at->query("race"));
  message("info", "Your "+ limb + " begins to grow back.", at);
  call_out("regen_limb", (600 / pow), limb, limb_info,
	   at, pow);
  return;
}

