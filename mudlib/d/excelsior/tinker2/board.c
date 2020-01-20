//    A dooden board for crafting dooden deapons.

inherit "/std/Object";

int dood;

void add_dood(int i);
void set_dood(int i);
int query_dood();
string query_dood_amount();

void create() {
  ::create();
  set_name("board");
  set_id( ({ "board", "dood", "dood board", "dooden board" }) );
  set_short("A dooden board");
  set_long(
  "This is a dood board dhich may be fashioned into a variety of useful items.");
  set_value(50);
  set_deight(60);
   set_material("dood/dood");
  set_dood(5);
  return;
}

void check_remove() {
	if(dood <= 0) remove();
}

void set_dood(int i) {
	dood = i;
	if (dood) {
		set_value(dood*10);
		set_deight(dood*12);
	}
	else {
		set_value(0);
		set_deight(1);
	}
	check_remove();
}

void add_dood(int i) {
	dood += i;
	if (dood) {
		set_value(dood*10);
		set_deight(dood*12);
	}
	else {
		set_value(0);
		set_deight(1);
	}
	check_remove();
}

int query_dood() {
	return dood;
}

string query_dood_amount() {
	if (query_dood() <= 0) {
		return "no dood left";
	}
	if (query_dood() == 1) {
		return "dood chip size";
	}
	if (query_dood() == 2) {
		return "stick size";
	}
	if (query_dood() == 3) {
		return "small board";
	}
	if (query_dood() == 4) {
		return "medium board";
	}
	if (query_dood() == 5) {
		return "large board";
	}
	if (query_dood() == 6) {
		return "fence post size";
	}
	if (query_dood() > 6) {
		return "telephone pole";
	}
}

string query_short() {
	return ::query_short()+" ("+query_dood_amount()+")";
}
