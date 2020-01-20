inherit "/std/spells/spell";

string caster_name;

void create() {
    ::create();
    set_property("name","sanctuary");
    set_property("skill","prayer");
    set_property("casting time",35);
    set_property("base mp cost",45);
    set_property("dev cost", 38);
    set_property("fast dev cost", 105);
    set_property("spell level", 7);
    set_property("moon","luna");
    set_property("caster message",
      "You summon a sanctuary in the room.");
    set_property("target message","");
    set_property("observer message",
      "$C summons a sanctuary in the room, preventing entry.");
    set_property("spell type",({ }));
    set_property("no target", 1);
    set_property("duration", 240);
    return;
}

void info() {
    message("help",
      "This spell prohibits entry into the caster's room by any living thing.  "
      "You may exit the room, but not return until the spell expires.  "
      "The caster may remove the aura at any time by typing 'remove sanctuary' in "
      "the room containing it.  The caster may freely walk in and out of the "
      "sanctuary.",
      this_player());
}

void spell_func(object caster, object at, int power, string args, int flag)
{
    object ob, ob2, *inv;
    int i;
    string *exits;

    if(environment(caster)->query_sanctuary()) {
	message("info", "This room already has a sanctuary.", caster);
	caster->add_mp(props["mp cost"]);
	remove();
	return;
    }
    if(file_name(environment(caster)) == "/wizards/misery/arena/booths_room" ||
      file_name(environment(caster)) == "/wizards/misery/arena/battle_room" ||
      file_name(environment(caster)) == "/wizards/misery/arena/listen_room") {
	message("info", "You cannot do that here.", caster);
	remove();
	return;
    }
    if(!environment(caster)->query_exits() ||
      !sizeof((string *)environment(caster)->query_exits())) {
	message("info", "This room has no exits!", caster);
	caster->add_mp(props["mp cost"]);
	remove();
	return;
    }
    seteuid(getuid());
    ob = new("/std/spells/shadows/room_no_enter");
    ob->start_shadow(environment(caster), props["duration"],
      "The sanctuary about this room dissipates.");
    ob->set_no_stack(1);
    ob->set_receive_func((: call_other, this_object(), "is_living" :));
    caster_name = (string)caster->query_name();
    ob2 = new("/wizards/diewarzau/obj/misc/sanc_ob");
    ob2->move(environment(caster));
    ob2->set_caster(caster_name);
    ob2->set_dur(props["duration"]);
    ob2->set_shadow(ob);
    if(flag) {
	message("info", "You have misdirected the sanctuary, forcing all "+
	  "present out of the room!", caster);
	message("info", (string)caster->query_cap_name() + 
	  " has misdirected "+possessive(caster)+" spell, "+
	  "forcing you out of the room!", environment(caster),
	  ({ caster }) );
	inv = all_inventory(environment(caster));
	i = sizeof(inv);
	exits = (string *)environment(caster)->query_exits();
	while(i--) {
	    if(!living(inv[i])) continue;
	    inv[i]->move_player((string)environment(caster)->
	      query_exit(exits[random(sizeof(exits))]));
	}
	caster_name = "";
    }
    call_out("remove", props["duration"] + 2);
    return;
}

int is_living(object who) { 
    if(!living(who)) return 0;
    if((string)who->query_name() == caster_name) return 0;
    return 1;
}


