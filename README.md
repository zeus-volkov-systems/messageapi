# MessageAPI

## Version

**0.0.10** (Pre-Release)

MessageAPI uses [Semantic Versioning 2.0.0](https://semver.org/) as its versioning strategy. The first official version will be released upon the implementation of the C and Fortran native APIs.


## Overview

MessageAPI is a structured-data-processing specification designed to allow the development of decomplected, transparent, easily understood, evolutionary, and highly configurable process oriented systems. MessageAPI does this by drawing a domain distinction between process structure (the 'Message' of MessageAPI) and data (the 'API' part) and then providing complimentary orthonormal bases that span each space. The structure and data domain definitions of MessageAPI are based on the principles of generic programming and designed using the language of Communicating Sequential Processes (CSP) in order to be easily picked up and understood by different audiences and users.

MessageAPI is ultimately a specification for data-process pipelines, but for practical purposes it is also an implementation that consists of a default **Session** that sets itself up using a declarative JSON specification of the MessageAPI structural model (through a manifest and parameter map), and then allows data to be formulated using the **Request** and **Response** APIs to process batch and/or streaming Requests asynchronously. In the provided Session implementation, Requests terminate on **Endpoints** which can be thought of as defining the terminus of a given computation. Endpoints are provided an interface and an abstract base class to extend. Endpoints have access to the data passed through MessageAPI as **Records**, which can be held in any number of *containers* - such as **Collections**, **Classifiers**, and **Transformations**. 

Collections are Record set containers, Classfiers are potentially cross-Collection Record containers, and Transformations are containers of Records which apply some manipulation on other containers (including other Transformations). In contrast with Endpoints, Transformations are more open ended, providing an interface to implement. Transformations exhibit lazy processing behavior that is only executed when they are referred to in an **Endpoint**. In MessageAPI, Transformations always get their own copies of inputs, making them easy to use without worrying about shared system state. 

*Caveat - if users provide their own Record Field 'types' (i.e., other than string, integer, float, etc.) that are some complex object, to make this guarantee, users must provide and call a 'deep copy' on each object in the record Field. Only standard types in the shipped default implementation guarantee immutable Transformations.*

By providing a shared mechanism for batch and stream operation, the default Session of MessageAPI is extremely flexible and allows code reuse for both modes. In the Default MessageAPI Session, streaming behavior can be accomplished by submitting a Request, updating its record with a new value, and resubmitting the same Request - a new response is generated for every Request, but they return asynchronously, so no blocking occurs. As Endpoints only initialize per-Request, endpoints also share state in this operation - this makes it possible to have long running endpoints (like other MessageAPI Sessions). Batch mode can be accomplished by creating a new Request for every new set of data - in this mode, Endpoints are reinitialized based on Session parameters, and hold independent state.

There are tests included in the package (including example Transformations and Endpoints) that demonstrate the use of MessageAPI for simple but ubiquitous use cases (like loading records from files). In one of the included tests, a ~80k line variable-byte-line file is read in as individual line records, each then holding the line number, value, container source, container type, and originating file name - in around 3/10ths of a second. This Endpoint is configurable enough to allow adjustment of Record Fields, and which Collections, Transformations, and/or Classifiers contain Files, entirely from configuration. While MessageAPI obviously isn't computationally 'free' (i.e., it can't compete with a straight buffer read of lines into an array-list) we are of the opinion that this test demonstrates that the benefits of MessageAPI, such as its extreme flexibility, code reuse potential, configurable control, and metadata inclusion, outweigh the overhead incurred in performance.

## Motivation

The Scientific Software Reengineering/Rearchitecting Group (SSRG) at NOAA NCEI is tasked with taking large, long-lived, evolutionary, polyglot, mission-critical, scientific research projects and/or systems, analyzing them through a lens of long term sustainability and security, and then reorienting them toward those general goals, while rejuvenating them to integrate with up to date and/or future organizational trends.

This process usually involves integrating with existing development teams, defining the project surface, performing an overall maturity assessment, performing individual process assessments on project subsystems (according to general principles of process performance systems like CMMI), and then (based on the assessment results) iteratively improving the overall system (this process is called 'Rejuvenation' at NCEI) - generally in order of testability, reliability, changeability, efficiency, security, maintainability, portability, and reusability (the SQALE method).

As the SSRG Rejuvenation program itself has matured, organizational patterns in the program's constraint parameters (character of systems under study, NCEI infrastructure and trends) have emerged. Based on these patterns, SSRG has endeavored to create and maintain an 'SSRG Toolbox' - a collection of generalized tools that standardize one or more aspects of the Rejuvenation process (assessment, testing, development, deployment). Some tools in the toolbox are commercial and/or organizational tools like Docker, Git, Jenkins, Slack, Understand, valgrind, gdb, JIRA, Google Docs - and some are custom tools like the FortranCommons (comprised of fortran language unit tests and properties, written in fortran), Harness (a data-oriented testing framework, written in python), and TaskAPI (a polyglot declarative workflow abstraction, written in java).

The TaskAPI tool was initially developed to replace Bash as the 'glue' for ASOS Ingest jobs, and was subsequently split from that project and made generic enough for any distributed computation project. TaskAPI provides distributed workflow parallelization capabilities, job control, declarative task definition, and logging standardization for the 3 language (fortran, java, c) ASOS Ingest system. It was also designed to promote iterative system improvement - allowing a quick load of existing project code into TaskAPI, and then allowing monolithic job tasks to be broken up into smaller tasks (and corresponding TaskAPI tasks) by factoring code over time. This iterative improvement and the end goal is still an ideal, but there is often a need for intraprocess tasks (e.g., a deeply nested x = system('ls -l'), or system('mail -s 'missing data!' bigArrayContents')) to be replaced first, or instead of, whole scale task splitting. 

TaskAPI does allow for arbitrary data to be passed between fortran, c, and java through a map structure, but the map changes are only communicated during native method invocation or return. In the case of ASOS Ingest it was also discovered that there was widespread use of a binary Fortran Direct Access file storage package throughout. This Direct Access storage turned out to be the primary storage container for the intermediary Low Resolution data format (CLISAM) which serves as the basis for almost all LowRes derived products - including ISD, SODGraph, HPD, and US-CLIMAT, among others. Removal of the direct access storage media of CLISAM is a major priority for several reasons, including - the format was shown to be brittle during operating system port; the data would be much more useful and easier to use organizationally if it were stored in something like a Kafka topic.

All of these use cases added up to the need for a new tool to provide generalized intraprocess communication. This is what MessageAPI was primarily designed to do - replace targeted intraprocess communication in native languages with a standardized, stable, general, flexible, and portable mechanism. Due to type system differences across languages, the system would have to 

- have a small, static API (any message would need to be transferred through a small set of bounded API methods)
- able to handle inward or outward directed messages
- be able to work in a non-blocking or blocking fashion

Due to the nature of the Rejuvenation work of SSRG, the tool would also have to conform to and promote SQALE standards. These requirements were interpreted to mean the system should

- be highly configurable outside of code
- be integratable in a potentially multi-threaded and/or multiprocess environment
- be generic enough to handle unknown use cases
- allow easy testing without complicated mocking
- be stable enough to be reliable for decades or more
- be extensible/changeable enough to be replaced if organizational standards changed
- be efficient in processing
- conform to organizational security standards
- be reusable
- be understandable to current system developers and future maintainers

All of these requirements added up to creating a specification first, and then writing a couple of implementations. Once the specification was designed and written, it became apparent that MessageAPI could handle the type of messages it was designed for, and potentially be extended for other use cases - distributed computation, system deployments, requirements management, versioning, etc.

## Philosophy

MessageAPI is designed with the belief that all processes are fundamentally simple, similar, and understandable. MessageAPI was designed to expose these process characteristics by the use of a simple (in the decomplected sense) information model. 

Every part of how a MessageAPI defined process will play out, down to the implementation classes, is laid bare in a pair of text based maps - one for the manifest, and one for the parameters. These maps makes trivial work out of reasoning about how a program is structured and will run before it is ever executed. 

The primary dimensions of MessageAPI are held to three - A **Schema** holds a flat map of all fields and conditions a user will interact with; a **Container** defines how fields will be factored and held in collections, classifications, and transformations; and a **Protocol** defines Endpoints and connections to them, which define where containers of records will go. All of these parts of a Message are viewable and configurable without touching code. Users write and share their own custom Endpoints and Transformations, which are then specified in the map. 

Everything that passes data in MessageAPI consumes and produces the same object type - the record. The manifests are used in code by creating a session based on them - and then using a stable API to create a request, add records, set field and/or condition values, and then submit, which immediately returns an async response. The response will hold its own records and rejections, and eventually get an 'isComplete' flag. That's the entirety of the API surface. Everything else depends on the Manifest.

MessageAPI is designed to be capable of passing any message content - objects, database entries, emails, etc., to/through anywhere - database tables, inboxes, s3 buckets, ftp, smtp, kafka, files, directories etc.

The benefits of using MessageAPI are its extreme schema flexibility, potential for tool decoupling and transport optimization, API standardization across all messaging, and self documentation through an information model.

It's important to point out that even though it's called MessageAPI, the provided implementations do not replace message tools like ActiveMQ, RabbitMQ, Spark, or Storm. Really, no tools are 'replaced' by this one. MessageAPI is fundamentally a process specification, and the provided implementation is a small (3MB total package size) universal connector. This means that other messaging systems could of course be used with MessageAPI - linking response steps, serving as input or output queues, or transformation steps. Even MessageAPI sessions can be endpoints for MessageAPI sessions.

## Package Contents

This package includes the MessageAPI specification as a set of interfaces, useful implementations that can perform batch and stream publication/consumption, and several tests that demonstrate common data processing tasks to provide an idea on how to build systems. The Java part of the core MessageAPI implementation is written almost entirely in Java8/9+ core, taking advantage of the Java Streams and Flow packages, with only one external dependency - a JSON parser - due to the lack of a core Java version. Similarly, APIs provided for any other languages found in this package (currently planned are C, Fortran, and CPython) - are written in their respective core languages. Endpoints and Transformations are left to the joy of the user and their domain.

### Description

Using MessageAPI means taking a data-messaging process, defining the process alphabet in terms of fields and conditions, determining how those fields are contained as different record permutations (including any transformations or conditions that affect that containment), and determining what to do with the records. All this information is then laid out in the session manifest and parameter map, and then data is moved through the initialized session by submitting records as either discrete requests, or resubmitting new records as a stream on the same request.

As previously described, in the provided implementation of the DefaultSession, records can be moved through the system in batch by using separate requests, or in stream by reusing the same request. When streaming over the same request, endpoints have a shared state over submissions.

The MessageAPI information model manifest is completely pluggable and is read when specifically referenced at runtime in code (i.e., ISession s = new Session('manifest.json')). This allows targeted improvements or modifications of the standard. Want to change the containers to ship somewhere else? Build Docker containers? Make Requests enforce always-batch behavior? Change the container plugin, or another plugin, and reuse the rest.

The complete pluggability of MessageAPI also provides another powerful potential - creation of Sessions at-a-distance. This opens the MessageAPI system up for complete and total automation by things like REST services, driver programs, GUI's, etc.

The default MessageAPI session provides a standard topology that will suit many messaging tasks (either publishing or consuming oriented, batch or stream oriented), along with providing a matching set of basic plugins. The provided implementations are well suited for individual or distributed use. For example, a MessageAPI session could be wrapped as a Kafka consumer, deployed as a single runtime pod in Kubernetes as a consumer group, started up, and then fed records coming from a service. Or a session could be used intra-process to send emails to different groups based on different conditions. Or, as recently discovered, MessageAPI could serve as the in-core engine for custom Apache NiFi processors. There are a lot of varied uses.

The following is an example of a DefaultSession manifest:

```
{
    "plugin": "gov.noaa.messageapi.sessions.DefaultSession",
    "constructor": {
        "schema": {
            "plugin": "gov.noaa.messageapi.schemas.DefaultSchema",
            "constructor": {
                "metadata": "{}/resources/test/metadata/file-reader/schema.json",
                "fields": "{}/resources/test/file-reader/parameters.json",
                "conditions": {
                    "map": "{}/resources/test/file-reader/parameters.json",
                    "factory": "gov.noaa.messageapi.factories.SimpleConditionFactory"
                }
            }
        },
        "container": {
            "plugin": "gov.noaa.messageapi.containers.DefaultContainer",
            "constructor": {
                "metadata": "{}/resources/test/metadata/file-reader/container.json",
                "collections": "{}/resources/test/file-reader/parameters.json",
                "transformations": {
                    "map": "{}/resources/test/file-reader/parameters.json",
                    "factory": "gov.noaa.messageapi.test.factories.transformations.FileReaderFactory"
                }
            }
        },
        "protocol": {
            "plugin": "gov.noaa.messageapi.protocols.DefaultProtocol",
            "constructor": {
                "metadata": "{}/resources/test/metadata/file-reader/protocol.json",
                "endpoints": [{
                        "plugin": "gov.noaa.messageapi.test.endpoints.InMemoryFileReader",
                        "connections": "{}/resources/test/file-reader/parameters.json"
                    }]
            }
        }
    }
}
```

The general pattern in a manifest is to declare a key with the class as the plugin, and then provide another map that holds constructor parameters. The specification for MessageAPI consists of 

- A **Session**, which holds the primary **Schema**, **Container**, and **Protocol** dimensions
- A **Schema**, which defines all the **Fields** and **Conditions** (optional) a user will interact with for each **Record**
- A **Container**, which defines any way a **Field** set will be contained - **Records** (**Field** and **Condition** sets) are each factored into **Collections**, **Collections** hold arbitrary **Classifiers** (optional), and **Transformations** (optional) can refer to **Collections**, **Classifiers**, **Transformations**, or entire **Records** (every **Collection** that a specific **Record** was factored into).
- A **Protocol**, which defines the Endpoints that record containers are sent to for processing. There can be multiple Endpoints per manifest, and multiple connections per session. Each Endpoint connection will hold and manage state independently of each other, in terms of the Request logic previously described (as far as batch vs streaming).

In more descriptive detail, Sessions are the primary abstraction in MessageAPI. Sessions in turn consist of Schema, Container, and Protocol abstractions, and each of these has its own set of properties that must/can be specified. Notice that in the example spec, any key labeled "plugin" points to a class. These classes are what are read at runtime (when the spec itself is referenced in the code). Anything found within the "constructor" map is then used by the class to build itself.

So, for example, if the above spec is taken literally, when it is used in the code, an instance of the "class.namespace.SessionPluginClass" class is loaded with the corresponding "constructor" map passed in as the constructor argument. This in turn kicks off the system to read the Schema, Container, and Protocol classes and create those using their own constructor maps. The information found in the associated key-values (usually referencing an underlying JSON map, with the exception being the "operators" key in the schema constructor) will be read and parsed at that time to build the component and ultimately the session.

Note that both Conditions and Transformations specify 'factories'. These factories have key/value associations in switch statements that return (either a Condition or Transformation) depending on the key in the parameter map. This is done for different reasons in each context - in the case of Conditions, this was done to both prevent the parameter map from becoming too large, and provide a way for Conditions to be easily extended to arbitrary user types. In the case of Transformations, this was done to ensure a level of security in what code may be executed in performing data manipulation. Because MessageAPI uses reflection to build the system, this pattern ensures only code compiled on the classpath can be run as a transformation.

*Notice that in this map, the **Fields, Conditions, Collections, Transformations,** and **Connections** all refer to the same 'parameters' map:*
***Also note - the only 'required' things are 'fields', 'collections', and 'connections'. If the other parts aren't needed (conditions/transformations/metadata), don't reference them in the manifest and don't include them in the parameters.***
```
{
    "fields": [{"id": "file-path",
                "type": "string",
                "required": true}],
    "conditions": [{"id": "is-relative-path",
                    "type": "comparison",
                    "operator": "contains",
                    "field": "file-path",
                    "value": "{}"}],
    "collections": [{"id": "coll-1",
                     "classifiers": {},
                     "fields": ["file-path"],
                     "conditions": ["is-relative-path"]}],
    "transformations": [{"id": "trans-1",
                         "operator": "fix-relative-paths",
                         "constructor": {"transform-key": "file-collection"},
                         "records": {"file-collection": {"COLLECTION": "coll-1"}},
                         "fields": ["file-path"]}],
    "connections": [{"id": "conn-1",
                     "transformations": ["trans-1"],
                     "constructor": {"file-fields": "file-path"},
                     "fields" : ["value","number", "length"]}]
}

```

*These parameters can be split up into separate files or held together like they are here. Each of these domain concepts will be explored in more depth further down.* 

Once built, this session is then in memory and can be reused as often as necessary (subsequent requests do deep-copies of loaded session components). MessageAPI trades initial speed of compile-time class construction for the flexibility and declarative nature of doing it at runtime (although the initial bootstrapping is generally very fast, as the provided MessageAPI implementation footprint is small). *Sessions can, for example, be passed as objects to different machines, different thread groups, etc. and used to construct brand new, guaranteed-isolated requests from the same template.*

Each session component is considered a fundamental and loosely orthogonal dimension of its parent. Every message session, no matter what the type, can be created by specifying the three primary dimensions (Schema, Container, and Protocol), and this concept is what allows MessageAPI to provide a powerful and lightweight abstraction on top of arbitrary messages. Each of these dimensions has its own particular properties which define it. All also include a catchall and optional 'metadata' property for storage of other useful self-documenting information, such as version or identifying labels.

#### MessageAPI Session Topology

Here we describe the three dimensions of a MessageAPI session:

##### Schemas

Schemas are what define records as seen by the Session holder. This is the part of the topology which defines what fields a record will have, any conditions on those fields, and an operator factory class that provides methods on evaluating fields against conditions (conditions may contain arbitrary logic).

Here we see that Schemas refer to a plugin class, and the constructor used to create the plugin.

```
"schema": {
    "plugin": "gov.noaa.messageapi.schemas.DefaultSchema",
    "constructor": {
        "metadata": "{}/resources/test/metadata/file-reader/schema.json",
        "fields": "{}/resources/test/file-reader/parameters.json",
        "conditions": {
            "map": "{}/resources/test/file-reader/parameters.json",
            "factory": "gov.noaa.messageapi.factories.SimpleConditionFactory"
        }
    }
```

Schemas contain **Fields** (required), **Conditions** (optional), and **MetaData** (optional). 

###### Metadata

The MetaData becomes part of the definition when the manifest is loaded, and can be accessed from the endpoint layer this allows for interaction with mutable endpoint schemas when field sets change over time (for example, Avro storage in Kafka).

```
{
    "metadata": {
        "id": "the-schema-id",
        "version": 1.0,
        "classifiers": {},
        "description": null
    }
}
```

Metadata is loaded from map to a Metadata object for convenience, so that API methods can sanely get different properties. Metadata, along with every other user-available concept in MessageAPI, is also programmed against an interface, so the available methods are available in the constructed groovydocs to peruse for that particular interface.

###### Field Sets

A Schema Field set is a flat set of field definitions - for example, software that wants to pass email messages through MessageAPI could have a field set of 'address, subject, body'. (Alternatively, the fields could just be key/value pairs of arbitrary content, and the 'target/subject' could be constructor parameters.) Schema Field sets should hold every Field in any collection that the user will use. So if there are two lists of two different record types feeding into a MessageAPI process, with different domains, fields from both lists should both be declared in the Schema Field map. The containment of different Field sets can be specified at the container level as Collections (ie, create two collections at the container level and hold fields for one set in the first container, and fields from the other in the second container). This pattern allows a clearly defined global field set while allowing an arbitrary number of record types to be part of a given processing action.

In the provided schema class, fields need to be provided with a 'name', 'type', and 'required' properties.

The 'name' must be unique in the schema, the 'type' must be understood by the parsing class, and the 'required' must be a boolean. If a field is required but not provided, that record will be immediately rejected on request submission. 

In the provided implementation, the types understood by the system (for use by conditions) are 'string', 'float', 'double', 'integer', 'datetime', and 'boolean'. Without adjustment, other types can be handled without issue, although to use the condition system, additional types should be added. This can be done easily by adjusting the ConditionFactory.

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


###### Condition Sets

Conditions can be set on fields that qualify records when passed in, serving as a potentially powerful filtering tool. In the provided default plugin, conditions must specify at least a unique id, a type, and an operator. Conditions that are to be used in filtering must be valued on individual records. Conditions are also provided on a whole-request basis - to be used in containerization of records. In this case, conditions can be given values when 

There are two condition types in the provided implementation  - composite and comparison.

Comparison type conditions are direct comparisons (things like equivalency, greater than, contains, etc.) while composite conditions reference other conditions and specify either an 'and' or an 'or' operator. This allows multiple conditions to be nested, referenced by their IDs.

Composite conditions can also include other composite conditions and will be unpacked and applied recursively, in whatever context is specified by the session type in the manifest. The only global restriction for the given implementation is that conditions cannot be self referential (no infinite loops).


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
            "id": "relative-path",
            "type": "comparison",
            "operator": "contains"
            "field": "filename",
            "value": "{}"
        },
        {
            "id": "nested_join",
            "type": "composite",
            "operator": "and",
            "conditions": ["relative-path", "three"]
        }
    ]
}
```

##### Containers

The **Container** dimension of a MessageAPI Session represents groupings of Schema information (Fields and/or Conditions). Because all Records are defined from a single flat schema, Containers allow records to specify how they are factored/binned, and then additionally given classifier information and computational specification. In the Session manifest, like the other two dimensions, the Container contains a plugin and a constructor. The constructor defines where to find 

- metadata (optional)
- collections (required)
- transformations (optional)

Transformations, if specified, must specify both a map of connections, and a factory. The factory contains key/value pairs of transformation handles and transformation classes, each of which implement the ITransformation interface. The map property provides the location for a list of transformations, described further in this README.

```
"container": {
    "plugin": "gov.noaa.messageapi.containers.DefaultContainer",
    "constructor": {
        "metadata": "{}/resources/test/metadata/file-reader/container.json",
        "collections": "{}/resources/test/file-reader/parameters.json",
        "transformations": {
            "map": "{}/resources/test/file-reader/parameters.json",
            "factory": "gov.noaa.messageapi.test.factories.transformations.FileReaderFactory"
        }
    }
}
```

There are three types of container groupings provided by the default MessageAPI implementation - **Collections**, **Classifiers**, and **Transformations**. 



###### Collections

- **Collections** are the most basic containers, and are the only type required in a session manifest. Collections specify a session-global unique id, a list of fields that belong to them, a list of conditions that must be met before a record will build into one, and optionally, a map of classifiers (keys with arbitrary values). When a request is submitted, the list of records attached to the request at submission time is mapped to collections. Each record individually is broken into whatever collections are specified. These collections are immutable - they can overlap fields, even containing the same identical field sets, and each one will get its own independent copy. After grouping, collections derived from the same Record are still tied together by a separate UUID that is attached to each.

```
{
    "collections": [
        {
            "id": "required-fields",
            "fields": ["boolean-required", "float-required", "double-required", "integer-required", "string-required", "datetime-required"],
            "conditions": ["cond-1", "cond-2"]
        },
        {
            "id": "optional-fields",
            "fields": ["boolean-optional", "float-optional", "double-optional", "integer-optional", "string-optional", "datetime-optional"]
        },
        {
            "id": "mix-and-match",
            "fields": ["string-required", "string-optional", "datetime-required"]
        }
    ]
}
```


###### Classifiers

- **Classifiers** are metadata containers, in that they are not specified directly in the Session manifest, but are attached to Collections. A single Classifier can be attached to different Collections, and this mechanism provides a guarantee of the ability to arbitrarily group Records in MessageAPI. These Classifier labels are then available separately for use in Transformations and/or Endpoints - retrieving a Classifier in an Endpoint or using it as an input of a Transformation will retrieve all records from all collections labeled with that Classifier, no matter which Collection it lives in. Determination of the potential utility of this mechanism is left to the user.

```
{
    "collections": [
        {
            "id": "required-fields",
            "classifiers": {"namespace": "condition-test"},
            "fields": ["boolean-required", "float-required", "double-required", "integer-required", "string-required", "datetime-required"],
            "conditions": ["cond-1", "cond-2"]
        },
        {
            "id": "optional-fields",
            "classifiers": {"namespace": "condition-test"},
            "fields": ["boolean-optional", "float-optional", "double-optional", "integer-optional", "string-optional", "datetime-optional"]
        },
        {
            "id": "mix-and-match",
            "classifiers": {"namespace": "condition-test"},
            "fields": ["string-required", "string-optional", "datetime-required"]
        }
    ]
}
```


###### Transformations

- **Transformations** are computational containers. They are an optional component of MessageAPI. Transformations act as instances of immutable functions that can hold global, configurable constructor/initialization parameters, use other arbitrary named containers as arguments in a process function, return a list of records, and list the fields that each record will provide in a 'fields' map entry. Transformations are always immutable, executed lazily (only when called in an Endpoint), and always operate on and produce lists of records. 

The 'records' entry on the Transformation map itself holds a map of named parameter keys that correspond to values describing what type of container and the id of that container to use as that particular input. For example, in the following Transformation map, the first Transformation is called 'join-test'. The Transformation has an operator of 'join', which corresponds to a java class in the TransformationFactory listed in the Session manifest. This Transformation provides a constructor map containing two keys, 'join_field' and 'collection_field', both which specify constants that are set in the Transformation when it is initialized. 

The 'join-test' Transformation defines three parameters in its process method map - 'parent', 'child', and 'other'. Each of these corresponds to a different container - when used in the Transformation, the 'parent' parameter will provide a list of all records contained by the 'namespace=condition-test' classifier; the 'child' parameter will provide a list of records contained by the 'mix-and-match' collection; and the 'other' parameter contains a special case - the UUID - which will provide every collection for a given UUID, and map the Transformation to every UUID, and all returned records for every UUID in this Transformation will be merged on return. The use of UUID as a Transformation record parameter is a special case, and due to its mapping ability, limits its use to once per Transformation.

The 'join-test' Transformation also specifies that it will return the 'key', 'record', filename', 'type', and 'mix-and-match' fields. This is useful for knowing in a configurable way what fields to expect for use in other Transformations or Endpoints. However, at this time, there is no restriction on what fields a Transformation can return.

In the second Transformation, the 'reduce-list' record parameter will provide all records contained by the 'join-test' Transformation. In practice, for the provided default MessageAPI implementation, when the 'reduce-test' Transformation is invoked, it will first invoke the 'join-test' transformation and used those returned records as input for its 'reduce-list' parameter. Transformations are always evaluated lazily in this manner, whereby they are only invoked when called, and chained/referenced transformations are similarly only invoked to provide an input to their parent when invoked.

It is the view of the package authors that Transformations hold computational tasks and List manipulations - Transformations are good places for things like Joins, Unions, Filters, etc. Any type of computation is technically allowed in a Transformation, but external behavior is better suited for taking place in Endpoints, which are specifically designed with external communication in mind.

```
{
    "transformations": [
    {
        "id": "join-test",
        "operator": "join",
        "constructor": {"join_field": "key",
                        "collection_field": "mix-and-match"},
        "records": {"parent": {"CLASSIFIER": ["namespace", "condition-test"]},
                    "child":  {"COLLECTION": "mix-and-match"},
                    "other": "UUID"},
        "fields": ["key", "record", "filename", "type", "mix-and-match"]
    },
    {
        "id": "reduce-test",
        "operator": "reduce-sum",
        "constructor": {"reduce-field": "mix-and-match",
                        "reduce-target": "mix-and-match-reduction"},
        "records": {"reduce-list" : {"TRANSFORMATION": "join-test"}},
        "fields": ["key", "mix-and-match-reduction"]
    }]
}
```


###### Metadata

Additionally, like **Schemas** and **Protocols**, **Containers** may provide a metadata map in the Session manifest. This metadata map is formed identically to the other metadata maps.

```
{
    "metadata": {
        "id": "condition-test",
        "version": "1.0",
        "classifiers": {},
        "description": null
    }
}
```

##### Protocols

The Protocol dimension of MessageAPI represents the boundary of a MessageAPI process. The Protocol holds **Endpoints** and Endpoint **Connections**. The Protocol is the part of the MessageAPI that grabs records from Containers, communicates out of process, and returns a data Packet containing its own Record and/or Rejection lists back to the original caller, to be merged with all other Records and Rejections retrieved from other Endpoints. Endpoints can do anything with Records - send emails, push to FTP or object storage, retrieve content from a Kafka topic, run unit tests, etc. 

Protocol layer can hold arbitrary Endpoints, and arbitrary Connections for every endpoint. Each Endpoint Connection has its own isolated state during computation, and the specific containers it has access to, along with any initialization parameters, are specified out of code in the configuration.



Here is an example of a connections map used by an email type endpoint:

```
{
    "connections": [
        {
            "id": "1",
            "bins": ["*"],
            "parameters": {
                "sender": "me@test.com",
                "password": "testpassword1234",
                "receivers": ["recipient1@me.gov", "recipient2@me.edu"]
            }
        },
        {
            "id": "2",
            "bins": ["only_secret_bins1"],
            "parameters": {
                "sender": "jackson.pollock@cia.org",
                "password": "passpass64",
                "receivers": ["template1@org.org", "template2@org.org"]
            }
        }
    ]
}
```

Note that there's a special character "*" that allows specification of all bins from the container layer.

#### MessageAPI API and Examples

Now that we've described the general topology, we will describe how a typical program will use this system using the API available.

All important parts of the MessageAPI model can be imported as interfaces. By convention, interfaces in MessageAPI begin with a capital I, followed by the word for the model component that the interface represents (no space). The most important interfaces of MessageAPI  that will probably be used are the ISession, IRequest, IRecord, and IResponse interfaces. Other interfaces that are useful are the IRejection, IField, IRelationship, and ICondition interfaces.

The overall strategy for using MessageAPI is simple:

Use the imported SessionFactory to create an ISession (pass the path to a specification like the one described above, or one in the package examples). Using the session object, create a request - the request type was baked into the session on session creation, so it's already set in memory (for example , a publish request in a publish session, or consume request in a consume session). On the request, create record(s) that will be sent to the endpoint.

Once the records are set, call submit on the request. This submission immediately creates a duplicate of the entire request inside a response object, and then returns. All logic is processed against that request copy and its parent response asynchronously. Inside a response, protocols can produce response records and response rejections.

This design is thread safe, because when submitted, a copy is operated on, and the original request is immutable. This design is also flexible, being able to handle throwaway results (just don't consume the IResponse), all-at-once-returns (like sql calls that return a bunch of data), or over-time-returns (subscription type returns). For example, to wait for all the data, just put a while(!response.isComplete()){}; before any further logic in the program. Or keep the response inline, and continue to pull records down the line over time, if it's a dynamic/streaming endpoint.

##### API Examples
To illustrate a typical use case, we will give a couple of examples - the first is adding some records, the second is getting some records.

###### Adding Records
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

        IRequest request = this.session.createRequest();

        recordsToAdd.stream().forEach(recordToAdd -> {
            for (int i = 0; i < record.getFields().size(); i++) {
                record.setField(i, recordToAdd.get(i));
            }
        });

        IResponse response = request.submit();

        while (!response.isComplete()) {}

        if (response.getRejections().size() > 0) {
            for (int j = 0; j < response.getRejections().size(); j++) {
                System.err.println("Rejected record because " + response.getRejections().get(j).getReasons());
            }
        } else {
            response.getRecords().stream().forEach(record -> {
                System.out.println(record.getFields());
            });
        }
    }
}
```

There is a lot going on in the above example, but it's all straightforward.

We first create a persistent session object based on a given spec when the example class is instantiated somewhere else. This session that is created then immediately has a concretely-defined schema, container set, and protocol which were all based on some runtime loaded text files. These are now in memory, and can be quickly grabbed and reused on any children requests based on this session.

When the addRecords method above is called with a list of string based records, a request is created from the session. The request is then populated with records (using createRecord on the request) for every record that the user has. This is done by setting field values for the record - again, these fields are all in the declarative spec that was loaded when the session was loaded.

In this case, record field values are set by index. It is also valid to set record field values by named fields - there are use cases for both approaches. In this case we are not setting any record conditions, but those are done the same way as fields (record.setCondition(conditionID, conditionValue)).

Once we've finished populating our response with all of the records, we submit the request to the session and immediately receive a response. Requests are submitted asynchronously and copied-on-submit to mitigate any blocking and responses or mutability issues and are returned immediately even if their work hasn't yet finished. This means the submitter can keep working if they want, and hold the request for later use, wait for it to complete by monitoring an isComplete method, or toss it away if there's no need to make sure of the response.

When the response finally finishes, it will contain a set of final rejections (if any) based on conditions or based on a failed protocol action and final records. The rejections can be inspected individually for the record as well as reasons for the rejection, and the records can be consumed according to the original defined schema.

Because requests contain a copy of the session variables which created them, they can always be the source of truth for any properties that might be inspected later. Schema, Container, Protocol information can always be inspected later, and the user should be confident in knowing that this COC for this data remained immutable since session-birth.

### Configurations


### Instructions

## Installation and Deployment

At the time of this writing, MessageAPI (0.0.10-PRERELEASE) was built using OpenJDK 11.0.3 with gradle 5.4.1.

There was a breaking change between older versions of gradle and the 5 series, and a relative path resolution
method was updated to accommodate this change. If building from scratch, the gradle version must be upgraded to 5.4.1+.

Older versions of the JDK, down to 1.8, still work for this build, although that isn't guaranteed going forward.

Once these two system dependencies are met, this package can be run with tests by running 'gradle' from the package root.


```
gradle
```

This will install MessageAPI to the local repository as an UberJAR on disk (usually in ~/.m2).
Beyond the core Java library, the main MessageAPI package uses only SimpleJSON as a dependency.

Other dependencies are installed for the purposes of running tests, including Groovy, Spock, SLF4J, and SpockReports.

## Developer Guide

In addition to reading issue, tag, and push history in the git repository, developers may refer to the more detailed [developer work log history](./DeveloperWorkLog.md). This document outlines features currently and previously under focus, providing motivations, descriptions, design behaviors, and justifications.

### Bugs

The package is in current, active development.
All bugs encountered should be reported to ryan.berkheimer@noaa.gov.

## License

THIS SOFTWARE AND ITS DOCUMENTATION ARE CONSIDERED TO BE IN THE PUBLIC
DOMAIN AND THUS ARE AVAILABLE FOR UNRESTRICTED PUBLIC USE. THEY ARE
FURNISHED "AS IS." THE AUTHORS, THE UNITED STATES GOVERNMENT, ITS
INSTRUMENTALITIES, OFFICERS, EMPLOYEES, AND AGENTS MAKE NO WARRANTY,
EXPRESS OR IMPLIED, AS TO THE USEFULNESS OF THE SOFTWARE AND
DOCUMENTATION FOR ANY PURPOSE. THEY ASSUME NO RESPONSIBILITY (1) FOR
THE USE OF THE SOFTWARE AND DOCUMENTATION; OR (2) TO PROVIDE TECHNICAL
SUPPORT TO USERS.
