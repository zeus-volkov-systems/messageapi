# MessageAPI


## Overview

MessageAPI is a completely pluggable and simple message transport layer that provides
an information model and code-level API for consumption and/or production of arbitrary
content to/from arbitrary endpoints.

Apart from a set of basic plugins, this is all that MessageAPI provides. This makes MessageAPI capable of passing any message content - code objects, database entries, emails, etc., to anywhere - database tables, inboxes, s3 buckets, etc. - through any protocol - ftp, smtp, kafka, etc.

The benefits of using MessageAPI are its extreme schema flexibility, potential for tool decoupling and transport optimization, API standardization across all messaging, and self documentation through an information model.

It's important to point out that MessageAPI does not replace traditional load balancing brokers (ActiveMQ, RabbitMQ)
or streaming platforms (Kafka, Storm). These other messaging systems are appropriate as protocol or container layer plugins in MessageAPI, depending on how the implementation models the system. MessageAPI adds additional desired behaviors to these tools - including the ability to switch them out at will as streaming technologies evolve, and adding a declarative model to them.

### Description

At a minimum, using MessageAPI means writing an information model specification
and incorporating the provided API methods in code to read the it.

MessageAPI information model specs are completely pluggable and are read when specifically
referenced at runtime in code. Because specs are completely pluggable, there is no
'right way' to write a MessageAPI spec - as long as the backing classes are available
on the classpath at runtime that understand the spec, anything can be written in one.

However, that wouldn't be very useful in practice, so MessageAPI provides a standard
topology that will suit most messaging tasks, along with providing a matching set of basic plugins.
This set of default classes can then serve as a reference for writing better versions of those which are provided and/or customized plugins for different containers or protocols.

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

In the default MessageAPI topology, sessions are the primary abstraction. Sessions in turn consist of schema, container, and protocol abstractions, and each of these has its own set of properties that must/can be specified. Notice that in the example spec, any key labeled "plugin" points to a class. These classes are what are read at runtime (when the spec itself is referenced in the code). Anything found within the "constructor" map is then used by the class to build itself.

So, for example, if the above spec is taken literally, when it is used in the code, an instance of the "class.namespace.SessionPluginClass" class is loaded with the corresponding "constructor" map passed in as the constructor argument. This in turn kicks off the system to read the schema, container, and protocol classes and create those using their own constructor maps. The information found in the associated key-values (usually referencing an underlying JSON map, with the exception being the "operators" key in the schema constructor) will be read and parsed at that time to build the component and ultimately the session.

Once built, this session is then in memory and can be reused as often as necessary. MessageAPI trades initial speed of compile-time class construction for the flexibility and declarative nature of doing it at runtime  (although the initial bootstrapping is generally very fast anyway), and then allows already created session objects to be reused. Additionally, individual parts of already created session objects can be used to create new objects (for example, using an existing in-memory schema instance, that's part of an existing, in-memory session, for use in creating a different, new session object).

Each session component is considered a fundamental and loosely orthogonal dimension of its parent. Every message session, no matter what the type, can be created by specifying these three dimensions, and this concept is what allows MessageAPI to provide a powerful abstract framework on top of arbitrary messages. Each of these dimensions has its own particular properties which define it. All also include a catchall 'metadata' property for storage of other useful self-documenting information, such as version or identifying labels.

Here we describe the three dimensions of a MessageAPI session:

 - Schemas
    - Schemas are what define records as seen by the session holder. This is the part of the topology which defines what fields a record will have, any conditions on those fields, and an operator factory class that provides methods on evaluating fields against conditions (conditions may contain arbitrary logic). A schema field set is a flat set of field definitions. For example, software that wants to pass email messages through MessageAPI could have a field set of 'email, subject, body'. In the provided schema class, fields need to be provided with a 'name', 'type', and 'required' properties. The 'name' must be unique in the schema, the 'type' must be understood by the parsing class, and the 'required' must be a boolean. Conditions can be set on these fields that qualify records when passed in, serving as a potentially powerful filtering tool. In the provided default plugin, conditions must specify at least a unique id, a type, and an operator. There are two provided types in the default - composite and comparison. Comparison type conditions are direct comparisons (things like equivalency, greater than, etc.) while composite conditions reference other conditions and specify either an 'and' or an 'or' operator. This allows multiple conditions to be nested, referenced by their IDs. Composite conditions can also include other composite conditions and will be unpacked and applied recursively. The only restriction on conditions is that no infinite loops are permitted. Conditions are applied on both 'get' and 'put' type operations, which provide a SQL type selection for records in arbitrary containers.

    - A schema 'metadata' json specification file (metadata.json)
      ```
      {
          "metadata": {
              "name": "clisam",
              "type": "simple"
          }
      }
      ```

    - A schema 'fields' json specification file (fields.json)
     ```
     {
         "fields": [
             {
                 "name": "id",
                 "type": "integer",
                 "required": false
             },
             {
                 "name": "key",
                 "type": "string",
                 "required": true
             },
             {
                 "name": "record",
                 "type": "string",
                 "required": true
             },
             {
                 "name": "filename",
                 "type": "string",
                 "required": true
             },
             {
                 "name": "type",
                 "type": "string",
                 "required": true
             },
             {
                 "name": "receipt_date",
                 "type": "datetime",
                 "required": true
             },
             {
                 "name": "insert_date",
                 "type": "datetime",
                 "required": true
             }
         ]
     }
     ```

     - A schema 'conditions' json specification file (conditions.json)
     ```
     {
         "conditions": [
             {
                 "id": "1",
                 "type": "comparison",
                 "operator": ">=",
                 "field": "key",
                 "value": null
             },
             {
                 "id": "2",
                 "type": "comparison",
                 "operator": "<",
                 "field": "key",
                 "value": null
             },
             {
                 "id": "three",
                 "type": "composite",
                 "operator": "or",
                 "conditions": ["1","2","hi"]
             },
             {
                 "id": "hi",
                 "type": "comparison",
                 "operator": "=",
                 "field": "type",
                 "value": null
             },
             {
                 "id": "dummy",
                 "type": "comparison",
                 "operator": "=",
                 "field": "type",
                 "value": null
             },
             {
                 "id": "nested_join",
                 "type": "composite",
                 "operator": "and",
                 "conditions": ["dummy", "three"]
             }
         ]
     }
     ```

 - Containers
    - Containers are what define records as seen by the session target(s), either as the source (for gets) or destination (for puts) of some data (or both, for situations where there is two-way data flow). There can be multiple containers per session and fields defined in the schema can exist on more than one container. Containers conceptually represent different endpoints - e.g., different tables in a database, different databases, an email address, a directory, a file, a Kafka topic, etc. Because records passed in a session can be parsed into multiple containers, records or parts of records can be passed to multiple endpoints concurrently in a single request. Some containers may have relationships defined between them, and these are defined in the relationships spec attached to the containers spec. These relationships are evaluated when processing 'get' type requests in order to ensure that users always see returned records in the flat structure specified in the schema. Relationships are completely unnecessary in many situations if data is being pushed.

    - A container 'metadata' json specification file (metadata.json)
      ```
      {
          "metadata": {
              "name": "clisam",
              "type": "simple",
              "version": "1.0"
          }
      }
      ```

    - A container 'containers' json specification file (containers.json)
        ```
        {
            "containers": [
                {
                    "name": "testTable1",
                    "namespace": "/path/to/test.db",
                    "fields": ["key", "record", "filename", "type"]
                },
                {
                    "name": "testTable2",
                    "namespace": "/path/to/test2.db",
                    "fields": ["key", "type", "receipt_date", "insert_date"]
                }
            ]
        }
        ```

    - A container 'relationships' json specification file (relationships.json)
        ```
          {
              "relationships": [
                  {
                      "id": "test1",
                      "join": "left",
                      "parent": "testTable1",
                      "child": "testTable2",
                      "field": "key"
                  }
              ]
          }
        ```

 - Protocols are specialized, library specific implementations that translate between container record sets and some external system. These protocols are the parts of the system that call out to the external world, such as FTP servers, email clients, Kafka topics, or similar things. Protocols depend on the system that needs to be called out to, so they are more specialized plugin components than the schema or container parts of MessageAPI, which can generally be reused with almost any message type.

```

```

 Now that we've described the general topology, we will describe how a typical program will use this system using the API available.

All important parts of the MessageAPI model can be imported as interfaces. By convention, interfaces in MessageAPI begin with a capital I, followed by the word for the model component that the interface represents (no space). The most important interfaces of MessageAPI  that will probably be used are the ISession, IRequest, IRecord, and IResponse interfaces. Other interfaces that are useful are the IRejection, IField, IRelationship, and ICondition interfaces.

The overall strategy for using MessageAPI is simple:

Use the imported SessionFactory to create an ISession (pass the path to a specification like the one described above, or one in the package examples). Using the session object, create the kind of request you want to use (i.e., an add, get, remove, or update request). On any request type, create a record. The request record is type-contextual - in an 'add' or 'update' request, the record will contain a field set (based on the session spec) that can be filled with values that are to be inserted. 'update' requests can also use the record more generally, to update certain records when specified conditionals are met. In a 'get' request, the fields are the fields requested, and conditions may be used to specify conditions for retrieving response records.

All of the interface documentation should be found in the corresponding javadoc. If it's there, please add and make a pull request for the documentation if you know what the interface does, or file a bug and the documentation will be updated when possible.

To illustrate a typical use case, we will give a couple of examples - the first is adding some records, the second is getting some records.

Here is how a class would add records with conditions from a list of program records according to a message api spec.

```
package gov.noaa.messageapi.test;

import gov.noaa.messageapi.factories.SessionFactory;

import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IResponse;
import gov.noaa.messageapi.interfaces.IRejection;

import java.util.List;

public class addRecordsTest {

    private ISession session;

    public addRecordsTest(sessionSpec) {
        this.session = SessionFactory.create(sessionSpec);
    }

    public void addRecords(List<List<String>> recordsToAdd) {
        IRequest request = this.session.createAddRequest();
        for (List<String> recordToAdd: recordsToAdd) {
            IRecord record = request.createRecord();
            for (int i = 0; i < record.getFields().size(); i++) {
                record.setField(i, recordToAdd.get(i));
            }
        }
        IResponse response = this.session.submitRequest(request);
        while (!response.isComplete()) {}
        if (response.getRejections().size() > 0) {
            for (int j = 0; j < response.getRejections().size(); j++) {
                System.err.println("Rejected record because " + response.getRejections().get(j).getReasons());
            }
        }
    }
}
```
There is a lot going on in the above example, but it's all straightforward.

We first create a persistent session object based on a given spec when the class is loaded somewhere else. This session then has a defined schema, container set, and protocol which were all based on some runtime loaded text files. When the addRecords method is called with a bunch of string based records, an add request is then created from the session. The add request is then populated with records (using createRecord on the request) for every record that the user has. This is done by setting field values for the record - again, these fields are all in the declarative spec that was loaded when the session was loaded. In this case, record field values are set by index. It is also valid to set record field values by named fields - there are use cases for both approaches. In this case we are not setting any record conditions, but those are done the same way as fields (record.setCondition(conditionID, conditionValue)). Once we've finished populating our response with all of the records, we submit the request to the session and immediately receive a response. Requests are submitted asynchronously to sessions to mitigate any blocking and responses are returned immediately even if their work hasn't yet finished. This means the submitter can keep working if they want, and hold the request for later use, wait for it to complete by monitoring an isComplete method, or toss it away if there's no need to make sure of the response. When the response finally finishes, it will contain a set of rejections (if any) based on conditions or based on a failed protocol action. These rejections can be inspected individually for the record as well as reasons for the rejection.

### Configurations


### Instructions

## Installation and Deployment

Install MessageAPI by navigating to the cloned directory and running

```
make install
```

This will install MessageAPI to the local repository on disk.
The main MessageAPI package will only pull Log4J and SimpleJSON for use as dependencies,
while the package testing additionally requires Spock.

## Developer Guide

### Bugs

The package is in current, active development.
All bugs encountered should be reported to ryan.berkheimer@noaa.gov.

## License

Copyright © 2019 United States Government
