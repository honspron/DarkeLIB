/* /adm/simul_efun/arena_ownerp.c
 *  Made for DarkeMUD
 *  Created by Geldron 031396
 *  Copyright (c) 1996, DarkeMUD
 *  Do not remove this header
 */

nomask int arena_ownerp(object ob) {
    if(!ob) return 0;
    if((string)ob->query_name() == "thrace" ||
      (string)ob->query_name() == "traer") return 1;
    return 0;
}
