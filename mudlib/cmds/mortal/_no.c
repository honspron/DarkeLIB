/*  /cmds/mortal/_no.c
 *  Made for DarkeMUD
 *  Created by Geldron 031796
 *  Copyright (c) 1996
 *  Do not remove this header
 */


inherit DAEMON;

int cmd_no(string arg) {
 if(find_object("/daemon/voter")->query_vote(TPQN) > 0) return 0;
if(!(int)find_object("/daemon/voter")->ok_vote()) return 0;
    message("setvote", "Thank you!", TP);
find_object("/daemon/voter")->set_vote(TPQN, 1);
    return 1;
}
