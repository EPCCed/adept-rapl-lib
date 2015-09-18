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
#include <unistd.h>

#include "rapl_lib.h"

void work(void){
  int a = 34;
  int b = 3424;
  long long c = 0;

  for(int i= 0;i<10000000;i++){
    c = a*b*i;
  }

}


int main(){

  printf("TEST start main\n");
  rapl_init();
  rapl_start();
  work();
  rapl_end();
  rapl_deinit();
  printf("TEST end main\n");

  return 0;
}

