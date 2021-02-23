/*
 * Spartan_data.h
 */

#include "my_sys.h"

class Spartan_data
{
public:
  Spartan_data(void);
  ~Spartan_data(void);
  int create_table(char *path);
  int open_table(char *path);
  int close_table();
private:
  File data_file;
  int header_size;
  int record_header_size;
  bool crashed;
  int number_records;
  int number_del_records;

  int read_header();
  int write_header();
};
