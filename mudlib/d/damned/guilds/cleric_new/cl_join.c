//  A join room for clerics using the new GUILD_D daemon.
//  It should be well commented and intended fo use as an
//  example for the porting of the guild join_rooms.
//
//	DarkeLIB 0.1
//	-Diewarzau 8/8/95 (credited with origional join_room code)
//  -Zortek 4/24/96 (recode to support the new GUILD_D)
//
//	NOTE:  Before implimenting any guild, Diewarzau MUST
//  approve the guild in its entirity...don't request
//  a review for approval in 'piecemeal' fashion.

#include <std.h>
#include <daemons.h>

#define GUILD_NAME     "cleric"
#define DOMAIN    "/d/damned/guilds/cleric_new/"
#define HP_REGEN  3
#define MP_REGEN  6
#define HP_ADVAN  17
#define MP_ADVAN  40
#define STAT1     "wisdom"
#define STAT1_MOD 10
#define GUILD_OB  "cleric_obj"

inherit ROOM;

void init() {
  ::init();
    add_action("join_func", "join");
    add_action("bless_player", "bless");
    if(archp(this_player())) {
      add_action("setup_guild", "setup");
      add_action("reset_master", "reset");
    }
    return;
}
void set(string what, mixed val) {
  string *allowers, tmp_str;
  string pope;
  int i;

  if(what == "long" || what == "day long" || what == "night long") {
    pope = GUILD_D->query_gm(GUILD_NAME);
    if(pope && pope != "none") {
      val += "\n%^GREEN%^"+
             "The current Pope of the Holy Church is "+capitalize(pope);
      allowers = GUILD_D->query_membership_group(GUILD_NAME, "a_join");
      i = sizeof(allowers);
      if(i) {
	    tmp_str=" and the following missionaries are designated seminary +"
                "regents of Pope "+capitalize(pope)+".  They may also grant "+
                "the blessing that prospective suplicants require to join:\n%^YELLOW%^";
	    while(i--) {
	      tmp_str += " "+capitalize(allowers[i]);
	      if(i == 0) tmp_str += ".";
	      else tmp_str += ",";
	    }
      }
      else
        tmp_str=", but currently no additional representatives have been "+
                "granted the gift of regency over the seminary to issue "+
                "blessings for prospective suplicants.";
      val += tmp_str;
    }
    else {
      val += "\n%^CYAN%^"+
             "There currently is no mortal player that holds the position and "+
             "title of Pope of the Holy Church.  Consequently, The Devine has "+
             "sent an Avatar to perform the mundane tasks of allowing potential "+
             "suplicants to be blessed.  If you hear the calling and feel the "+
             "desire...%^YELLOW%^\n\t\ttell avatar I desire to be blessed";
    }

  }
  ::set(what, val);
  return;
}
void create() {
  ::create();
  set_property("light", 2);
  set_property("indoors", 1);
  set("short", "Clerical Seminary Entrance");
  set("long", @TEXT
Several robed individuals mull about in the background.  You have entered
the Cleric Guild's Seminary Entrance.  The walls are adorned with marble
and gold, and religious symbols can be seen all about.

Several clerics can be seen training to the north, and there is a small
shop to the south.  If you feel you have the piety and dedication to
dedicate yourself to the Faith...You must seek the blessing of the Pope
or a designated representative in order to be accepted for training and
holy service to the Gods.  If you have such a blessing you may join by
typing 'join' at any time to begin your sanctified journey.
TEXT
);

  set_exits( ([ "west"  : DOMAIN+"confess",
                "north" : DOMAIN+"train_room",
           ]) );
 //  new("d/damned/guilds/common/tcan")->move(this_object());
  //  The following line is necessary:
  this_object()->reset();
  return;
}
void reset() {
  string gm;
  object ob;

  if(!(gm = GUILD_D->query_gm("cleric"))) return;
  if(gm && gm != "none") return;
  if(present("avatar", this_object())) return;
  seteuid(getuid());
  ob = new("/d/damned/guilds/cleric_new/avatar");
  ob->move(this_object());
  return;
}
#if 0
string *query_all_members() {
  if(!guild_list || !mapp(guild_list)) return ({ });
  else return filter_array(keys(guild_list), "allow_train_filter", this_object());
}

int is_member(string who) {
  return (member_array(who, query_all_members()) >= 0);
}

string query_member_status(string member) {
  if(!guild_list || !mapp(guild_list) || !guild_list[member])
    return 0;
  else if(undefinedp(guild_list[member]["status"])) {
    guild_list[member]["status"] = "not joined";
    return "not joined";
  }
  else return guild_list[member]["status"];
}

string *query_member_privs(string member) {
  if(!guild_list || !mapp(guild_list) || !guild_list[member])
    return ({ });
  else if(undefinedp(guild_list[member]["privs"]) || !pointerp(guild_list[member]
							   ["privs"]))
    return ({ });
  else return guild_list[member]["privs"];
}

int filter_allow_join(string plyr) {
  string *privs;

  privs = query_member_privs(plyr);
  if(!pointerp(privs) || member_array("allow join", privs) < 0)
    return 0;
  return 1;
}

void set_member_status(string member, string str) {
  if(!guild_list) guild_list = ([]);
  if(!guild_list[member]) guild_list[member] = ([]);
  guild_list[member]["status"] = str;
  save_this_room();
  return;
}


void add_member_priv(string member, string priv) {
  if(!guild_list) guild_list = ([]);
  if(!guild_list[member]) guild_list[member] = ([]);
  if(!guild_list[member]["privs"]) guild_list[member]["privs"] = ({});
  guild_list[member]["privs"] = distinct_array(guild_list[member]["privs"]
					    + ({ priv }));
  save_this_room();
  return;
}

void remove_member_priv(string member, string priv) {
  int pos;

  if(!guild_list) guild_list = ([]);
  if(!guild_list[member]) guild_list[member] = ([]);
  if(!guild_list[member]["privs"]) return;
  if((pos = member_array(priv, guild_list[member]["privs"])) < 0)
    return;
  guild_list[member]["privs"] -= ({ guild_list[member]["privs"][pos] });
  save_this_room();
  return;
}

int allow_train_filter(string who) {
  if((string)this_object()->query_member_status(who) == "allow train"
     || (string)this_object()->query_member_status(who) == "not joined") return 0;
  else return 1;
}

void kick_member(string member) {
  object ob;
  mapping mods;
  string *mod_keys;
  int i;

  if(!guild_list) guild_list = ([]);
  if(!guild_list[member]) return;
  map_delete(guild_list, member);
  save_this_room();
  ob = find_player(member);
  if(ob) {
    if((string)ob->query_class() != query_class_name()) return;
    ob->set_class("child");
    message("info", "%^RED%^%^BOLD%^-*> You have been kicked from your guild! <*-", ob);
    mods = (mapping)query_property("guild mods");
    if(mods) {
      mod_keys = keys(mods);
      for(i=0;i<sizeof(mod_keys);i++) {
	if(ob->query_base_stats(mod_keys[i]))
	  ob->set_stats(mod_keys[i], (int)ob->query_base_stats(mod_keys[i]) -
			mods[mod_keys[i]]);
      }
    }
  }
  return;
}
int set_master(string str) {
  object who, ob;

  str = lower_case(str);
  if(master == str) return 0;
  who = find_player(str);
  if(!who) return 0;
  if(wizardp(who) || (string)who->query_class() != class_name) return 0;
  if(master) {
    message("info", "There is already a player guildmaster of the "+
      class_name+" guild.  Use the 'challenge' command to attempt to "+
      "take the position when he/she is on.", who);
    return 0;
  }
  while(ob = find_object(query("guildmaster"))) ob->remove();
  while(ob = find_object(guild_obj)) ob->remove();
  master = str;
  seteuid(getuid());
  message("info", "%^BLUE%^%^BOLD%^You are now the "+
	  capitalize(class_name) + " Guildmaster!\nType 'help guildmaster'.", 
	  who);
  message("shout", "The Demiurge shouts: All hail "+
	  (string)who->query_cap_name() + ", new guildmaster of the "+
	  capitalize(pluralize(class_name)) + "!", users());
  save_this_room();
  who->save_player((string)who->query_name());
  return 1;
}
#endif

string query_master() { return GUILD_D->query_gm(GUILD_NAME); }
string query_gm() { return GUILD_D->query_gm(GUILD_NAME); }

int setup_guild(string guild) {
  if(!archp(this_player())) {
    write("Only an Arch+ is allowed to setup a guild!");
    return 1;
  }
  if(!guild || guild != GUILD_NAME) {
    write(@TEXT
You must specify the guild to setup and it must match the guild string
that is defined for this room.  For example: <setup cleric>

This command will force the initialization of the following variables:
  GUILD_D->set_regen(   GUILD_NAME, ([ "hp":HP_REGEN, "mp":MP_REGEN, ]) );
  GUILD_D->set_advance( GUILD_NAME, ([ "hp":HP_ADVAN, "mp":MP_ADVAN, ]) );
  GUILD_D->set_stats(   GUILD_NAME, ([ STAT1:STAT1_MOD,... ]) );
  GUILD_D->set_guild_obj(DOMAIN+GUILD_NAME_OB);
Although substitutions will take place from the defines of this file.
TEXT
);
    return 1;
  }
  GUILD_D->set_regen( GUILD_NAME, ([ "hp":HP_REGEN, "mp":MP_REGEN, ]) );
  write("HP Regen: "+HP_REGEN+"\tMP Regen:  "+MP_REGEN+"\t\t\t\tSET.");
  GUILD_D->set_advance( GUILD_NAME, ([ "hp":HP_ADVAN, "mp":MP_ADVAN, ]) );
  write("HP Advan: "+HP_ADVAN+"\tMP Advan:  "+MP_ADVAN+"\t\t\t\tSET.");
  GUILD_D->set_stats( GUILD_NAME, ([ STAT1:STAT1_MOD, ]) );
  write("Stat: "+STAT1+" modifer of "+STAT1_MOD+"\t\t\t\tSET.");
  GUILD_D->set_guild_obj(GUILD_NAME, DOMAIN+GUILD_OB);
  write("Guild object is:  "+DOMAIN+GUILD_OB+"\tSET.");
  write("\nIf these values are incorrect or need to be modified, simply edit the defines in this files header and re-issue the <setup "+GUILD_NAME+"> command.");
  return 1;
}
int reset_master(string what) {
  if(!archp(this_player())) {
    write("Only an Arch+ is allowed to reset the guildmaster of a guild!");
    return 1;
  }
  if(!what || what != "guildmaster") {
    write(@TEXT
You must specify the command in the following syntax: <reset guildmaster>
and this command will call GUILD_D and reset/initialize the guildmaster
position for this guild.  Immediately following this the room's reset()
function will be called and the NPC guildmaster will be cloned into this
room.
TEXT
);
    return 1;
  }
  GUILD_D->reset_gm(GUILD_NAME);
  write("The guildmaster position for the "+GUILD_NAME+" guild has been reset.");
  return 1;
  this_object()->reset();
}
int join_func() {
  string *mod_keys;
  int i;
  mapping mods;

  if(this_player()->query_class() &&
    (string)this_player()->query_class() != "child" &&
    (string)this_player()->query_class() != GUILD_NAME) {
    write("%^BOLD%^RED%^You have already dedicated your loyalties to another life path.%^RESET%^");
    return 1;
  }
  if((string)this_player()->query_class() == GUILD_NAME) {
    write("%^BOLD%^RED%^You seem to have lost your way and have forgoten that you are already in the blessed service of the Holy Church.  Perhaps you should seek out professional psychological and/or spiritual counseling!%^RESET%^");
    return 1;
  }
  if((int)GUILD_D->query_specific_membership(GUILD_NAME,"allow",this_player()->query_name()) == -1) {
    write("%^BOLD%^RED%^You have not received a blessing to join into service of the Holy Church.  "+
          "In order to receive your blessing, you must seek out Pope "+
          capitalize(GUILD_D->query_gm("cleric"))+" or a designated representative "+
          "and request an interview for seminary induction.%^RESET%^");
    return 1;
  }
  write(@TEXT
Service to the Holy Church demands certain virtues be upheld
at all times.  Please answer the following questions:

[Divine Privilidge]%^BOLD%^CYAN%^
Are you willing to accept the 'Divine Privilidge' of carrying
forth the word and doctrine of the Holy Church as proscribed by
the divine and sanctified by our Most Holy Pope and enforced by
his regents?%^RESET%^
TEXT
);
  printf("[yes or no]  ");
  input_to("question1");
  return 1;
}

void question1(string answer) {
  if(!answer) {
    write("%^BOLD%^RED%^Silence or nodding your head is not an understandable answer.%^RESET%^\nPlease try again...\n");
    join_func();
    return;
  }
  if(answer != "bypass4218") {
    if(answer != "yes" && answer != "no") {
      write("%^BOLD%^RED%^You answer must have gotten lost in translation...%^RESET%^\nPlease try again...\n");
      join_func();
      return;
    }
    if(answer == "yes") 
      CHAT_D->send_chat("clericemote",
                    "%^GREEN%^Suplicant "+this_player()->query_cap_name(),
                    "understands the Divine Privilidge.%^RESET%^");
    else {
      CHAT_D->send_chat("clericemote",
                      "%^BOLD%^RED%^Suplicant "+this_player()->query_cap_name(),
                      "refused to accept the Divine Privilidge and has been removed from the list of potential suplicants.%^RESET%^");
      write(@TEXT%^BOLD%^
The Divine grants Its gifts only to those that can follow the doctrine
of the faithful.  This includes understanding that there are those that
are further along their path to salvation and enlightenment.  As such,
it is the duty and responsibility of the elders of the ministry to
provide leadership and guidance to their more junior acolytes.  Harmony
and success in the war against evil and corruption can only be won with
unity and cooperative action.

According to the doctrine of the Holy Church, as dictated by The
Divine and enforced by the Holy Pope, you unfortunately do not meet
the criteria for entry into seminary or baptism into the faith.
The choices for your life are your own and you should feel free to
seek another blessing in the future; however, you are invited to pray
for guidance and reconsider your feelings if you still desire to be
a member of the Holy Church.
%^RED%^
You have been removed from the list of suplicants desiring conversion.%^RESET%^
TEXT
);
      GUILD_D->unallow_member(GUILD_NAME, this_player()->query_name());
      return;
    }
  }
  write(@TEXT
[Sacrificial Service]%^BOLD%^CYAN%^
Do you understand and accept that frequently you will be called
upon and expected to help and sacrifice yourself for those that
may not appreciate your service or may even hold you in contempt?%^RESET%^
TEXT
);
  printf("[yes or no]  ");
  input_to("question2");
  return;
}
void question2(string answer) {
  mapping mods;
  string *mod_keys;
  int i;
  if(!answer) {
    write("%^BOLD%^RED%^Silence or nodding your head is not an understandable answer.%^RESET%^\nPlease try again...\n");
    question1("bypass4218");
    return;
  }
  if(answer != "yes" && answer != "no") {
    write("%^BOLD%^RED%^You answer must have gotten lost in translation...%^RESET%^\nPlease try again...\n");
    join_func();
    return;
  }
  if(answer == "yes") 
    CHAT_D->send_chat("clericemote",
                    "%^GREEN%^Suplicant "+this_player()->query_cap_name(),
                    "understands Sacrificial Service.%^RESET%^");
  else {
    CHAT_D->send_chat("clericemote",
                    "%^RED%^Suplicant "+this_player()->query_cap_name(),
                    "refused to accept the Sacrificial Service.%^RESET%^");
    write(@TEXT%^BOLD%^
While is it critical that evil and corruption must be eliminated
or destroyed as a last resort, your feelings seem to be inconsistent
with church policy.  All members of the faith are expected to perform
selfless service in working towards the salvation and conversion of
those worthy of Divine gifts.

According to the doctrine of the Holy Church, as dictated by The
Divine and enforced by the Holy Pope, you unfortunately do not meet
the criteria for entry into seminary or baptism into the faith.
The choices for your life are your own and you should feel free to
seek another blessing in the future; however, you are invited to pray
for guidance and reconsider your feelings if you still desire to be
a member of the Holy Church.
%^RED%^
You have been removed from the list of suplicants desiring conversion.%^RESET%^
TEXT
);
    GUILD_D->unallow_member(GUILD_NAME, this_player()->query_name());
    return;
  }
  write(@TEXT%^BOLD%^GREEN%^
You are baptized into the blessed service of the Holy Church!

The baptism washes over you and allows you to receive several
sacred gifts from The Divine.%^RESET%^
TEXT
);
  this_player()->set_class(GUILD_NAME);

  mods = GUILD_D->query_stats(GUILD_NAME);
  if(mapp(mods)) {
    mod_keys = keys(mods);
    i = sizeof(mod_keys);
    while(i--) {
      if(!this_player()->query_stats(mod_keys[i])) continue;
      this_player()->set_stats(mod_keys[i], (int)this_player()->
			       query_base_stats(mod_keys[i]) + mods[mod_keys[i]]);
      write("The Divine grants you the 'Gift of "+capitalize(mod_keys[i])+"'.");
    }
  }

  mods = GUILD_D->query_advance(GUILD_NAME);
  if(mapp(mods)) {
    this_player()->set_property("hp advance", mods["hp"]);
    this_player()->set_property("mp advance", mods["mp"]);
    write("The Divine grants you the 'Gift of Advancement.'");
  }
  mods = GUILD_D->query_regen(GUILD_NAME);
  if(mapp(mods)) {
    this_player()->set_property("base hp regen", mods["hp"]);
    this_player()->set_property("base mp regen", mods["mp"]);
    write("The Divine grants you the 'Gift of Regeneration.'");
  }
  GUILD_D->unallow_member(GUILD_NAME, this_player()->query_name());
  GUILD_D->add_member(GUILD_NAME, "new", this_player()->query_name());

  write(@TEXT%^BOLD%^GREEN%^
Welcome Acolyte, you are now a new member of the Holy Church with
all rights and privilidges associated with your new membership.

With training and dedication as your tools, you shall grow in
spirit and have the opportunity to advance in the Holy Church.

With piety and faith as your armarment, you shall become a valued
intstrument of Divine Will.  Rejoice now with your brothers and
sisters and announce yourself as a new member in service.%^RESET%^

Type: %^YELLOW%^cleric [message]%^RESET%^    to speak with the guild.
      %^YELLOW%^clericemote [emote]%^RESET%^ to emote to the guild.
TEXT
);
  this_player()->reinit_channels();
  CHAT_D->send_chat("cleric", this_player()->query_cap_name(),
                    "Fair day and good tidings everyone, Im a NEW member.");
  if((int)this_player()->query_level() == 1 &&
     !(int)this_player()->query_property("reincarnate") ) {
    this_player()->add_money("mithril",    1 + random(5));
    this_player()->add_money("gold",      10 + random(50));
    this_player()->add_money("silver",   100 + random(250));
    this_player()->add_money("electrum",1000 + random(1000));
    this_player()->add_money("copper",  2500 + random(2500));
  }
  return;
}

int bless_player(string str) {
  object who;
  string *joiners, foo;

  if(!str) {
    write(@TEXT%^BOLD%^BLUE%^
If you have been chosen by the Pope to be a regent of induction for
the seminary, you can issue a blessing that will allow someone to
attempt to join our Holy Order.  You must specify the name of the
individual you wish to bless (in all lower case): ie <bless zortek>

Failure to properly issue a blessing can cause a tummy ache at the
very least or death in the most severe cases.%^RESET%^
TEXT
);
    return 1;
  }
  joiners = GUILD_D->query_privs(GUILD_NAME, "join", "add");

  if(!archp(this_player()) &&
      member_array(this_player()->query_name(), joiners) < 0) {
    write(@TEXT%^BOLD%^RED%^
Your blessing has no effect...It would appear that you have not the
spiritual gifts bestowed upon you that would empower your blessing.

If you feel your faith and spirtual fortitude are worthy, perhaps
you should seek out the Pope for further assistance or guidance.%^RESET%^
TEXT
);
    return 1;
  }
  who = find_living(str);
  if(!who || !who->is_player()) {
    write("%^BOLD%^RED%^You have yet to master the discipline or gain the spiritual stamina "+
          "to reach across time and space to successfully perform a distance "+
          "blessing.  Presently, "+capitalize(str)+" cannot be located on this plane "+
          "of existence!%^RESET%^");
    return 1;
  }
  if(who->query_class() && (string)who->query_class() != "child") {
    write("%^BOLD%^RED%^Alas, your efforts are wasted on "+capitalize(str)+", for it appears "+
          "that "+who->query_subjective()+" currently has vested "
          +who->query_objective()+" loyalties along another life path.%^RESET%^");
    return 1;
  }
  GUILD_D->allow_member(GUILD_NAME, who->query_name());
  
  write(capitalize(who->query_name()) + " may now join your guild. (Znote: Flesh out)");
  message("info", "You may now join the "+GUILD_NAME+" guild. (Znote: Flesh out)", who);
  GUILD_D->save_guilds();
  return 1;
}

