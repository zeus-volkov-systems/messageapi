package gov.noaa.messageapi.test.endpoints;

import java.util.Map;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.stream.Collectors;

import java.io.IOException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;

import gov.noaa.messageapi.interfaces.IEndpoint;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.IPacket;
import gov.noaa.messageapi.interfaces.IProtocolRecord;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.packets.DefaultPacket;
import gov.noaa.messageapi.utils.general.ListUtils;
import gov.noaa.messageapi.endpoints.BaseEndpoint;
import gov.noaa.messageapi.fields.DefaultField;

import org.apache.commons.net.ftp.FTPClient;
import org.apache.commons.net.ftp.FTPFile;
import org.apache.commons.net.ftp.FTPReply;


/**
 * <h1>FtpCopier</h1> <b>Description:</b>
 * <p>
 * The core action of this endpoint is retrieving resources from an FTP endpoint
 * and writing them to a specified location. Which resources to retrieve are
 * specified in records that flow through the endpoint. Records can come from
 * collections, transformations, or classifiers.
 * <p>
 * Errors in FTP retrieval, whether due to inaccessibility, missing parameters,
 * incomplete retrieval, or otherwise, will be recorded as a rejection and
 * returned in the response. Incomplete retrieval will result in the endpoint
 * removing any incomplete transfer if possible. If not possible to remove
 * incomplete transactions, a rejection record will be returned stating as much.
 * <p>
 * The lists of assembled records and rejections will be added to the DataPacket
 * returned by this Endpoint.
 * <p>
 * <h2>Required Record Fields</h2> Records that are to be processed in this
 * endpoint, whether passed through a transformation, classifier, or collection,
 * should have fields that contain resources to retrieve. The name of these
 * fields is arbitrary and is specified in the configuration.
 * <p>
 * <h2>Configuration Parameters</h2> <b>resource-fields</b>(required)
 * (String,List(String)): The name of the fields containing resources to be
 * retrieved. The endpoint looks at these fields expecting a complete path
 * relative to the server. For example, if records contain a field 'file' that
 * contains a file named om2.tar.gZ at /asos/hidden/onemin to retrieve, the
 * config should list resource-fields: 'file', And the endpoint should be passed
 * with a field 'file'='/asos/hidden/onemin/om2.tar.gZ'. If the records contain
 * multiple fields with resources to retrieve, they should all be listed in the
 * config as resource-fields: ['field1', 'field2']. All of these fields will be
 * processed for every record.
 * <p>
 * <b>server</b> (required) (String): The server to connect to - e.g.,
 * ftp.ncdc.noaa.gov
 * <p>
 * <b>port</b> (optional) (Integer): The port on the server to connect -
 * defaults to 21
 * <p>
 * <b>user</b>(optional) (String): The name of the user to connect as. Defaults
 * to anonymous.
 * <p>
 * <b>password</b>(optional) (String): The password for the user. Defaults to
 * guest.
 * <p>
 * <b>overwrite</b>(optional) (Boolean): Specifies whether to overwrite existing
 * files if found. 
 * <p>
 * <h2>Default Return Fields</h2> Below lists the fields returned in each
 * response record by default. The fields can be limited by specifying a subset
 * in the configuration map.
 * <p>
 * <b>name: </b>Name of the resource
 * <p>
 * <b>server: </b>The ftp server hosting the resource
 * <p>
 * <b>path: </b>Directory the resource was found at relative to the server
 * <p>
 * <b>size: </b>Size of the resource in bytes.
 * <p>
 * <b>type: </b>Type of the resource (file, directory, symlink, unknown).
 * <p>
 * <b>modified: </b>Date of the last modification of the resource. Format is
 * specified by the passed date-format config param. If none specified there,
 * defaults to yyyy-MM-dd HH:mm:ss
 * 
 * @author Ryan Berkheimer
 */
public class FtpCopier extends BaseEndpoint implements IEndpoint {

    private String server = null;
    private Integer port = 21;
    private String user = "anonymous";
    private String password = "guest";
    private Boolean recursive = false;
    private List<String> directoryFields = null;
    private String dateFormat = "yyyy-MM-dd HH:mm:ss";
    private DateFormat dateFormatter;
    private FTPClient ftpClient;

    public FtpCopier(Map<String,Object> parameters) {
        super(parameters);
        this.setServer(parameters);
        this.setPort(parameters);
        this.setUser(parameters);
        this.setPassword(parameters);
        this.setRecursive(parameters);
        this.setDateFormat(parameters);
        this.setDateFormatter(this.getDateFormat());
        this.setDirectoryFields(parameters);
        this.setFtpClient();
    }

    public IPacket process(IProtocolRecord protocolRecord) {
        DefaultPacket packet = new DefaultPacket();
        Boolean connectionStatus = this.connectFtpClient();
        if (connectionStatus) {
            try {
                List<IRecord> collectionRecords = this.processCollections(protocolRecord);
                packet.addRecords(collectionRecords);
                List<IRecord> classifierRecords = this.processClassifiers(protocolRecord);
                packet.addRecords(classifierRecords);
                List<IRecord> transformationRecords = this.processTransformations(protocolRecord);
                packet.addRecords(transformationRecords);
                this.disconnectFtpClient();
            } catch (Exception e) {
                this.disconnectFtpClient();
            }
        }
        return packet;
    }

    private Boolean connectFtpClient() {
        try {
            this.getFtpClient().connect(this.getServer(), this.getPort());
            if (!FTPReply.isPositiveCompletion(ftpClient.getReplyCode())) {
                return false;
            }
            if (ftpClient.login(this.getUser(), this.getPassword())) {
                return true;
            }
        } catch(Exception e) {
            return false;
        }
        return false;
    }

    private void disconnectFtpClient() {
        if (this.getFtpClient().isConnected()) {
            try {
                this.getFtpClient().logout();
                this.getFtpClient().disconnect();
            } catch (Exception e) {}
        }
    }

    private List<IRecord> processCollections(IProtocolRecord protocolRecord) throws IOException {
        return ListUtils.removeAllNulls(ListUtils.flatten(this.getCollections().stream().map(collection -> {
            return ListUtils.flatten(protocolRecord.getRecordsByCollection(collection).parallelStream().map(record -> {
                return ListUtils.flatten(this.getDirectoryFields().stream().map(directoryField -> {
                    if (record.hasField(directoryField)) {
                        try {
                            return this.createResourceRecords((String) record.getField(directoryField).getValue());
                        } catch (Exception e) {
                            return null;
                        }
                    }
                    return null;
                }).collect(Collectors.toList()));
            }).collect(Collectors.toList()));
        }).collect(Collectors.toList())));
    }


    private List<IRecord> processClassifiers(IProtocolRecord protocolRecord) throws IOException {
        return ListUtils.removeAllNulls(ListUtils.flatten(this.getClassifiers().stream().map(classifier -> {
            return ListUtils.flatten(protocolRecord.getRecordsByClassifier(classifier.getKey(), classifier.getValue())
                    .parallelStream().map(record -> {
                        return ListUtils.flatten(this.getDirectoryFields().stream().map(directoryField -> {
                            if (record.hasField(directoryField)) {
                                try {
                                    return this.createResourceRecords((String) record.getField(directoryField).getValue());
                                } catch (Exception e) {
                                    return null;
                                }
                            }
                            return null;
                        }).collect(Collectors.toList()));
                    }).collect(Collectors.toList()));
        }).collect(Collectors.toList())));
    }

    private List<IRecord> processTransformations(IProtocolRecord protocolRecord) throws IOException {
        return ListUtils.removeAllNulls(ListUtils.flatten(this.getTransformations().stream().map(transformation -> {
            return ListUtils.flatten(protocolRecord.getRecordsByTransformation(transformation).parallelStream().map(record -> {
                return ListUtils.flatten(this.getDirectoryFields().stream().map(directoryField -> {
                    if (record.hasField(directoryField)) {
                        try {
                            return this.createResourceRecords((String) record.getField(directoryField).getValue());
                        } catch (Exception e) {
                            return null;
                        }
                    }
                    return null;
                }).collect(Collectors.toList()));
            }).collect(Collectors.toList()));
        }).collect(Collectors.toList())));
    }

    private List<IRecord> createResourceRecords(String directoryName) {
        try {
            FTPFile[] resources = this.getFtpClient().listFiles(directoryName);
            if (resources != null && resources.length > 0) {
                List<List<IRecord>> records = Arrays.stream(resources).map(resource -> {
                    String resourceName = resource.getName();
                    if (resourceName.equals(".") || resourceName.equals("..")) {
                        return null;
                    }
                    if (resource.isDirectory() && this.getRecursive()) {
                        List<IRecord> recursiveRecords = this.createResourceRecords(String.format("%s/%s", directoryName, resource.getName()));
                        recursiveRecords.addAll(this.createResourceRecord(resource, directoryName));
                        return recursiveRecords;
                    }
                    return this.createResourceRecord(resource, directoryName);
                }).collect(Collectors.toList());
                return ListUtils.flatten(records);
            }
        } catch (Exception e) {}
        List<IRecord> emptyRecords = new ArrayList<IRecord>();
        return emptyRecords;
    }

    private List<IRecord> createResourceRecord(FTPFile resource, String directoryName) {
        List<IRecord> returnRecords = new ArrayList<IRecord>();
        IRecord record = this.createRecord();
        if (record.hasField("name")) {
            record.setField("name", resource.getName());
        }
        if (record.hasField("server")) {
            record.setField("server", this.getServer());
        }
        if (record.hasField("path")) {
            record.setField("path", directoryName);
        }
        if (record.hasField("size")) {
            record.setField("size", resource.getSize());
        }
        if (record.hasField("type")) {
            if (resource.isDirectory()) {
                record.setField("type", "directory");
            } else if (resource.isFile()) {
                record.setField("type", "file");
            } else if (resource.isSymbolicLink()) {
                record.setField("type", "symlink");
            } else if (resource.isUnknown()) {
                record.setField("type", "unknown");
            }
        }
        if (record.hasField("modified")) {
            record.setField("modified", this.getDateFormatter().format(resource.getTimestamp().getTime()));
        }
        returnRecords.add(record);
        return returnRecords;
    }

    /**
     * Returns the default fields for this endpoint. The default fields are
     * name, path, size (in bytes), type (file or directory), and modified.
     */
    public List<IField> getDefaultFields() {
        List<IField> fields = new ArrayList<IField>();
        fields.add(new DefaultField("name", "string", true, null, true));
        fields.add(new DefaultField("server", "string", true, null, true));
        fields.add(new DefaultField("path", "string", true, null, true));
        fields.add(new DefaultField("size", "integer", true, null, true));
        fields.add(new DefaultField("type", "string", true, null, true));
        fields.add(new DefaultField("modified", "string", true, null, true));
        return fields;
    }


    /**
     * Sets the server from the configuration map. Server is a required config parameter
     * for an ftp connection. If no server is specified, this method throws an error
     * during endpoint connection creation, halting the program.
     */
    private void setServer(Map<String, Object> parameters) {
        if (parameters.containsKey("server")) {
            this.server = (String) parameters.get("server");
        } else {
            throw new Error("Missing required configuration parameter 'server' in FtpLister endpoint.");
        }
    }

    private void setPort(Map<String,Object> parameters) {
        if (parameters.containsKey("port")) {
            if (parameters.get("port") instanceof String) {
                this.port = Integer.parseInt((String) parameters.get("port"));
            } else if (parameters.get("port") instanceof Integer) {
                this.port = (Integer) parameters.get("port");
            }
        }
    }

    private void setUser(Map<String, Object> parameters) {
        if (parameters.containsKey("user")) {
            this.user = (String) parameters.get("user");
        }
    }

    private void setPassword(Map<String, Object> parameters) {
        if (parameters.containsKey("password")) {
            this.password = (String) parameters.get("password");
        }
    }

    private void setDateFormat(Map<String, Object> parameters) {
        if (parameters.containsKey("date-format")) {
            this.dateFormat = (String) parameters.get("date-format");
        }
    }

    private void setRecursive(Map<String,Object> parameters) {
        if (parameters.containsKey("recursive")) {
            try {
                this.recursive = (Boolean) parameters.get("recursive");
            } catch (Exception e) {
                throw new Error("Could not parse the specified recursive parameter in FtpLister. Should be boolean true or false.");
            }
        }
    }

    private void setDateFormatter(String dateFormat) {
        try {
            this.dateFormatter = new SimpleDateFormat(this.getDateFormat());
        } catch (Exception e) {
            throw new Error("Could not set the date format with the specified date-format string in FtpLister. Please check the configuration.");
        }
    }

    private void setFtpClient() {
        this.ftpClient = new FTPClient();
    }

    @SuppressWarnings("unchecked")
    private void setDirectoryFields(Map<String,Object> parameters) {
        if (parameters.containsKey("directory-fields")) {
            Object directoryFields = parameters.get("directory-fields");
            if (directoryFields instanceof String) {
                this.directoryFields = new ArrayList<String>();
                this.directoryFields.add((String) directoryFields);
            } else if (directoryFields instanceof List) {
                this.directoryFields = ((List<Object>) directoryFields).stream().map(ff -> (String) ff)
                        .collect(Collectors.toList());
            }
        } else {
            throw new Error("Missing required configuration parameter 'directory-fields' in FtpLister endpoint.");
        }
    }

    private FTPClient getFtpClient() {
        return this.ftpClient;
    }

    private DateFormat getDateFormatter() {
        return this.dateFormatter;
    }

    private String getServer() {
        return this.server;
    }

    private Integer getPort() {
        return this.port;
    }

    private String getUser() {
        return this.user;
    }

    private String getPassword() {
        return this.password;
    }

    private String getDateFormat() {
        return this.dateFormat;
    }

    private Boolean getRecursive() {
        return this.recursive;
    }

    private List<String> getDirectoryFields() {
        return this.directoryFields;
    }

}
