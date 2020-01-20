/*  /cmds/adm/_setvote.c
 *  Made for DarkeMUD
 *  Created by Geldron 031796
 *  Copyright (c) 1996
 *  Do not remove this header
 */


inherit DAEMON;

int cmd_setvote(string arg) {
    object *tmp;
    mapping vote;
    int i;

    if(!TP) return 0;
    if(!archp(TP)) return 0;
    if(!arg) {
	message("setvote", syntax("setvote WHAT"), TP);
	return 1;
    }
vote = find_object("/daemon/voter")->query_votes();
    if(!sizeof(keys(vote)))
	message("setvote", TPQCN + " cancels the previous vote.", users());
    message("setvote", "You start a vote on: " + arg, TP);
    message("setvote", TPQCN + " starts a vote on whether or not:\n"
      "%^MAGENTA%^" + arg + "%^RESET%^", users());
    message("setvote", "%^BOLD%^%^RED%^Type \"yes\" if you agree, "
      "and \"no\" if you disagree.%^RESET%^", users());
    tmp = users();
    for(i = 0; i < sizeof(tmp); i++)
	vote += ([ tmp[i]->query_name() : 0 ]);
find_object("/daemon/voter")->set_votes(vote);
    return 1;
}

void help() {
    message("setvote_help", syntax("setvote WHAT") +
      "\n\nStarts a vote on WHAT.  If there already was one started "
      "and tally wasn't used yet, it'll cancel the current one.", TP);
}
