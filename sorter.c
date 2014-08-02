#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ruby/ruby.h"

void print_array (int *array, int size)
{
  int i;
  for (i = 0; i < size; i++)
  {
    printf("%d, ", array[i]);
  }
  printf("\n");
}

int is_sorted(int *array, int size)
{
  int i;

  for (i = 0; i < (size - 1); i++)
  {
    if (array[i] > array[i + 1]) return 0;
  }

  return 1;
}

void swap(int *i, int *j)
{
  int temp;
  temp = *i;
  *i = *j;
  *j = temp;
}

static VALUE
bogosort_m(VALUE self, VALUE ruby_array)
{
  int i, size = RARRAY_LEN(ruby_array);
  int x, y;
  unsigned long long int sort_count = 0;

  int* data = (int*)malloc(size * sizeof(int));

  srand((unsigned int)time(NULL));

  for (i = 0; i < size; i++)
  {
    data[i] = NUM2INT(rb_ary_shift(ruby_array));
  }

  while (!(is_sorted(data, size)))
  {
    for (i = 0; i < size; i++)
    {
      x = rand() % size;
      swap(&data[i], &data[x]);
    }

    sort_count++;
    // print_array(data, size);
  }

  printf("C:    done in %d times\n", sort_count);

  VALUE return_array = rb_ary_new2(size);
  for (i = 0; i < size; i++)
  {
    rb_ary_store(return_array, i, INT2FIX(data[i]));
  }

  return return_array;
}

void Init_sorter()
{
  VALUE cSorter = rb_define_class("Sorter", rb_cObject);
  rb_define_singleton_method(cSorter, "bogosort", bogosort_m, 1);
}
