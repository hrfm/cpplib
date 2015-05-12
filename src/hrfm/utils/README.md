# Utils Packege

package ::hrfm::utils

## DynamicMap

### Example

```cpp
hrfm::utils::DynamicMap dmap;
dmap.setValue("key","hoge");
std::cout << dmap.getValue<string>("key") << std::endl;
std::cout << dmap.hasValue("key") << std::endl;
```

### Result

    hoge
    true
