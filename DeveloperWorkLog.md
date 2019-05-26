# Developer Work Log History

This work log was established as an in-package tracking tool for
system development. It was established fairly late, when the essential
structure of the package was well established, and the basic functionality
of the package was complete. It attempts to provide a clear
'state of development' document for developers, to be used for quick integration
with current development, and should be supplemental to the repository record.

This work log is also useful as a supplemental documentation for end users of the package - features are described and contextualized with as much detail as possible.


## Current Focus

### Collection Conditions

The goal is to implement condition behavior, similar to that currently seen at the record level, at the collection level. This involves allowing the user to optionally specify a 'conditions' property on individual collections, as a key/value pair, where the key is the word 'conditions' is the key, corresponding to a list of condition ids.

Currently, we have conditions listed as a list of maps, e.g.

```
"conditions": [
    {
        "id": "1",
        "type": "comparison",
        "operator": ">=",
        "field": "key"
    },
    {
        "id": "2",
        "type": "comparison",
        "operator": "<",
        "field": "key"
    },
    {
        "id": "three",
        "type": "composite",
        "operator": "or",
        "conditions": ["1","2"]
    }]
```

And we have a list of collections in another list of maps, e.g.,


```
"collections": [
    {
        "id": "required-fields",
        "classifiers": {
            "namespace": ["yellow"],
            "required": true
        },
        "fields": ["boolean-required", "float-required", "double-required", "integer-required", "string-required", "datetime-required"]
    },
    {
        "id": "optional-fields",
        "classifiers": {"namespace": "condition-test"},
        "fields": ["boolean-optional", "float-optional", "double-optional", "integer-optional", "string-optional", "datetime-optional"]
    },
    {
        "id": "mix-and-match",
        "classifiers": {"namespace": ["condition-test", "test3"]},
        "fields": ["string-required", "string-optional", "datetime-required"]
    }
]
```

Each of these maps is referred to in the Session spec. Following package convention, conditions are contained in the schema, because they are able to be updated (by value) at runtime through the Request API; collections are contained in the container, because they define how to split/categorize/factor each record schema.

Each of these maps follows another package convention, in that they are the sole source of truth for the given domain model/concept within the given Session. This means that all conditions for the entire session are contained in the conditions map, all collections are contained in the collections map - there are no other places where these may be stored.

At the time of this feature specification, the condition map is copied and attached to a record when the record is created on a request. Users can set condition values on the record, or pre-specify values on conditions in the map. When the request is submitted for response, every record is then checked individually against conditions which have set values for that record, and is rejected if it don't meet all conditions.

This feature addition would add these same abilities - condition value setting, record filtering, to collections.

**We want the system to conform to the following conditions**

- conditions are able to be valued on requests by the user, or specified beforehand on the map, in addition to individual records
- conditions are able to be added to collections by id with an optional 'conditions' keyword on each collections map
- when a request is submitted, after records are individually filtered, they are only placed in collections if they meet conditions specified on the collection

**We want the internal behavior to conform to the following conditions**

- conditions are now parsed and checked as part of collection map parsing in the container definition
- a request should hold an ICondition (in addition to a list of IRecords, etc.)
- when requests are submitted, condition chains are computed for each collection (top level conditions, nested, etc.)
- when factoring a record into collections, if a schema record does not satisfy the conditions of a collection, that collection is not created
- that collection should be thrown as a rejection with a reason - rejected in container layer due to condition mismatch

## Previous Foci

### Transformations

The goal is to make the method getRecordsByTransformation("transformationID")
on the protocol record functional. 'Being functional' in this context means
when we call this method from an endpoint class instance, we should get a list
of records that satisfy the conditions specified by the transformation.

**We want the method to conform to the following conditions**

- method should only compute when called (lazy behavior)
- method should be as fast/optimized as possible - don't build common things more than we have to
- method should select data from the protocol record records map
- method should allow any combination of record sets to be used in transformations
- method should allow as record set parameters
    - collections
    - classifiers
    - uuids
    - other transformations

**We want the internal behavior to conform to the following conditions**

- transformation factory should be preloaded in the container layer
- classifiers and/or collections used by a transformation or its child transformations as parameters must be available to any associated connection
- the transformation instance should be preloaded before getRecordsByTransformation method invocation
- records used by a transformation should be immutable, in that they don't change any already existing record

#### Baselining our Status

**The following configuration maps are involved in transformations**

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

#### Design Path

Based on the stated constraints, a straightforward design path is evident. First we describe how the design is implemented when calling the method, and then we describe what changes will be made to the baseline system to implement this change.

**Method Invocation Action**

When a transformation is desired, the user calls getRecordsByTransformation("transformationId"), and the following things happen:


1. the transformationId key is accessed on the transformationMap held in the associated connection where the method is invoked
    - The value associated with the transformationId is another map with entries
        - entry 1:
            - key: instance
            - value: transformation instance
        - entry 2:
            - key: parameters
            - value: a map of arbitrary entries corresponding to parameters in the original transformation map (can be references to named collection, classification, transformation, or UUID-wise)
                - example entries
                    - entry 1
                        - key: "parent_records"
                        - value: "CLASSIFIER=X.Y"
                    - entry 2
                        - key: "child_records"
                        - value: "COLLECTION=collection1"
                    - entry 3
                        - key: "wildcard_records"
                        - value: "UUID"
                    - entry 4
                        -key: "another_set_of_records"
                        - value: "TRANSFORMATION=a_different_transformation"
2. The parameters map is copied
3. The copy of the parameters map is recursively filled out, replacing strings with the record sets they refer to
    - The record sets which replace their reference string consist of copies of the original records in the set to ensure immutability of the method
    - The recursive part applies to transformation parameters, where children transformations get this same treatment before returning their own results eventually to this method
    - If UUID is encountered, the transformation is applied as a map operation for every UUID available to the connection, and the results are aggregated in a single record set. This does mean UUID can only be used as one parameter per transformation.
4. The completed map is passed to the instance on the original transformation map.
5. Operations are completed as specified within the transformation class. This transformation class has access to the record sets as values of the keys which were originally specified on the map.
6. The transformation class must return a new record set, where each record contains the keys listed in the original transformation map.

**Implementation Design**

In order to implement the transformation, the following modifications must be made to the baseline system

1. Set container initialization to happen prior to protocol definition initialization, so that the transformation factory associated with the container layer is instantiated.
2. During session initialization, update the initialization method in the default protocol so that the transformation factory and the raw transformation spec maps are passed into the setConnections method
3. Add a copyConnections() method that deep-copies connection instances when creating new Requests on an in-memory Session.
4. Add a getCopy() method onto connections (and IConnection requirement) that makes a deep copy of a connection instance to be used with the copyConnections() method in step 3
5. In the connection constructor, make a call to assemble the connection-specific transformation map.
    - This will involve the following steps
        - determine all transformations that will be required for use by the connection (including parent transformations of direct referenced ones)
        - create a map entry for each of these
            - the key will be the transformation ID
            - the value will be a map
                - instantiate the transformation class (from the factory) with associated fields/params and add it to the map
                - create a value map for the input record sets and add it
6. In the body of getRecordsByTransformation, add logic that processes a method invocation according to the steps outlined in the previous section.
