# Event Packege

package ::hrfm::events

## EventDispatcher

### Example

```cpp
class MyClass{
  
  public :
  
  MyClass(){
    init();
  }
  
  void init(){
    count = 0;
    _dispatcher.addEventListener("event",this,&MyClass::_onEvent);
    _dispatcher.dispatchEvent(new hrfm::events::Event("event"));
    _dispatcher.dispatchEvent(new hrfm::events::Event("event"));
    _dispatcher.dispatchEvent(new hrfm::events::Event("event"));
    _dispatcher.removeEventListener("event",this,&MyClass::_onEvent);
    _dispatcher.dispatchEvent(new hrfm::events::Event("event"));
  }
  
  private :
  
  void _onEvent(hrfm::events::Event * evt  ){
    std::cout << "Event dispatched! : " << ++count << std::endl;
  }
  
  hrfm::events::EventDispatcher _dispatcher;
  int count;
  
}

new MyClass();
```

### Result

    Event dispatched! : 1
    Event dispatched! : 2
    Event dispatched! : 3
