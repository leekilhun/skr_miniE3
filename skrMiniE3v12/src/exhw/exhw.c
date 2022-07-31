/*
 * exhw.c
 *
 *  Created on: 2022. 7. 24.
 *      Author: gns2l
 */



#include "exhw.h"


bool exhwInit(void)
{
  bool ret = true;

  ret &=  stepperInit();

  return ret;
}
