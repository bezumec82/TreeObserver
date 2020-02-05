This was the attempt to add Observer pattern to the ::boost::property_tree.
The idea is to add through Observer mechanism for quick traversing of tree.
Comparison test is provided.
Results :
```find``` method from boost finds node in time 6...10microsec.
```getNode``` method from Observer, finds node in time 50...70microsec.
In booth cases the same tree is used, where string is used as the key.
Find time doesn't depend of size of tree.
Look implementation.