//  Logic for stacked weepon spells.
//  Requires the weapon spell to have the following
//  properties set:
//    "stack key" - a key for the type of weapon spell -
//                  (any string)
//    "stack num" - The max amount of spells of that key
//                  which may be stacked.


// This function returns a 0 if the max stack amount
// has already been reached.  The first arguement is the
// recipient of the spell (usually a weapon object).
// The second arg is the weapon SHADOW itself.

int check_stack(object ob, object shad) {
  string key;
  int num;
//  object tmp;

  key = (string)this_object()->query_property("stack key");
  num = (int)this_object()->query_property("stack num");
  if(!shad || !ob || !key || !num) return 0;
  if(!ob->query_stack()) return 1;
  if((int)ob->query_stack(key) >= num) return 0;
  shad->set_stack_key(key);
  return 1;
}
