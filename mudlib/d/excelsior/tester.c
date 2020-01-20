// /wizards/excelsior/tester
// Excelsior 5-6-96

inherit "std/Object";

void create() {
	::create();
	set("short","Crit tester");
	set("long","crit tester. Usage: test <func> <who>. Excelsior");
	set_weight(1);
	set_value(1);
	set_name("tester");
	set("id",({"tester","test","crit","crit tester"}));
}

void init() {
	::init();
	add_action("test","test");
}

int test(string str) {
	string func;
	mixed who;
	write("hello");
	if(sscanf(str,"%s %s",func,who) != 2) return 0;
		if(!who) { write("not who1"); return 0; }
		if(!func) { write("not func"); return 0; }
	who = present(who,environment(environment(this_object())));
		if(!who) {write(
"not who2"); return 0; }
	if(!living(who)) return 0;
	call_other("/wizards/excelsior/crits/crit_func",func,this_player(),who);
	return 1;
}
