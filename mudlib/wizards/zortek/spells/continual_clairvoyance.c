inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","continual clairvoyance");
    set_property("skill","clairsentience");
    set_property("casting time",4);
    set_property("base mp cost",12);
    set_property("dev cost", 12);
    set_property("fast dev cost", 72);
    set_property("spell level", 5);
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
This discipline will create a one-way, psychic link between the <victim>
and the receiptient of the spell.  The victim's location will then be
periodically identified to the receiptient in either brief or verbose
mode (depending on the verbose toggle of the receiptient).  At any time
the receiptient may sever the link with the <sever continual clairvoyance>
command.  The frequency of updated reports and duration are directly
related to the power level used in the casting.
TEXT
,this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob, who;
  int flag2;

  if(flag) {
    if(who = find_living(args)) {
      message("info", "%^CYAN%^You accidently reverse the target and receiptient.", caster);
      this_object()->spell_func(caster,find_living(args),power+1,at->query_true_name(),0);
    }
    else {
      message("info", "%^CYAN%^Not only did you fumble but you screwed up the syntax too...OUCH!",caster);
      caster->do_damage("head",10*power);
      if(caster != at)
        at->do_damage("head",10*power);
    }
    return;
  }
  if(!args || args == "") {
    message("info", @TEXT
You must supply the receiptient of the spell as well as the target to be
continually monitored.  The syntax of the command should be:
    cast *# continual clairvoyance at <receiptient> with <victim>
Where: # is the spell power, <receiptient> is the person monitoring,
and <victim> is the subject to be monitored.  Discipline aborted.
TEXT
, caster);
    remove();
    return;
  }
  if(!who = find_living(args)) {
    message("info", @TEXT
Your victim could not be located.
TEXT
, caster);
    remove();
    return;
  }
  if(wizardp(who)) {
    message("info", "You should be destroyed for attempting this on an immortal.",caster);
    remove();
    return;
  }
  if((int)who->query_level() - (int)caster->query_level() > power) {
    message("info", "The power was insufficient for a victim of that level.", caster);
    remove();
    return;
  }
  if((int)at->query_level() - (int)caster->query_level() > power) {
    message("info", "The power was insufficient for a receiptient of that level.", caster);
    remove();
    return;
  }
  message("info", "%^CYAN%^You link to "+who->query_cap_name()+"'s mind.", caster);
  ob=new("/wizards/zortek/spells/cc_ob");
  ob->set_up(caster->query_true_name(),at->query_true_name(),who->query_true_name(),power);
  remove();
  return;
}