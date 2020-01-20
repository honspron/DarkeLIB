#define THE_BEGINNING 720561600
#define NOW(x) x-THE_BEGINNING

#define SECOND 1
#define MINUTE 20
#define HOUR 800
#define DAY 16000
#define WEEK 80000
#define MONTH 320000
#define YEAR 3200000

#define CURRENT_YEAR(x) (1+((NOW(x))/(YEAR)))
#define CURRENT_MONTH(x) ((NOW(x))%YEAR)/MONTH
#define CURRENT_WEEK(x) ((NOW(x))%MONTH)/WEEK
#define CURRENT_DAY(x) ((NOW(x))%WEEK)/DAY
#define CURRENT_DATE(x) (1+((NOW(x))%MONTH)/DAY)
#define CURRENT_HOUR(x) ((NOW(x))%DAY)/HOUR
#define CURRENT_MINUTE(x) ((NOW(x))%HOUR)/MINUTE
#define CURRENT_SECOND(x) ((NOW(x))%MINUTE)

#define LONGEST_DAY 101
#define SHORTEST_DAY 1

#define DAYS ({ "Oneday", "Twoday", "Threeday", "Fourday", "Lastday" })
#define MONTHS ({ "Onery", "Twoery", "Threery", "Fourey", "Fivey",\
"Sixy", "Seveny", "Eighty", "Niney", "Yearend" })
