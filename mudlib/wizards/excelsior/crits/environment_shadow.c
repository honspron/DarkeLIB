// /wizards/excelsior/crits/evironment_shadow

inherit "/std/spells/shadows/shadow";

object where,*people;

/*
int receive_objects() {
  object who;
  string *guys;
  who = previous_object();
  if(!who) return 0;
  if(!who->is_player()) return next_shadow()->receive_objects();
	if(!living(who)) return next_shadow()->receive_objects();
  if(who->is_pet()) return next_shadow()->recieve_objects();
  if((int)who->query_skill("stealth") > 100+random(60)) {
  	write("%^RED%^You manage to sneak into the room!!!");
  	return 1;
  }
  if(member_array(who,people) > -1) {
		return 1;
	}
  write("You start to enter the room but a severe energy blast throws you back. "+
  	"What is this?");
  return 0;
}
*/

void create() {
	people = ({});
}

void start_shadow(object what,object *stuff) {
	if(!objectp(what)) return;
	where = what;
	people = stuff;
	begin_shadow(where);
	return;
	call_out("remove",800);
}
