#define LEGAL_CHANNELS ({"thief","cleric","arch-mage","fighter","paladin","war-priest","chaotic-lord","elementalist","enchanter","sword-mage","nightblade","tinker","necromancer","high-mortal","council","darke","seer","secret"})
inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","ward channel");
    set_property("skill","clairsentience");
    set_property("casting time",1);
    set_property("base mp cost",15);
    set_property("dev cost", 10);
    set_property("fast dev cost", 60);
    set_property("spell level", 3);
    set_property("moon","luna");
    set_property("caster message","");
    set_property("target message","You feel the presence of another mind.");
    set_property("observer message","$C seems to concentrate intesely.");
    set_property("spell type",({ }));
    set_property("target type", "living");
    set_property("must be present", 1);
    return;
}

void info() {
message("help",@TEXT
This discipline establishes a psychic link between the target and one
or more channels of communication (channel ward).  This ward permits
the target to secretly "evesdrop" on a channel.  The number of channels
and duration are governed by the skill and ability of the caster.

The owner of the channel ward can sever the link at any time by issuing
the <sever channel ward> command.  Psychic wards are not without their
dangers...you have been warned!
TEXT
,this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;
  int flag2, x;
  string *chans;

  if(wizardp(at) ) {
    message("info", @TEXT
Due to the fact that immortals have access to all the channels this
discipline services, your casting fails in order to protect against
channel access redundancy.
TEXT
, caster);
    remove();
    return;
  }
  if(wizardp(caster) ) {
    message("info", @TEXT
There is no reason an immortal should be casting this spell except
to "cheat" or aid in an attempt therein...

Thus your casting has been aborted!
TEXT
, caster);
    caster->delete_spell("ward channel");
    "/daemon/inform_d"->do_inform("security",
      "%^BOLD%^YELLOW%^CHEAT:%^RESET%^ "+
      capitalize(caster->query_true_name())+
      " attempted to use the ward channel spell on "+
      capitalize(at->query_true_name())+".\n");
    remove();
    return;
  }
  if(flag) {
    message("info","You fail to establish the channel ward!",caster);
    chans = explode(args, " ");
    if(x = sizeof(chans)) {
      while(x--) {
        "/daemon/chat"->send_chat(chans[x]+"emote", at->query_cap_name(),
        "struggles to listen to this channel but fails miserably.");
        at->do_damage("head",10);
        message("info", "You feel a stabbing pain in your head.", at);
      }
    }
    remove();
    return;
  }
  if(!args || args == "") {
    message("info", "Syntax: cast *# ward channel at <name> with <channel> <channel> ...", caster);
    remove();
    return;
  }
  if((int)at->query_level() - (int)caster->query_level() > power) {
    message("info", "The power was insufficient for a target of that level.", caster);
    remove();
    return;
  }
  chans = explode(args, " ");
  if(x = sizeof(chans)) {
    if(x > power) {
      message("info", "You have grossly over estimated your skill.",caster);
      if(at != caster) {
        message("info", "You feel a stabbing pain in your brain!", at);
        at->do_damage("head",x*10-power);
      }
      message("info", "You feel a stabbing pain in your brain!", caster);
      caster->do_damage("head",x*10-power);
      remove();
      return;
    }
    while(x--) {
      if(member_array(chans[x], LEGAL_CHANNELS) == -1) {
        message("info", "You have attempted to ward an channel that does not exist.",caster);
        remove();
        return;
      }
    }
  }
  ob = new("/wizards/zortek/spells/channel_ward");
  ob->set_up(caster->query_true_name(), at->query_true_name(), power, chans);
  remove();
  return;
}
