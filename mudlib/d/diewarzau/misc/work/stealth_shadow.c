//	Stealth shadow for spells and skills.  Incorporates spot hidden
//	skill.
//	DarkeLIB 0.1
//	Diewarzau 4/7/94

object who_shadowed;
int skill, skill_bonus;
string expire_mesg;

void set_skill_bonus(int bonus) { skill_bonus = bonus; }

void set_skill(int amt) { skill = amt; }

void set_expire_message(string mesg) { expire_mesg = mesg; }

varargs void start_shadow(object ob, int duration) {
    if(!ob) return;
    shadow(ob,1);
    who_shadowed = ob;
    if(duration) call_out("remove",duration);
    return;
}

void remove() {
