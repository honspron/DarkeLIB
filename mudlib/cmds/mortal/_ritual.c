#include <std.h>
#include <ritual.h>

inherit DAEMON;

int form_ritual(string str);
int list();
int ritual_leader(string str);
int remove_caster(string str);
int leave_ritual();
int join_ritual(string str);
int add_caster(string str);
int ritual_cast(string str);
void help();


int cmd_ritual(string str) {
        string com, extra;

        if(!str) {
        help();
        return 1;
}

        if(sscanf(str, "%s %s", com, extra) == 2) {
        switch(com) {
                case "form": return form_ritual(extra); break;
                case "leave": return leave_ritual(); break;
                case "join": return join_ritual(extra); break;
                case "add": return add_caster(extra); break;
                case "remove": return remove_caster(extra); break;
                case "leader": return ritual_leader(extra); break;
                case "cast": return ritual_cast(extra); break;
                case "list": return list(); break;
                default: help(); return 1; break;
}
}

        else {
                if(str == "leave") return leave_ritual();
                else if(str == "list") return list();
        else {
                help();
                return 1;
}
}
}


int form_ritual(string str) {
        string *tmp;
        int x;

        tmp = (string *)RITUAL_OB->query_rituals();
        if(!tmp) tmp = ({});
        if(member_array(str, tmp) != -1) {
        notify_fail("A casting group by that name already exists.\n");
        return 0;
}
        x = (int)RITUAL_OB->add_caster(this_player(), str);
        if(x==ALREADY_MEMBER) {
        notify_fail("You are already a member of another casting group.\n");
        return 0;
}
        write("You form the casting group "+str+".\nYou are the leader.\n");
        return 1;
}


int leave_ritual() {
        int x;

        x = (int)RITUAL_OB->remove_caster(this_player());
        if(x==NOT_MEMBER) {
        notify_fail("You are not a member of any casting group!\n");
        return 0;
}
        write("You leave your ritual casting group.\n");
        return 1;
}


int add_caster(string str) {
        object ob;
        string ritual;
        int x;

        ob = find_player(str);
        if(!ob) {
        notify_fail("No player by that name on the mud.\n");
        return 0;
}
        if(wizardp(ob)) { 
        notify_fail("Immortals may not join.\n");
        return 0;
}
        ritual = (string)this_player()->query_ritual();
        if(!ritual) {
        notify_fail("You must be the leader of a casting group to add any members!\n");
        return 0;
}
        if(this_player() != (object)RITUAL_OB->query_leader(ritual)) {
        notify_fail("You must be the leader of your casting group to add any members!\n");
        return 0;
}
        RITUAL_OB->add_invited(ob, ritual);
        RITUAL_OB->notify_ritual(ritual, (string)ob->query_cap_name()+" has been invited to join the ritual group.");
        tell_object(ob, this_player()->query_cap_name()+" invites you to join the ritual group \""+ritual+"\".\nYou have 60 seconds to type <ritual join "+ritual+">.\n");
        return 1;
}


int remove_caster(string str) {
        object ob;
        string ritual;
        int i;

        ob = find_player(str);
        if(!ob) {
        notify_fail("That player is not on the mud.\n");
        return 0;
}
        ritual = (string)this_player()->query_ritual();
        if(!ritual) {
        notify_fail("You must be the leader of a ritual group to remove a member.\n");
        return 0;
}
        if(this_player() != (object)RITUAL_OB->query_leader(ritual)) {
        notify_fail("You must be the leader of the ritual group to remove a member.\n");
        return 0;
}
        i = (int)RITUAL_OB->remove_caster(ob);
        if(i==NOT_MEMBER) {
        notify_fail(ob->query_cap_name()+" is not a member of your ritual group.\n");
        return 0;
}
        RITUAL_OB->notify_ritual(ritual, (string)ob->query_cap_name()+" is no longer in the casting group.");
        return 1;
}


int ritual_leader(string str) {
        object ob;
        string ritual;
        int x;

        ob = find_player(str);
        if(!ob) {
        notify_fail("No such player on the MUD.\n");
        return 0;
}
        if(ob == this_player()) {
        notify_fail("You are already the leader!\n");
        return 0;
}
        ritual = (string)this_player()->query_ritual();
        if(!ritual) {
        notify_fail("You must lead a casting group before you may change its leader.\n");
        return 0;
}
        if(this_player() != (object)RITUAL_OB->query_leader(ritual)) {
        notify_fail("You must be the leader of a casting group in order to change the leadership.\n");
        return 0;
}
        if((string)ob->query_ritual() != ritual) {
        notify_fail(ob->query_cap_name()+" is not in your casting group!\n");
        return 0;
}
        x = (int)RITUAL_OB->change_leader(ob);
        if(x != OK) {
        notify_fail("Leadership change failed.\n");
        return 0;
}
        write("You are no longer the leader.\n");
        RITUAL_OB->notify_ritual(ritual, (string)ob->query_cap_name()+" is now the casting group leader.");
        return 1;
}


int list() {
        object *who;
        int i, tot_exp;
        string ritual, tmp, *items;

        ritual = (string)this_player()->query_ritual();
        if(!ritual) {
        notify_fail("You are not a member of any casting group.\n");
        return 0;
}
        who = (object *)RITUAL_OB->query_ritual_members(ritual);
        if(!sizeof(who)) {
        notify_fail("You are no longer in a casting group.\n");
        return 0;
}
	i = sizeof(who);
	tmp = "Casting Group:"+ritual+"\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
	while(i--){
	tmp += who[i]->query_cap_name()+"\n";
}
	message("info", tmp, this_player());
	return 1;
}


int join_ritual(string str) {
        int x;

        if(!str) return 0;
        if(!RITUAL_OB->invited_now(this_player(), str)) {
        notify_fail("You must be invited into a casting group in order to join.\n");
        return 0;
}
        x = (int)RITUAL_OB->add_caster(this_player(), str);
        if(x==ALREADY_MEMBER) {
        notify_fail("You are already in another casting group!\n");
        return 0;
}
        RITUAL_OB->notify_ritual(str, (string)this_player()->query_cap_name()+" has joined the casting group.\n");
        return 1;
}


int ritual_cast(string str) {
	string ritual, file, spell, arg, skillname;
	object spell_ob, *who;
	int b, i, c, d, pow, skill;


	ritual = (string)this_player()->query_ritual();

	if(this_player()->query_ghost()) {
	notify_fail("You cannot do that in an immaterial state.\n");
	return 0;
}
	if(this_player() != (object)RITUAL_OB->query_leader(ritual)) {
	notify_fail("You must be the leader of your casting group to start a ritual cast!\n");
	return 0;
}
	if(!ritual) {
	notify_fail("You must be a member of a casting group to ritual cast!\n");
	return 0;
}

	who = RITUAL_OB->query_ritual_members(ritual);
	b = sizeof(who);
	if(b < 2)
	return notify_fail("You are the only member in your casting group.  That won't do much good.\n");

	seteuid(getuid());

        if(!str || (sscanf(str,"*%d %s at %s",pow,spell,arg) != 3 && sscanf(str,"*%d %s",pow,spell) != 2))
        return notify_fail("Usage: cast *<pow> <spell> at <target>[<args>]\n");

        if(pow < 0)
        return notify_fail("Usage: cast *<pow> <spell> at <target>[<args>]\n");

        if(!this_player()->query_spell_level(spell))
        return notify_fail("You do not know that spell.\n");

        spell = replace_string(spell," ","_");

        file = "/std/spells/"+spell+".c";

	if(!this_player()->query_skill(find_object_or_load(file)->query_property("skill")))
	return notify_fail("You don't know the skill required to cast that spell.");

        if(!file_exists(file))
        return notify_fail("BUG! You know a spell that doesn't exist!\n");

        if(this_player()->query_paralyzed())
        return notify_fail("You may not cast while stunned!\n");

        if((this_player()->query_cant_attack() == 1) && (spell_ob->query_property("combat spell") == 1))
        return notify_fail("You are under influence of mysterious forces, making that impossible!\n");

if(find_object_or_load(file)->query_property("long term spell") == 1)
	return notify_fail("You cannot cast long term spells with ritual cast as of yet, it's being worked on... give me a day or two.\n");


	// These lines make sure everyone in the group has the spell.
        while(b--){
	if(!who[b]->query_spell_level(replace_string(spell,"_"," ")))
	return notify_fail("Someone in the group doesn't know that spell.\n");
	if(who[b]->query_spell_level(replace_string(spell,"_"," ")) < pow)
	return notify_fail("Someone in the group doesn't know that spell at that power level.\n");
}
	// End of spell testing code.


	// Next few lines make sure everyone has the skill
	who = RITUAL_OB->query_ritual_members(ritual);
	b = sizeof(who);

	while(b--){
	if(!who[b]->query_skill(find_object_or_load(file)->query_property("skill")))
	return notify_fail("Someone in the group doesn't know the skill required to cast that spell.\n");
}
	// End of skill test code.


	// Next few lines determines the skill level at which the spell will be cast.
	who = RITUAL_OB->query_ritual_members(ritual);
	b = sizeof(who);

	while(b--){
	skill += who[b]->query_skill(find_object_or_load(file)->query_property("skill") );
}
	skill /= sizeof(who);
	// End of skill code.
	

	// Finally it sets the casting of the generic ritual spell.
	who = RITUAL_OB->query_ritual_members(ritual);
	b = sizeof(who);
	d = sizeof(who);
	while(b--){
	spell_ob = new("/std/spells/ritualdud");
	if(who[b] == this_player())
	spell_ob->set_property("ritual spell", 1);
	else
	spell_ob->set_property("ritual dud", 1);
        spell_ob->set_property("casting time", find_object_or_load(file)->query_property("casting time") + (d * (find_object_or_load(file)->query_property("casting time") / 2)));
	spell_ob->set_property("real skill", find_object_or_load(file)->query_property("skill"));
        spell_ob->set_property("base mp cost", find_object_or_load(file)->query_property("base mp cost") + (d * (find_object_or_load(file)->query_property("base mp cost") / 2)));
        spell_ob->set_property("original spell", file);
	spell_ob->set_property("original name", spell);
        spell_ob->set_property("original power", pow);
        spell_ob->set_property("original arg", arg);
        spell_ob->set_property("original skill", skill);
	spell_ob->set_property("original members", d);
        spell_ob->begin_casting(who[b], 1);
}
        return 1;
}


void help() {
        write("Command: Ritual\n"+
        "Syntax: <ritual form [name]>\n"+
        "        <ritual add [player]>\n"+
        "        <ritual join [name]>\n"+
        "        <ritual remove [player]>\n"+
        "        <ritual leave>\n"+
        "        <ritual list>\n"+
        "        <ritual cast>\n"+
        "        <ritual leader [player]>\n\n"+
        "This command accesses the various casting group enabling functions.\n"+
        "The person who forms any group is automatically the leader of\n"+
        "the group.  Only that player may add or remove players.  That\n"+
        "player may also designate another player as the group leader.\n"+
        "Any group member may leave the group at any time through the\n"+
        "\"leave\" function.  A list of all current group members is\n"+
        "given by the \"list\" function.  Once you have been invited\n"+
        "to join the group, you must type <ritual join [name]>\n"+
        "(where name is the name of the group).\n"
        "See also: follow, kill\n");
}
