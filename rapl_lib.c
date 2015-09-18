/* Copyright (c) 2015 The University of Edinburgh. */

/* 
* This software was developed as part of the                       
* EC FP7 funded project Adept (Project ID: 610490)                 
* www.adept-project.eu                                            
*/

/* Licensed under the Apache License, Version 2.0 (the "License"); */
/* you may not use this file except in compliance with the License. */
/* You may obtain a copy of the License at */

/*     http://www.apache.org/licenses/LICENSE-2.0 */

/* Unless required by applicable law or agreed to in writing, software */
/* distributed under the License is distributed on an "AS IS" BASIS, */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. */
/* See the License for the specific language governing permissions and */
/* limitations under the License. */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <inttypes.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#include "rapl_lib.h"

double power_units;
double energy_units;
double time_units;
int fd;
uint64_t result_start = 0;
uint64_t result_end = 0;


void open_msr(int core) {

  char msr_filename[BUFSIZ];

  sprintf(msr_filename, "/dev/cpu/%d/msr", core);
  fd = open(msr_filename, O_RDONLY);

}

uint64_t read_msr(int which) {

  uint64_t data;

  if ( pread(fd, &data, sizeof data, which) != sizeof data ) {
    perror("rdmsr:pread - you probably forgot to run as sudo or with CAP_SYS_RAWIO=ep set on your executable.");
    exit(127);
  }

  return data;
}

void rapl_init(void){

  uint64_t result = 0;

  open_msr(0);
  result=read_msr(MSR_RAPL_POWER_UNIT);
  power_units=pow(0.5,(double)(result&0xf));
  energy_units=pow(0.5,(double)((result>>8)&0x1f));
  time_units=pow(0.5,(double)((result>>16)&0xf));

}

void rapl_deinit(void){
  close(fd);
}

void rapl_start(void){

  uint64_t result_tmp = 0;
  result_tmp=read_msr(MSR_PP0_ENERGY_STATUS);
  while(result_tmp==(result_start=read_msr(MSR_PP0_ENERGY_STATUS))){
    usleep(50);
  }

}

void rapl_end(void){

  uint64_t result_tmp = 0;
  double pp0 = 0;
  result_tmp=read_msr(MSR_PP0_ENERGY_STATUS);
  while(result_tmp==(result_end=read_msr(MSR_PP0_ENERGY_STATUS))){
    usleep(50);
  }
  pp0=(double)(result_end-result_start)*energy_units;
  printf("PowerPlane0 (core) for core %d energy expended: %.9f J\n",0,pp0);

}
