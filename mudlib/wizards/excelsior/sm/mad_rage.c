// a spell that makes you a fighting lunatic

inherit "std/spells/spell";

void create() {
	::create();
	set_property("name","mad rage");
	set_property("target type","living");
	set_property("must be present",1);
	set_property("skill","magery");
	set_property("casting time",10);
	set_property("base mp cost",40);
	set_property("dev cost",39);
	set_property("spell level",10);
	set_property("fast dev cost",102);
	set_property("moon","warzau");
	set_property("caster message","%^YELLOW%^%^BOLD%^You cast MAD RAGE!");
	set_property("target message","%^BLUE%^$C has sent you into a mad rage!");
	set_property("observer message","$C sends $T into a MAD RAGE!");
}

void spell_func(object caster,object at,int power,string args,int flag) {
	object shadow,tmp,*tmp2;
	int rounds,mod;
	if(!present(at,environment(caster))) {
		message("info","The spell target must be present for mad rage to "+
			"work.",caster);
		caster->add_mp(-props["mp cost"]);
		return;
	}
	if(!at->query_current_attacker()) {
		message("info","ok",at);
		message("info","%^BLUE%^"+(string)at->query_cap_name()+" is sent "+
			"into a wild fighting rage, but as "+(string)at->query_subjective()+
			" is not fighting anyone, "+
			"the spell has little effect.",environment(at),({at}));
		message("info","%^BLUE%You are sent "+
			"into a wild fighting rage, but as you are not fighting anyone, "+
			"the spell has little effect.",at);
		return;
	}
	mod = (int)at->query_skill("attack")/20;
	if(mod < 1) mod = 1;
	if(!flag) {
		message("info","%^RED%^%^BOLD%^"+(string)at->query_cap_name()+
		" lets out an ear "+
			"piercing scream. AHHHHH!!!",environment(at));
		rounds = (power*(skill/20) + random(2)) + mod;
		while(rounds > 0) {
			message("info","%^BOLD%^%^YELLOW%^ATTACK!",environment(at));
			at->continue_attack();
			rounds--;
		}
		shadow = new("/wizards/excelsior/misc/max_hp_shadow"); 
		shadow->start_shadow(at,-1000/skill,power*40);
		return;
	}
	switch(random(3)) {
		case 0:
			message("info","You try to jump into a crazed rage, but suddenly "+
				"you realize you can't. In fact, you realize that you have "+
				"become nothing but a feeble wreck!",at);
			message("info","The spell backfires on "+(string)at->query_cap_name()+
				"and "+(string)at->query_subjective()+" is weakened.",
				environment(at),({at}));
			shadow = new("/wizards/excelsior/misc/max_hp_shadow");
			shadow->start_shadow(at,100*skill,power*80);
			return;
		case 1:
			message("info","Uh oh! Something has gone wrong! Your opponent is sent "+
				"into the rage!",at);
			tmp = (object)at->query_current_attacker();
			message("info","%^BLUE%^Suddenly "+tmp->query_cap_name()+" is sent "+
				"into a mad rage!",environment(tmp),({at}));
			rounds = random(30)+1;
			while(rounds > 0) {
				tmp->continue_attack();
				rounds--;
			}
			return;
		case 2:
			message("info",(string)caster->query_cap_name()+" loses control "+
				"of "+(string)caster->query_possesive_pronoun()+" spell, and "+
				"you go berserk"+
				", hitting everyone in the room!",at);
			message("info","You lose control "+
				"of your spell, and "+(string)at->query_cap_name()+" goes "+
				"into a mad rage, hitting everyone in the room!",caster);
			message("info",(string)caster->query_cap_name()+" loses control "+
				"of "+(string)caster->query_possesive_pronoun()+" spell, and "+
				(string)at->query_cap_name()+" goes berserk"+
				", hitting everyone in the room!",environment(at),
				({caster,at}));
			tmp2 = filter_array(all_inventory(environment(at)),"check_living",
				this_object());
			rounds = sizeof(tmp2);
			while(rounds--)
				at->kill_ob(tmp2[rounds],0);
			rounds = (power*(skill/20) + random(2)) + mod;
			while(rounds > 0) {
				at->heart_beat();
				rounds--;
			}
			return;
	}
}

void info() {
	message("info","This spell sends the target into a mad rage. "+
		"If the target is in combat, he will get multiple attacks (as many "+
		"as 30 at extreme levels) in a row on his opponent. The down side "+
		"of this is that such physical exertion temporarily weakens the the one in the rage- "+
		"and thus his max hp is lowered for a little while.\n"+
		"example: cast *4 mad rage at excelsior",this_player());
} 
