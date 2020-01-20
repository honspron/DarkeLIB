// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud
// Breeding Pit for the Chaotic-Lord GM Weapon, Chemoch
// 10/02/96

#include <std.h>

inherit OBJECT;

int THRALLS;

void create() {
	::create();
	set_name("breeding pit");
	set("id", ({ "breeding pit", "pit" }) );
	set("short", "%^BLUE%^%^BOLD%^a foul pit of darkness%^MAGENTA%^%^BOLD%^");
	set("long",
		"Swirling around and around, forms can be seen just below "
		"the surface of the black surface."
	);
	set_weight(1000000);
	THRALLS = 30;
	call_out("create_spawn", 5);
	call_out("pool_message", random(15) + 45);
	return;
}

void destroy_me() {
	message("info", "%^BLUE%^%^BOLD%^The pool of darkness spins in upon "
		"itself and disappears.%^RESET%^", ENV(TO));
	TO->remove();
	return;
}

void create_spawn(object master) {
	object ob;
	string owner;
	message("info", "%^BLUE%^%^BOLD%^From the foul pit emerges a "
		"creature of shadow and darkness.", ENV(TO));
	seteuid(getuid());
	ob = new("/d/damned/guilds/chaotic-lord/nihil");
	ob->set_up();
	owner = call_other("/d/damned/guilds/join_rooms/chaotic-lord_join",
		"query_master");
	ob->set_owner("nevin");
//	ob->set_owner(master);
	ob->move(ENV(TO));
	THRALLS -= 1;
	if(THRALLS == 0) { TO->destroy_me(); }
	call_out("create_spawn", 5);
	return;
}

void pool_message() {
	string mess;
	switch(random(10)) {
		case 0: mess = "The pool boils and turns."; break;
		case 1: mess = "A moaning sound comes up from the pool."; break;
		case 2: mess = "The breeding pit froths."; break; 
		case 3: mess = "A scream escapes from the pit."; break;
		case 4: mess = "A dismembered arm floats to the surface of "
			"the pit and then disappears."; break;
		case 5: mess = "Bubbles burst upon the surface of the pool "
			"sending ichor about the room."; break;
		case 6: mess = "A foul scent rises from the dark pool."; break;
		case 7: mess = "The pool casts strange shadows about you.";
			break;
		case 8: mess = "A cold fear grips your heart!"; break;
		case 9: mess = "Your knees begin to shiver before the "
			"retched breeding pit."; break;
	}
	message("info", "%^BLUE%^%^BOLD%^"+mess+"%^RESET%^", ENV(TO));
	call_out("pool_message", random(15) + 45);
	return;
}

void feed_me_seymour() {
	message("info", "The pit glows briefly and then subsides...", ENV(TO));
	THRALLS += 10;
	return;
}

int query_status() { return THRALLS; }
