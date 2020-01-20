inherit "/std/spells/spell";

void create() {
	::create();
	set_property("name", "ritualdud");
	set_property("skill", query_property("real skill"));
	set_property("casting time",1);
	set_property("base mp cost",1);
	set_property("dev cost", 1);
	set_property("fast dev cost", 1);
	set_property("spell level", 1);
	set_property("moon","luna");
	set_property("no target", 1);
	set_property("caster message","You successfully cast your part of the ritual spell.");
	set_property("target message","");
	set_property("observer message","");
	set_property("spell type",({ }));
	return;
}

void info() {
        message("help","This is the generic ritual casting spell, it cannot be learned.",this_player());
}


void spell_func(object caster, object at, int power, string args, int flag){
	object spell_ob;
	int bonus;

	if(query_property("ritual spell") && !query_property("no cast")){
	spell_ob = new(query_property("original spell"));
        spell_ob->set_property("casting time", 0);
        spell_ob->set_property("base mp cost", 0);
	spell_ob->set_property("ritual final", 1);
	message("info", "%^BOLD%^GREEN%^The group combines it's abilities and casts "+query_property("original name"), environment(caster));

switch(query_property("original members")){
	case 0..1: bonus = 0;
	break;
	case 2..3: bonus = 1;
	break;
	case 4..6: bonus = 2;
	break;
	case 7..9: bonus = 3;
	break;
	case 10..12: bonus = 4;
	break;
	case 13..15: bonus = 5;
	break;
	case 16..18: bonus = 6;
	break;
	case 19..1000: bonus = 7;
	break;
}


	set_property("ritual bonus", bonus);

        spell_ob->begin_casting(caster, query_property("original arg"), query_property("original power"));
}
}

