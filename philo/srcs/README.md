This projects aims at understanding concurrent programming through the _Dining philosophers_ problem, first exposed by Djikstra in 1965.

# Underlying concepts

Concurrent programming relies on simultaneous execution  and shared access to resources.

__threads__ are a common way to achieve simultaneous execution. Contrary to _processes_ (which are closer to a fully-fledged program), they don't have their own memory space.

As different threads have access to the same parts of memory, it can leads to errors :

__race condition__ happens when a thread modifies a resource while another is also modifying it.

Therefore protections can be placed around resources, such as __mutex__ allowing only one concurrent access. But this can also be error-prone :

__deadlock__ happens when due to unreleased protections or wrong dependency management between program parts, no thread can be completed.

# Problem

In this problem, philosophers are represented by threads and forks are the shared resource.
Deadlock happen due to the conjunction of four phenomena:
- mutual exclusion : a resource cannot be shared by two processes at a time.
- resource holding : as the thread needs two resources, there is a period during which the first one is held, while waiting for the second.
- non preemption : a thread cannot forcefully take a resource
- circular wait : all threads are waiting to resources according to the same pattern (there is the same algorithm to decide which fork philosophers are going to wait)

# Solutions

To resolve deadlock, we should break at least one of its conditions.
Negating mutual exclusion or non preemption harly comply with the problem guidelines, thefore :

## preventing resource holding
This is Djiskstra's solution. It consists in allowing a thread to access resources only if it can takes them all at a time.

## preventing circular wait
There are different possible implementations :
### limiting concurrent threads
The aims at allowing no more threads than available resource would allow. In other words, this solution acts like a reception staff which allows only as many guests as there are free tables.
### limiting concurrent access
This would be more like a waiter telling the philosopher it forks are available or not.

Another solution presented by Chandy and Mistra also solves the issue with no "arbitrator" but at the cost of enabling communication between threads.

# This implementation

Deadlocks are prevented through a mix of above solutions : dissociated launch of threads based on their indexes and checks on mutexes to prevent concurrent access.

There is no mutex for printing messages. Yet the death notification requires a small wait of 3 usec to ensure it is printed after other concurring activities, while remaining within the requested margin of 10 millisec between actual death and its notification.

## Reducing delays due to function calls
Some function calls generate delay and may lead to remature death, especially when the _time to live_ comes close to the total activity time.
After discussing with one fellow student, I tried to implement his idea of bypassing the `printf` function and use `write` to instantaneously display the activity.

# Tests

- Parsing
- Are there any leaks ?
- Are there any race conditions ? Are timestamps chronologically consistent ?
- Base cases

|Min nb of meals	|Lifetime > Other activities|Expected result		|
| :---------------: | :-----------------------: |:----------------------|
|no					|yes						|endless loop			|
|no					|no							|death of a philosopher |
|yes				|yes						|ends once all have eaten enough|
|yes				|no							|death of a philosopher	|

- Edge case for single philosopher
- Stress resistance with many (> 200) philosophers, short (< 60 msec) activity duration, time
