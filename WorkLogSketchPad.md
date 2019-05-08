# Work Log Sketch Pad

This work log was established as an in-package tracking tool for
system development. It was established fairly late, when the essential
structure of the package was well established, and the basic functionality
of the package was complete. It attempts to provide a clear
'state of development' document for developers, to be used for quick integration
with current development, and should be supplemental to the repository record.


## Current Focus

### Transformations

#### The following configuration maps are involved in transformations:

- the global transformation list of transformation maps (contains specifications of transformations)
- the connection list for each endpoint (lists by id transformations that should be available)
- the global session spec (specifies transformation maps and connection lists)

**Currently, we do the following toward providing transformations to the user:**

1. On session initialization, we load the transformation spec into memory as
a list of transformation hash-maps owned by the Container Definition
2. On session initialization, we load the transformation factory class into memory
as an object factory owned by the Container Definition
3. On session initialization, we load the connection maps into memory as a list
of connection hash-maps
4. On initialization of a protocol, in the setConnections method, connections in
the protocol definition endpoint map are turned into a flat list of connections,
and held by the protocol.


## Previous Foci
