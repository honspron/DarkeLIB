void set_users_reply(string str) {
  object *usrs;
  int x,y,z;
  
  usrs = users();
  for(x=0;x<sizeof(usrs);x++) {
    usrs[x]->set("reply", str);
  }
}