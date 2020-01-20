//	This is the Avitar (NPC guildmaster) for the Cleric Guild
//
//	DarkeLIB 0.1
//	Diewarzau 8/8/95
//  Rewrite: Zortek

#include <std.h>

inherit MONSTER;

void create() {
  object ob;

  ::create();

  set("short", "Avitar of the Holy Church");
  set("long", @LONG
This is an Avitar of the Holy Church.  It is a gentle soul
that has incarnated in the body of a seraph.  The Divine has
commissioned this Avitar to bless potential suplicants of the
Holy Church...
LONG
);
  set_level(50);
  set_max_hp(5500);
  set_hp(5500);
  set_max_mp(7000);
  set_mp(7000);
  set_overall_ac(60);
  set_property("base mp regen", 240);
  set_property("base hp regen", 200);
  set_gender("male");
  set("race", "seraph");
  set_body_type("seraph");
  set_skill("body alteration", 250);
  set_skill("prayer", 250);
  set_id(({ "avitar", "seraph" }));
  set_name("avitar");
  set_property("melee damage", ([ "crushing" : 50, "holy" : 70 ]));
  set_skill("perception", 150);
  set_skill("melee", 200);
  set_skill("dodge", 150);
  set_skill("parry", 150);
  set_skill("blunt", 87);
  set_skill("attack",200);

  set_speech(10, "common",
            ({ "Greetings and fair day!  Welcome to the Holy Church.",
		       "Type 'say avitar, bless me' to become a suplicant.",
            }), 0);
  set_languages(({ "common","serra","yin","treefolk","catfolk","lapm",
                   "elvish","dwarvish","vr'krr","rachk","mountainspeak",
                   "gr'grr","middle-english","drow","orcish","ogryn",
                   "pix","draconian","zebber","hisaaa","grken",
                   "thri'krien","stormspeak","undead-tongue","rel", }));

  set_spell_level("decrease metabolism", 6);
  add_spell("decrease metabolism", "$A");

  set_spell_level("cure light wounds", 6);
  add_spell("cure light wounds", "$R");

  set_spell_level("cure serious wounds", 6);
  add_spell("cure serious wounds", "$(ME)");

  set_spell_level("harm", 6);
  add_spell("harm", "$A");

  set_spell_level("heal", 6);
  add_spell("heal", "$(ME)");

  set_spell_level("cause serious wounds", 6);
  add_spell("cause serious wounds", "$A");

  set_casting_chance(10);
  set_combat_chance(120);
  set_property("ambidextry", 1);
  ob = new("/d/damned/guilds/cleric/gm_cross");
  ob->move(this_object());
    ob->set_property("enchantment", 15);
    ob->set_property("enhance criticals", 1);
    ob->set_property("hit bonus", 10);
    force_me("wear cross");

  return;
}

int query_num_rounds() { return 2; }

void catch_tell(string str) {
  string tmp;

  if(sscanf(str, "%*s says something in %s", tmp)) {
    if(!random(2)) return;
    force_me("speak common");
    force_me("say I can't understand "+tmp);
    return;
  }
}

void directed_message(object who, string str) {
#if 0
  if(str == "join" && who) {
    if(who->query_class() && (string)who->query_class() != "child") {
      tell_object(who, "Guildmaster tells you: Sorry, you already belong to a guild.");
      return;
    }
    if(!join_room) {
      tell_object(who, "Guildmaster tells you: Uh-oh, there is a bug in the joining room.");
      return;
    }
    join_room->set_member_status(lower_case((string)who->query_name()), "not joined");
    tell_object(who, "Guildmaster tells you: You may now join the guild.");
    return;
  }
#endif
  force_me("say This is a test I heard you tell me: "+str);
  return;
}

