int check_forest(object ob){
   if(environment(ob)->query_terrain()=="F") 
      return 1;
   else 
      return 0;
}

int check_outside(object ob){
    if(environment(ob)->query_property("indoors")==0)
       return 1;
    else 
       return 0;
}
