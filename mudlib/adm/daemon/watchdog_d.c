//   A watchdog for the delayed_function_d to make
//   sure its heartbeat is always pumping.

#define FUNCTION_D "/adm/daemon/delayed_funtion_d"

int check;

void create() {
  check = 0;
  set_heart_beat(1);
  return;
}

void heart_beat() {
  if(check >= 2) {
    check = 0;
    FUNCTION_D->restart_heart();
  }
  check++;
  return;
}

void reset_check() {
  check = 0;
  return;
}

