package gov.noaa.messageapi.endpoints;

import java.util.Map;
import java.util.List;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IRejection;
import gov.noaa.messageapi.interfaces.IEndpoint;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.IPacket;
import gov.noaa.messageapi.interfaces.IProtocolRecord;

import gov.noaa.messageapi.fields.DefaultField;
import gov.noaa.messageapi.records.schema.SchemaRecord;
import gov.noaa.messageapi.rejections.DefaultRejection;

/**
 * <h1>NativeEndpoint</h1> This is a wrapper class for endpoints that call into
 * native code held as binary libs through the <b>JNI (Java Native
 * Interface).</b>
 * <p>
 * This endpoint is designed so that native code doesn't have to provide an
 * additional Java wrapper. The native library code <b>will</b> have to be built
 * with a C wrapper that imports the MessageApiEndpoint.h header. A guide for building these
 * native libraries can be seen in the examples, and is facilitated by the use of the
 * provided makefile templates.
 * <p>
 * To make use of this endpoint, users are asked to configure three
 * properties in the manifest (2 required, 1 optional):
 * <p>
 * <b>native-library</b>(<i>required</i>, string) - corresponds to a fully
 * qualified path pointing to the native library binary. This is usually a .so,
 * .dll, or .jnilib, depending on operating system.
 * <p>
 * <b>default-fields</b>(<i>required</i>, array of field maps) - corresponds to
 * an array of field maps identical to schema field maps. Each field map specifies
 * an id, type, required, and optional value. These default fields are used when
 * creating a new Endpoint Record in native code.
 * <p>
 * <b>state-container</b>(<i>optional</i>, array of field maps) - corresponds to
 * an array of field maps identical to schema field maps. This should look just like
 * the default-fields above except the fields in the set are different.
 * If specified, this  property provides a persistent state container for use across multiple
 * submissions of the same request (e.g., holding a counter value across submissions).
 * <p>
 * <i>It should be noted that state-containers are persistent within a request, but unique
 * across separate requests.</i>
 * <p>
 * The state-container is held in the endpoint as a single record, and can be
 * manipulated in native code by calling set_state(id, value) or get_state(id)
 *  (where id refers to the field id).
 * <p>
 * <p>
 * <h3>Implementation</h3>
 * The specific API of methods in native code are dependent on the language (e.g, C, Fortran);
 * however, every native language will be initially wrapped by a JNI method in a C file that corresponds to the
 * 'process' method in this class, and all native processing related to use
 * of MessageAPI will operate on the passed jlong and the provided MessageApiEndpoint Library.
 * <p>
 * In this package, look at the src/c/test/DemoLibrary.c for a straightforward example on how to use this
 * library in native code.
 * <p>
 * This Endpoint works by first initializing the library during Endpoint construction, then creating
 * a C++ object using the calling instance and the passed protocolRecord during a process call,
 * returning the C++ instance cast as a long, and then passing this long to the native library for use as a jlong.
 * Within native code, the jlong is used within the MessageApiEndpoint library to communicate back and forth
 * with Java.
 * This process is designed to guarantee isolation of protocolRecords in native code.
 * <p>
 * <p>
 * <h3>Example Endpoint Connection Map Entry</h3>
 * <p>
 * {
 * <p>
 * "id": "native-conn-1",<p>
 * "collections": "*",<p>
 * "transformations": ["trans-1"],<p>
 * <p>
 * "constructor": {"native-library":
 * "/system/path/to/native/lib/libNativeLib.so",<p>
 * "default-fields": [{"id": "test", "type": "string", "required": false}],<p>
 * "state-container": [{"id": "counter", "type": "integer", "required": true, "value": 0}]}
 * <p>
 * }
 * 
 * @author Ryan Berkheimer
 */
public class NativeEndpoint extends BaseEndpoint implements IEndpoint {

    /**
     * Calls the process method implemented in C by the user's code. User code must
     * be templated to be wrapped inside a JNI call.
     * <p>
     * See DemoEndpointLibrary.c for an example on how all user libraries must be
     * wrapped, and what includes need to be added.
     * <p>
     * Generally, the following headers must be included in user native libs:
     * <p>
     * jni.h
     * <p>
     * messageapi_structs.h
     * <p>
     * MessageApiEndpointLib.h
     * <p>
     * gov_noaa_messageapi_endpoints_NativeEndpoint.h
     * 
     * @param nativeInstance
     * @return IPacket
     */
    private native IPacket process(long nativeInstance);
    private synchronized native long create(IProtocolRecord protocolRecord);
    private synchronized native void release(long instanceId);

    private IRecord stateContainer = null;
    private List<IField> defaultFields = null;

    public NativeEndpoint(Map<String, Object> parameters) {
        super(parameters);
        this.setDefaultFields(parameters);
        super.updateFields(parameters);
        this.setStateContainer(parameters);
        this.loadNativeLib((String)parameters.get("native-library"));
    }

    public void loadNativeLib(String nativeLibrary) {
        try {
            System.load(nativeLibrary);
        } catch (Exception e) {}
    }

    public IRecord getStateContainer() {
        return this.stateContainer;
    }

    public IPacket process(IProtocolRecord protocolRecord) {
        long nativeInstance = this.create(protocolRecord);
        IPacket nativePacket =  this.process(nativeInstance);
        this.release(nativeInstance);
        return nativePacket;
    }

    public List<IField> getDefaultFields() {
        return this.defaultFields;
    }

    @SuppressWarnings("unchecked")
    private void setDefaultFields(Map<String,Object> parameters) {
        try {
            List<Map<String,Object>> fieldMaps = (List<Map<String,Object>>)parameters.get("default-fields");
            this.defaultFields = fieldMaps.stream().map(fMap -> new DefaultField(fMap)).collect(Collectors.toList());
        } catch (Exception e) {
            throw new Error("Error parsing default-fields parameter in NativeEndpoint.");
        }
    }

    @SuppressWarnings("unchecked")
    private void setStateContainer(Map<String,Object> parameters) {
        try {
            List<Map<String, Object>> fieldMaps = (List<Map<String, Object>>) parameters.get("state-container");
            this.stateContainer = new SchemaRecord(fieldMaps.stream().map(fMap -> new DefaultField(fMap)).collect(Collectors.toList()));
        } catch (Exception e) {}
    }

    public IRejection createRejection(IRecord record) {
        return new DefaultRejection(record);
    }
    
}