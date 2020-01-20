/* A generic inheritable object fro guild joining rooms.
 *
 * Note that the player must have permission from the
 * guildmaster to join.  NPC guildmasters will give
 * permission to any guildless person.
 *
 * Handles all necessary changes to a character, including
 * setting of class, mods of stats, etc.  The daemon also 
 * saves itself so the global data is perpetually accessable.
 *
 * This is a rewrite from ideas gained from the origional guild
 * system from DarkeMud's join_room code.  This rewrite daemonized
 * many of the quild queries, storage, and maintenance for the
 * purpose of reducing cpu, memory overhead and centralizing
 * the function calls.
 * 
 * Zortek 4-15-96
 */
#include <std.h>       // Standard include file
#include <security.h>  // Security include file
#include <guild.h>    // Global Guild include file

/* GLOSSARY:  (Terms used in the comments throughout this file).
 *          fqfn = "fully qualified file name"
 *      name|who = "player name"
 *          guild= "guild name (lower case)"
 *          what = qualifier
 *          item = fqfn of an item in the mud
 *          time = integer time value from time();
 */
mapping all_masters;
// ([ guild_0:name, guild_1:name, guild_X:name, ]);

mapping all_members;
// ([ guild_0:({name_a,name_b,name_n,...}),...]);

mapping allowers;
// ([ guild_0:({name_a,name_b,name_n,...}),...]);

mapping guests;
// ([ guild_0:({name_a,name_b,name_n,...}),...]);
 
mapping allies;
// ([ guild_0:({name_a,name_b,name_n,...}),...]);
 
mapping enemies;
// ([ guild_0:({name_a,name_b,name_n,...}),...]);
 
mapping join_rooms;
// ([ guild_0:fqfn, guild_1:fqfn, guild_X:fqfn, ]);

mapping guild_office;
// ([ guild_0:fqfn_a, guild_1:fqfn_b, guildX:fqfn_n, ]);

mapping related_guilds;
// ([ guild_0:({guild_a,guild_b,guild_n,...}),...]);

mapping guild_items;
// ([ guild_0:([item_a, item_b, item_n,...}),...]);

mapping last_on;
// ([ guild_0:time, guild_1:time, guild_X:time,...]);

mapping regen;
// ([ guild_0:(["hp":int,"mp":int_2,]),...]);

mapping advance;
// ([ guild_0:(["hp":int,"mp":int_2,]),...]);

mapping stats;
// ([ guild_0:(["stat_a":int,"stat_b":int_2,]),...]);

void save_guilds();

//----------BEGIN FUNCTIONS-------------

/* REGEN, ADVANCE, STATS---------------------------------------------
 * These functions deal directly with the base guild data items, such
 * as regen and advance rate for 'mp' and 'hp' and stat modifications
 * that are received when initially joining the guild.  Technically,
 * these functions should only be called from the guild office.
 */
mapping query_regen(string guild) {
  return regen[guild];
}
void set_regen(string guild, mapping foo) {
  regen[guild] = foo;
  return;
}
mapping query_advance(string guild) {
  return advance[guild];
}
void set_advance(string guild, mapping foo) {
  advance[guild] = foo;
  return;
}
mapping query_stats(string guild) {
  return stats[guild];
}
void set_stats(string guild, mapping foo) {
  stats[guild] = foo;
  return;
}
// END OF REGEN, ADVANCE, and STATS----------------------------------

/* ALL_MASTERS-------------------------------------------------------
 * These functions deal strictly with manipulating the data
 * stored in the all_masters mapping (within THIS daemon).
 * No data is manipulated in any outside object.  Additionally,
 * no data verification or certification takes place in these
 * functions.  Such checks should have already taken place.
 */
string *query_masters() {
  return values(all_masters);
}
string query_master(string guild) {
  return all_masters[guild];
}
int is_master(string who) {
  string *foo = values(all_masters);
  return member_array(who, foo);
}
void set_master(string guild, string who) {
  all_masters[guild] = who;
  return;
}
// END OF ALL_MASTERS------------------------------------------------

/* ALL_MEMBERS-------------------------------------------------------
 * These functions deal strictly with manipulating the data
 * stored in the all_members mapping (within THIS daemon).
 * No data is manipulated in any outside object.  Additionally,
 * no data verification or certification takes place in these
 * functions.  Such checks should have already taken place.
 */
string *query_members(string guild) {
  if(!all_members[guild]) all_members[guild] = ({});
  return all_members[guild];
}
int is_member(string guild, string who) {
  if(!all_members[guild]) all_members[guild] = ({});
  return member_array(who, all_members[guild]);
}
void add_member(string guild, string who) {
  if(!all_members[guild]) all_members[guild] = ({});
  all_members[guild] = distinct_array(all_members[guild]+({who}) );
  return;
}
void rm_member(string guild, string who) {
  if(!all_members[guild]) all_members[guild] = ({});
  all_members[guild] -= ({who});
  return;
}
// END OF ALL_MEMBERS------------------------------------------------

/* ALLOWERS----------------------------------------------------------
 * These functions deal strictly with manipulating the data
 * stored in the allowers mapping (within THIS daemon).
 * No data is manipulated in any outside object.  Additionally,
 * no data verification or certification takes place in these
 * functions.  Such checks should have already taken place.
 */
string *query_allowers(string guild) {
  if(!allowers[guild]) allowers[guild] = ({});
  return allowers[guild];
}
int is_allower(string guild, string who) {
  if(!allowers[guild]) allowers[guild] = ({});
  return member_array(who, allowers[guild]);
}
void add_allower(string guild, string who) {
  if(!allowers[guild]) allowers[guild] = ({});
  allowers[guild] = distinct_array(allowers[guild]+({who}) );
  return;
}
void rm_allower(string guild, string who) {
  if(!allowers[guild]) allowers[guild] = ({});
  allowers[guild] -= ({who});
  return;
}
// END OF ALLOWERS------------------------------------------------

/* GUESTS------------------------------------------------------------
 * These functions deal strictly with manipulating the data
 * stored in the guests mapping (within THIS daemon).
 * No data is manipulated in any outside object.  Additionally,
 * no data verification or certification takes place in these
 * functions.  Such checks should have already taken place.
 */
string *query_guests(string guild) {
  if(!guests[guild]) guests[guild] = ({});
  return guests[guild];
}
int is_guest(string guild, string who) {
  if(!guests[guild]) guests[guild] = ({});
  return member_array(who, guests[guild]);
}
void add_guest(string guild, string who) {
  if(!guests[guild]) guests[guild] = ({});
  guests[guild] = distinct_array(guests[guild]+({who}) );
  return;
}
void rm_guest(string guild, string who) {
  if(!guests[guild]) guests[guild] = ({});
  guests[guild] -= ({who});
  return;
}
// END OF GUESTS-----------------------------------------------------

/* ALLIES------------------------------------------------------------
 * These functions deal strictly with manipulating the data
 * stored in the allies mapping (within THIS daemon).
 * No data is manipulated in any outside object.  Additionally,
 * no data verification or certification takes place in these
 * functions.  Such checks should have already taken place.
 */
string *query_allies(string guild) {
  if(!allies[guild]) allies[guild] = ({});
  return allies[guild];
}
int is_ally(string guild, string who) {
  if(!allies[guild]) allies[guild] = ({});
  return member_array(who, allies[guild]);
}
void add_ally(string guild, string who) {
  if(!allies[guild]) allies[guild] = ({});
  allies[guild] = distinct_array(allies[guild]+({who}) );
  return;
}
void rm_ally(string guild, string who) {
  if(!allies[guild]) allies[guild] = ({});
  allies[guild] -= ({who});
  return;
}
// END OF ALLIES-----------------------------------------------------

/* ENEMIES-----------------------------------------------------------
 * These functions deal strictly with manipulating the data
 * stored in the enemies mapping (within THIS daemon).
 * No data is manipulated in any outside object.  Additionally,
 * no data verification or certification takes place in these
 * functions.  Such checks should have already taken place.
 */
string *query_enemies(string guild) {
  if(!enemies[guild]) enemies[guild] = ({});
  return enemies[guild];
}
int is_enemy(string guild, string who) {
  if(!enemies[guild]) enemies[guild] = ({});
  return member_array(who, enemies[guild]);
}
void add_enemy(string guild, string who) {
  if(!enemies[guild]) enemies[guild] = ({});
  enemies[guild] = distinct_array(enemies[guild]+({who}) );
  return;
}
void rm_enemy(string guild, string who) {
  if(!enemies[guild]) enemies[guild] = ({});
  enemies[guild] -= ({who});
  return;
}
// END OF ENEMIES----------------------------------------------------

/* JOIN_ROOMS--------------------------------------------------------
 * These functions deal strictly with manipulating the data
 * stored in the join_rooms mapping (within THIS daemon).
 * No data is manipulated in any outside object.  Additionally,
 * no data verification or certification takes place in these
 * functions.  Such checks should have already taken place.
 */
string *query_join_rooms() {
  return values(join_rooms);
}
string query_join_room(string guild) {
  return join_rooms[guild];
}
void set_join_room(string guild, string fqfn) {
  join_rooms[guild] = fqfn;
  return;
}
// END OF JOIN_ROOMS-------------------------------------------------

/* GUILD_OFFICE------------------------------------------------------
 * These functions deal strictly with manipulating the data
 * stored in the guild_office mapping (within THIS daemon).
 * No data is manipulated in any outside object.  Additionally,
 * no data verification or certification takes place in these
 * functions.  Such checks should have already taken place.
 */
string *query_guild_offices() {
  return values(guild_office);
}
string query_guild_office(string guild) {
  return guild_office[guild];
}
void set_guild_office(string guild, string fqfn) {
  guild_office[guild] = fqfn;
  return;
}
// END OF GUILD_OFFICE-----------------------------------------------

/* RELATED_GUILDS----------------------------------------------------
 * These functions deal strictly with manipulating the data
 * stored in the related_guilds mapping (within THIS daemon).
 * No data is manipulated in any outside object.  Additionally,
 * no data verification or certification takes place in these
 * functions.  Such checks should have already taken place.
 */
string *query_related_guilds(string guild) {
  if(!related_guilds[guild]) related_guilds[guild] = ({});
  return related_guilds[guild];
}
int is_related_guild(string guild, string what) {
  if(!related_guilds[guild]) related_guilds[guild] = ({});
  return member_array(what, related_guilds[guild]);
}
void add_related_guild(string guild, string what) {
  if(!related_guilds[guild]) related_guilds[guild] = ({});
  related_guilds[guild] = distinct_array(related_guilds[guild]+({what}) );
  return;
}
void rm_related_guild(string guild, string what) {
  if(!related_guilds[guild]) related_guilds[guild] = ({});
  related_guilds[guild] -= ({what});
  return;
}
// END OF RELATED_GUILDS---------------------------------------------

/* GUILD_ITEMS-------------------------------------------------------
 * These functions deal strictly with manipulating the data
 * stored in the guild_items mapping (within THIS daemon).
 * No data is manipulated in any outside object.  Additionally,
 * no data verification or certification takes place in these
 * functions.  Such checks should have already taken place.
 */
string *query_guild_items(string guild) {
  if(!guild_items[guild]) guild_items[guild] = ({});
  return guild_items[guild];
}
int is_guild_item(string guild, string what) {
  if(!guild_items[guild]) guild_items[guild] = ({});
  return member_array(what, guild_items[guild]);
}
void add_guild_item(string guild, string what) {
  if(!guild_items[guild]) guild_items[guild] = ({});
  guild_items[guild] = distinct_array(guild_items[guild]+({what}) );
  return;
}
void rm_guild_item(string guild, string what) {
  if(!guild_items[guild]) guild_items[guild] = ({});
  guild_items[guild] -= ({what});
  return;
}
// END OF GUILD_ITEMS------------------------------------------------

int query_last_on(string guild) {
  if(last_on[guild]) return last_on[guild];
  else return 0;
}
int set_last_on(string guild, int num) {
  return last_on[guild] = num;
}
/* CREATE, RESET, SAVE_GUILDS----------------------------------------
 * It is critical that these functions be at the END of this file. The
 * reason for this is simple, I have decided not to provide function
 * defs for every bloody function that MAY end up being called in the
 * following functions.
 */
void create() {
  int x;
  all_masters  = allocate_mapping(sizeof(LEGAL_GUILDS));
  all_members  = allocate_mapping(sizeof(LEGAL_GUILDS));
  allowers     = allocate_mapping(sizeof(LEGAL_GUILDS));
  guests       = allocate_mapping(sizeof(LEGAL_GUILDS));
  allies       = allocate_mapping(sizeof(LEGAL_GUILDS));
  enemies      = allocate_mapping(sizeof(LEGAL_GUILDS));
  join_rooms   = allocate_mapping(sizeof(LEGAL_GUILDS));
  guild_office = allocate_mapping(sizeof(LEGAL_GUILDS));
  guild_items  = allocate_mapping(sizeof(LEGAL_GUILDS));
  last_on      = allocate_mapping(sizeof(LEGAL_GUILDS));
  regen        = allocate_mapping(sizeof(LEGAL_GUILDS));
  advance      = allocate_mapping(sizeof(LEGAL_GUILDS));
  stats        = allocate_mapping(sizeof(LEGAL_GUILDS));
  related_guilds=allocate_mapping(sizeof(LEGAL_GUILDS));

/* INITIALIZE all the mappings...this is critical due to the
 * that all of this daemon's functions have been optimized
 * to reduce excessive mapp, pointerp, and undefinedp calls.
 */
  for(x=0; x<sizeof(LEGAL_GUILDS);x++) {
     rm_guild_item(LEGAL_GUILDS[x], "foo");
     rm_related_guild(LEGAL_GUILDS[x], "foo");
     rm_enemy(LEGAL_GUILDS[x], "foo");
     rm_ally(LEGAL_GUILDS[x], "foo");
     rm_guest(LEGAL_GUILDS[x], "foo");
     rm_member(LEGAL_GUILDS[x], "foo");
     rm_allower(LEGAL_GUILDS[x], "foo");
     set_master(LEGAL_GUILDS[x], "");
     set_join_room(LEGAL_GUILDS[x], "");
     set_guild_office(LEGAL_GUILDS[x], "");
     set_last_on(LEGAL_GUILDS[x], 1);
     set_regen(LEGAL_GUILDS[x], ([]));
     set_advance(LEGAL_GUILDS[x], ([]));
     set_stats(LEGAL_GUILDS[x], ([]));
  }
  seteuid(UID_SECURE_DAEMONSAVE);
  if(file_exists("/adm/save/daemons/guild2_d.o"))
    restore_object("/adm/save/daemons/guild2_d",1);
  seteuid(getuid());
  return;
}
void reset() {
  seteuid(UID_SECURE_DAEMONSAVE);
//  save_object("/adm/save/daemons/guild_archive/"+time()+"backup");
  seteuid(getuid());
  return;
}
void save_guilds() {
  seteuid(UID_SECURE_DAEMONSAVE);
  save_object("/adm/save/daemons/guild2_d");
  seteuid(getuid());
  return;
}

