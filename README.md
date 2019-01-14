# MessageAPI


## Overview

MessageAPI is a completely pluggable and simple message transport layer that provides
an information model and code-level API for consumption and/or production of arbitrary
content to/from arbitrary endpoints.

Apart from a set of basic plugins, this is all that MessageAPI provides. This makes
MessageAPI capable of passing any message content anywhere - code objects, database
entries, emails, etc.

The benefits of using MessageAPI are extreme schema flexibility, tool decoupling,
transport optimization potential, message API standardization, and a self-documenting information model.

## Installation and Deployment

Install MessageAPI by navigating to the cloned directory and running

```
make install
```

This will install MessageAPI to the local repository on disk.
The main MessageAPI package will only pull Log4J and SimpleJSON for use as dependencies,
while the package testing additionally requires Spock.

### Description

At a minimum, using MessageAPI means writing an information model specification
and incorporating the provided API methods in code to read the it.

MessageAPI information model specs are completely pluggable and are read when specifically
referenced at runtime in code. Because specs are completely pluggable, there is no
'right way' to write a MessageAPI spec - as long as the backing classes are available
on the classpath at runtime that understand the spec, anything can be written in one.

However, that wouldn't be very useful in practice, so MessageAPI provides a standard
topology that will suit most messaging tasks, along with providing a matching set of basic plugins.

In the provided model, the spec looks like the following:

```
{
    "plugin": "class.namespace.SessionPluginClass",
    "constructor": {
        "schema": {
            "plugin": "class.namespace.SchemaPluginClass",
            "constructor": {
                "metadata": "path/to/schema/metadata.json",
                "fields": "path/to/fields.json",
                "conditions": "path/to/conditions.json",
                "operators": "class.namespace.OperatorPluginClass"
            }
        },
        "container": {
            "plugin": "class.namespace.ContainerPluginClass",
            "constructor": {
                "metadata": "path/to/container/metadata.json",
                "containers": "path/to/containers.json",
                "relationships": "path/to/relationships.json"
            }
        },
        "protocol": {
            "plugin": "class.namespace.ProtocolPluginClass",
            "constructor": {}
        }
    }
}
```

In the default MessageAPI topology, sessions are the primary abstraction.
Sessions in turn consist of schema, container, and protocol abstractions, and each
of these has its own set of properties that must/can be specified. Notice that in
the spec, any key labeled "plugin" points to a class. These classes are what are read
at runtime (when the spec itself is referenced in the code). Anything found within
the "constructor" map is then used by the class to build itself.

So, for example, if the above spec is taken literally, when it is used in the code, an instance of the
"class.namespace.SessionPluginClass" class is loaded with the corresponding "constructor"
map passed in as the constructor argument. This in turn kicks off the system to read the schema,
container, and protocol classes and create those using their own constructor maps. The information
found in values (usually JSON maps, with the exception being the "operators" key in the schema constructor)
will be read and parsed at that time to build the component and ultimately the session.

Once built, this session is then in memory and can be reused as often as necessary. MessageAPI trades initial speed of compile-time class construction for the flexibility and declarative nature of doing it at runtime, but mitigates this by allowing already created session objects to be reused. additionally, individual parts of already created session objects can be used to create new objects (for example, using an existing in-memory schema instance, that's part of an existing, in-memory session, for use in creating a different, new session object).

Each session component is considered a fundamental and loosely orthogonal dimension of its parent. Every message session, no matter what the type, can be created by specifying these three dimensions, and this concept is what allows MessageAPI to provide a powerful abstract framework on top of arbitrary messages. Each of these dimensions has its own particular properties which define it. All also include a catchall 'metadata' property for storage of other useful self-documenting information.

Here we describe the three dimensions of a MessageAPI session:

 - Schemas are what define records as seen by the session holder. This is the part of the topology which defines what fields a record will have, any conditions on those fields, and an operator factory class that provides methods on evaluating fields against conditions (conditions may contain arbitrary logic). A schema field set is a flat set of field definitions. For example, software that wants to pass email messages through MessageAPI could have a field set of 'email, subject, body'. In the provided schema class, fields need to be provided with a 'name', 'type', and 'required' properties. The 'name' must be unique in the schema, the 'type' must be understood by the parsing class, and the 'required' must be a boolean. Conditions can be set on these fields that qualify records when passed in, serving as a potentially powerful filtering tool. In the provided default plugin, conditions must specify at least a unique id, a type, and an operator. There are two provided types in the default - composite and comparison. Comparison type conditions are direct comparisons (things like equivalency, greater than, etc.) while composite conditions reference other conditions and specify either an 'and' or an 'or' operator. This allows multiple conditions to be nested, referenced by their IDs. Composite conditions can also include other composite conditions and will be unpacked and applied recursively. The only restriction on conditions is that no infinite loops are permitted.
 - Containers are what define records as seen by the session target(s), either as the source or destination of some data (or both). There can be multiple containers per session and fields defined in the schema can exist on more than one container. Containers conceptually represent different endpoints - e.g., different tables in a database, different databases, an email address, a kafka topic, etc. Because records passed in a session can be parsed into multiple containers, records or parts of records can be passed to multiple endpoints concurrently in a single request. Some containers may have relationships defined between them, and these are defined in the relationships spec attached to the containers spec. These relationships are evaluated when processing requests in order to ensure that users always see records in the flat structure specified in the schema.
 - Protocols are specialized, library specific implementations that translate between container record sets and some external system. These protocols are the parts of the system that call out to the external world, such as FTP servers, email clients, Kafka topics, or similar things. Protocols depend on the system that needs to be called out to, so they are more specialized plugin components than the schema or container parts of MessageAPI, which can generally be reused with almost any message type.

 Now that we've described the general information model, we will describe how a typical program will use this system.

 In a java class, 


### Configurations


### Instructions

## Developer Guide

### Bugs

The package is in current, active development.
All bugs encountered should be reported to ryan.berkheimer@noaa.gov.

## License

Copyright © 2019 United States Government
