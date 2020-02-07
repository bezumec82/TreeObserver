This was the attempt to add Observer pattern to the ::boost::property_tree.
The idea is to add through Observer mechanism for quick traversing of tree.
Comparison test is provided.
Results :
```find``` method from boost finds node in time 6...10microsec.
```getNode``` method from Observer, finds node in time 50...70microsec.
In booth cases the same tree is used, where string is used as the key.
Find time doesn't depend of size of tree.
Look implementation.
=== Update ===
```::boost::property_tree``` internally uses ```::boost::multi_index``` which is much faster than hash in ```::std::unordered_map```.
Problem with ```::boost::property_tree``` is that it is strongly dependent of class```string_path```, that imposes to use string-like classes as keys and some path separator :
```
template <typename String, typename Translator>
    class string_path
    {
        ...
        string_path(const char_type *value,
            char_type separator = char_type('.'),
            Translator tr = Translator());
```
