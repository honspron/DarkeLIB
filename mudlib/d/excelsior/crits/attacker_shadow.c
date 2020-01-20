// /std/spells/shadows/attacker_shadow

object to,from;

inherit "/std/spells/shadows";

void start_shadow(object doer,object target) {
	from = doer;
	to = target;
	begin_shadow(from);
}

object query_current_attacker() {
	return to;
}

void create() {
	::create();
	to = 0;
	from = 0;
}
