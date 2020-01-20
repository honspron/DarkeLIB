#include <std.h>
#include <nevin.h>
inherit "/std/vault";

void create(){
	::create();
	set_property("indoors", 1);
	set_property("light", 1);
	set_property("night light", -3);
	set_property("no castle", 1);
	set("short", "Corpse Market Storage Room");
	set("long",
		"Cold dead bodies fill small cubicles made of stone.  "
		"Only the dead silence disturbs the corpses in their "
		"temporary rest."
	);
	set_exits( ([
		"south": ROOMS+"corpse_market"
	]) );
	set_items( ([
		({"metal door", "door"}): (: call_other, this_object(), "look_door" :),
		({"bodies", "corpses"}): "These corpses are in excelent "
			"condition, no wonder all the necromancers do their "
			"shopping here."
	]) );
	set_door("metal door", "corpse_market", "south", "kuril corpse 
		market storage");
	set_open ("metal door", 0);
	set_locked("metal door", 1);
	set_lock_level("metal door", 25);
	set_property("storage room", 1);
	return;
}

void reset() {
	object *inv, ob;
	int i;

	::reset();
	seteuid(getuid());
	inv = all_inventory(this_object());
	while(i--) if(!living(inv[i])) inv[i]->remove();
	for(i=1; i<=5;i++) {
		ob = new(MISC+"emb_corpse");
		ob->set_level(1);
		ob->set_value(100);
		ob->move(this_object());
		if(i < 4) {
			ob = new(MISC+"emb_corpse");
			ob->set_level(2);
			ob->set_value(200);
			ob->move(this_object());
		}
		if(i < 2) {
			if(random(4) == 0) {
				ob = new(MISC+
					"emb_corpse");
				ob->set_level(3);
				ob->set_value(300);
				ob->move(this_object());
			}
			if(random(5) == 0) {
				ob = new(MISC+
					"emb_corpse");
				ob->set_level(4);
				ob->set_value(400);
				ob->move(this_object());
			}
			if(random(6) == 0) {
				ob = new(MISC+
					"emb_corpse");
				ob->set_level(5);
				ob->set_value(500);
				ob->move(this_object());
			}
			if(random(7) == 0) {
				ob = new(MISC+
					"emb_corpse");
				ob->set_level(6);
				ob->set_value(600);
				ob->move(this_object());
			}
			if(random(8) == 0) {
				ob = new(MISC+
					"emb_corpse");
				ob->set_level(7);
				ob->set_value(700);
				ob->move(this_object());
			}
			if(random(10) == 0) {
				ob = new(MISC+
					"emb_corpse");
				ob->set_level(7 + random(3));
				ob->set_value(1500);
				ob->move(this_object());
			}
			if(random(100) == 0) {
				ob = new(MISC+
					"emb_corpse");
				ob->set_level(10 + random(10));
				ob->set_value(3000);
				ob->move(this_object());
			}
		}
	}
	return;
}

void look_door() {
	if(query_open("metal door")) {
		write("The metal door is open.");
	}
	else {
		write("The metal door is closed.");
	}
}
