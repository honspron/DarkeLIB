/*  /adm/simul_efun/arenap.c
 *  Made for Medievia
 *  Created by Geldron 031096
 *  Copyright (c) 1996, DarkeMUD
 *  Do not remove this header
 */


nomask int arenap(object ob) {
    if(!ob) return 0;
    if(!ENV(ob)) return 0;
    if(BN(ENV(ob)) == "/d/damned/arena/battle_room") return 1;
    if(BN(ENV(ob)) == "/d/damned/arena/0,0" || 
      BN(ENV(ob)) == "/d/damned/arena/0,1" ||
      BN(ENV(ob)) == "/d/damned/arena/0,2" ||
      BN(ENV(ob)) == "/d/damned/arena/1,0" ||
      BN(ENV(ob)) == "/d/damned/arena/1,1" ||
      BN(ENV(ob)) == "/d/damned/arena/1,2" ||
      BN(ENV(ob)) == "/d/damned/arena/2,0" ||
      BN(ENV(ob)) == "/d/damned/arena/2,1" ||
      BN(ENV(ob)) == "/d/damned/arena/2,2") return 2;
    return 0;
}
