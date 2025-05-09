// RUN: %clang_cc1 %s -verify -fopenacc

void func() {

  // expected-error@+1{{expected OpenACC directive}}
#pragma acc
  for(;;){}

  // expected-error@+2{{expected OpenACC directive}}
  // expected-error@+1{{invalid OpenACC clause 'whatever'}}
#pragma acc(whatever) routine

  // expected-error@+2{{expected OpenACC directive}}
  // expected-error@+1{{invalid OpenACC clause 'routine'}}
#pragma acc) routine

  // expected-error@+1{{invalid OpenACC directive 'invalid'}}
#pragma acc invalid
  for(;;){}

  // expected-error@+1{{invalid OpenACC clause 'clause'}}
#pragma acc parallel clause list
  for(;;){}
  // expected-error@+2{{expected clause-list or newline in OpenACC directive}}
  // expected-error@+1{{invalid OpenACC clause 'clause'}}
#pragma acc parallel() clause list
  for(;;){}
  // expected-error@+3{{expected clause-list or newline in OpenACC directive}}
  // expected-error@+2{{expected ')'}}
  // expected-note@+1{{to match this '('}}
#pragma acc parallel( clause list
  for(;;){}
  // expected-error@+2{{expected clause-list or newline in OpenACC directive}}
  // expected-error@+1{{invalid OpenACC clause 'clause'}}
#pragma acc parallel() clause list
  for(;;){}
  // expected-error@+3{{expected clause-list or newline in OpenACC directive}}
  // expected-error@+2{{expected ')'}}
  // expected-note@+1{{to match this '('}}
#pragma acc parallel( clause list
  for(;;){}
  // expected-error@+2{{expected clause-list or newline in OpenACC directive}}
  // expected-error@+1{{invalid OpenACC clause 'clause'}}
#pragma acc serial() clause list
  for(;;){}
  // expected-error@+3{{expected clause-list or newline in OpenACC directive}}
  // expected-error@+2{{expected ')'}}
  // expected-note@+1{{to match this '('}}
#pragma acc serial( clause list
  for(;;){}
  // expected-error@+1{{invalid OpenACC clause 'clause'}}
#pragma acc serial clause list
  for(;;){}
  // expected-error@+1{{invalid OpenACC clause 'clause'}}
#pragma acc kernels clause list
  for(;;){}
    // expected-error@+2{{OpenACC 'data' construct must have at least one 'attach', 'copy', 'copyin', 'copyout', 'create', 'default', 'deviceptr', 'no_create', or 'present' clause}}
  // expected-error@+1{{invalid OpenACC clause 'clause'}}
#pragma acc data clause list
  for(;;){}
  // expected-error@+2{{OpenACC 'enter data' construct must have at least one 'attach', 'copyin', or 'create' clause}}
  // expected-error@+1{{invalid OpenACC clause 'clause'}}
#pragma acc enter data clause list
  for(;;){}
  // expected-error@+2{{OpenACC 'exit data' construct must have at least one 'copyout', 'delete', or 'detach' clause}}
  // expected-error@+1{{invalid OpenACC clause 'clause'}}
#pragma acc exit data clause list
  for(;;){}
  // expected-error@+1{{invalid OpenACC directive 'enter invalid'}}
#pragma acc enter invalid
  for(;;){}
  // expected-error@+1{{invalid OpenACC directive 'exit invalid'}}
#pragma acc exit invalid
  for(;;){}
  // expected-error@+1{{invalid OpenACC directive 'enter'}}
#pragma acc enter
  for(;;){}
  // expected-error@+1{{expected identifier}}
#pragma acc exit }
  for(;;){}
  // expected-error@+2{{OpenACC 'host_data' construct must have at least one 'use_device' clause}}
  // expected-error@+1{{invalid OpenACC clause 'clause'}}
#pragma acc host_data clause list
  for(;;){}
  // expected-error@+1{{invalid OpenACC clause 'clause'}}
#pragma acc loop clause list
  for(int i = 0; i < 6;++i){}
  // expected-error@+1{{invalid OpenACC clause 'invalid'}}
#pragma acc parallel invalid clause list
  for(int i = 0; i < 6;++i){}
  // expected-error@+1{{invalid OpenACC clause 'invalid'}}
#pragma acc serial invalid clause list
  for(int i = 0; i < 6;++i){}
  // expected-error@+1{{invalid OpenACC clause 'clause'}}
#pragma acc parallel loop clause list
  for(int i = 0; i < 6;++i){}

#pragma acc parallel loop
  for(int i = 0; i < 6;++i){}
  // expected-error@+1{{invalid OpenACC clause 'clause'}}
#pragma acc serial loop clause list
  for(int i = 0; i < 6;++i){}
#pragma acc serial loop
  for(int i = 0; i < 6;++i){}
  // expected-error@+1{{invalid OpenACC clause 'clause'}}
#pragma acc kernels loop clause list
  for(int i = 0; i < 6;++i){}
#pragma acc kernels loop
  for(int i = 0; i < 6;++i){}

  int i = 0, j = 0, k = 0;
#pragma acc atomic
  i = i + 1;
  // expected-error@+1{{invalid OpenACC clause 'garbage'}}
#pragma acc atomic garbage
  i = i + 1;
  // expected-error@+1{{invalid OpenACC clause 'garbage'}}
#pragma acc atomic garbage clause list
  i = i + 1;
#pragma acc atomic read
  i = j;
  // expected-error@+1{{invalid OpenACC clause 'clause'}}
#pragma acc atomic write clause list
  i = i + j;
  // expected-error@+1{{invalid OpenACC clause 'clause'}}
#pragma acc atomic update clause list
  i++;
  // expected-error@+1{{invalid OpenACC clause 'clause'}}
#pragma acc atomic capture clause list
  i = j++;


  // expected-error@+2{{invalid OpenACC clause 'clause'}}
  // expected-error@+1{{no valid clauses specified in OpenACC 'declare' directive}}
#pragma acc declare clause list
  for(;;){}
  // expected-error@+1{{invalid OpenACC clause 'clause'}}
#pragma acc init clause list
  for(;;){}
  // expected-error@+1{{invalid OpenACC clause 'clause'}}
#pragma acc shutdown clause list
  for(;;){}
  // expected-error@+2{{invalid OpenACC clause 'clause'}}
  // expected-error@+1{{OpenACC 'set' construct must have at least one 'default_async', 'device_num', or 'device_type' clause}}
#pragma acc set clause list
  for(;;){}
  // expected-error@+2{{OpenACC 'update' construct must have at least one 'device', 'host', or 'self' clause}}
  // expected-error@+1{{invalid OpenACC clause 'clause'}}
#pragma acc update clause list
  for(;;){}
}

#pragma acc routine seq
void routine_func();
// expected-error@+2{{invalid OpenACC clause 'clause'}}
// expected-error@+1{{OpenACC 'routine' construct must have at least one 'gang', 'seq', 'vector', or 'worker' clause}}
#pragma acc routine clause list
void routine_func();

// expected-error@+1{{use of undeclared identifier 'func_name'}}
#pragma acc routine (func_name) seq
// expected-error@+3{{use of undeclared identifier 'func_name'}}
// expected-error@+2{{invalid OpenACC clause 'clause'}}
// expected-error@+1{{OpenACC 'routine' construct must have at least one 'gang', 'seq', 'vector', or 'worker' clause}}
#pragma acc routine (func_name) clause list

#pragma acc routine (routine_func) seq
// expected-error@+2{{invalid OpenACC clause 'clause'}}
// expected-error@+1{{OpenACC 'routine' construct must have at least one 'gang', 'seq', 'vector', or 'worker' clause}}
#pragma acc routine (routine_func) clause list

// expected-error@+2{{expected ')'}}
// expected-note@+1{{to match this '('}}
#pragma acc routine (routine_func()) seq

// expected-error@+1{{expected identifier}}
#pragma acc routine() seq

// expected-error@+1{{expected identifier}}
#pragma acc routine(int) seq
