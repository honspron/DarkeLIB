//  A join room for clerics using the new GUILD2_D daemon.
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
// 
//  BUILDERS: IF YOU DO NOT MIRROR THE INDENTION CONVENTIONS
//  THAT ARE IN THIS FILE...YOUR GUILD WILL NOT BE APPROVED!

/* The following three includes are required. */
#include <std.h>
#include <daemons.h>
#include <guild.h>

/* The GUILD_NAME is the official name (code-wise) that is given
 * to this guild.  It is the name that will be used/referenced in
 * the guild daemon and the name that is sent to this_player()
 * via set_class()  The name should be in all lower case and a
 * single space should be avoided where possible.  A single hyphen
 * is allowable as a spacer between words.
 */
#define GUILD_NAME     "cleric"

/* The HP_REGEN and MP_REGEN are used to establish the regeneration
 * rate of hp's and mp's for members of this guild.  Builders should
 * be cautioned that these values are to be considered constants for
 * this guild and are subject to change only by an act of congress or
 * god (which ever is more difficult).
 * HP BASELINE: X          MIN/MAX: Y/Z
 * MP BASELINE: X          MIN/MAX: Y/Z
 * The above baseline values should be considered the mean by which
 * all guilds should "in theory" be compared against and under NO
 * circumstance should ANY value ever exceed the MIN/MAX parameters.
 */
#define HP_REGEN  3
#define MP_REGEN  6

/* The HP_ADVAN and MP_ADVAN are used to establish the advancement
 * rate of hp's and mp's for members of this guild.  Builders should
 * be cautioned that these values are to be considered constants for
 * this guild and are subject to change only by an act of congress AND
 * god (truely not a daily occurance).
 * HP BASELINE: X          MIN/MAX: Y/Z
 * MP BASELINE: X          MIN/MAX: Y/Z
 * The above baseline values should be considered the mean by which
 * all guilds should "in theory" be compared against and under NO
 * circumstance should ANY value ever exceed the MIN/MAX parameters.
 */
#define HP_ADVAN  17
#define MP_ADVAN  40

/* The "STAT" defines are used to build a mapping of modifiers that
 * are applied to new members statistics when they initially join the
 * guild.  These defines are a tad more complex only in that their
 * number (quantity of defines) is variable.  It is critical to note
 * that a change here MUST be mirrored in the code (see annotation
 * below) and failure to follow these very detailed instruction could
 * result in the death of a famous movie star or a nervous breakdown
 * in your neighbors beloved pet!
 * [or even cause the code not to work.....GASP!]
 * Your additional defines should follow the standard STAT#_MOD and
 * STAT# format with each STAT# reflecting the string of the statistic
 * to be modified and STAT#_MOD reflecting the modifier that is to be
 * applied to the new member's statistic.
 * BASELINE MODIFIER:  0  (no modification)    MAX/MIN: X/Y
 * The above baseline values should be considered the mean by which
 * all guilds should "in theory" be compared against and under NO
 * circumstance should ANY value ever exceed the MIN/MAX parameters.
 *
 * EXAMPLE ADDITIONS:  (NOT reflected in the code below)
 * #STAT2         "intelligence"
 * #STAT2_MOD     -10
 * #STAT3         "strength"
 * #STAT3_MOD     15
 */
#define STAT1     "wisdom"
#define STAT1_MOD 10

/* The GUILD_OB define or often called the guildmaster object is/was
 * used in the old system to apply the add_action() guild maintenance
 * commands to the guildmaster.  In the new system, this context is
 * obsolete since all of the guild maintenance commands will be moved
 * to the guild office (room) or converted to _cmds that will utilize
 * the new guild_security bit string as an access check.  The define
 * is present here only for the emotional support of the admins, but
 * it is possible that a valid implimentation for this may yet be
 * discovered.
 * NOTE: the guild domain is not included in the define here since it
 * appears in a string addition later in the code.
 */
#define GUILD_OB  "cleric_obj"

/* Yes, this is a room...thus the inherit of /std/room */
inherit ROOM;

/* The init() function is used primarily at this time to add_action()
 * the minimum commands necessary to satisfy the minimum functionality
 * of this "join room"  Now, you may ask, "Why is the setup and reset
 * present in this room?"...well, the answer is simple...because, at
 * the time of this writing, Zortek has worn his fingers to bloody stumps
 * and has yet to code the guild office room (which is where these two
 * commands will eventually end up)!  I will document them here though
 * and port the annotations with the code.
 * Builder will note the archp() control-break structure.  Builders ARE
 * allowed to bypass this check for development and testing of NEW guilds
 * but the check MUST be in place and active before any guild will be
 * allowed to go "online"
 */
void init() {
  ::init();
    add_action("join_func", "join");     //join a player to guild
    add_action("bless_player", "bless"); //allow a player to join
    if(archp(this_player())) {
      add_action("setup_guild", "setup");  //initialize the guild
      add_action("reset_master", "reset"); //reset the guildmaster
    }
    return;
}

/* The following set() function interrupts the call to ROOM::set()
 * and allows the room to adjust its description to reflect guild
 * conditions at the time of cloning.  Builders are encouraged to
 * adjust the "flavor" of the descriptions but cautioned against
 * making modifications to the fundimental logic or intent of the
 * code in this function.  Which brings me to the intent--
 * The function is designed to modify the description based on
 * the following issues:
 *   Is there a PC guildmaster?
 *   When was the last_on for a member on that can allow a player to join?
 *   Um...anything else that admin decides to check...
 */
void set(string what, mixed val) {
  string *allowers,
         tmp_str; // people permitted to allow and temporary string
  string pope;    // pope aka guildmaster
  int i;          // counter

  if(what == "long" || what == "day long" || what == "night long") {
    pope = GUILD2_D->query_master(GUILD_NAME);
    if(pope && pope != "") {
//@@ Builder should change the description below to match the theme
//@@ or title of the guildmaster of their guild.
      val += "\n%^GREEN%^"+
             "The current Pope of the Holy Church is "+capitalize(pope);
      allowers = GUILD2_D->query_allowers(GUILD_NAME);
      i = sizeof(allowers);
      if(i) {
//@@ Builder can change the following description to match the theme
//@@ of thier particular guild.  This description indicates who else
//@@ in the guild is a DIPLOMAT and granted the guild_security needed
//@@ to allow another player to join the guild.
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
//@@ Builder can change the following description to match the theme
//@@ of their guild.  This description is given if the guildmaster has
//@@ granted permission to NO OTHER member of this guild.
        tmp_str=", but currently no additional representatives have been "+
                "granted the gift of regency over the seminary to issue "+
                "blessings for prospective suplicants.";
      val += tmp_str;
    }
    else {
//@@ Builder can change the following description to match the theme
//@@ of their guild.  This description is given when there is no mortal
//@@ player that holds the official title/position of guildmaster OR !!!
//@@ EVENTUALLY, if a DIPLOMAT or the GUILDMASTER has not logged on in
//@@ a predetermined length of time the guild's "avatar" will be granted
//@@ the permission to allow people to join the guild!!!
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

/* Yes we need a create function. */
void create() {
  seteuid(getuid());
  ::create();
  set_property("light", 2);
  set_property("indoors", 1);
  set("short", "Clerical Seminary Entrance");  //Customizable by builder
//@@ DO NOT ALTER this to use set_long(), set_day_long(), or set_night_long()
//@@ You will be inflicted by herpes if you do!
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
); //Customizable by builder

/* Exits themselves are customizable; HOWEVER, the builder should be aware
 * that in order for your guild file to be accepted as valid by the guild
 * daemon you must utilize the XX_DOMAIN+"file_name" structure...the DOMAIN
 * is defined in <guild.h> and must be implimented by an admin.  If you
 * don't like it, then you can go back to building weapons, monsters, and
 * other petty (but important) files.
 */
  set_exits( ([ "west"  : CL_DOMAIN+"confess",
                "north" : CL_DOMAIN+"train_room",
           ]) );

/* Ye olde rubbish bin...*/
  new("d/damned/guilds/common/tcan")->move(this_object());

/* The following line is NECESSARY and should under NO circumstance
 * be removed...now although personally (Zortek) I think it may be
 * UNnecessary considering that as part of the cloning of an item
 * reset() gets called anyway...but I felt it was important initially
 * to mandate the reset() call so I musta had a reason.
 */
  this_object()->reset();

/* This call to the guild daemon lets it know what my file name and
 * path are "just in case" I need to know...generically, this puts
 * the daemon in the position of being capable of "daemon servicing"
 * external files and while not critical or implimented currently,
 * it is provided for expansion (Builders should read this as a note
 * meaning "Don't muck with the following line, Just because!")
 */
  GUILD2_D->set_join_room(GUILD_NAME,file_name(this_object()));
  return;
}

/* Well, now I get the spendid chance to figure out why I felt this
 * dern reset() function was so important that I had to mutter out
 * several extra lines of comments....*cough*
 */
void reset() {
  string gm;           //the guildmaster's name
  int last_on, flag;   //last time a DIPLOMAT or GM was on, uh..flag
  object ob;           //generic object

  seteuid(getuid());
  flag = 0;
  gm = GUILD2_D->query_master(GUILD_NAME);
//@@ Builder, you will need to know what your "Guild Guardian's" name
//@@ or id is or will be...once you know, change the "avatar" to the
//@@ id of your mob.
  if(present("avatar", this_object())) {
    ob = find_living("avatar");
    flag = 1;
  }
  else
//@@ Obviousely, this is the file of the guardian mob
    ob = new("/d/damned/guilds/cleric_new/avatar2");
  if(gm && gm != "") {
    last_on = GUILD2_D->query_last_on(GUILD_NAME);
    ob->set_last_on(last_on);
  }
//@@ MUDLIB...the guardian should always be present in this room;
//@@ however, based upon the existence of a GM or a time since
//@@ last_on, we will mitigate the mob's functionality.
  if(!flag) ob->move(this_object());
  return;
}

/* Self-explanitory...or do I really need to state the obvious? */
string query_master() { return GUILD2_D->query_master(GUILD_NAME); }

/* The setup_guild() function will eventually end up in the code for
 * the guild office.  However, it is here for now, sooo...
 * The following function draws upon the defines established at the
 * top of this file relating to Regen, Advance, and Stat mods.
 * Once a guild is established, this function is callable via the
 * add_action() in the above init() function.  This function,
 * technically, should only need to be called once to activate
 * the guild into the system; however, it is recognized that for
 * balance purposes, an arch may need to adjust these values.
 * Builders really have no need or reason to modify anything in
 * this function.
 */
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
  GUILD2_D->set_regen(   GUILD_NAME, ([ "hp":HP_REGEN, "mp":MP_REGEN, ]) );
  GUILD2_D->set_advance( GUILD_NAME, ([ "hp":HP_ADVAN, "mp":MP_ADVAN, ]) );
  GUILD2_D->set_stats(   GUILD_NAME, ([ STAT1:STAT1_MOD,... ]) );
//OFFLINE  GUILD2_D->set_guild_obj(CL_DOMAIN+GUILD_NAME_OB);
Although substitutions will take place from the defines of this file.
TEXT
);
    return 1;
  }
  GUILD2_D->set_regen( GUILD_NAME, ([ "hp":HP_REGEN, "mp":MP_REGEN, ]) );
  write("HP Regen: "+HP_REGEN+"\tMP Regen:  "+MP_REGEN+"\t\t\t\tSET.");
  GUILD2_D->set_advance( GUILD_NAME, ([ "hp":HP_ADVAN, "mp":MP_ADVAN, ]) );
  write("HP Advan: "+HP_ADVAN+"\tMP Advan:  "+MP_ADVAN+"\t\t\t\tSET.");
  GUILD2_D->set_stats( GUILD_NAME, ([ STAT1:STAT1_MOD, ]) );
  write("Stat: "+STAT1+" modifer of "+STAT1_MOD+"\t\t\t\tSET.");
//OFFLINE  GUILD2_D->set_guild_obj(GUILD_NAME, CL_DOMAIN+GUILD_OB);
//OFFLINE  write("Guild object is:  "+CL_DOMAIN+GUILD_OB+"\tSET.");
  write("\nIf these values are incorrect or need to be modified, simply edit the defines in this files header and re-issue the <setup "+GUILD_NAME+"> command.");
  return 1;
}

/* The setup_guild() function will eventually end up in the code for
 * the guild office.  However, it is here for now, sooo...
 * The following function will set the guildmaster IN THE DAEMON to a
 * null string ("") and this will have the effect of initializing the
 * guildmaster position.  Since all guild members have (or will have)
 * their guild security bits verified when they login this will allow
 * a guildmaster that is even offline to be affected (albiet distantly).
 * Down the road we may wish to clone a null user object, restore_object
 * on the null user with the GM's .o file, remove, and save the guild
 * security bit string, this should serve us well with a minimal amount
 * of primary cpu usage.  Builders should have no reason/need to edit
 * or modify the reset_master() function.
 */
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
  GUILD2_D->set_master(GUILD_NAME, "");
  write("The guildmaster position for the "+GUILD_NAME+" guild has been reset.");
  return 1;
  this_object()->reset();
}

/* This function (bless_player) is the function that is called when
 * a DIPLOMAT player or the GM chooses to allow someone to join the
 * guild.  Where noted the descriptions may be changed to meet the
 * theme requirements of the particular guild.
 */
int bless_player(string str) {
  object who;  //variable that will hold the "allowed" player
  string *joiners,
         foo,
         guild_security; //Array of DIPLOMATS, generic var, bits string

  if(!str) {
//@@ Builders may adjust this description to meet theme requirements.
//@@ This is a failure to supply an argument to the bless command.
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
  guild_security = this_player()->query_guild_security();

  if(!archp(this_player()) && !test_bit(guild_security, GUILD_DIPLOMAT) ) {
//@@ Builders may adjust this description to meet theme requirements.
//@@ This is a guild security failure message (Not a diplomat)
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
//@@ Builders may adjust this description to meet theme requirements.
//@@ This is a failure to locate the target player message
    write("%^BOLD%^RED%^You have yet to master the discipline or gain "+
          "the spiritual stamina to reach across time and space to "+
          "successfully perform a distance blessing.  Presently, "+
          capitalize(str)+" cannot be located on this plane "+
          "of existence!%^RESET%^");
    return 1;
  }
  if(who->query_class() && (string)who->query_class() != "child") {
//@@ Builders may adjust this description to meet theme requirements.
//@@ This is a failure due to the target already being a member of
//@@ another guild.
    write("%^BOLD%^RED%^Alas, your efforts are wasted on "+
          capitalize(str)+", for it appears that "+
          who->query_subjective()+" currently has vested "+
          who->query_objective()+" loyalties along another life path.%^RESET%^");
    return 1;
  }
  guild_security = who->query_guild_security();
  if(test_bit(guild_security, BANISHED) && !archp(this_player())) {
//@@ Builders may adjust this description to meet theme requirements.
//@@ This is a guild security failure message (Target has been banished)
    write("%^BOLD%^RED%^"+capitalize(str)+
          " has been banished from another guild..."+
          "this must be resolved before your blessing can succeed.");
//@@ Builders may adjust this description to meet theme requirements.
//@@ This is a guild security failure message (Target has been banished)
    message("info", @TEXT
%^BOLD%^RED%^
You have been banished from another guild and this issue must be
resolved with your former guildmaster.  The Pope of the Holy Church
is the only cleric that can absolve you of your former sins and
grant you a blessing.
TEXT
, who);

    return 1;
  }
//@@ Builders may adjust this description to meet theme requirements.
//@@ This is a guild security failure message (Target is a guild enemy)
  if(test_bit(guild_security, CLERIC_ENEMY) && !archp(this_player())) {
    write("%^BOLD%^RED%^"+capitalize(str)+
          " has been declared an enemy of the Holy Church!!!  "+
          "The Divine will not channel a blessing to the Damned.");
//@@ Builders may adjust this description to meet theme requirements.
//@@ This is a guild security failure message (Target is a guild enemy)
    message("info", @TEXT
%^BOLD%^RED%^
You are currently Damned as an enemy of the Holy Church and The Divine
will not channel the blessing to you until your soul is redeemed of this
most foul blight.  The Pope of the Holy Church is the only cleric who may
absolve you of your former sins and grant you a blessing.
TEXT
, who);
    return 1;
  }
  if((string)who->query_property("guild allowing") == GUILD_NAME)
    if(test_bit(guild_security, ALLOW_TO_JOIN)) {
//@@ Builders may adjust this description to meet theme requirements.
//@@ This is a guild security failure message (Target already allowed HERE)
      write("%^BOLD%^RED%^"+capitalize(str)+" has already been blessed to "+
          "enter the Holy Church.");
      return 1;
    }
  else {
//@@ Builders may adjust this description to meet theme requirements.
//@@ This is a guild security failure message (Target already allowed OTHER)
    write("%^BOLD%^RED%^"+capitalize(str)+" currently has petitioned and "+
          "been accepted for membership with the "+
          capitalize((string)who->query_property("guild allowing"))+
          "'s and as such is not permitted to be blessed at this time.");
    return 1;
  }
  guild_security = set_bit(guild_security, ALLOW_TO_JOIN);
  who->set_guild_security(guild_security);
  who->set_property("guild allowing", GUILD_NAME);
//@@ Builders may adjust this description to meet theme requirements.
//@@ These are the success messages (allower and allowee respectively)
  write(capitalize(who->query_name()) + " may now enter into Seminary.");
  message("info", "You have received a blessing from "+
          this_player()->query_cap_name()+
          " and may now enter into Seminary.", who);
  GUILD2_D->save_guilds();
  return 1;
}

/* Welcome to the wonderful world of joining a guild!
 * Below is the primary code that is used to convert someone
 * that has been allowed to join THIS guild into a probationary
 * new member.  I won't address the details of guild security
 * here (that is a seperate document, hopefully).  Builders
 * are encouraged to change the descriptions to meet the theme
 * requirements of their guild; however, unless otherwise noted,
 * changes to the core logic is discouraged.
 */
int join_func() {
  string *mod_keys, guild_security;  //array of modifiers, bit string
  int i;                             //counter
  mapping mods;                      //mapping of modifiers

  if(this_player()->query_class() &&
    (string)this_player()->query_class() != "child" &&
    (string)this_player()->query_class() != GUILD_NAME) {
//@@ Builders may adjust this description to meet theme requirements.
//@@ This is a rejection because player is already in a guild (OTHER)
    write(@TEXT
%^BOLD%^RED%^
You have already dedicated your loyalties to another life path.
%^RESET%^
If you are interested in giving your life and soul over to the
Holy Church, you must liberate yourself from ties that bind you
to other obligations.  A life in the Order of the Clerics demands
complete dedication and The Divine demands nothing less than utter
loyalty and faith.
TEXT
);
    return 1;
  }
  if((string)this_player()->query_class() == GUILD_NAME) {
//@@ Builders may adjust this description to meet theme requirements.
//@@ This is a rejection because player is already in a guild (HERE)
    write(@TEXT
%^BOLD%^RED%^
You seem to have lost your way and have forgoten that you are already
in the blessed service of the Holy Church.  Perhaps you should seek
professional psychological and/or spiritual counseling!
TEXT
);
    return 1;
  }
  guild_security = this_player()->query_guild_security();
// CODER NOTE: possible fubar if security is set and property is not?
  if(!test_bit(guild_security, ALLOW_TO_JOIN) ||
     (string)this_player()->query_property("guild allowing") != GUILD_NAME) {
//@@ Builders may adjust this description to meet theme requirements.
//@@ This is a rejection because player has NOT been allowed to join
    write("%^BOLD%^RED%^You have not received a blessing to join "+
          "into service of the Holy Church.  In order to receive "+
          "your blessing, you must seek out Pope "+
          capitalize(GUILD2_D->query_master(GUILD_NAME))+
          " or a designated representative and request an interview "+
          "for seminary induction.%^RESET%^");
    return 1;
  }
/* Here begins the AFFIRMATIONS for membership.  This section is
 * somewhat variable, in that, there is the ability to support
 * more than the TWO questions that are required for membership
 * in this stock file that is used for the Cleric guild.  The
 * questions SHOULD be modified to fit the theme of the particular
 * guild.  The STANDARD expectation in these questions is for the
 * questions to be answered with a yes/no response.  "Yes" answers
 * continue the process and "no" answers will abort and boot or
 * remove the player from consideration of membership.  This need
 * not ALWAYS be the case, but if you change the logic be sure it
 * is sound and properly adjusted (caviat programmus).
 */
//@@ Builders note that the player is warned/notified that s/he
//@@ must "answer the following questions:"
  write(@TEXT
Service to the Holy Church demands certain virtues be upheld
at all times.  Please answer the following questions:

[Divine Privilidge]%^BOLD%^CYAN%^
Are you willing to accept the 'Divine Privilidge' of carrying
forth the word and doctrine of the Holy Church as proscribed by
the divine and sanctified by our Most Holy Pope and enforced by
his regents?
TEXT
);
//@@ This printf should not be changed except to qualify the
//@@ content of expected answers.  The printf string is NOT
//@@ terminated with a \n so that the player's response is
//@@ kept on the same line...
  printf("[yes or no]  ");
  input_to("question1");
  return 1;
}

/* Note the naming convention of the question functions (questionX) */
void question1(string answer) {
  string guild_security;

  if(!answer) {
//@@ Description used if a null response is recieved
    write(@TEXT
%^BOLD%^RED%^
Silence or nodding your head is not an understandable answer.
%^RESET%^
Please try again...
TEXT
);
    join_func();
    return;
  }
//@@ This check is basically a cryptic (impossible) response that is
//@@ used internally as a bypass flag for recursive calls to this function
  if(answer != "bypass4218") {
    if(answer != "yes" && answer != "no") {
//@@ If the answer is not an acceptable one (ie yes/no)
      write(@TEXT
%^BOLD%^RED%^
You answer must have gotten lost in translation...
%^RESET%^
Please try again...
TEXT
);
      join_func();
      return;
    }
//@@ Action taken in the event of a "yes" answer
    if(answer == "yes") 
      CHAT_D->send_chat("clericemote",
                    "%^GREEN%^Suplicant "+this_player()->query_cap_name(),
                    "understands the Divine Privilidge.%^RESET%^");
    else {
//@@ Action taken in the event of a "no" answer (or a missed OTHER response)
      CHAT_D->send_chat("clericemote",
              "%^BOLD%^RED%^Suplicant "+this_player()->query_cap_name(),
              "refused to accept the Divine Privilidge and has been "+
              "removed from the list of potential suplicants.%^RESET%^");
//@@ Builders may adjust this description to meet theme requirements.
//@@ This is the message sent to the player explaining WHY s/he has been
//@@ determined to be unfit to join the guild based upon the context of
//@@ the question s/he just answered.
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
      guild_security = this_player()->query_guild_security();
      this_player()->set_guild_security(clear_bit(guild_security, ALLOW_TO_JOIN));
      this_player()->remove_property("guild allowed");
      return;
    }
  }
//@@ Builders may adjust this description to meet theme requirements.
//@@ This is the next question that is sent to the player...
  write(@TEXT
[Sacrificial Service]%^BOLD%^CYAN%^
Do you understand and accept that frequently you will be called
upon and expected to help and sacrifice yourself for those that
may not appreciate your service or may even hold you in contempt?%^RESET%^
TEXT
);
//@@ Ditto the comment above reguarding this printf
  printf("[yes or no]  ");
  input_to("question2");
  return;
}
void question2(string answer) {
  mapping mods;
  string *mod_keys, guild_security, cnames;
  int i, x;
  object *womblers;
  if(!answer) {
//@@ Here we send the null response message and you will see now why/how
//@@ the cryptic bypass flag is used.
    write("%^BOLD%^RED%^Silence or nodding your head is not an understandable answer.%^RESET%^\nPlease try again...\n");
    question1("bypass4218");
    return;
  }
  if(answer != "yes" && answer != "no") {
//@@ Ditto the non-acceptable answer note.
    write("%^BOLD%^RED%^You answer must have gotten lost in translation...%^RESET%^\nPlease try again...\n");
    join_func();
    return;
  }
  if(answer == "yes")
//@@ Ditto the "yes" response action.
    CHAT_D->send_chat("clericemote",
                    "%^GREEN%^Suplicant "+this_player()->query_cap_name(),
                    "understands Sacrificial Service.%^RESET%^");
  else {
//@@ Ditto the "no" or OTHER response action.
    CHAT_D->send_chat("clericemote",
                    "%^RED%^Suplicant "+this_player()->query_cap_name(),
                    "refused to accept the Sacrificial Service.%^RESET%^");
//@@ Ditto reguarding WHY this player is unfit for membership
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
    guild_security = this_player()->query_guild_security();
    this_player()->set_guild_security(clear_bit(guild_security, ALLOW_TO_JOIN));
    this_player()->remove_property("guild allowed");
    return;
  }
//@@ YEA!!!! This player is accepted and what follows are the messages
//@@ and actions that complete the membership conversion for this player.
  write(@TEXT%^BOLD%^GREEN%^
You are baptized into the blessed service of the Holy Church!

The baptism washes over you and allows you to receive several
sacred gifts from The Divine.%^RESET%^
TEXT
);

//@@ BUILDERS...DO NOT TOUCH EXCEPT TO CHANGE THE CLERIC_??? DEFINES
//@@ TO REFLECT YOUR GUILD NAME
  GUILD2_D->rm_guest(GUILD_NAME, this_player()->query_name());
  GUILD2_D->add_member(GUILD_NAME, this_player()->query_name());
  GUILD2_D->save_guilds();

  guild_security = this_player()->query_guild_security();

  guild_security = clear_bit(guild_security, CLERIC_ALLY);
  guild_security = clear_bit(guild_security, CLERIC_ENEMY);
  guild_security = clear_bit(guild_security, CLERIC_GUEST);

  guild_security = clear_bit(guild_security, GUILDMASTER);
  guild_security = clear_bit(guild_security, GUILD_BANKER);
  guild_security = clear_bit(guild_security, GUILD_ENFORCER);
  guild_security = clear_bit(guild_security, GUILD_DIPLOMAT);
  guild_security = clear_bit(guild_security, ALLOW_TO_JOIN);
  guild_security = clear_bit(guild_security, PUNISHED);
  guild_security = clear_bit(guild_security, BANISHED);
  guild_security = clear_bit(guild_security, ELITE_GUILD_MEMBER);
  guild_security = clear_bit(guild_security, FULL_GUILD_MEMBER);

  guild_security = set_bit(guild_security, NEW_GUILD_MEMBER);
  guild_security = set_bit(guild_security, PROBATION);

  this_player()->set_class(GUILD_NAME);
  this_player()->set_guild_security(guild_security);

  mods = GUILD2_D->query_stats(GUILD_NAME);
  if(mapp(mods)) {
    mod_keys = keys(mods);
    i = sizeof(mod_keys);
    while(i--) {
      if(!this_player()->query_stats(mod_keys[i])) continue;
      this_player()->set_stats(mod_keys[i], (int)this_player()->
			       query_base_stats(mod_keys[i]) + mods[mod_keys[i]]);
//@@ Builders may adjust this description to meet theme requirements.
//@@ This message is confirming the stat mods.
      write("The Divine grants you the 'Gift of "+capitalize(mod_keys[i])+"'.");
    }
  }

  mods = GUILD2_D->query_advance(GUILD_NAME);
  if(mapp(mods)) {
    this_player()->set_property("hp advance", mods["hp"]);
    this_player()->set_property("mp advance", mods["mp"]);
//@@ Builders may adjust this description to meet theme requirements.
//@@ This message is confirming the Advance mods
    write("The Divine grants you the 'Gift of Advancement.'");
  }
  mods = GUILD2_D->query_regen(GUILD_NAME);
  if(mapp(mods)) {
    this_player()->set_property("base hp regen", mods["hp"]);
    this_player()->set_property("base mp regen", mods["mp"]);
//@@ Builders may adjust this description to meet theme requirements.
//@@ This message is confirming the Regeneration mods
    write("The Divine grants you the 'Gift of Regeneration.'");
  }
//@@ Builders may adjust this description to meet theme requirements.
//@@ This is the actual welcome message for the guild that is sent to
//@@ this player (should be kept under 1 screen in length).
  write(@TEXT%^BOLD%^GREEN%^
Welcome Acolyte, you are now a probationary new member of the
Holy Church with all rights and privilidges associated with
your new membership.

With training and dedication as your tools, you shall grow in
spirit and have the opportunity to advance in the Holy Church.

With piety and faith as your armarment, you shall become a valued
intstrument of Divine Will.  Rejoice now with your brothers and
sisters and announce yourself as a new member in service.%^RESET%^

Type: %^YELLOW%^cleric [message]%^RESET%^    to speak with the guild.
      %^YELLOW%^clericemote [emote]%^RESET%^ to emote to the guild.
TEXT
);
//@@ The following code is to add the player to the guild channel,
//@@ and reinit them (so they don't have to relog to get on channel...
//@@ and then broadcasts a "Hello, world..." message.
  this_player()->reinit_channels();
  CHAT_D->query_channel_listeners(GUILD_NAME);
  cnames = "";
  i = 0;
  for(x=0;x<sizeof(womblers);x++) {
    if(this_player() == womblers[x]) continue;
    cnames += womblers[x]->query_cap_name();
    i++;
    if(x < sizeof(womblers)-1) cnames += ", ";
  }
  if(i)
    CHAT_D->send_chat("clericemote", this_player()->query_cap_name(),
          "greets, "+cnames+" and says, \"Fair day everyone, Im a "+
          "new Acolyte and need someone to help me begin my training "+
          "so that I may eliminate my probationary status.\"");
  else
    CHAT_D->send_chat("clericemote", this_player()->query_cap_name(),
          "announces, \"Fair day everyone, Im a new Acolyte.  If anyone "+
          "were on, I would ask for someone to help me begin my training "+
          "so that I may eliminate my probationary status.\"");
//@@ BUILDERS SHOULD NOT ADJUST THE FOLLOWING VALUES...THEY WILL BE
//@@ ESTABLISHED AND MANAGED BY THE ARCH COUNCIL
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

