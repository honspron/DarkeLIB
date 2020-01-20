inherit "/std/room";

string who_trial;

void init() {
  ::init();
  add_action("do_read", "read");
  add_action("do_ponder", "ponder");
  add_action("block_decend", "decend");
}

void create() {
  ::create();
  set_property("indoors",1);
  set_property("light",3);
  set("short","Reception Hall of the Seer's Spire");
  set("long", @TEXT
This is the reception lounge of the Seer's Spire.  The area is
comfortably furnished with an over-stuffed divan and several
chairs arranged around a central conversation table.  There is
well groomed fireplace that seems to keep the area plesantly
warm from the chill mountain air outside.
TEXT
);
  set_exits( ({
    "/d/damned/guilds/join_rooms/seer_join",
    }),({
    "stairway",
    }) );
  add_invis_exit("stairway");
  set_items( ([
    "divan" : "It looks comfortable.",
    "fireplace" : "The embers emit a soft glow.",
    "table" : @TABLE
The conversation table is relatively squat, sitting on a short but
broad granite pedistal and topped with a large oval of smoked glass.
There is a well worn tome on the table.
TABLE
,
    "tome" : @TOME
This is a hard leather bound book with detailed scroll work and
bound with silver brads.  Light blue inlayed lettering spells out
the words, "%^CYAN%^The Order%^RESET%^."
TOME
,
  ]) );
}

int do_read(string str) {
  if(!str) {
    notify_fail("Read what?\n");
    return 0;
  }
  switch(str) {
    case "book":
    case "tome":
    case "The Order":
    case "the order":
      write(@TEXT
The cover of the tome says, "%^CYAN%^The Order%^RESET%^."

If you desire to read any particular page of the tome you may type
<read page #> where # is the page number you desire to read.
TEXT
);
      return 1;
    case "page 1":
      write(@TEXT%^CYAN%^
               TABLE OF CONTENTS%^RESET%^
Topic          -----------------               Page
    
%^CYAN%^What is "The Order"%^RESET%^ ...........................  %^CYAN%^3
Entry Criteria%^RESET%^  ...............................  %^CYAN%^7
Banes & Boons%^RESET%^  ...............................  %^CYAN%^12
Political Standing%^RESET%^  ..........................  %^CYAN%^19
Services & Fees%^RESET%^  .............................  %^CYAN%^24
TEXT
);
      return 1;
    case "page 3":
      write(@TEXT%^CYAN%^
                What is "The Order"%^RESET%^
                -------------------

The Order is a tightly knit group of individuals that
have discovered, within themselves, a desire to seek
enlightenment beyond the physical world.  In this
persuit, they have learned to appreciate the body as a
mere repository for the mind...and it is with their mind
that they choose to experience this reality, and others.

Therefore, The Order is comprised of people that might
call themselves Sages, Shaman, or Wise-old-windbags,
but most content themselves with an identity of Seer.

To see beyond...but some would ask, %^CYAN%^
  "Beyond what?"%^RESET%^
to which the Seer responds,%^CYAN%^
  "Precisely, it's as easy as 2+2."
TEXT
);
      return 1;
    case "page 7":
      write(@TEXT%^CYAN%^
                 Entry Criteria%^RESET%^
                 --------------

In order to even consider becoming a Seer you must:%^CYAN%^
    ...be of the High-Man race.
    ...be a titled "Artisan" or better.
    ...be willing and able to achieve and
       maintain a politically neutral reputation.
    ...undergo a special reincarnation that will
       "rape" your current skills and spells.%^RESET%^
    ...understand "Quad once added twice divided once."

Under NO circumstance will anyone "younger" than the
title of Artisan be considered for "The Trial," so
don't ask and we won't have to hear you whine!
TEXT
);
      return 1;
    case "page 12":
      write(@TEXT%^CYAN%^
                 Banes & Boons%^RESET%^
                 -------------
                 
There are several disadvantages to being a Seer.
We call these our Banes:%^CYAN%^
  1) Lowest Stamina of any Guild/Class/Race combo.
  2) Retched physcial combat ability.
  3) Enemies with everyone.%^RESET%^

However, there are sever advantages we gain and we
call these our Boons:%^CYAN%^
  1) Highest mental faculties...hands down!
  2) Incredible non-physical combat ability.
  3) Friends with everyone.%^RESET%^

For those that enjoy the "social" style of existance
(read mudding), that is our baliwick.  To those that
meerly seek personal power and glory...perhaps you
should consider the Chaos Lords, because we don't
want you.
TEXT
);
      return 1;
    case "page 19":
      write(@TEXT%^CYAN%^
              Political Standing%^RESET%^
              ------------------

People are often confused by the actions that are
taken by the Seers.  Frequently, people assume that
our kind (and often times friendly) manner implies
an "alliance" or "loyalty."  This can be a fatal
mistake, because we clearly and openly declair
ourselves "neutral" to all parties in a conflict.

Conversely, those that may hold us in contempt or
dispise an action we may take that is not in their
best interest should remember the wicked assumption
stated above.  We are brokers of information and
safety.  And we hold that our integrity our honor
and integrity in high reguard...thus,

If you are lucky enough to get the "word" of a
Seer, you can be guaranteed that he or she will
abide by his or her word...even at the risk of
physical danger or death!  Just remember...%^CYAN%^
   We see all, we hear all, we know all!%^RESET%^
TEXT
);
      return 1;
    case "page 24":
      write(@TEXT%^CYAN%^
                Services & Fees%^RESET%^
                ---------------

Due to the fact that none of our powers and abilities
have been revealed to the world, we are not advertising
anything at this time.  However, check occationally and
as we begin to display our talents, availability and
pricing information will be made available.
TEXT
);
      return 1;
    case "page 22":
      write(@TEXT%^CYAN%^
                How do I join?%^RESET%^
                --------------

Congratulations on taking the first step towards your
enlightenment!  If you meet all the criteria for joining
you must be pondering about "the trial."  This is not
unusual, in fact, such thoughts should be cultivated if
you ever hope to aspire as a Seer.%^CYAN%^

Q1) What if I am not a High-man?%^RESET%^
A1) You need not worry...if you are worthy, but "the trial"
    will be more difficult.%^CYAN%^
Q2) What if I have not earned the title of Artisan?%^RESET%^
A2) If you try, you die...and still get raped for your
    arrogance and stupidity.%^CYAN%^
Q4) What if I'm unwilling or unable to be "neutral?"%^RESET%^
A4) (See A2)%^CYAN%^
Q5) What happened to Q3?%^RESET%^
A3) The same thing that happened to A5!
TEXT
);
      return 1;
    default:
      write("Dispite your efforts you can't read that.");
      return 1;
  }
}

int do_ponder(string str) {
  if(!str) return 0;
  if(str == "the trial" || str == "the trial.") {
    write(@TEXT
You hear a voice in your head, "It is good you ponder
your fate and the trial.  If you are convinced you are
willing and able to face physical obliteration, you may
decend the stairs.  You should consider this choice
carefully...for once you leap from a cliff there is no
stopping the fall and no turning back.  I will give
you 60 seconds to decide your future."
TEXT
);
    who_trial = this_player()->query_true_name();
    add_exit("trial", "decend");
    call_out("remove_exit",60,"decend");
    return 1;
  }
  return 0;
}

int block_decend(string str) {
  if(who_trial == (string)this_player()->query_true_name() ) {
    return 0;
  }
  write(@TEXT%^MAGENTA%^
You suddenly feel a sharp stab of pain at the base of your skull.
Then your head feels like it is going to explode as you crumple
into a heap of unconscious flesh.
TEXT
);
  this_player()->set_paralyzed(45,"Huh? You are unconscious!");
  return 1;
}

void reset() {
  object ob;
  if(!present("simon"))
    new("/d/damned/guilds/seer/mobs/simon")->move(this_object());
  return;
}
