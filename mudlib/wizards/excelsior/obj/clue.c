// /wizards/excelsior/obj/clue

inherit "/std/Object";

void create() {
	::create();
	set_name("clue");
	set("id",({"clue","a clue"}));
	set("short","A clue");
	set("long","Congradulations! You have bought a clue. The clue is: "+
		"Go south from the poem.");
	set_weight(20);
	set_value(100);
}
