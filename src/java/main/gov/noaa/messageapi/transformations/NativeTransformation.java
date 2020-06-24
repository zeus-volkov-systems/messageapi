package gov.noaa.messageapi.transformations;

import java.util.Map;
import java.util.List;

import gov.noaa.messageapi.interfaces.ITransformation;
import gov.noaa.messageapi.interfaces.IRecord;

/**
 * <h1>NativeTransformation</h1> This is a wrapper class for transformations that call into
 * native code held as binary libs through the <b>JNI (Java Native
 * Interface).</b>
 * <p>
 * This transformation is designed so that native code doesn't have to provide an
 * additional Java wrapper. The native library code <b>will</b> have to be built
 * with a C wrapper that imports the Transformation.h header. A guide for building these
 * native libraries can be seen in the examples, and is facilitated by the use of the
 * provided makefile templates.
 * <p>
 * To make use of this transformation, users are asked to configure 1
 * property in the manifest:
 * <p>
 * <b>native-library</b>(<i>required</i>, string) - corresponds to a fully
 * qualified path pointing to the native library binary. This is usually a .so,
 * .dll, or .jnilib, depending on operating system.
 * <p>
 * 
 * @author Ryan Berkheimer
 */
public class NativeTransformation extends BaseTransformation implements ITransformation {

    private native List<IRecord> process(long nativeInstance);
    private synchronized native long create(Map<String,List<IRecord>> recordMap);
    private synchronized native void release(long instanceId);

    public NativeTransformation(Map<String,Object> params) {
        super(params);
        this.loadNativeLib((String)params.get("native-library"));
    }

    public void loadNativeLib(String nativeLibrary) {
        try {
            System.load(nativeLibrary);
        } catch (Exception e) {}
    }

    public List<IRecord> process(Map<String,List<IRecord>> recordMap) {
        long nativeInstance = this.create(recordMap);
        List<IRecord> transformedRecords =  this.process(nativeInstance);
        this.release(nativeInstance);
        return transformedRecords;
    }

}