# Zen Enterprise

Zen Enterprise is a service bus and application container framework.

## Version 2.0

With this new version there are a number of breaking changes.  This version is
under heavy development, and so if you're using an older implementation then
you should probably consider carefully before adopting this new implementation.

### C++ 14 and beyond

%his library ius now utilizing some of the new features provided by C++ 11/14
as well as some experimental C++ 17 features.

The advantage of using these new versions of C++ and the standard template 
library is that Zen Core is no longer necessary.

### Minimal Dependencies

With this version we're removing (as much as 
possible) all dependencies from other libraries including boost, libxml, and 
Zen Core 1.0.

Current dependencies include the Boost unit testing framework, but the goal is 
to make these dependencies optional.
