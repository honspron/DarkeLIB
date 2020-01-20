//    Advance command to be used with reincarnation.
//
//    DarkeLIB 1.0
//    -Diewarzau 1/15/96
#include <daemons.h>
#include <security.h>

int cmd_advance(string null) {
  int exp, bank, tmp, lvl;

  if(wizardp(this_player())) {
    write("You're kidding, right?");
    return 1;
  }
  exp = (int)ADVANCE_D->get_exp((int)this_player()->query_level() + 1) -
          (int)this_player()->query_exp() + 10;
  bank = (int)this_player()->query_property("old exp");
  if(!bank || bank < exp) {
    write("You do not have enough exp in your bank to advance to "
          "the next level.");
//    this_player()->set_property("old exp", 0);
    return 1;
  }
  bank -= exp;
  tmp = (int)this_player()->query_property("xp mod");
  this_player()->set("no add dev", 1);
  seteuid(UID_ROOT);
  this_player()->override_add_exp(exp);
  seteuid(getuid());
  this_player()->set("no add dev", 0);
  this_player()->add_dev(exp / 4000);

//Added by drizzt to cover intra lvl dev
  lvl = (int)this_player()->query_level();
  if(lvl < 10) {
    this_player()->add_dev(lvl*20);
  }  
  else {
    if(lvl <18) { 
    this_player()->add_dev(lvl*50);
      }
    else {
     this_player()->add_dev(lvl*100);
    }
  }
  this_player()->set_property("xp mod", tmp);
  this_player()->set_property("old exp", bank);
// Added by Drizzt to prevent cheating!
  exp = (int)ADVANCE_D->get_exp((int)this_player()->query_level() + 1) -
         (int)this_player()->query_exp() + 10;
  bank = (int)this_player()->query_property("old exp"); 
  if(!bank || bank < exp) {
    this_player()->override_add_exp(bank);
    this_player()->set_property("old exp", 0);
  }
//Added by Drizzt to fix the dev pt thingy bug
  this_player()->reset_max_exp();
  bank = (int)this_player()->query_property("old exp");
  write("You have "+bank+" exp left in your bank");
  return 1;
}


int help() {
message("help",
"Usage: 'advance'\n"
"You may use this command after reincarnation to advance a level, "
"using exp from your exp bank.", this_player());
return 1;
}


