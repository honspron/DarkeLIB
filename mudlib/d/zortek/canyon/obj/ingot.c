//    An ingot!  You mine them and stuff!

inherit "/std/Object";

void create() {
  ::create();
  set_name("ingot");
  set_id(({ "ingot" }));
  set_long("This ingot can be melted into a weapon blank, or sold for "
  "money.");
  set_weight(70);
  return;
}

int id(string str) {
  if(::id(str)) return 1;
  if(::id(replace_string(str, query_property("material_name")+" ", ""))) return 1;
  return 0;
}


int query_value() {
  if(this_object()->prop("value")) return (int)this_object()->prop("value");
  else return ::query_value();
}

float query_float_value() {
  if(this_object()->prop("value")) return to_float((int)this_object()->prop("value"));
  else return ::query_float_value();
}

string query_short() {
  return capitalize(article(query_property("material_name") + " ingot"));
}

