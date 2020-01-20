#include <move.h>

inherit "/std/Object";
int contents;

int move(object dest) {
  if(living(dest)) return MOVE_NOT_ALLOWED;
  else return ::move(dest);
}

void create() {
  ::create();
  set_name("cask");
  set_id(({ "cask", "wine cask" }) );
  set_short("A cask of wine");
  set_long(@TEXT
This cask may be used to fill waterskins with wine for communion
ceremonies or general consumption.  A donation of silver is assumed
for this generous service.

Syntax: fill <object>  --to fill something with wine
TEXT
);
  contents = 100+random(50);
  return;
}

void init() {
  ::init();
  add_action("fill_vessel", "fill");
  return;
}

int fill_vessel(string str) {
  object ob;
  int how_much = 0;
  int full = 0;
  if(contents <= 0) {
    write("The cask appears to be empty.");
    say(this_player()->query_cap_name()+" examines an empty cask.");
    return 1;
  }
  ob = present(str, this_player());
  if(!ob) {
    write("Without "+article(str)+", you find it hard to contain the "+
        "wine and it spills upon the floor...alcohol abuse is such a shame.");
    say(this_player()->query_cap_name()+" tries to fill "+article(str)+
        " despite the fact that "+this_player()->query_subjective()+
        " doesn't have such...as a result wine spills on the floor.");
    contents--;
    return 1;
  }
  switch(ob->query_name()) {
    case "blessed wine bottle" :
      how_much = 15;
      break;
    case "blessed flask" :
      how_much = 5;
      break;
    case "blessed wine skin" :
      how_much = 6;
      break;
    case "blessed jar" :
      how_much = 3;
      break;
    default:
      write("Friar Samual stops you from filling "+article(str)+" with holy wine!\nYou must use a container that will not defile the blessing.");
      return 1;
  }
  full = (int)ob->full();
  if(full >= how_much) {
    write("That "+ob->query_name()+" is already filled completely.");
    return 1;
  }
  else if(full > 0) how_much-=full;
  if(wizardp(this_player())) {
    write("WizInfo:\tQuantity: "+how_much+"\n\t\tContents: "+contents);
  }
  if(contents < how_much) how_much = contents;
  if((int)this_player()->query_money("silver") < how_much) {
    write("You do not have the requested donation of "+how_much+" silver.");
    return 1;
  }
  this_player()->add_money("silver", -how_much);
  
  ob->fill("wine", 15, 40);
  write("You fill the "+ob->query_name()+".");
  say((string)this_player()->query_cap_name() +
    " fills "+article(ob->query_name())+" with holy wine from the cask.");
  contents-=how_much;
  return 1;
}

int clean_up() { return 0; }
