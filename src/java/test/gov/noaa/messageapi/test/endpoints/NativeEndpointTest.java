package gov.noaa.messageapi.test.endpoints;

import java.util.Map;
import java.util.List;
import java.util.ArrayList;

import gov.noaa.messageapi.interfaces.IEndpoint;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.IPacket;
import gov.noaa.messageapi.interfaces.IProtocolRecord;
import gov.noaa.messageapi.packets.DefaultPacket;
import gov.noaa.messageapi.endpoints.BaseNativeEndpoint;
import gov.noaa.messageapi.fields.DefaultField;

/**
 * <h1>NativeEndpointTest</h1>
 * <b>Description:</b>
 * <p>
 * This Endpoint class tests a simple Native call to a dynamic
 * Library in C.
 * @author Ryan Berkheimer
 */
public class NativeEndpointTest extends BaseNativeEndpoint implements IEndpoint {

    public NativeEndpointTest(Map<String, Object> parameters) {
        super(parameters);
    }

    public IPacket process(IProtocolRecord protocolRecord) {
        DefaultPacket packet = new DefaultPacket();
        return packet;
    }

    /**
     * Returns the default fields for this endpoint. The default fields are number,
     * value, length, file, container-type, container-name
     */
    public List<IField> getDefaultFields() {
        List<IField> fields = new ArrayList<IField>();
        fields.add(new DefaultField("value", "string", true, null, true));
        return fields;
    }

}
