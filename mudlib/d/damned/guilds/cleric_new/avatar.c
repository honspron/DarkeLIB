//	This is the Avatar (NPC guildmaster) for the Cleric Guild
//
//	DarkeLIB 0.1
//	Diewarzau 8/8/95
//  Rewrite: Zortek

#include <std.h>
#include <daemons.h>
#define GUILD_NAME "cleric"

inherit MONSTER;

int last_on;

void ask_for_blessing(object who);
void question_allow(string str, object who);
int set_last_on(int num) { return last_on = num; }

void create() {
  object ob;

  ::create();
  seteuid(getuid());
  set("short", "Avatar of the Holy Church");
  set("long", @LONG
This is an Avatar of the Holy Church.  It is a gentle soul
that has incarnated in the body of a seraph.  The Divine has
commissioned this Avatar to bless potential suplicants of the
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
  set_id(({ "avatar", "seraph" }));
  set_name("avatar");
  set_property("melee damage", ([ "crushing" : 50, "holy" : 70 ]));
  set_skill("perception", 150);
  set_skill("melee", 200);
  set_skill("dodge", 150);
  set_skill("parry", 150);
  set_skill("blunt", 87);
  set_skill("attack",200);

  set_property("random langs", 1);
  set_speech(10, "common",
    ({ "Greetings and fair day!  Welcome to the Holy Church.  If you need help, any member of the Faith will try to offer assistance.",
	   "Say unto me, \"avatar, I desire to be blessed\" in order to receive the blessing necessary to become a suplicant.",
       "Tell unto me, \"I desire to be blessed\" if you wish to begin walking on the path of righteousness.",
       "The Holy Church and its members of the faith welcome you. If you have any questions, please ask any member of the Faith for guidance.",
       "If you desire to share in the love of The Divine, worship the path of the pure, or seek the truest path to salvation, merely say unto me, \"avatar, I desrie to be blessed\"",
       "For a blessing to join in the refinement of your faith, tell me, \"I desire to be blessed\" and your journey can begin.",
       "Power lies not in raw might, but in the wielding of \"Faith,\" for when you are naked, lame, and toothless before the heavens, what have you, but that which you carry in your spirit?", 
       "Should you feel the urge to help others, heal the sick and infirm, raise the dead, and save souls...speak to me and in so saying, express to me \"I desire to be blessed\" and so it shall be.",
       "Does your life path point towards The Divine?  If your heart is certain...tell me \"I desire to be blessed\" and I will grant you the opportunity to explore your destiny.",
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
  string wibble;
  int allow;

  if( (str == "I desire to be blessed" || str == "Idesiretobeblessed") && who) {
    if( who->query_class() && (string)who->query_class() != "child" ) {
      wibble = who->query_class();
      if(wibble = "cleric") {
        force_me("speak "+who->query_primary_lang());
        force_me("say You are currently an active member of the Holy "+
               "Church!  Seeking additional blessings will not aid you "+
               "on your quest towards salvation...You are a valued member "+
               "of the Faith and with continued dedication and prayer, I "+
               "have no doubt you shall find spiritual enlightenment.");
        return;
      }
    }
    else if( who->query_property("allow") ) {
      wibble = who->query_property("allow");
      if(wibble = "cleric") {
        force_me("speak "+who->query_primary_lang());
        force_me("say You have already received my blessing to become "+
               "a suplicant of the Holy Church.  Multiple blessings "+
               "will do nothing to aid you in your quest to salvation!  "+
               "However, if you are trying to free yourself from your "+
               "obligation and loyalty to the Holy Church, all you need "+
               "to do is tell me to \"%^BOLD%^RED%^remove the blessing"+
               "%^RESET%^\" and it will be removed without question.");
        return;
      }
    }
    if(wibble) {
      force_me("speak "+who->query_primary_lang());
      force_me("say I'm terribly sorry, but you have already chosen a "+
               "life path with the "+capitalize(wibble)+
               "'s and are not unfettered.  Until you free yourself "+
               "of your loyalties and obligations to your current destiny, "+
               "I am not at liberty to bestow my blessing upon you.");
      return;
    }
    ask_for_blessing(who);
    return;
  }
  if( (str == "remove the blessing" || str == "removetheblessing") && who) {
    if( who->query_property("allowed") != "cleric" ) {
      force_me("speak "+who->query_primary_lang());
      force_me("say You currently do not carry my blessing, thus I cannot "+
               "remove what you do not have.  The Divine; however, could "+
               "remove something that does not exist, but that is an issue "+
               "best left for higher order priests to debate.");
      return;
    }
    GUILD_D->unallow_member(GUILD_NAME, who->query_name());
    force_me("speak "+who->query_primary_lang());
    force_me("say I have lifted my blessing from you, "+who->query_cap_name()+
             ".  I wish you well on your journey and will pray for your soul.");
    return;
  }
  return;
}
void ask_for_blessing(object who) {
  force_me("speak "+who->query_primary_lang());
  force_me("say "+who->query_cap_name()+
           ", I hear your words that you desire my blessing.  "+
           "Do you realize you are requesting to become a suplicant "+
           "to the Holy Church?");
  printf("[yes or no] ");
  set_heart_beat(0);
  input_to("question_allow", who);
  return;
}
void question_allow(string str, object who){
  if(!who) return;
  if(!str) {
    message("info", "%^BOLD%^RED%^Silent answers or nodding your head is not practical communication in this venue.%^RESET%^\nLet's try this again...", who);
    ask_for_blessing(who);
    set_heart_beat(1);
    return;
  }
  if(str != "yes" && str != "no") {
    message("info", "%^BOLD%^RED%^Your answer must have gotten lost in translation...%^RESET%^\nLet's try this again...", who);
    ask_for_blessing(who);
    set_heart_beat(1);
    return;
  }
  if(str == "yes") {
    GUILD_D->allow_member(GUILD_NAME, who->query_name());
    who->set_property("allowed", GUILD_NAME);
    CHAT_D->send_chat("cleric", this_object()->query_cap_name(),
            who->query_cap_name()+" has been blessed to become a suplicant.%^RESET%^");
    message("info", @TEXT
The Avatar begins to mumble in prayer...suddenly there is a warm palm
on your forehead and you feel a chill race up your spine.

The Avatar looks lovingly upon you and it's lips no longer move as it
speaks to you...%^BOLD%^GREEN%^

I sense you are deserving of my blessing...You have taken your first
step towards salvation.  Your next step will be to ask to "join" and
pass the spiritual fitness interview.  If all goes well you will soon
become a NEW member of the Holy Church.

Should you change your mind or decide you are unworthy, you may speak
unto me as you have done just now yet saying "%^YELLOW%^remove the blessing%^GREEN%^" and
without question, I will remove my blessing from you.%^RESET%^

The Avatar then turns its attention away from you...
TEXT
    , who);
    set_heart_beat(1);
    return;
  }
  else {
    message("info", @TEXT
The Avatar looks puzzled for a moment and then looks at you very
carefully, as if pondering the possibility of diabolical forces
at work...then, with compassion in its tone, you hear in your mind...
%^BOLD%^GREEN%^
I sense that you are have lost your way...My blessing and the way of
righteousness is understandably frightening...You need not fear the
Holy Church, unless you be infused with corruption or tainted by
diabolical forces...You are welcome in our house of The Divine and
should you change your mind, we will be here for you.
%^RESET%^
The Avatar then turns its attention away from you...
TEXT
    , who);
  }
  set_heart_beat(1);
  return;
}
