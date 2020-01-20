// /std/spells/living_weapon
// created by Excelsior
// 7-6-96
// do not remove this header

inherit "/std/spells/spell";

void create() {
	::create();
	set_property("name","living weapon");
	set_property("target type","any");
	set_property("must be present",1);
	set_property("skill","magery");
	set_property("casting time",10);
	set_property("spell level",6);
	set_property("base mp cost",75);
	set_property("dev cost",15);
	set_property("fast dev cost",44);
	set_property("duration",200);
	set_property("moon","luna");
	set_property("target message","$C casts living weapon!");
	set_property("caster message","You cast living weapon!");
	set_property("observer message","$C casts living weapon!");
}

void info() {
	write("This spell will bring a weapon to life! The weapon will then fight "+
		"along your side as a pet. The skill of the living weapon depends "+
		"on how good the weapon was the spell was cast at. The target of "+
		"this spell MUST be a weapon. Spell level affects duration only.");
	return;
}

void spell_func(object caster, object at, int power, string args, int flag) {
	object ob;
	if(!(int)at->is_weapon()) {
		message("info","Living weapon can only be cast at a weapon!",caster);
		caster->add_mp(props["mp cost"]);
		remove();
		return;
	}
	if(flag) {
		message("info","Shoot! You accidentally disentegrate the weapon!!",caster);
		message("info",(string)caster->query_cap_name()+" disentegrates"+
			" a weapon amid much cursing.",environment(caster),({caster}));
		caster->add_hp(-70);
		at->remove();
		remove();
		return;
	}
	if(at->query_wielded()) {
		message("info","Living weapon must be cast at an unwielded weapon.",caster);
		caster->add_mp(props["mp cost"]);
		remove();
		return;
	}
	ob = new("/wizards/excelsior/misc/weapon_pet");
	ob->set_name((string)at->query_name());
	ob->set("short",(string)at->query_short()+" {[alive]}");
	ob->set("long",(string)at->query_long()+"\nThis weapon is alive, "+
		"and is now a pet. See 'help pet' for more information.");
	ob->set("id",(string *)at->query_id());
	ob->set_level(skill/8 + (int)at->query_quality());
	ob->set("race","weapon");
	ob->set_gender("neuter");
	ob->set_body_type("sphere");
	ob->set_overall_ac((int)at->query_ac());
	ob->set_melee_damage((mapping)at->query_all_wc());
	ob->set_owner((string)caster->query_name());
	ob->set_expire(query_property("duration") * power);
	ob->set_skill("attack",(50 + (int)at->query_hit_bonus()));
	if((int)ob->query_skill("attack") < 1) ob->set_skill("attack",5);
	ob->set_skill("dodge",(10 + (int)at->query_parry_bonus()));
	if((int)ob->query_skill("dodge") < 1) ob->set_skill("dodge",0);
	ob->set_skill("melee",(int)ob->query_level()*(int)at->query_quality());
	if((int)ob->query_skill("melee") > 95) ob->set_skill("melee",92);
	ob->set_max_hp((int)at->query_decay_rate()/3 + random(20) - random(20));
	ob->set_hp((int)ob->query_max_hp());
	ob->move(environment(caster));
	at->move("/wizards/excelsior/misc/weapon_store");
	ob->set_parent(at);
	remove();
	return;
}
