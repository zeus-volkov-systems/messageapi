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
of these has its own set of properties that must/can be specified.

### Configurations


### Instructions

## Developer Guide

### Bugs

The package is in current, active development.
All bugs encountered should be reported to ryan.berkheimer@noaa.gov.

## License

Copyright © 2019 United States Government
