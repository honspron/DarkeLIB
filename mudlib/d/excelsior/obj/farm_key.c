// /wizards/excelsior/obj/farm_key

#include <std.h>

inherit OBJECT;

object owner,shadow;
int raise_str,time,when;

void remove_shadow();

void create() 
{
	::create();
	set_name("key");
	set("id",({"farm key","object","magical object","octogon","key"}));
	set("short","A strange magical object");
	set("long","This is a strange magical object that is in the shape of "+
		"an octogon. While you hold it it makes you feel stronger!");
	set_weight(90);
	set_value(1);
	time = 600;
	set_property("no save",1);
}

void reset() {
	::reset();
	if(!living(environment(this_object())) || !random(30)) {
		tell_room(environment(),"The octogon suddenly dissolves into thin air.",({}));
		raise_str = 0;
		remove();
	}
}

void set_time(int i) { time = i; }

void set_raise(int i) { raise_str = i; }

int move(mixed dest) {
	int x;
	remove_shadow();
	x = ::move(dest);
	if(living(environment(this_object()))) {
		raise_str = 1;
		shadow = new("/std/spells/shadows/stat_shadow");
		shadow->set_stat("strength");
		shadow->set_mod(5);
		owner = environment();
		shadow->start_shadow(owner,time,"%^BLUE%^The power of the octogon "+
			"suddenly fades into nothingness.");
		tell_object(owner,"You feel stronger as you pick up the octogon.");
		when = time();
	} else { raise_str = 0; }
	return x;
}

remove() {
	remove_shadow();
		::remove();
}

void remove_shadow() {
	if(raise_str && shadow) {
		shadow->external_destruct(shadow);
		if(living(owner)) 
			message("info","You feel weaker as you let go of the octogon.",
owner);
		time -= (time() - when);
		raise_str = 0;
	}
}
