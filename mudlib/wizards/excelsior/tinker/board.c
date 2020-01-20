//    A wooden board for crafting wooden weapons.

inherit "/std/Object";

int wood;

void add_wood(int i);
void set_wood(int i);
int query_wood();
string query_wood_amount();

void create() {
  ::create();
  set_name("board");
  set_id( ({ "board", "wood", "wood board", "wooden board" }) );
  set_short("A wooden board");
  set_long(
  "This is a wood board which may be fashioned into a variety of useful items.");
  set_value(50);
  set_weight(60);
   set_material("wood/wood");
  set_wood(5);
  return;
}

void check_remove() {
	if(wood <= 0) remove();
}

void set_wood(int i) {
	wood = i;
	if (wood) {
		set_value(wood*10);
		set_weight(wood*12);
	}
	else {
		set_value(0);
		set_weight(1);
	}
	check_remove();
}

void add_wood(int i) {
	wood += i;
	if (wood) {
		set_value(wood*10);
		set_weight(wood*12);
	}
	else {
		set_value(0);
		set_weight(1);
	}
	check_remove();
}

int query_wood() {
	return wood;
}

string query_wood_amount() {
	if (query_wood() <= 0) {
		return "no wood left";
	}
	if (query_wood() == 1) {
		return "wood chip size";
	}
	if (query_wood() == 2) {
		return "stick size";
	}
	if (query_wood() == 3) {
		return "small board";
	}
	if (query_wood() == 4) {
		return "medium board";
	}
	if (query_wood() == 5) {
		return "large board";
	}
	if (query_wood() == 6) {
		return "fence post size";
	}
	if (query_wood() > 6) {
		return "telephone pole";
	}
}

string query_short() {
	return ::query_short()+" ("+query_wood_amount()+")";
}
