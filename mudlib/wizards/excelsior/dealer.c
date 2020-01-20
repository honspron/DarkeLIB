// a fun poker dealer
// EXCELSIOR!!!!

//  __________  __________  __________  __________  __________
// | 5        || A        || 10       || J        ||          |
// |    /\    ||    /\    ||   /\/\   ||    /\    ||          |          
// |   /  \   ||   /  \   ||   \  /   ||  |~  ~|  ||          |
// |   \  /   ||   ~||~   ||    \/    ||   ~||~   ||          |
// |    \/    ||          ||          ||    ||    ||          |
// |        5 ||        A ||        10||        J ||          |
// |__________||__________||__________||__________||__________|
//      1           2           3           4           5

#include <std.h>

#define FIRST_LINE " __________  __________  __________  __________  __________"
#define SECOND_LINE ({"| ","       || ","       || ","       || ","       || ","       |"})
#define SUIT_LINES ({ ({"|   ","   ||   ","   ||   ","   ||   ","   ||   ","   |"}), \
			({"|  ","  ||  ","  ||  ","  ||  ","  ||  ","  |"}), \
			({"|   ","   ||   ","   ||   ","   ||   ","   ||   ","   |"}), \
			({"|    ","    ||    ","    ||    ","    ||    ","    ||    ","    |"}) }) 
#define SEVENTH_LINE ({"|        ","||        ","||        ","||        ","||        ","|"})
#define EIGHT_LINE "|__________||__________||__________||__________||__________|"
#define HEARTS ({"%^RED%^%^BOLD%^/\\/\\%^RESET%^","%^RED%^%^BOLD%^ \\  / %^RESET%^","%^RED%^%^BOLD%^ \\/ %^RESET%^","  "})
#define SPADES ({"%^BOLD%^ /\\ %^RESET%^","%^BOLD%^ /  \\ %^RESET%^","%^BOLD%^~||~%^RESET%^","  "})       
#define DIAMONDS ({"%^RED%^%^BOLD%^ /\\ %^RESET%^","%^RED%^%^BOLD%^ /  \\ %^RESET%^","%^RED%^%^BOLD%^\\  /%^RESET%^","%^RED%^%^BOLD%^\\/%^RESET%^"})
#define CLUBS ({"%^BOLD%^ /\\ %^RESET%^","%^BOLD%^|~  ~|%^RESET%^","%^BOLD%^~||~%^RESET%^","%^BOLD%^||%^RESET%^"})
#define FACE ({" 2"," 3"," 4"," 5"," 6"," 7"," 8"," 9","10"," J"," K"," Q"," A"})
#define SUIT ({"D","S","C","H"})
#define CARD_NAMES ({"joker","ace","duce","three","four","five","six","seven","eight","nine","ten","jack","queen","king","ace"})

inherit MONSTER;

string *cards_dealt;
mapping hands,met_raise;
int pot,flag,whose_turn,current_bet,raises;
object *players;

void display_hand(object who,object to_who);
int fold();
int ante();
void start_game();
void next_turn();
void who_wins();
string deal_card();
void show_cards(int i,int *scores, mixed *sd_hands);
void award_prize(int *scores,mixed *sd_hands);

void display_hand(object who,object to_who) {
	int n,i,row;
	string name,suit_pic,*tmp,str;
	name = (string)who->query_name();
	if(!hands[name]) {
		write("You don't have any cards.");
		return;
	}
	message("info",FIRST_LINE,to_who);
	n = 0;
	i = 0;
	while(n < 6) {
		if(n != 5) {
			message("Ninfo",SECOND_LINE[n]+hands[name][i][0..1],to_who);
			i++;
			n++;
		}
		else {
			message("Ninfo",SECOND_LINE[n]+"\n",to_who);
			n++;
		}
	}
	row = 0;
	n = 0;
	i = 0;
	while(row < 4) {
		while(n < 6) {
			if(n != 5) {
				switch(hands[name][i][2..2]) {
				case "S":
					message("Ninfo",SUIT_LINES[row][n]+SPADES[row],to_who);
					break;
				case "D":
					message("Ninfo",SUIT_LINES[row][n]+DIAMONDS[row],to_who);
					break;
				case "C":
					message("Ninfo",SUIT_LINES[row][n]+CLUBS[row],to_who);
					break;	
				case "H":
					message("Ninfo",SUIT_LINES[row][n]+HEARTS[row],to_who);
					break;	
				}
				i++;
				n++;
			}
			else {
				message("Ninfo",SUIT_LINES[row][n]+"\n",to_who);
				n++;
			}
		}
		row++;
		n = 0;
		i = 0;
	}
	n = 0;
	i = 0;
	while(n < 6) {
		if(n != 5) {
			message("Ninfo",SEVENTH_LINE[n]+
				hands[name][i][0..1],to_who);
			i++;
			n++;
		}
		else {
			message("Ninfo",SEVENTH_LINE[n]+"\n",to_who);
			n++;
		}
	}
	message("info",EIGHT_LINE,to_who);
	message("info","%^BLUE%^%^BOLD%^     1           2           3 "+
		"          4           5",to_who);
}

int present_players(object who) {
	if(!present(who,environment())) return 0;
	return 1;
}

string deal_card() {
	string test;
	int i,i2,flag3;
	i = sizeof(FACE);
	i2 = sizeof(SUIT);
	flag3 = 1;
	while(flag3) {
		test = FACE[random(i)]+SUIT[random(i2)];
		if(member_array(test,cards_dealt) < 0) {
			flag3 = 0;
		}
	}
	cards_dealt += ({test});
	return test;
}

void init() {
	::init();
	add_action("ante","ante");
	add_action("bet","bet");
	add_action("call_bet","call");
	add_action("check","check");
	add_action("raise","raise");
	add_action("discard","discard");
	add_action("fold","fold");
	add_action("hand","hand");
	add_action("turn","turn");
	add_action("pot","pot");
	add_action("change_card","change"); /*this line to go*/
}

int change_card(string str) {
	int card;
	string what;
	if(sscanf(str,"%d - %s",card,what) != 2) {
		notify_fail("Bad argements.\n");
		return 0;
	}
	what = replace_string(what,"x"," ");
	hands[(string)this_player()->query_name()][card - 1] = what;
	return 1;
}

int hand() {
	display_hand(this_player(),this_player());
	return 1;
}

int	turn() {
	if(!flag) {
		write("No game is currently in progress.");
		return 1;
	}
	if (!players) return 0;
	if(whose_turn >= sizeof(players)) {
		write("No game is currently in progress.");
		return 1;
	}
	if(players[whose_turn] == this_player()) {
		write("It is currently your turn to play.");
		return 1;
	}
	write("It is currently "+(string)players[whose_turn]->query_cap_name()
		+"'s turn.");
	return 1;
}
	
int discard(string cards) {
	mixed *stf2;
	int i,flg,*stf;
	if(players[whose_turn] != this_player()) {
		write("It it not your turn to play.");
		return 1;
	}
	if(current_bet || flag != 2) {
		write("Discarding is not an option right now.");
		return 1;
	}
	if(!cards) {
		whose_turn++;
		next_turn();
		return 1;
	}
	cards = replace_string(cards," ","");
	stf2 = explode(cards,",");
	stf = allocate(sizeof(stf2));
	i = sizeof(stf2);
	while(i--) {
		if(sscanf(stf2[i],"%d",stf[i]) != 1
				|| stf[i] > 5 || stf[i] < 1) {
			flg = 1;
			break;
		}
	}
	if(flg) {
		write("That is not in the right format.");
		return 1;
	}
	i = sizeof(stf);
	while(i--) 
		hands[(string)this_player()->query_name()][stf[i]-1] = deal_card();
	message("other_action","%^BLUE%^"+(string)this_player()->query_cap_name()+
		" takes "+sizeof(stf)+" cards.",environment(),({this_player()}));
	message("my_action","%^BLUE%^You"+
		" take "+sizeof(stf)+" cards.",this_player());
	display_hand(this_player(),this_player());
	whose_turn++;
	next_turn();
	return 1;
}

int pot() {
	int bet;
	if(!flag) {
		write("No game is currently in progress.");
		return 1;
	}
	if (!players) return 0;
	if(whose_turn >= sizeof(players)) {
		write("No game is currently in progress.");
		return 1;
	}
	if(flag != 2 && flag < 4) {
		bet = current_bet*sizeof(players);
	} else {
		bet = 0;
	}
	bet += pot;
	write("The pot is currently worth %^BLUE%^"+bet+"%^RESET%^ silver.");
	return 1;
}

void create() {
	::create();
	set_name("dealer");
	set("id",({"dealer","poker dealer","card dealer"}));
	set("short","poker dealer");
	set_level(6);
}

void start_game() {
	object *p_present;
	int i,n;
	if(!players) return;
	p_present = filter_array(players,"present_players",this_object());
	if(sizeof(p_present) <= 1) {
		players = 0;
		flag = 0;
		if(!sizeof(p_present))	return;
		message("info","You are the only one in the game still here, so the pot "+
			"is returned to you.",p_present[0]);
		p_present[0]->add_money("silver",pot);
		return;
	}
	flag = 1;
	players = p_present;
	i = sizeof(players);
	cards_dealt = ({});
	hands = ([]);
	raises = 0;
	current_bet = 0;
	met_raise = ([]);
	whose_turn = 0;
	message("info","The dealer deals the cards.",environment());
	while(i--) {
		n = 5;
		hands[(string)players[i]->query_name()] = ({});
		while(n > 0) {
			hands[(string)players[i]->query_name()] += ({deal_card()});
			n--;
		}
		display_hand(players[i],players[i]);
	}
	whose_turn = 0;
	next_turn();
}

int fold() {
	int i;
	if(flag == 2) {
		write("You can't fold right now.");
		return 1;
	}
	if(players[whose_turn] != this_player()) {
		write("It it not your turn to play.");
		return 1;
	}
	write("You throw in your cards.");
	message("info",(string)this_player()->query_cap_name()+
		" %^GREEN%^%^BOLD%^folds.",environment(),({this_player()}));
	i = member_array(this_player(),players);
	players -= ({this_player()});
	if(met_raise[(string)this_player()->query_name()] > 
			(int)this_player()->query_money("silver")) {
		this_player()->set_money("silver",0); }
	else { this_player()->set_money("silver",
		-met_raise[(string)this_player()->query_name()]); }
	hands[(string)this_player()->query_name()] = 0;
	whose_turn++;
	next_turn();
	return 1;
}

int bet(string number) {
	int amount;
	if(players[whose_turn] != this_player()) {
		write("It it not your turn to play.");
		return 1;
	}
	if(current_bet || flag == 2 || flag >= 4) {
		write("Betting is not an option right now.");
		return 1;
	}
	if(sscanf(number,"%d",amount) != 1) {
		write("Bet how much?");
		return 1;
	}
	if(amount > 100) {
		write("The maximum bet allowed is 100 silver.");
		return 1;
	}
	if(amount > (int)this_player()->query_money("silver")) {
		write("You cannot afford that bet.");
		return 1;
	}
	current_bet = amount;
	met_raise[(string)this_player()->query_name()] = amount;
	this_player()->add_money("silver",-amount);
	message("info",(string)this_player()->query_cap_name()+
		" %^GREEN%^bets%^RESET%^ %^BLUE%^"+amount+"%^RESET%^ "+
		"silver.",environment(),({this_player()}));
	message("info","You bet %^BLUE%^"+amount+"%^RESET%^ silver.",
		this_player());
	if(!this_player()->query_env("NO_MONEY_REPORT")) 
		write("You have: %^CYAN%^"+(int)this_player()->query_money(
			"silver")+"%^RESET%^ silver.");
	whose_turn++;
	raises++;
	next_turn();
	return 1;
}
	
int raise(string number) {
	int amount;
	if(players[whose_turn] != this_player()) {
		write("It it not your turn to play.");
		return 1;
	}
	if(!current_bet || flag == 2 || flag >= 4) {
		write("Raising is not an option right now.");
		return 1;
	}
	if(sscanf(number,"%d",amount) != 1) {
		write("Raise how much?");
		return 1;
	}
	if(amount > 100) {
		write("The maximum raise allowed is 100 silver.");
		return 1;
	}
	if((amount+current_bet) > (int)this_player()->query_money("silver")) {
		write("You cannot afford that bet.");
		return 1;
	}
	current_bet += amount;
	this_player()->add_money("silver",
		-(current_bet - met_raise[(string)this_player()->query_name()]));
	met_raise[(string)this_player()->query_name()] = current_bet;
	message("info",(string)this_player()->query_cap_name()+
		" %^GREEN%^raises%^RESET%^ the pot %^BLUE%^"+amount+"%^RESET%^ "+
		"silver.",environment(),({this_player()}));
	message("info","You raise the pot %^BLUE%^"+amount+"%^RESET%^ silver.",
		this_player());
	if(!this_player()->query_env("NO_MONEY_REPORT")) 
		write("You have: %^CYAN%^"+(int)this_player()->query_money(
			"silver")+"%^RESET%^ silver.");
	whose_turn++;
	raises++;
	next_turn();
	return 1;
}

int call_bet() {
	if(!current_bet || flag == 2 || flag >= 4) {
		write("Calling is not an option right now.");
		return 1;
	}
	if(players[whose_turn] && players[whose_turn] != this_player()) {
		write("It it not your turn to play.");
		return 1;
	}
	message("info","You call the bet.",this_player());
	message("info",(string)this_player()->query_cap_name()+
		" %^GREEN%^%^BOLD%^calls%^RESET%^.",environment(),
		({this_player()}));
	this_player()->add_money("silver",
		-(current_bet - met_raise[(string)this_player()->query_name()]));
	met_raise[(string)this_player()->query_name()] = current_bet;
	if(!this_player()->query_env("NO_MONEY_REPORT")) 
		write("You have: %^CYAN%^"+(int)this_player()->query_money(
			"silver")+"%^RESET%^ silver.");
	whose_turn++;
	next_turn();
	return 1;
}

int check() {
	if(players[whose_turn] != this_player()) {
		write("It it not your turn to play.");
		return 1;
	}
	if(current_bet || flag == 2 || flag >= 4) {
		write("Checking is not an option right now.");
		return 1;
	}
	message("info","You check.",this_player());
	message("info",(string)this_player()->query_cap_name()+
		" %^GREEN%^%^BOLD%^checks%^RESET%^.",environment(),
		({this_player()}));
	met_raise[(string)this_player()->query_name()] = current_bet;
	whose_turn++;
	next_turn();
	return 1;
}

void check_player() {
	message("info",(string)players[whose_turn]->query_cape_name()+
		" has taken too long to play. He is removed from the hand.",
		environment(),({ players[whose_turn] }));
	message("info","You"+
		" has taken too long to play. Sorry, you are removed from the hand.",
		environment(),({ players[whose_turn] }));
	players -= ({this_player()});
	if(met_raise[(string)this_player()->query_name()] > 
			(int)this_player()->query_money("silver")) {
		this_player()->set_money("silver",0); }
	else { this_player()->set_money("silver",
		-met_raise[(string)this_player()->query_name()]); }
	hands[(string)this_player()->query_name()] = 0;
	whose_turn++;
	next_turn();
}

void next_turn() {
	object *p_present;
	string options;
	int whee;
//	remove_call_out("check_player");
//	call_out("check_player",20);
	if(!players) {
		flag = 0;
		return;
	}
	p_present = filter_array(players,"present_players",this_object());
	if(sizeof(p_present) <= 1) {
		players = 0;
		flag = 0;
		if(!sizeof(p_present))	return;
		message("info","You are the only one in the game still here, so the pot "+
			"is returned to you.",p_present[0]);
		p_present[0]->add_money("silver",pot);
		return;
	}
	whee = 0;
	if(current_bet) {
		if(whose_turn >= sizeof(players)) whose_turn = 0;
		while(met_raise[(string)players[whose_turn]->query_name()] 
				>= current_bet) {
		 	whose_turn++;
		 	whee++;
		 	if(whose_turn >= sizeof(players)) whose_turn = 0;	
		 	if(whee >= sizeof(players)) {
		 		whose_turn = whee;
		 		break;
		 	}
		}
	}
	if(whose_turn >= sizeof(players)) {
		met_raise = ([]);
		switch(flag) {
			case 0:
				return;
			case 1:
				pot += current_bet * sizeof(players);
				message("info","Discarding begins.",environment());
				whose_turn = 0;
				current_bet = 0;
				break;
			case 2:
				message("info","The second betting round begins.",
					environment());
				whose_turn = 0;
				met_raise = ([]);
				current_bet = 0;
				raises = 0;
				break;
			case 3:
				pot += current_bet * sizeof(players);
				who_wins();
				return;
		}
		flag++;
	}
	message("info","The dealer looks towards "+
		(string)players[whose_turn]->query_cap_name()+".",environment(),
		({players[whose_turn]}));
	switch(flag) {
		case 0:
			return;
		case 1:
			if(current_bet) {
				options = "You can '%^GREEN%^fold%^RESET%^', "+
					"'%^GREEN%^call%^RESET%^'"+
					", or '%^GREEN%^raise%^RESET%^'.";
				break;
			}
			options = "'%^GREEN%^fold%^RESET%^', '%^GREEN%^check%^RESET%^'"+
				", or '%^GREEN%^bet%^RESET%^'.";
			break;
		case 2:
			options = "You can now '%^GREEN%^discard <#>%^RESET%^'. "+
				"This must "+
				"be in the form 'discard 1,2,3' etc. If you wish to keep "+
				"your current hand supply no numbers with the command.";
			break;
		case 3:
			if(current_bet) {
				options = "'%^GREEN%^fold%^RESET%^', "+
					"'%^GREEN%^call%^RESET%^'"+
					", or '%^GREEN%^raise%^RESET%^'.";
				break;
			}
			options = "'%^GREEN%^fold%^RESET%^', '%^GREEN%^check%^RESET%^'"+
				", or '%^GREEN%^bet%^RESET%^'.";
			break;
	}
	message("info","The dealer looks at you. "+options
		,players[whose_turn],({}));
}
	
int ante() {
	int flag2,i;
	if(flag) {
		write("You must wait until the current game is over.");
		return 1;
	}
	if((int)this_player()->query_money("silver") < 10) {
		write("You don't have enough silver to play.");
		return 1;
	}
	if(!players) players = ({});
	if(member_array(this_player(),players) > -1) {
		write("You have already put in your money stupid.");
		return 1;
	}
	message("info","You pound down 10 silver and join the hand.",this_player());
	message("info",(string)this_player()->query_cap_name()+" pounds done "+
		"10 silver and enters the hand.",environment(this_object()),({this_player()}));
	this_player()->add_money("silver",-10);
	pot += 10;
	hands = ([]);
	cards_dealt = ({});
	players += ({this_player()});
	i = sizeof(call_out_info());
	while(i--) {	
		if(call_out_info()[i][0] == this_object() && 
			call_out_info()[i][1] == "start_game") {
			flag2 = 1;
			break;
		}
	}
	if(!flag2) {
		call_out("start_game",20);
		message("info","%^GREEN%^%^BOLD%^The game will begin in 20 seconds.",
			this_player());
		message("info",(string)this_player()->query_cap_name()+" has started "+
			"a hand! \n%^GREEN%^%^BOLD%^The game will begin in 20 secs.",
			environment(this_object()),({this_player()}));
	}
	return 1;
}

int *order_array(int *what) {
	mixed *test;
	int ben;
	ben = 1;
	test = ({});
	while(ben < 15) {
		if(member_array(ben,what) > -1) 
			test += ({ben});
			if(sizeof(test) >= sizeof(what)) break;
		ben++;
	}
	return test;
}

void who_wins() {
	int i,n,x,whee,*dhands;
	mixed *chands,*sd_hands,*scores;
	string h,name;
	i = sizeof(players);
	scores = allocate(sizeof(players));
	sd_hands = allocate(sizeof(players));
	while(i--) {
		whee = 0;
		name = (string)players[i]->query_name();
		scores[i] = allocate(3);
//		 message("info","Checking "+name,environment()); /*remove this line*/
		n = 0;
// the following while loop checks for flushes
		while( hands[name][n][2..2] == hands[name][0][2..2]) {
			n++;
			if(n >= sizeof(hands[name])) break;
		}
		if(n >= sizeof(hands[name])) scores[i][1] = 1;
		chands = allocate(sizeof(hands[name]));
		dhands = allocate(sizeof(chands));
		x = sizeof(chands);
		while(x--) {
			chands[x] = hands[name][x][0..1];
			chands[x] = replace_string(chands[x]," ","");
			chands[x] = replace_string(chands[x],"J","11");
chands[x] = replace_string(chands[x],"Q","12");
			chands[x] = replace_string(chands[x],"K","13");
			chands[x] = replace_string(chands[x],"A","14");
			sscanf(chands[x],"%d",dhands[x]);
//			message("info",chands[x],environment());     /*this line to go*/
		}
		chands = dhands;
		n = sizeof(chands);
// this while loop checks for matches
		while(n--) {
			x = sizeof(chands);
			while(x--) {
				if(x == n) x--;
				if(x < 0) break;
				if(chands[x] == chands[n]) {
// the following line assigns the matching card a new value so that it will
// not be matched again
//  message("info","Match: "+chands[x]+" "+chands[n],environment());
					chands[x] = 999 + x;
					whee++;
				}
			}
//  message("info",(string)players[i]->query_cap_name()+" current score is "+
//	scores[i][0],environment());
			if(whee == 3) {
				scores[i][0] = 7;
				scores[i][2] = dhands[n];
				break;
			}
			if(whee == 2) {
				if(scores[i][0] == 1) {
					scores[i][0] = 6;
					break;
				} else { scores[i][0] = 3; }
				scores[i][2] = dhands[n];
			}
			if(whee == 1) {
				if(scores[i][0] == 3) {
					scores[i][0] = 6;
					break;
				}
				if(scores[i][0] == 1) {
					scores[i][0] = 2;
					if(chands[n] > scores[i][2]) scores[i][2] = dhands[n];
					break;
				}
				scores[i][0] = 1;
				scores[i][2] = dhands[n];
			}
//			message("info",(string)players[i]->query_cap_name()+" now has a score of "+
//	scores[i][0],environment());
		whee = 0;
		}
// the following if checks for a straight
		if(!scores[i][0]) {
			n = 1;
			while(n < 5) {
				if(member_array(dhands[0]+n,dhands) > -1) whee++; 
				if(member_array(dhands[0]-n,dhands) > -1) whee++;
				if((dhands[0]-n) == 1 && member_array(14,dhands) > -1
					&& member_array(13,dhands) < 0 )
					whee++;
				if(whee == 4) break;
				n++;
			}		
			if(whee == 4) scores[i][0] = 4;
		} 
		if(!scores[i][2]) scores[i][2] = order_array(dhands)[4];
		if(!scores[i][0] && scores[i][1]) scores[i][0] = 5;
		sd_hands[i] = dhands;
//		message("info","%^RED%^"+(string)players[i]->query_cap_name()+" now has a final score of "+
//	scores[i][0],environment());
	}
	show_cards(0,scores,sd_hands);
}

void show_cards(int i,mixed *scores, mixed *sd_hands) {
	string what;
	if(i >= sizeof(players)) {
		award_prize(scores,sd_hands);
		return;
	}
	message("info",(string)players[i]->query_cap_name()+" lays down "+
(string)players[i]->query_possessive()+" cards.",
		environment());
	display_hand(players[i],environment());
//  message("info","%^RED%^"+(string)players[i]->query_cap_name()+" now has a score of "+
//	scores[i][0],environment());
	switch(scores[i][0]) {
		case 0:
// correct grammar etc.
			if(CARD_NAMES[scores[i][2]] == "ace" ||
					CARD_NAMES[scores[i][2]] == "eight") {
				what = "an "+CARD_NAMES[scores[i][2]]+" high."; break;
			} else {
				what = "a "+CARD_NAMES[scores[i][2]]+" high."; break;
			}
		case 1:
			what = "a pair of "+CARD_NAMES[scores[i][2]]+"s."; break;
		case 2:
			what = "two pairs."; break;
		case 3:
			what = "three "+CARD_NAMES[scores[i][2]]+"s."; break;
		case 4:
			message("info",order_array(sd_hands[i])[3],environment());
			message("info",scores[i][2],environment());
			if(scores[i][1] && scores[i][2] == 14 && 
				order_array(sd_hands[i])[3] == 13) {
				what = "- %^FLASH%^%^BOLD%^%^RED%^J%^BLUE%^E"+
					"%^GREEN%^S%^YELLOW%^U"+
					"%^CYAN%^S%^RESET%^%^BOLD%^!!!!! \n"+
"|~~| |~~| |_ _| |~~| |      %^RED%^|~~~ |    |  | |~~~ |   | "+
"%^GREEN%^| | | | | |\n"+
"%^RESET%^%^BOLD%^|__| |  |   |   |--| |      "+
"%^RED%^|--- |    |  | |__  |---| %^GREEN%^| | | | | |\n"+
"%^RESET%^%^BOLD%^|  \\ |__|   |   |  | |___   "+
"%^RED%^|    |___ |__| ___| |   |  %^GREEN%^0   0   0"; break; }
			else { if(scores[i][1]) {
				what = " straight- %^YELLOW%^%^FLASH%^FLUSH!!!!!!";
				break;
			}}   
			what = " a straight!"; break;
		case 5:
			what = " %^BLUE%^FLUSH!!!"; break;
		case 6:
			what = " %^RED%^%^BOLD%^a full house!!"; break;
		case 7:
			what = " %^GREEN%^%^BOLD%^FOUR "+
				CARD_NAMES[scores[i][2]]+"s."; break;
	}
	message("info",(string)players[i]->query_cap_name()+" has "+what,
		environment(),({players[i]}));
	message("info","You have "+what,players[i]);
	i++;	
	call_out("show_cards",2,i,scores,sd_hands);
}	

void award_prize(mixed *scores,mixed *sd_hands) {
	 int i,leader,*tied,ways;
	 string who,tmp;
	 object *tied_people;
	 i = sizeof(scores);
	 leader = 0;
	 tied = ({});
	 while(i--) {
	 	if(scores[i][0] == 4 && scores[i][1] &&
	 		scores[i][2] >= 14 && order_array(sd_hands[i])[3] == 13) {
	 		scores[i][0] = 9; }
	 	if(scores[i][0] == 4 && scores[i][1]) {
	 		scores[i][0] = 8; }
	 	if(scores[i][0] > scores[leader][0]) leader = i;
	 	if(scores[i][0] == scores[leader][0]) {
	 		if(scores[i][2] == scores[leader][2]) {
	 			if(order_array(sd_hands[i])[4] == 
	 				order_array(sd_hands[leader])[4] &&
	 				leader != i)
	 				tied += ({i}); 
	 			if(order_array(sd_hands[i])[4] >
	 					order_array(sd_hands[leader])[4])
	 				leader = i;
	 		}
	 		if(scores[i][2] > scores[leader][2])
	 			leader = i;
	 	}
	 }
	 if(sizeof(tied) <= 0) {
	 	message("info",(string)players[leader]->query_cap_name()+
	 		" wins the pot, "+pot+" silver!",environment(),
	 		({ players[leader] }));
	 	message("info","You"+
	 		" win the pot, "+pot+" silver!",players[leader]);
	 	players[leader]->add_money("silver",pot);
	 	pot = 0;
	 	flag = 0;
	 	return;
	 }
	 if(sizeof(tied) > 0) {
	 	tied += ({leader});
	 	ways = sizeof(tied);
	 	tied_people = ({});
	 	i = ways;
	 	while(i--) {
	 		if(!who) { who = (string)players[tied[i]]->query_cap_name(); }
	 		else { who += " and "+
	 			(string)players[tied[i]]->query_cap_name(); }
	 		tied_people += ({ players[tied[i]] });
	 	}
	 	message("info","WTF!!! The game is a tie between "+who+"! "+
	 		"The pot of "+pot+" silver is split "+ways+" way!",
	 		environment());
	 
	 	pot = 0;
	 	flag = 0;
	 	return;
	}
	pot = 0;
	flag = 0;
	return;
} 
