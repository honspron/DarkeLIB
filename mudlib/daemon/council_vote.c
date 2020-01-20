#include "/adm/include/security.h"
#include "/adm/include/daemons.h"
#include "/adm/include/dirs.h"

#define VOTE_DATA		"/adm/save/votes/"
#define LEGAL_GUILDS		({ "arch-mage","chaotic-lord","cleric","elementalist","enchanter","fighter","necromancer","nightblade","paladin","sword-mage","thief","tinker","war-priest",})
#define LEGAL_GUILD_INIT	([ "arch-mage":0,"chaotic-lord":0,"cleric":0,"elementalist":0,"enchanter":0,"fighter":0,"necromancer":0,"nightblade":0,"paladin":0,"sword-mage":0,"thief":0,"tinker":0,"war-priest":0,])
#define VOTE_OK 		0
#define VOTE_ERROR		1
#define ALREADY_VOTED		2
#define BAD_VOTE		3

mapping votes;   // (["issue0":([who:1|0,]),"issue1":([who:1|0,]),])

void create() {
  seteuid(getuid());
  votes = ([]);
  seteuid(UID_DAEMONSAVE);
  if(file_exists(DIR_DAEMONS_SAVE+"/council_vote.o"))
    restore_object(DIR_DAEMONS_SAVE+"/council_vote");
  seteuid(getuid());
}

mapping query_all_votes() { return votes; }
mapping query_all_issues() { return votes; }
mapping query_votes(string issue) { return votes[issue]; }

int add_issue() {
  string *issues;
  int x;
  string str;

  issues = keys(votes);
  x = sizeof(issues);
  str = "prop"+(x++); 
  votes[str] = LEGAL_GUILD_INIT;
  seteuid(UID_DAEMONSAVE);
  save_object(DIR_DAEMONS_SAVE+"/council_vote");
  seteuid(getuid());
  return 1;
}
int rm_issue(string str) {
  string *issues;
  int x;

  issues = keys(votes);
  if(member_array(str, issues) == -1) return 0;
  map_delete(votes, str);
  seteuid(UID_DAEMONSAVE);
  save_object(DIR_DAEMONS_SAVE+"/council_vote");
  seteuid(getuid());
  return 1;
}
int cast_vote(string issue, string guild, int vote) {
  string *issues,*guilds;
  int x;

  issues = keys(votes);
  if(member_array(issue, issues) == -1) return 0;
  guilds = keys(votes[issue]);
  if(member_array(guild, guilds) == -1) return 0;
  
  votes[issue][guild] = vote;
  
  seteuid(UID_DAEMONSAVE);
  save_object(DIR_DAEMONS_SAVE+"/council_vote");
  seteuid(getuid());
  return vote;
}
mapping query_issue(string issue) {
  return votes[issue];
}
int query_guild_vote(string issue, string guild) {
  return votes[issue][guild];
}
