//      /adm/simul_efun/legendp.c
//      coded for Darkelib 0.2
//      a pointer for legends
//      written by Thrace for DarkeDomain 
//      April 18 1999

int legendp(object ob) {
    if(!ob) ob = previous_object();
    if(!wizardp(ob) && (int)ob->query_property("legend") == 1) return 1;
    return 0;
}
