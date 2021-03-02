#ifndef _serialize_h
#define _serialize_h

#include "../information/stu_info.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT 1000

int write_info(Stu_Info *node_list, unsigned int length, Col_Type type);
int add_info(Stu_Info *node_list, unsigned int length, Col_Type type);
int read_info(Stu_Info *node_list, unsigned int start, unsigned int length, int *total, Col_Type type);

int get_name(Col_Type type, char *fname);

#endif