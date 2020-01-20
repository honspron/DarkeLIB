// /std/party.c
// party daemon for the Nightmare mudlib
// created by Descartes of Borg 10 Nov 1992
// EDITED BY RhaSpeR for RITUAL CASTING 11/3/98

#include <ritual.h>
#include <ansi.h>

mapping ritual;
mapping ritual_invited;

string ritual_member(object ob);

void manage_ritual(string group);
void remove_ritual(string group);
void remove_invitation(mixed *bing);

int invited_now(object ob, string str);

void create() {
	ritual = ([]);
	ritual_invited = ([]);

	call_out("manage_all_rituals", 300);
}

int add_caster(object ob, string group) {
	string name;

	if(!ritual) ritual = ([]);
	if(ritual_member(ob)) return ALREADY_MEMBER;
	if(!ritual[group]) {
	tell_object(ob, "You are the leader of ritual casting group "+group+".\n");
	ritual[group] = ({});
}
	ritual[group] += ({ ob });
	name = (string)ob->query_name();
	if(ritual_invited) if(ritual_invited[group]) if(member_array(ob, ritual_invited[group]) != -1) {
	remove_invitation( ({ ob, group, 1 }) );
}
	ob->set_ritual(group);
	manage_ritual(group);
	return OK;
}


int remove_caster(object ob) {
	string group, name;

	if(!ritual) return NOT_MEMBER;
	group = ritual_member(ob);
	if(!group) return NOT_MEMBER;
	name = (string)ob->query_name();
	ritual[group] -= ({ ob });
	tell_object(ob, "You are no longer in the ritual casting group "+group+".\n");
	ob->set_ritual(0);
	manage_ritual(group);
	return OK;
}


string ritual_member(object ob) {
	string *groups;
	int i;

	if(!ritual) return 0;
	groups = keys(ritual);
	for(i=0; i<sizeof(groups); i++) {
	if(member_array(ob, ritual[groups[i]]) != -1) return groups[i];
}
	return 0;
}


int change_leader(object ob) {
	string group;
	object *this_ritual;
	int x;

	if(!ritual) return NOT_MEMBER;
	group = ritual_member(ob);
	if(!group) return NOT_MEMBER;
	manage_ritual(group);
	this_ritual = ritual[group];
	x = member_array(ob, this_ritual);
	if(!x) return ALREADY_LEADER;
	this_ritual[x] = this_ritual[0];
	this_ritual[0] = ob;
	tell_object(ob, "You are now the leader of the ritual casting group "+group+".\n");
	ritual[group] = this_ritual;
	manage_ritual(group);
	return OK;
}


void manage_ritual(string group) {
	object *tmp;
	object *who;
	object ob;
	int i, j;

	tmp = ({});
	if(!ritual) return;
	if(!ritual[group]) return;
	if(!sizeof(ritual[group])) {
	remove_ritual(group);
	return;
}
	ob = ritual[group][0];
	who = ritual[group];
	for(i=0; i<sizeof(who); i++) {
	if(!who[i]) continue;
	if(!living(who[i]) || !interactive(who[i])) {
	who[i]->set_ritual(0);
	continue;
}
	tmp += ({ who[i] });
}
	if(!sizeof(tmp)) {
	remove_ritual(group);
	return;
}
	if(tmp[0] != ob) tell_object(tmp[0], "You are now the leader of the ritual casting group "+group+".\n");
	ritual[group] = tmp;
	return;
	tmp = ({});
	for(i=0; i<sizeof(ritual[group]); i++) {
	if((who = ritual[group][i]->query_attackers())) {
	for(j=0; j<sizeof(who); j++) {
	if(member_array(who[j], tmp) == -1) tmp += ({ who[j] });
}
}
}
	for(i=0; i < sizeof(ritual[group]); i++)
	ritual[group][i]->set_attackers(tmp);
}


void remove_ritual(string group) {
	if(!ritual) return;
	if(undefinedp(ritual[group])) return;
	map_delete(ritual, group);
}


int filter_rec_exp(object who, object tmp) {
	object *list;

	if(!tmp || !living(tmp)) return 1;
	list = (object *)tmp->query_hunted() + (object *)tmp->query_attackers();
	if(member_array(who, list) >= 0) return 1;
	return 0;
}


string *query_rituals() {
    if(!ritual) return 0;
    return keys(ritual);
}

object *query_ritual_members(string group) {
	if(!ritual) return 0;
	if(!ritual[group]) return 0;
	manage_ritual(group);
	return ritual[group];
}


object query_leader(string str) {
	if(!ritual) return 0;
	if(!ritual[str]) return 0;
	if(!pointerp(ritual[str])) return 0;
	manage_ritual(str);
	if(!ritual) return 0;
	if(!ritual[str] || !pointerp(ritual[str])) return 0;
	return ritual[str][0];
}


void notify_ritual(string str, string what) {
	int i, sz;

	if(!ritual) return;
	if(!ritual[str]) return;
	manage_ritual(str);
	sz = sizeof(ritual[str]);
	for(i=0; i<sz; i++) {
	if(ritual[str][i]->query_ansi())
	tell_object(ritual[str][i], BLU+"[ "+str+" info ]"+NOR+what+"\n");
	else
	tell_object(ritual[str][i], "[ "+str+" info ] "+what+"\n");
}
}


void add_invited(object ob, string str) {
	if(!ritual_invited) return;
	if(!ritual_invited[str]) ritual_invited[str] = ({});
	ritual_invited[str] += ({ ob });
	call_out("remove_invitation", 60, ({ ob, str, 0 }));
}


object *query_invited(string str) {
	if(!ritual_invited) return 0;
	if(!ritual_invited[str]) return 0;
	return ritual_invited[str];
}


int invited_now(object ob, string str) {
	if(!ritual_invited) return 0;
	if(!ritual_invited[str]) return 0;
	if(member_array(ob, ritual_invited[str]) == -1) return 0;
	return 1;
}


void remove_invitation(mixed *bing) {
	if(!ritual_invited) return;
	if(!ritual_invited[bing[1]]) return;
	if(member_array(bing[0], ritual_invited[bing[1]]) == -1) return;
	ritual_invited[bing[1]] -= ({ bing[0] });
	if(!bing[2]) tell_object(bing[0], "You are no longer invited to be a member of the ritual group.\n");
}


void manage_all_rituals() {
	string *grps;
	int i;

	if(i = sizeof(grps = keys(ritual)))
	while(i--) manage_ritual(grps[i]);
	call_out("manage_all_rituals", 300);
}
