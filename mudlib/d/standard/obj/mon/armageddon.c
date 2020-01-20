inherit "std/monster";

#include <daemons.h>

void create() {
    ::create();
    set_name("gamedriver");
    set_id( ({ "armageddon", "crasher", "asshole", "game crasher", "armageddon the game crasher" }) );
    set_short("The All Powerful GameDriver");
    set_long("He appears once and briefly only to cause doom to the mud.\n");
    set_level(1);
    set_exp(1);
    set_property("enhance criticals", -10); 
    set_property("base hp regen", 9999);
    set_property("melee damage", ([ "crushing" : 200 ]));
    set_skill("melee", 800);
    set_skill("perception", 200);
    set_skill("dodge", 16);
    set_stats("strength", 2000);
    set_skill("attack", 2000);
    set_overall_ac(9999);
    set_max_hp(900000);
    set_hp(900000);
    set_stats( "dexterity", 1000);
    set_stats( "strength", 1000);
    set_body_type("human");
}


void catch_tell(string str) {
    string who, what, extra;

    if((int)SHUT_D->query_time_remaining() > 180) return;
    if(sscanf(str, "%s %s %s", who, what, extra) != 3) return;
    if(what != "tells") return;
    who = lower_case(who);
    if(!find_living(who)) return;
    find_living(who)->move("/d/daybreak/room/shop/general_store");
    tell_object(find_living(who), "You are magically teleported somewhere.\n");
}
