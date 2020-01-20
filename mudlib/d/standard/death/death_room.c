inherit "std/room";

mapping visitors;

void init() {
  ::init();
  if(!wizardp(this_player()))
    add_action("filter_act", "", 1);
  call_out("begin_death", 4, this_player());
}

void create() {
  ::create();
  set_property("light", 1);
    set_property("no teleport", 1);
  set("short", "The void between life and death");
    set("long", (:this_object(), "d_long" :));
    skip_obvious();
  visitors = ([]);
}

string d_long() { return ""; }
int filter_act(string str) {
    if(query_verb() == "says" || query_verb() == "tell" || query_verb() == "shout") {
        write("You let out a haunting wail.\n");
        tell_room("d/standard/sewer_ent", "You hear a haunting wail.\n");
    }
    else {
        write("The dead are incapable of such acts.\n");
    }
    return 1;
}

void begin_death(object tp) {
  string nom;

  nom = (string)tp->query_name();
  visitors[nom] = 1;
  tell_object(tp, 
    "The real world fades away into a distant memory as you slip away from\n"
    "your fragile mortal life.\n"
    "You find yourself falling down a seemingly bottomless pit of darkness\n" 
    "towards a fast approaching room which seems oddly out of place here.\n\n");
  call_out("continue_death", 5, tp);
}

void continue_death(object tp) {
  string nom;
  int beat, deaths;

  nom = (string)tp->query_name();
  deaths = sizeof(tp->query_deaths());
  visitors[nom]++;
  beat = visitors[nom];
  switch(beat) {
    case 2:
      tell_object( tp,
        "You land roughly on the wooden floor of what seems to be a clerical office.\n\n" );
      break;
    case 3:
      tell_object(tp,
        "You clear your head of the cobwebs and look around this strange\n"
        "place. You look for where you came from, but now all you see are\n"
        "four walls, a floor, and a ceiling.\n\n" );
      break;
    case 4:
      tell_object(tp,
        "You take a closer look and notice a desk, filing cabinets, coat rack\n"
        "and other office furniture. Sitting in the chair is a worn old man.\n\n");
      break;
    case 5:
      tell_object(tp,
        "The old man says: Sorry I couldn't meet you before you got here.\n"
        "The old man says: I am so old now I can't get my uniform on in time anymore.\n"
        "The old man points at the coat rack where sits a giant black cloak.\n"
        "You notice a large sickle resting against the wall next to the cloak.\n\n");
      break;
    case 6:
      tell_object(tp,
        "The old man says: In my prime I was known as the Grim Reaper.\n"
        "The old man says: But those days are over.\n" 
        "The old man says: So now I let the unfortunate come here instead of me\n"
        "  working up a sweat in that hot cloak going to you.\n\n" );
      break;
    case 7:
      tell_object(tp,
        "The old man says: Let me see here...\n"
        "The old man starts digging through his files.\n\n" );
      break;
    case 8:
      tell_object(tp,
        "Pulling out a stack of papers the old man says: Ah... here we are.\n\n");
      if(deaths<2) 
        tell_object(tp,
          "The old man says: I didn't think you looked familiar.\n"
          "The old man says: This is your first experience with me, eh?\n"
          "The old man says: I used to be mean and cruel with the dead, but\n"
          "  I have softened in my old age.\n\n" );
      else {
        tell_object(tp,
          "The old man says: Nice to see you again.\n"
          "The old man says: You've died, what, "+deaths+" times?\n\n" );
        if(deaths>10) 
          tell_object(tp,
            "The old man whistles appreciatively.\n"
            "The old man says: We have got to stop meeting like this!\n"
            "The old man laughs his head off.\n\n" );
       if(deaths>25)
         tell_object(tp,
           "The old man laughs and says: Too bad we don't have a frequent diers club!\n" );
      }
      break;
    case 9:
      tell_object(tp,
        "A concerned look appears on the man's face.\n"
        "The old man clears his throat.\n\n" );
      break;
    case 10:
      tell_object(tp,
        "The old man says: I bet you want to give up and stay dead, don't you?\n"
        "You look confused.\n\n" );
      break;
    case 11:
      tell_object(tp,
        "The old man says: But that is the easy way out.\n"
        "The old man says: I don't want any sissy ghosts hanging around when\n" 
        "  when I buy the farm!\n"
        "The old man looks at you appraisingly.\n\n" );
      break;
    case 12:
      tell_object(tp,
        "The old man says: You're heading back to "+mud_name()+"...\n"
        "The old man says: But I can't let you get off for free!\n"
        "The old man says: All this paperwork costs!\n"
        "The old man points at the red tape cluttering his desk.\n\n" );
      break;
    case 13:
      tell_object(tp,
        "The old man pushes a button underneath his desk.\n" 
        "You hear a soft click.\n\n");
      break;
    case 14:
      tell_object(tp,
        "All of a sudden the floor drops out from underneath you.\n"
        "As you fall once again, you hear the man say: I'll be seeing you!\n" 
        "You notice a familiar world around you.\n\n");
      if(tp->query_ghost())
        tp->return_to_death_site();
      map_delete(visitors, nom);
      return;
      break;
    }
  call_out("continue_death", 5, tp);
  return;
}
