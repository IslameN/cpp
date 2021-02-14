# Fluent Builder
I have had a lot of problems due to circular references in this project.

Importing in `main.cpp` the `Person.hpp` caused all the project to fail (but now
is working... why?)

I had to use forward declaring the builders so it could work, but not sure why.