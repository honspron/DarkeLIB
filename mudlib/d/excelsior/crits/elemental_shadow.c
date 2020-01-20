#define AETHER_ELEMENTS ({"vacuum","electricity","fire","cold","holy"})

inherit "/std/spells/shadows/shadow";

object to,from;

void do_element();

void start_shadow(object target,object doer) {
	from = doer;
	to = target;
	message("info","start",environment(from));
	begin_shadow(from);
}

void heart_beat() {
	do_element();
	write("shadow test");
	next_shadow()->heart_beat();
}

void do_element() {
	string crit;
	int i;
	object tmp;
	i = random(30);
	message("info","do_element",environment(from));
	if(to->query_ghost() || !i || !find_living((string)to->query_name())) {
		if(!i) message("info","%^PINK%^You feel your elemental control "+
			"fade away...",from);
		remove();
		return;
	}
	i = random(3);
	tmp = present(to,environment(from));
	if(!tmp && !i) {
		message("info","%^GREEN%^%^BOLD%^CA_NAME uses a powerful wind to drag "+
			"you back into battle!",to);
		message("info","%^GREEN%^%^BOLD%^A powerful wind suddenly "+
			"drags CT_NAME away.",environment(to),
			({to}));
		message("info","%^GREEN%^%^BOLD%^CA_NAME uses a powerful wind to "+
			"drag CT_NAME back into the "+
			"room.",environment(from),({from}));
		message("info","%^GREEN%^%^BOLD%^HA! You're not about to let CT_NAME get "+
			"away that easily! "+
			"You drag "+(string)to->query_objective()+" back into the room!",from);
		to->move(environment(from));
	} else {
		if(!tmp) {
			return;
		}
	}
	i = random(sizeof(AETHER_ELEMENTS));
	crit = AETHER_ELEMENTS[i];
	message("info","CA_NAME uses %^RED%^"+crit+"%^RESET%^.",
		environment(from),({from}));
	message("info","You use %^RED%^"+crit+"%^RESET%^.",
		from);
	crit = crit+" "+({"B","C","D","E"})[random(5)];
	do_critical(from, to, ({ crit }) );
}
