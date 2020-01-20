/*
 * A daemon which handles clan membership , etc.
 *
 * Diewarzau 8/4/96
 * DarkeLIB 1.0
 */

#define FORBIDDEN ({ "admin", "cre", "newbie", "darke", \
  "gossip", "intercre", "sales", "council", "none" })
#include "/adm/include/clan.h"
#include "/adm/include/security.h"
#include "/adm/include/dirs.h"

class clan_list {
  string cname;
  string leader;
  int num_rooms;
  string *member_list;
  string *member_privs;
  string *forbidden;
  int east, south;
  int last_upkeep;
}

class clan_list *clans;

void save_me();
class clan_list find_list(string clan);

void create() {
  clans = ({});
  seteuid(UID_DAEMONSAVE);
  if(file_exists(DIR_DAEMONS_SAVE+"/clan.o"))
    restore_object(DIR_DAEMONS_SAVE+"/clan");
 /*
  * Activate the code block below to institute clan upkeep, but first, the
  * function (check_upkeep) needs to be coded.
  * Also, remember to stick in a function that will bring the last_upkeep
  * member of clan_list up to date for all clans, or else everyone will lose
  * their clan.
  *
  
  if(!event_pending(this_object())) {
    this_object()->check_upkeep();
    event("check_upkeep", 86400, 0, 1);
  }

  *
  */
  
  seteuid(getuid());
}

void save_me() {
  seteuid(UID_DAEMONSAVE);
  if(file_exists(DIR_DAEMONS_SAVE+"/clan.o"))
    rm(DIR_DAEMONS_SAVE+"/clan.o");
  save_object(DIR_DAEMONS_SAVE+"/clan");
  seteuid(getuid());
}

class clan_list find_list(string clan) {
  int i;

  if(!sizeof(clans)) return 0;
  i = sizeof(clans);
  while(i--) if(clans[i]->cname == clan) return clans[i];
  return 0;
}

string new_clan(string clan, string ldr) {
  string *guilds;
  class clan_list clist;
  int i;

  if(strsrch(" ", clan) != -1)
    return "The clan name may not include a space.";
  clan = lower_case(clan);
  i = strlen(clan);
  if(i > 16 || i < 3)
    return "Clan names must be between 3 and 16 characters long.\n";
  while(i--)
    if(clan[i] != '-' && 
       (clan[i] < 'a' || clan[i] > 'z'))
      return "Clan names must contain alphabetic characters and '-' only.\n";
  seteuid(getuid());
  guilds = get_dir("/d/damned/guilds/join_rooms/*_join.c");
  guilds = map_array(guilds, (: replace_string :), "_join.c", "");
  if(member_array(clan, guilds) != -1)
    return "Clans may not have the same name as a guild.\n";
  guilds = get_dir("/cmds/mortal/_*.c");
  guilds = map_array(guilds, (: replace_string :), "_", "", 1);
  guilds = map_array(guilds, (: replace_string :), ".c", "");
  if(member_array(clan, guilds) != -1)
    return "Clans may not have the same name as a user command.\n";
  if(member_array(clan, FORBIDDEN) != -1)
    return "Clans may not have the same name as a chat channel.\n";
  if(find_list(clan))
    return "There is already a clan by that name.\n";
  clist = new(class clan_list);
  clist->leader = ldr;
  clist->member_list = ({});
  clist->member_privs = ({});
  clist->cname = clan;
  clist->num_rooms = 1;
  clist->forbidden = ({});
  clist->last_upkeep = time() + 2592000;
  clans += ({ clist });
  save_me();
  return 0;
}

void set_clan_location(string clan, int s, int e) {
  class clan_list clist = find_list(clan);

  if(!clist) return;
  clist->south = s;
  clist->east = e;
  save_me();
  return;
}

string *all_clans() {
  string *ret = ({});
  int i = sizeof(clans);
  
  if(!i) return ret;
  while(i--) ret += ({ clans[i]->cname });
  return ret;
}

string *all_members(string clan) {
  class clan_list clist = find_list(clan);

  if(!clist) return ({});
  return clist->member_list;
}

int clan_member(string who, string clan) {
  class clan_list clist = find_list(clan);
  
  if(!clist) return 0;
  if(lower_case(who) == clist->leader) return 1;
  if(member_array(lower_case(who), clist->member_list) >= 0)
    return 1;
  return 0;
}

string clan_leader(string clan) {
  class clan_list clist = find_list(clan);

  if(!clist) return 0;
  return clist->leader;
}

int add_member(string who, string clan) {
  class clan_list clist = find_list(clan);

  if(!clist) return -1;
  who = lower_case(who);
  if(member_array(who, clist->member_list) >= 0 || who == clist->leader) return -2;
  if(member_array(who, clist->forbidden) >= 0) return 0;
  clist->member_list += ({ who });
  clist->member_privs += ({ "" });
  save_me();
  return 1;
}

void remove_member(string who, string clan) {
  class clan_list clist = find_list(clan);
  int idx;

  if(!clist) return;
  who = lower_case(who);
  if((idx=member_array(who, clist->member_list)) < 0) return;
  clist->member_list = exclude_array(clist->member_list, idx);
  clist->member_privs = exclude_array(clist->member_privs, idx);
  clist->forbidden += ({ who });
  save_me();
  return;
}

void remove_clan(string clan) {
  int i = sizeof(clans);
  int idx = -1;

  if(!i) return;
  while(i--) {
    if(idx != -1) break;
    if(clans[i]->cname == lower_case(clan))
      idx = i;
  }
  if(idx < 0) return;
  clans = exclude_array(clans, idx);
  save_me();
  return;
}

void add_member_priv(string clan, string who, int bit) {
  class clan_list clist = find_list(clan);
  int idx;

  if(!clist) return;
  idx = member_array(lower_case(who), clist->member_list);
  if(idx < 0) return;
  clist->member_privs[idx] = set_bit(clist->member_privs[idx], bit);
  save_me();
  return;
}

void remove_member_priv(string clan, string who, int bit) {
  class clan_list clist = find_list(clan);
  int idx;

  if(!clist) return;
  idx = member_array(lower_case(who), clist->member_list);
  if(idx < 0) return;
  clist->member_privs[idx] = clear_bit(clist->member_privs[idx], bit);
  save_me();
  return;
}

int test_member_priv(string clan, string who, int bit) {
  class clan_list clist = find_list(clan);
  int idx;

  if(!clist) return 0;
  idx = member_array(lower_case(who), clist->member_list);
  if(idx < 0) return 0;
  return test_bit(clist->member_privs[idx], bit);
}

string *clan_members(string clan) {
  class clan_list clist = find_list(clan);
  
  if(!clist) return 0;
  return clist->member_list;
}

int query_num_rooms(string clan) {
  class clan_list clist = find_list(clan);
  
  if(!clist) return 0;
  return clist->num_rooms;
}

void add_room(string clan) {
  class clan_list clist = find_list(clan);
  
  if(!clist) return;
  clist->num_rooms++;
  save_me();
  return;
}

