# Current Focus - Transformations


## The following configuration maps are involved in transformations:

- the global transformation list of transformation maps (contains specifications of transformations)
- the connection list for each endpoint (lists by id transformations that should be available)
- the global session spec (specifies transformation maps and connection lists)

**Currently, we do the following toward providing transformations to the user:**

1. On session initialization, we load the transformation spec into memory as
a list of transformation hash-maps owned by the Container Definition
2. On session initialization, we load the transformation factory class into memory
as an object factory owned by the Container Definition.
3. On session initialization, we load the connection maps into memory as a list
of connection hash-maps
4. On
