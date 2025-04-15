This projects aims at understanding concurrent programming through the _Dining philosophers_ problem, first exposed by Djikstra in 1965.

# Underlying concepts

Concurrent programming relies on simultaneous execution  and shared access to resources.

__threads__ are a common way to achieve simultaneous execution. Contrary to _processes_ (which are closer to a fully-fledged program), they don't have their own memory space.

As different threads have access to the same parts of memory, it can leads to errors :

__race condition__ happens when a thread modifies a resource while another is also modifying it.

Therefore protections can be placed around resources, such as __mutex__ allowing only one concurrent access. But this can also be error-prone :

__deadlock__ happens when due to unreleased protections, no thread can access the resource.
