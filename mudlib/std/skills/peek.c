#include "/adm/include/str_fmt.h"
#include "/adm/include/std.h"
inherit "/std/skills/skill.c";

void create() {
::create();
set_stat("dexterity");
set_dev_cost(10);
set_fast_dev_cost(26);
set_property("target type", "living");
set_property("must be present", 1);
    set_property("prereq", "hide in shadows");
}

void info() {
message("help",
"This skill lets you look at someone and see their booty, " +
"without them noticing you're peeking. May only be used " +
"while you are hidden.\n"
"Usage: use peek at <player> Attempts to peek at the player.\n",
this_player());
}

int is_hiding (object from) {
return ((from->query("hide shad")) || ((from->query_my_skill()) ==
"invisibility art"));
}

int chk_peek_thf (int result, int thf_ovrflw) {

if (result > 0)
thf_ovrflw += (int)((3*result)/4);
else
thf_ovrflw -= (int)(result/2);
return (result + thf_ovrflw);
}

int chk_peek_tar (int result, int tar_ovrflw) {

if (result > 0)
tar_ovrflw += (int)(result/2);
else
tar_ovrflw += (int)(result/2);
return (result + tar_ovrflw);
}

int getmod(int mod, int skill) {

if ((random(skill)) < ((int)(skill/2)))
return (-((int)((mod*(random(skill)))/100)));
else
return (((int)((mod*(random(skill)))/100)));
}


void chk_money (object at, int mod, int skill) {

string *currs;
string borg;
int i, tmp;
currs = (string *)at->query_currencies();
if(!currs || !sizeof(currs)) {
say(at->query_cap_name()+" has no money you can see.");
}
write((sizeof(currs)>1) ? ""+at->query_cap_name()+" appears to have "+
"these currencies: " : ""+at->query_cap_name()+" appears to have
only: ");
for(borg = "", i=0, tmp = sizeof(currs); i<tmp; i++) {
if (mod == 100)
borg += ((at->query_money(currs[i]))+" "+currs[i]);
else
borg += ((int)(((getmod(mod, skill) +
mod)/100)*(at->query_money(currs[i])))+" "+currs[i]);
if(i == tmp-1) borg +=(".\n");
else if(tmp > 2 && i == tmp-2) borg += (", and ");
else if(tmp == 2) borg +=(" and ");
else borg +=(", ");
}
write(str_fmt(borg, 3));
}

void thf_msg(int result, object from, object at) {

int skill = 0;
string himher, heshe;

skill = (int)from->query_skill("peek");
if ((at->query_gender()) == "male") {
himher = "him" ;
heshe = "he";
}
else {
himher = "her" ;
heshe = "she";
}
if (result < 26)
message("info", "You see "+at->query_cap_name()+" looking "+
"in your direction, so you freeze up and don't get at "+himher+
".", from) ;
else if (result < 51)
message("info", "You briefly look over "+at->query_cap_name()+
".  "+at->query_cap_name()+" "+at->query_description(), from) ;
else if (result < 76)
message("info", at->query_long(), from) ;
else if (result < 101) {
message("info", at->query_long(), from) ;
chk_money(at, 20, skill) ;
}
else if (result < 151) {
message("info", at->query_long(), from) ;
chk_money(at, 50, skill) ;
}
else if (result < 501) {
message("info", at->query_long(), from) ;
chk_money(at, 80, skill) ;
}
else {
message("info", at->query_long(), from) ;
chk_money(at, 100, skill) ;
}
}

void tar_msg (int result, object from, object at) {

if (result < 61)
return 0;
else if (result < 111)
message("info", "You get the feeling you are being watched.", at) ;
else if (result < 151)
message("info", "You see someone watching you from the shadows.",
at) ;
else if (result < 181)
message("info", "You see "+from->query_cap_name()+"
peering at "+
"you rather intently.", at) ;
else if (result < 501)
message("info", "You see "+from->query_cap_name()+" peering at "+
"you rather intently, especially at your pouch.", at) ;
else
message("info", "You see "+from->query_cap_name()+" drooling over "+
"you and your money pouch.", at) ;
}

void skill_func(object from, object at, string arg) {

int tar_per = 0;     // Perception of target
int thf_skl = 0;     // Peek skill level of thief
int tar_int = 0;     // Intelligence of the target
int thf_dex = 0;     // Dexterity of thief
int stat_dif = 0;    // thf_dex - tar_int
int skill_dif = 0;   // thf_skl - tar_per
int result = 0;      // Result = stat_dif + skill_dif
int thf_test = 0;    // thf_test = thf_skl + result + thf_ovrflw
int tar_test = 0;    // tar_test = tar_per + result + tar_ovrflw
int thf_ovrflw = 0;  // If result > 0, thf_ovrflw += result
int tar_ovrflw = 0;  // else tar_ovrflw += result

if (!is_hiding(from))
write("You can't use this skill without being hidden.\n");
else {
thf_skl = (int)from->query_skill("peek");
thf_dex = (int)from->query_stats("dexterity");
tar_per = (int)at->query_skill("perception");
tar_int = (int)at->query_stats("intelligence");
stat_dif = thf_dex - tar_int;
skill_dif = thf_skl - tar_per;
result = stat_dif + skill_dif;
if (result >= 0)
thf_ovrflw = thf_ovrflw + (int)(result/2);
else
tar_ovrflw = tar_ovrflw + (int)(result/2);
thf_test = thf_skl + chk_peek_thf(result, thf_ovrflw);
tar_test = tar_per + chk_peek_tar(result, tar_ovrflw);
thf_msg(thf_test, from, at);
tar_msg(tar_test, from, at);
}
}
