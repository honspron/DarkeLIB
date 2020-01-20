inherit "/std/spells/shadows/shadow";

// this shadow changes the maximum hp of the shadowed persons.
// usage:
// start_shadow(object who, int mod, mixed duration)
// where mod is the amount to change it by and duration is how long it should last
// if you want it to be permanent, set duration too "permanent"
// if the new max_hp is less than the current hp, the hp will be lowered to
// the new max_hp
// Excelsior 4/4/96

int mod_amount;
object who_shadowed;
string msg;

// sets message for when shadow wears off
void set_message(string str);
// queries message set above
string query_message();

void create() {
	who_shadowed = 0;
	msg = "You feel your health restored.";
}

void start_shadow(object who, int mod, mixed duration) {
	if(!objectp(who)) return;
	who_shadowed = who;
	mod_amount = mod;
	if((int)who->query_hp() > ((int)who->query_max_hp() + mod_amount))
		who->set_hp((int)who->query_max_hp() + mod_amount);
	begin_shadow(who);
	if(intp(duration)) call_out("remove",duration);
	if(stringp(duration) && duration == "permanent") return;
	return;
}

void remove() {
	if(!::remove()) return;
	message("info",msg,who_shadowed);
	return;
}

int query_max_hp() {
	return mod_amount + (int)next_shadow()->query_max_hp();
}

void set_message(string str) {
	if(!str) return;
	msg = str;
}

string query_message() { return msg; }
