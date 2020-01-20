//	/std/party.c
//	party daemon for the Nightmare mudlib
//	created by Descartes of Borg 10 Nov 1992

#include <party.h>
#include <ansi.h>

mapping party;
mapping invited;
mapping party_exp;

string party_member(object ob);
void manage_party(string group);
void remove_party(string group);
void remove_invitation(mixed *bing);
int invited_now(object ob, string str);
int perc_exp_bonus(int *levs);

int perc_exp_bonus(int *levs) {
  int sz = sizeof(levs);
  int avg = 0;
  int ldiff = 0;
  int i;

  if(sz <= 1) return 0;
  i = sz;
  while(i--)
    avg += levs[i];
  avg /= sz;
  i = sz;
  while(i--)
    ldiff += (levs[i] >= avg)?(levs[i] - avg):(avg - levs[i]);
  ldiff /= sz;
  if(ldiff > 2) return 0;
  return (3-ldiff) * (sz-1) * 10;
}

void create() {
    party = ([]);
    invited = ([]);
    party_exp = ([]);
    call_out("manage_all_parties", 300);
}

int add_member(object ob, string group) {
    string name;
    
    if(!party) party = ([]);
    if(party_member(ob)) return ALREADY_MEMBER;
    if(!party[group]) {
        tell_object(ob, "You are the leader of party "+group+".\n");
        party[group] = ({});
    }
    party[group] += ({ ob });
    name = (string)ob->query_name();
    party_exp[name] = (int)ob->query_exp();
    if(invited) if(invited[group]) if(member_array(ob, invited[group]) != -1) {
	remove_invitation( ({ ob, group, 1 }) );
    }
    ob->set_party(group);
    manage_party(group);
    return OK;
}

int remove_member(object ob) {
    string group, name;

    if(!party) return NOT_MEMBER;
    group = party_member(ob);
    if(!group) return NOT_MEMBER;
    name = (string)ob->query_name();
    if(party_exp[name]) map_delete(party_exp, name);
    party[group] -= ({ ob });
    tell_object(ob, "You are no longer in the party "+group+".\n");
    ob->set_party(0);
    manage_party(group);
    return OK;
}

int query_party_exp(object who) {
  string name;

  name = (string)who->query_name();
  if(!party_exp[name]) return 0;
  else return (int)who->query_exp() - party_exp[name];
}

string party_member(object ob) {
    string *groups;
    int i;

    if(!party) return 0;
    groups = keys(party);
    for(i=0; i<sizeof(groups); i++) {
        if(member_array(ob, party[groups[i]]) != -1) return groups[i];
    }
    return 0;
}

int change_leader(object ob) {
    string group;
    object *this_party;
    int x;

    if(!party) return NOT_MEMBER;
    group = party_member(ob);
    if(!group) return NOT_MEMBER;
    manage_party(group);
    this_party = party[group];
    x = member_array(ob, this_party);
    if(!x) return ALREADY_LEADER;
    this_party[x] = this_party[0];
    this_party[0] = ob;
    tell_object(ob, "You are now the leader of party "+group+".\n");
    party[group] = this_party;
    manage_party(group);
    return OK;
}

void manage_party(string group) {
    object *tmp;
    object *who;
    object ob;
    int i, j;

    tmp = ({});
    if(!party) return;
    if(!party[group]) return;
    if(!sizeof(party[group])) {
        remove_party(group);
        return;
    }
    ob = party[group][0];
    who = party[group];
    for(i=0; i<sizeof(who); i++) {
        if(!who[i]) continue;
        if(!living(who[i]) || !interactive(who[i])) {
            who[i]->set_party(0);
            continue;
        }
        tmp += ({ who[i] });
    }
    if(!sizeof(tmp)) {
        remove_party(group);
        return;
    }
    if(tmp[0] != ob) tell_object(tmp[0], "You are now the leader of the party "+group+".\n");
    party[group] = tmp;
    return;
    tmp = ({});
    for(i=0; i<sizeof(party[group]); i++) {
        if((who = party[group][i]->query_attackers())) {
            for(j=0; j<sizeof(who); j++) {
                if(member_array(who[j], tmp) == -1) tmp += ({ who[j] });
            }
        }
    }
    for(i=0; i < sizeof(party[group]); i++) party[group][i]->set_attackers(tmp);
}

void remove_party(string group) {
    if(!party) return;
    if(undefinedp(party[group])) return;
    map_delete(party, group);
}

int filter_rec_exp(object sharer, object gainer, object mob) {
    object *list;
    object *tmp;
  
    if(!mob || !living(mob)){
        if(gainer == sharer)
            return 1;
        else
            return 0;
    }
    list = ({});
    tmp = (object *)mob->query_hunted();
    if(!tmp)
        tmp = ({});
    list += tmp;
    tmp = (object *)mob->query_attackers();
    if(!tmp)
        tmp= ({});
    list += tmp;
    if((member_array(sharer, list) != -1) && (environment(gainer) == environment(sharer)) )
        return 1;
    return 0;
}

void calculate_exp(string group, int exp, object tmp) {
    int tot, x, i, bonus;
    object *rec_exp, gainer;

    gainer = previous_object();
    if(!party) {
        gainer->fix_exp(exp, tmp);
        return;
    }
    if(!party[group]) {
        gainer->fix_exp(exp, tmp);
        return;
    }
    if(sizeof(party[group]) == 1) {
	    gainer->fix_exp(exp, tmp);
	    return 0;
    }
    manage_party(group);
    rec_exp = filter_array(party[group], "filter_rec_exp",
      this_object(), gainer, tmp);
    for(i=0, tot=0; i<sizeof(rec_exp); i++) {
	    x = (int)rec_exp[i]->query_level();
	    tot += x * x;
    }
    bonus = perc_exp_bonus(map_array(rec_exp, (: call_other :), "query_level"));
    exp += (exp * bonus) / 100;
    for(i=0; i<sizeof(rec_exp); i++) {
        x = (int)rec_exp[i]->query_level();
        rec_exp[i]->fix_exp( (x*x*exp)/tot + 1, tmp);
    }
}

string *query_parties() {
    if(!party)
        return 0;
    return keys(party);
}

object *query_party_members(string group) {
    if(!party) return 0;
    if(!party[group]) return 0;
    manage_party(group);
    return party[group];
}

object query_leader(string str) {
    if(!party) return 0;
    if(!party[str]) return 0;
    if(!pointerp(party[str])) return 0;
    manage_party(str);
    if(!party) return 0;
    if(!party[str] || !pointerp(party[str])) return 0;
    return party[str][0];
}

void party_line(string str, string what, string who) {
    int i, sz;

    if(!party) return;
    if(!party[str]) return;
    manage_party(str);
    sz = sizeof(party[str]);
    for(i=0; i<sz; i++) {
//           if(party[str][i]->query_ansi())
             message("info", "%^BOLD%^%^RED%^["+str+" %^RESET%^: "+who+"] "+what+"\n",
		   party[str][i]);
//           else
//             tell_object(party[str][i], "["+str+" : "+who+"] "+what+"\n");
    }
}

void party_lineemote(string str, string what, string who) {
    int i, sz;

    if(!party) return;
    if(!party[str]) return;
    manage_party(str);
    sz = sizeof(party[str]);
    for(i=0; i<sz; i++) {
//           if(party[str][i]->query_ansi())
             message("info", "%^RED%^%^BOLD%^["+str+"] %^RESET%^"+who+" "+what+"\n",
                   party[str][i]);
//           else
//             tell_object(party[str][i], "["+str+"] "+who+" "+what+"\n");
    }
}

void notify_party(string str, string what) {
    int i, sz;

    if(!party) return;
    if(!party[str]) return;
    manage_party(str);
    sz = sizeof(party[str]);
    for(i=0; i<sz; i++) {
//            if(party[str][i]->query_ansi())
             tell_object(party[str][i], "%^YELLOW%^[ "+str+"] %^RESET%^"+what+"\n");
//           else
//              tell_object(party[str][i], "[ "+str+" info ] "+what+"\n");
    }
}

void add_invited(object ob, string str) {
    if(!invited) return;
    if(!invited[str]) invited[str] = ({});
    invited[str] += ({ ob });
    call_out("remove_invitation", 60, ({ ob, str, 0 }));
}

object *query_invited(string str) {
    if(!invited) return 0;
    if(!invited[str]) return 0;
    return invited[str];
}

int invited_now(object ob, string str) {
    if(!invited) return 0;
    if(!invited[str]) return 0;
    if(member_array(ob, invited[str]) == -1) return 0;
    return 1;
}

void remove_invitation(mixed *bing) {
    if(!invited) return;
    if(!invited[bing[1]]) return;
    if(member_array(bing[0], invited[bing[1]]) == -1) return;
    invited[bing[1]] -= ({ bing[0] });
    if(!bing[2]) tell_object(bing[0], "You are no longer invited to be a member of the party.\n");
}

void manage_all_parties() {
    string *grps;
    int i;

    if(i = sizeof(grps = keys(party)))
      while(i--) manage_party(grps[i]);
    call_out("manage_all_parties", 300);
}
