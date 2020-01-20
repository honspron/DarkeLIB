inherit "/std/spells/spell";

void create() {
	::create();
	set_property("name", "ritual dud");
	set_property("skill","conjuration");
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

	if(query_property("ritual spell") && !query_property("no cast")){
	spell_ob = new(query_property("original spell"));
        spell_ob->set_property("casting time", 0);
        spell_ob->set_property("base mp cost", 0);
	spell_ob->set_property("ritual final", 1);
	message("info", "%^BOLD%^GREEN%^The group combines it's abilities and casts "+query_property("original name"), environment(caster));
        spell_ob->begin_casting(caster, query_property("original arg"), query_property("original power") + query_property("original members"));
}
}