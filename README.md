Fork of xv6 educative operating system for an Advanced OS course in Universidad de Murcia.
The original can be found in https://pdos.csail.mit.edu/6.828/2014/xv6.html.

We implemented some improvements as instructed by our professors:

- Added the following syscalls:
  - `date`: Prints date in a readable format.
  - `dup2`: Posix dup2 funcionality.

- Lazy page allocation.
- sbrk() takes negative values (frees memory).
- Stack guard page protection.
- Kernel-mode user page allocation (used when a syscall allocates memory).
- Kernel memory protection.
- Included general protection fault.

Problems:

- Kernel-mode user page allocation is too permissive.
- TLB is not being cleaned when switching between kernel and user mode.

Feel free to copy and pull this repository. We are not experts in OS development and this code might not be correct or properly designed.
