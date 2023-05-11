// clang-format off
#include <assert.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <pipy/nmi.h>
#include <mysql.h>

enum {
  id_variable_mysqlIp,
  id_variable_mysqlPort,
  id_variable_mysqlUser,
  id_variable_mysqlPasswd,
  id_variable_mysqlSql,
};
// clang-format on

int probe_mysql(char *ip, int port, char *user, char *passwd, char *sql) {
  int rc = -1000;
  MYSQL *con = mysql_init(NULL);

  if (con == NULL) {
    return -1;
  }
  if (mysql_real_connect(con, ip, user, passwd, NULL, port, NULL, 0) == NULL) {
    mysql_close(con);
    return -2;
  }
  if (mysql_query(con, sql)) {
    mysql_close(con);
    return -3;
  }

  MYSQL_RES *result = mysql_store_result(con);

  if (result == NULL) {
    mysql_close(con);
    return -4;
  }
  if (mysql_fetch_row(result)) {
    rc = 1;
  } else {
    rc = 0;
  }

  mysql_free_result(result);
  mysql_close(con);
  return rc;
}

struct pipeline_state {
  int is_started;
};

static void pipeline_init(pipy_pipeline ppl, void **user_ptr) {
  *user_ptr = calloc(1, sizeof(struct pipeline_state));
  ((struct pipeline_state *)*user_ptr)->is_started = 0;
}

static void pipeline_free(pipy_pipeline ppl, void *user_ptr) {
  struct pipeline_state *state = (struct pipeline_state *)user_ptr;
  free(user_ptr);
}

static char *get_string(pipy_pipeline ppl, int id, char *buf, int size) {
  pjs_value value = pjs_undefined();
  pipy_get_variable(ppl, id, value);
  if (pjs_is_undefined(value)) {
    return NULL;
  }
  int n = pjs_string_get_utf8_data(value, buf, size - 1);
  if (n > 0) {
    buf[n] = '\0';
    return buf;
  }
  return NULL;
}

static int get_int(pipy_pipeline ppl, int id) {
  pjs_value value = pjs_undefined();
  pipy_get_variable(ppl, id, value);
  if (pjs_is_undefined(value)) {
    return -1;
  }
  return pjs_to_number(value);
}

static void pipeline_process(pipy_pipeline ppl, void *user_ptr, pjs_value evt) {
  struct pipeline_state *state = (struct pipeline_state *)user_ptr;
  if (pipy_is_MessageStart(evt)) {
    state->is_started = 1;
  } else if (pipy_is_MessageEnd(evt)) {
    if (state->is_started == 1) {
      pjs_value response_head = pjs_object();

      int port = get_int(ppl, id_variable_mysqlPort);
      char ip[128] = {'\0'};
      char user[128] = {'\0'};
      char passwd[128] = {'\0'};
      char sql[1024] = {'\0'};

      get_string(ppl, id_variable_mysqlIp, ip, sizeof(ip));
      get_string(ppl, id_variable_mysqlUser, user, sizeof(user));
      get_string(ppl, id_variable_mysqlPasswd, passwd, sizeof(passwd));
      get_string(ppl, id_variable_mysqlSql, sql, sizeof(sql));

      int rc = probe_mysql(ip, port, user, passwd, sql);

      pjs_object_set_property(response_head, pjs_string("result", strlen("result")), pjs_number(rc));

      pipy_output_event(ppl, pipy_MessageStart_new(response_head));
      pipy_output_event(ppl, pipy_MessageEnd_new(0, 0));
    }
  }
}

void pipy_module_init() {
  pipy_define_variable(id_variable_mysqlIp, "__mysqlIp", "mysql-nmi", pjs_undefined());
  pipy_define_variable(id_variable_mysqlPort, "__mysqlPort", "mysql-nmi", pjs_undefined());
  pipy_define_variable(id_variable_mysqlUser, "__mysqlUser", "mysql-nmi", pjs_undefined());
  pipy_define_variable(id_variable_mysqlPasswd, "__mysqlPasswd", "mysql-nmi", pjs_undefined());
  pipy_define_variable(id_variable_mysqlSql, "__mysqlSql", "mysql-nmi", pjs_undefined());

  pipy_define_pipeline("", pipeline_init, pipeline_free, pipeline_process);
}