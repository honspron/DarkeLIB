//  An illusionary wall.

inherit "/wizards/diewarzau/obj/misc/wall";

string *elems;

void create() {
  ::create();
  set_function("do_element");
  set_short("An elemental wall");
  set_id(({ "wall", "elemental wall" }));
  set_long("It looks like there is no getting around it.");
  return;
}

void set_ele_name(string name) {
  set_short("A wall of "+capitalize(name));
  set_id(({ "wall", "elemental wall", name+" wall",
      "wall of "+name }));
  return;
}

void set_elements(string *p_str) { elems = p_str; }

int do_element(object who) {
  int i, j, dmg;
  string *crits;

  if(!elems || !(i=sizeof(elems))) return 1;
  dmg = 0;
  for(j=1; j <= 10; j++) dmg += random(20)+1;
  dmg *= query_power() * i;
  crits = ({});
  while(i--) {
    switch(query_power() * random(10)) {
    case 0..5:
      break;
    case 6..8:
      crits += ({ elems[i] + " A" });
      break;
    case 9..15:
      crits += ({ elems[i] + " B" });
      break;
    case 16..20:
      crits += ({ elems[i] + " C" });
      break;
    case 21..26:
      crits += ({ elems[i] + " D" });
      break;
    case 27..32:
      crits += ({ elems[i] +" E" });
      break;
    case 33..40:
      crits += ({ (elems[i] + " A"), (elems[i] + " E") });
      break;
    case 41..47:
      crits += ({ (elems[i] + " B"), (elems[i] + " E") });
      break;
    case 48..60:
      crits += ({ (elems[i] + " C"), (elems[i] + " E") });
      break;
    }
  }
  who->do_damage(dmg, (string)who->return_target_limb());
  do_critical(this_object(), who, crits);
  return 1;
}

