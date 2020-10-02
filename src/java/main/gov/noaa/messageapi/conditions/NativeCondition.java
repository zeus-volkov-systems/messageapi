package gov.noaa.messageapi.conditions;

import java.util.Map;

import gov.noaa.messageapi.interfaces.ICondition;
import gov.noaa.messageapi.interfaces.IConditionOperator;
import gov.noaa.messageapi.interfaces.IField;

/**
 * <h1>NativeCondition</h1> This is a wrapper class for condition operators that call into
 * native code held as binary libs through the <b>JNI (Java Native
 * Interface).</b>
 * <p>
 * This condition operator is designed so that native conditions written by the user don't have to provide an
 * additional Java wrapper. The native library code <b>will</b> have to be built
 * with a C wrapper that imports the NativeCondition.h header. A guide for building these
 * native libraries can be seen in the examples, and is facilitated by the use of the
 * provided makefile templates accessible by environment variable on a system with MessageAPI C/C++ installed.
 * <p>
 * To make use of this operator, users are asked to configure one required
 * property in the condition constructor map and are allowed to pass in other properties as well:
 * <p>
 * <b>native-library</b>(<i>required</i>, string) - corresponds to a fully
 * qualified path pointing to the native library binary. This is usually a .so,
 * .dll, or .jnilib, depending on operating system and if not self-generated 
 * should be provided to you by the library developer.
 * <p>
 * <b>other key-value parameters</b>(<i>optional</i>, key=string, value=any supported) - the constructor
 * is accessible as a value map within native code, so any other parameters added to the constructor
 * may be used to aid in comparison.
 * <p>
 * 
 * @author Ryan Berkheimer
 */
public class NativeCondition implements IConditionOperator {

    public Map<String, Object> constructorMap = null;
    public IField field = null;
    public ICondition condition = null;
    private native boolean compare(long nativeInstance);
    private synchronized native long create(IField field, ICondition condition);
    private synchronized native void release(long instanceId);

    public NativeCondition(final Map<String, Object> params) {
        this.setConstructor(params);
        this.loadNativeLib((String) params.get("native-library"));
    }

    public void loadNativeLib(final String nativeLibrary) {
        try {
            System.load(nativeLibrary);
        } catch (final Exception e) {
        }
    }

    public boolean compare(final IField field, final ICondition condition) {
        this.setField(field);
        this.setCondition(condition);
        final long nativeInstance = this.create(field, condition);
        final boolean comparison = this.compare(nativeInstance);
        this.release(nativeInstance);
        return comparison;
    }

    public Map<String, Object> getConstructor() {
        return this.constructorMap;
    }

    public IField getField() {
        return this.field;
    }

    public ICondition getCondition() {
        return this.condition;
    }

    private void setField(final IField field) {
        this.field = field;
    }

    private void setCondition(final ICondition condition) {
        this.condition = condition;
    }

    private void setConstructor(final Map<String, Object> constructorMap) {
        this.constructorMap = constructorMap;
    }

}