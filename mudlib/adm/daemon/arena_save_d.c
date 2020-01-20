/*  /adm/daemon/arena_save_d.c
 *  Made for DarkeMUD
 *  Created by Geldron 070596
 *  Copyright (c) 1996
 *  Do not remove this header
 */

#include <security.h>

inherit DAEMON;
inherit "/std/user";

void create() {
    daemon::create();
    user::create();
}

void clean_up() {
    daemon::clean_up();
    user::clean_up();
}

int save(object ob) {
    if(BN(PO) != "/d/damned/arena/booths_room")
	error("Illegal caller.\n");
    seteuid(UID_ROOT);
    ob->save_player((string)ob->query_name());
    restore_object("/adm/save/users/" + (string)ob->query_name()[0..0] +
      "/" + (string)ob->query_name());
    save_object("/d/damned/arena/data/" + (string)ob->query_name());
    seteuid(0);
    return 1;
}

int restore(object ob) {
    if(BN(PO) != "/d/damned/arena/booths_room")
	error("Illegal caller.\n");
    seteuid(UID_ROOT);
    ob->restore_arena_save();
    ob->set_attackers(({}));
    ob->stop_hunting();
    ob->save_player((string)ob->query_name());
    rm("/d/damned/arena/data/" + (string)ob->query_name() + ".o");
    seteuid(0);
    return 1;
}
