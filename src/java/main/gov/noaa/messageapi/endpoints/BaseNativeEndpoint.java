package gov.noaa.messageapi.endpoints;

import java.util.Map;

import gov.noaa.messageapi.interfaces.IPacket;
import gov.noaa.messageapi.interfaces.IProtocolRecord;
import gov.noaa.messageapi.endpoints.BaseEndpoint;

/**
 * <h1>BaseNativeEndpoint</h1> This is essentially a <b>convenience base
 * class</b> for endpoints that call into native code held as binary libs
 * through the <b>JNI (Java Native Interface).</b>
 * <p>
 * To make use of this endpoint, extending classes should provide a fully
 * qualified path to the native resource as a string value corresponding to the
 * 'native-library' key.
 * <p>
 * Classes extending this base class are responsible for providing a list of
 * DefaultFields (in the getDefaultFields() method) that will serve as the
 * template for what fields exist when a native call to 'createRecord()' is made.
 * <p>
 * This base class handles the call into native code - native libraries using
 * this endpoint must be wrapped in a JNI entry point function called
 * 'nativeProcess' that returns an IPacket, which holds lists of IRecords and
 * IRejections.
 * <p>
 * Implementations of this endpoint will deal with and/or have access to three state
 * containers for multiple use case configurations:
 * <p>
 * 1. An Endpoint-Connection-global Packet that may be used to hold general,
 * stateful Records and/or Rejections of any field schema, that persists for
 * the life of the Endpoint Connection. This is useful for sharing some native
 * state between sequential streams of records in the same Endpoint Connection instance.
 * E.g. - A counter variable could be held in a native program, initialized at zero.
 * The first record stream to pass through the Endpoint Connection may update this counter
 * to 1. The second record stream to pass through the Endpoint Connection may update this
 * counter to 2.
 * <p>
 * 2. The data record stream (List<IRecord>) that is sent into the Endpoint Connection
 * is always an isolated state to itself. These records can be operated on with data pulled
 * out and processed natively as needed in an isolated state environment.
 * <p>
 * 3. The native method requires the return of a Packet that contains a list of
 * Records in the shape of the default Fields set by the extending Endpoint class,
 * and/or Rejections. This packet is isolated to the bounding stream invocation
 * (between the call into native and the endpoint return).
 * <p>
 * <p>
 * <h2>Required Constructor Parameters</h2>
 * <p>
 * <b>native-library</b>(string): the <i>fully qualified</i> path to the jni
 * library containing the native code this endpoint will call into.
 * <p>
 * <p>
 * 
 * <h3>Example Endpoint Connection Map Entry</h3>
 * <p>
 * {
 * <p>
 * "id": "native-conn-1",
 * <p>
 * "constructor": {"native-library":
 * "/system/path/to/native/lib/libNativeLib.so"}
 * <p>
 * } 
 * 
 * @author Ryan Berkheimer
 */
public abstract class BaseNativeEndpoint extends BaseEndpoint {

    private native IPacket processNativeInstance(long nativeInstance);
    private synchronized native long createNativeInstance(IProtocolRecord protocolRecord);
    private synchronized native void releaseNativeInstance(long instanceId);

    public BaseNativeEndpoint(Map<String, Object> parameters) {
        super(parameters);
        this.loadNativeLib((String)parameters.get("native-library"));
    }

    public void loadNativeLib(String nativeLibrary) {
        try {
            System.load(nativeLibrary);
        } catch (Exception e) {}
    }

    private IPacket process(IProtocolRecord protocolRecord) {
        System.out.println("Processing!!!");
        Long nativeInstance = this.createNativeInstance(protocolRecord);
        IPacket nativePacket =  this.processNativeInstance(nativeInstance);
        this.releaseNativeInstance(nativeInstance);
        return nativePacket;
    }
    
}