//	Use command used to call skills from /std/skills
//	DarkeLIB 0.1
//	Diewarzau 4/4/94

#include <std.h>

int cmd_use(string str) {
    string skill, arg, file;
    int level;
    object skill_ob;


if(this_player()->query_ghost()) {
        notify_fail("You cannot do that in an immaterial state.\n");
        return 0;
   }
    seteuid(getuid());
    if(!str || (sscanf(str,"%s at %s", skill, arg) != 2 &&
        !sscanf(str,"%s",skill)))
	return notify_fail("Usage: use <skill> at <target> [with <args>]\n");
    if(!wizardp(TP) && !TP->query_skill(skill))
	return notify_fail("You do not know that skill.\n");
    if(wizardp(this_player())) file = "/wizards/"+
				 (string)this_player()->query_name()+"/skills/"+
      replace_string(skill, " ", "_")+".c";
    else file = 0;
    if(!file || !file_exists(file))
      file = "/std/skills/"+replace_string(skill, " ", "_")+".c";
    if(!file_exists(file))
        return notify_fail("That skill is latent and cannot be used.\n");
    if(!function_exists("skill_func",find_object_or_load(file)))
	return notify_fail("That skill is latent and cannot be used.\n");
    skill_ob = clone_object(file);
  if(!wizardp(TP)) {
    skill_ob->set_property("skill level", (int)this_player()->query_skill(
	skill));
  }
    else if(wizardp(TP)) {
    if(TP->query_property("ALL SKILLS"))
      skill_ob->set_property("skill level", TP->query_property("ALL SKILLS"));
    else skill_ob->set_property("skill level", 100);
  }
  if(TP->getenv("DEBUG") == "1")
    message("info","Skill Level: "
    +skill_ob->query_property("skill level"), TP);
    skill_ob->do_skill(this_player(),arg);
    return 1;
}

void help() {
message("help",
"This command is used to invoke skills.  The syntax is:\n"
"use <skill> at <target> [with <args>]\n"
"<skill> is the skill to be used, <target> is the taget of the skill (if "
"any), and <args> are optional extra arguements that depend on the skill.\n"
"See: skills",
this_player());
}















