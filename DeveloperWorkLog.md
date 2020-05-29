# Developer Work Log History

This work log was established as an in-package tracking tool for
system development. It was established fairly late, when the essential
structure of the package was well established, and the basic functionality
of the package was complete. It attempts to provide a clear
'state of development' document for developers, to be used for quick integration
with current development, and should be supplemental to the repository record.

This work log is also useful as a supplemental documentation for end users of the package - features are described and contextualized with as much detail as possible.

## Future Work

- Fortran API
- Python API
- Split Publish/Consumer Sessions
- Example Endpoints (Email, Directory, Kafka)

## Current Focus

### C API

#### Status - In Progress

We are currently working on the linkage between C++ and the NativeEndpoint class. The NativeEndpoint class has been established and the majority of C structs have been created. The next challenge is to create C/C++ methods that work on these C structs, and then methods that bind to Java methods.

#### Description and Goals

A C API should be provided that allows use of MessageAPI in native code. This API should both allow Endpoint use (i.e., grabbing Container Records, parsing Field values, creating Endpoint Records, setting Field values, creating Endpoint Rejections, and returning a Data Packet), and Session use (i.e., creating a new Session, creating a new Request, adding Records to the Request, submitting the Request, retrieving a Response, and parsing Responses by retriving Rejections/reasons and Records/fields). This API should be as seamless as possible - i.e., being a native library, should feel as much like a native library as possible -  it should be well behaved WRT state, i.e., if we require isolated state it should satisfy that requirement - and it should provide a simple mechanism for extension to Fortran support.

## Previous Foci

### README Updating

#### Status - Complete up to Current Status

Resolution - The README was updated to the final architectural state, removing incorrect information, updating incomplete information, and adding basic system diagrams. There is still work to be done - README must be updated with Polyglot API discussion when that's done.

#### README Updating Description and Goals

The README should be updated to match the current state of the package. It should be correct, comprehensive enough to serve as a complete guide for getting the system running, and contain enough information for external review. It should form the basis of a MessageAPI white paper.

### Field Definition Enforcement on Transformations and Endpoints

#### Status - Completed Successfully With Design Change

Resolution - after an analysis of the initial design specifications WRT patterns found in communicating sequential processes, it was determined that the process both Transformation and Endpoint alphabets had an unknown potential for collision when intersected with the Schema alphabet. Due to this potential for collision and inability to make guarantees that fields which are part of the global alphabet are uniquely typed, a solution was implemented that provides configurable control and as many guarantees about endpoint fields as possible. This was done by creating an abstract base class that requires extending endpoints to define their own default fields. Then which of these fields returned is configurable by the session that uses the endpoint (on the connection map). In other words, the endpoint defines its maximal/default return field set, but that is a maximum bound that can be reduced by sessions, by specifying a subset on the connection map.

```json
Author: Ryan Berkheimer
```

#### Transformation and Endpoint Field Definition Enforcement Description and Goals

The goal is to implement enforcement of field definitions on transformations and endpoints. This means that fields should be specified for each transformation and endpoint connection, and these fields must be defined in the schema fields map. The transformation and endpoint base classes would then be able to have a stereotyped method for creating a record that can be used inside the transformation or endpoint, and the caller/receiver will also would know what type of record to expect as emergent from the system. This also introduces the potential for future system type validation.

Currently fields are specified by transformations on transformation spec maps, and read in at run-time into the created class instance. Endpoint connections currently have no similar mechanism. Neither endpoint connections nor transformations currently perform any validation or offer automatic record generation. All of these mentioned missing behaviors must be implemented for this feature to be considered successfully implemented.

#### Design Path

Ultimately it was decided that the best that could be done with endpoint fields without breaking some mathematical domain guarantees was to create a BaseEndpoint abstract class, which other endpoints could extend, that would parse default fields (to be specified on the endpoint itself). This design allows consumers of endpoints to have a guarantee of what fields they will expect to originate out of an endpoint. In the specification, a subset of those fields can be specified to restrict what endpoints return. This design compromise was due to the uncertainty in the field domain of reusable endpoints - i.e., the possibility for endpoints to define fields with the same name but different types. This could either be controlled via

### Collection Conditions

#### Status - Completed Successfully

Resolution - This feature was implemented as described below. All conditions originate from the global conditions map. In default sessions, the request now gets a complete copy of the conditions, as well as each record. If initial conditions are set, they are kept in the request set of conditions. Any initial conditions that are set are wiped from individual records - if the values are set independently, they will be honored for that record. When a request is submitted, conditions valued on individual records will filter records as before - in new behavior, request-wide records are  applied to all records being parsed/factored into different containers - ie, records must satistfy the conditions specified on a contained to be added to that container. Currently, only collection containers allow specified conditions. This is due to the ability of transformations for arbitrary fieldset modification, including addition of fields that are not specified on the global fieldset schema.

```json
Author: Ryan Berkheimer
```

#### Collection Condition Description and Goals

The goal is to implement condition behavior, similar to that currently seen at the record level, at the collection level. This involves allowing the user to optionally specify a 'conditions' property on individual collections, as a key/value pair, where the key is the word 'conditions' is the key, corresponding to a list of condition ids.

Currently, we have conditions listed as a list of maps, e.g.

```json
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

```json
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

##### We want the system to conform to the following conditions

- conditions are able to be valued on requests by the user, or specified beforehand on the map, in addition to individual records
- conditions are able to be added to collections by id with an optional 'conditions' keyword on each collections map
- when a request is submitted, after records are individually filtered, they are only placed in collections if they meet conditions specified on the collection

##### We want the internal behavior to conform to the following conditions

- conditions are now parsed and checked as part of collection map parsing in the container definition
- a request should hold an ICondition (in addition to a list of IRecords, etc.)
- when requests are submitted, condition chains are computed for each collection (top level conditions, nested, etc.)
- when factoring a record into collections, if a schema record does not satisfy the conditions of a collection, that collection is not created
- that collection should be thrown as a rejection with a reason - rejected in container layer due to condition mismatch

#### Baselining our Status

At the time of writing, the condition engine is complete and already implemented on a per-record basis for records passed for response as part of a request submission. A complete set of methods to accomplish the parsing, determination, and evaluation of conditions exists in a ConditionUtils static class, and operates on records, which hold individual sets of conditions.

In the current implementation, the engine attempts to be clever in determining which conditions apply to a given record. It does this by first removing all conditions on a record that don't have values. From the conditions that are left (those with values), top level conditions are determined (conditions not referenced in any remaining condition). For each top level condition, a condition tree is created. Each of these independent condition trees are then evaluated against the record as an 'and' condition (all condition trees must be satisfied for the record to be accepted). This process is repeated for every record that is passed in a request, in order to determine which records should be filtered out before the entire record set is passed onto the container layer for factoring into collections.

#### Collection Condition Design Path

Comparing the desired status to baseline, we see some obvious system characteristics that will have an impact on the path of change implementation. These affecting characteristics are

1. The condition utility methods all operate on the IRecord. To reuse these methods, the IRequest should get an IRecord, rather than a condition list directly.
2. Due to the clever implementation of ICondition value-checking in individual IRecord filtering, there are competing interests (between the existing behavior and the desired) in declaring values on the map up front. Because any ICondition that has a value will be used for IRecord filtering, if we want to use initial values for the entire IRequest, those conditions will also be picked up on an individual record basis, even if we only wanted the value to apply to collections against the entire record set. There are different solutions to resolving this conflict:
    a. We can ignore values for the purpose of individual records on initialization, only using explicitly added values for that level of filtering
    b. We can ignore values for the purpose of request wide filtering, only using explicitly added values for that level of filtering
    c. We can remove initial values all together from the system, forcing the user to add all initial values in code

    All three of these options have pros and cons. The pro of option (c) is that the system is uniform, making it easier to remember how it works. However, the con of this option is that it is the most limiting, because it moves major condition configuration behavior into the code. The principle pro of option (a) is that it would maintain the original behavior exactly. However, this option also maintains an incomplete flexibility in the most fine resolution of uses, while making the least fine resolution (request-wide) have its configuration inside code. Option (b) seems like it has a clear pro - request-wide configuration of conditions outside of code - with the smallest con - fine-grained filtering on single records must be specified in code.

For our purposes in this feature addition, we choose to implement option (c). While this means we will lose some flexibility in individual record filtering, we will not lose the ability to configure request wide filtering into collections from the specification map. This will require a small change in current behavior - when creating a new record in a request, any existing values in the condition set will be wiped, and must be explicitly set by the user.

To implement our change with the chosen option and for maximum reuse of existing code, our path is now straightforward:

1. Update existing requests to hold a new request wide IRecord to hold IRequest wide IConditions
2. Update existing IRecord creation in an IRequest to wipe initial values from the ICondition map
3. Add an interface method to IRequest to access the RequestRecord
4. Add an interface method to IRequest to set a value on a condition
5. Add parsing logic for an optional 'conditions' keyword on collections
6. Add initialization behavior to DefaultCollection for conditions, reusing ConditionUtils
7. Add access methods to ICollection for condition evaluation of a passed record
8. Update the factoring process during response processing to include condition evaluation during collection creation

### Transformations

#### Transformation Status - Completed Successfully

Resolution - Transformations are fully implemented and functional. Transformations get their own copies of records, so they are completely functional. They can accept an arbitrary number of any container type as inputs - i.e., collections, classifiers, or other transformations, as well as UUID sets. Because they can accept other transformations, they can be recursive. Transformations are also lazy, in the sense that they are containers. They hold definitions until they are used inside an endpoint, at which point they are evaluated. In the case that the UUID keyword is used as an input to a transformation, the transformation will be applied to every UUID set individually, and then the transformation will return an aggregate of all evaluations.

```json
Author: Ryan Berkheimer
```

#### Transformation Description and Goals

The goal is to make the method getRecordsByTransformation("transformationID")
on the protocol record functional. 'Being functional' in this context means
when we call this method from an endpoint class instance, we should get a list
of records that satisfy the conditions specified by the transformation.

##### We want the method to conform to the following conditions

- method should only compute when called (lazy behavior)
- method should be as fast/optimized as possible - don't build common things more than we have to
- method should select data from the protocol record records map
- method should allow any combination of record sets to be used in transformations
- method should allow as record set parameters
  - collections
  - classifiers
  - uuids
  - other transformations

##### We want the internal behavior for the transformation mod to conform to the following conditions

- transformation factory should be preloaded in the container layer
- classifiers and/or collections used by a transformation or its child transformations as parameters must be available to any associated connection
- the transformation instance should be preloaded before getRecordsByTransformation method invocation
- records used by a transformation should be immutable, in that they don't change any already existing record

#### Transformation - Baselining our Status

##### The following configuration maps are involved in transformations

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

#### Transformation Design Path

Based on the stated constraints, a straightforward design path is evident. First we describe how the design is implemented when calling the method, and then we describe what changes will be made to the baseline system to implement this change.

##### Method Invocation Action

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

##### Transformation Implementation Design

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
