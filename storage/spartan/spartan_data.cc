/*
 * Spartan_data.cc
 */

#include "spartan_data.h"
#include "my_dbug.h"
#include "my_dir.h"
#include "string.h"

Spartan_data::Spartan_data(void)
{
  data_file = -1;
  number_records = -1;
  number_del_records = -1;
  header_size = -1;
  record_header_size = sizeof(bool) + sizeof(int) + sizeof(int);
}

Spartan_data::~Spartan_data(void)
{
}

int Spartan_data::create_table(char *path)
{
  DBUG_ENTER("Spartan_data::create_table");
  open_table(path);
  number_records = 0;
  number_del_records = 0;
  crashed = false;
  write_header();
  DBUG_RETURN(0);
}


int Spartan_data::open_table(char *path)
{
  DBUG_ENTER("Spartan_data::open_table");
// TODO: file flag
  data_file = my_open(path, O_RDWR | O_CREAT, MYF(0));
  if(data_file == -1)
	DBUG_RETURN(errno);
  read_header();
  DBUG_RETURN(0);
}


int Spartan_data::close_table()
{
  DBUG_ENTER("Spartan_data::close_table");
  if (data_file != -1)
  {
	my_close(data_file, MYF(0));
	data_file = -1;
  }
  // already closed when data_file == -1
  DBUG_RETURN(0);	
}


int Spartan_data::read_header()
{ 
  int len;
  
  DBUG_ENTER("Spartan_data::read_header");
  if (number_records == -1)
  {
	my_seek(data_file, 0l, MY_SEEK_SET, MYF(0));
	my_read(data_file, (uchar *)&crashed, sizeof(bool), MYF(0));
	my_read(data_file, (uchar *)&len, sizeof(int), MYF(0));
	memcpy(&number_records, &len, sizeof(int));
	my_read(data_file, (uchar *)&len, sizeof(int), MYF(0));
	memcpy(&number_del_records, &len, sizeof(int));
  }
  else
	my_seek(data_file, header_size, MY_SEEK_SET, MYF(0));

  DBUG_RETURN(0);
}

int Spartan_data::write_header()
{
 DBUG_ENTER("Spartan_data::write_header");
 if (number_records == -1)
 {
   my_seek(data_file, 0l, MY_SEEK_SET, MYF(0));
   my_write(data_file, (uchar *)&crashed, sizeof(bool), MYF(0));
   my_write(data_file, (uchar *)&number_records, sizeof(int), MYF(0));
   my_write(data_file, (uchar *)&number_del_records, sizeof(int), MYF(0)); 
 }

 DBUG_RETURN(0);
}
