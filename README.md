Copyright (c) 2015 The University of Edinburgh.
 
This software was developed as part of the                       
EC FP7 funded project Adept (Project ID: 610490)                 
    www.adept-project.eu                                            

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

A very basic implementation of the TU:D Greenmetrics 2012 paper by Hahnel et al
in which they suggest alignment between reading the values of the RAPL counters
with RAPL updates. This is intended to make it much less noisy and more accurate
for short code paths but should help with some of our smaller benchmarks.

To build, use the Makefile.
'make lib' will build only the shared (dynamic) library
'make test' will build the dummy application to demonstrate use.

'make' or 'make all' builds both.

As this library accesses the MSRs on Intel plaforms, make sure that you either:
+ run as sudo / root
+ chmod the /dev/cpu/*/msr files to be go+r AND run setcap cap_sys_rawio=ep <exe>
where <exe> is the name of the final executable (not the library).

To use, include the header in the source and link with -lrapl_lib providing
librapl_lib.so is on your LD_LIBRARY_PATH OR see the example in the Makefile
where the path to the library is hardcoded at the link stage.