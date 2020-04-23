package gov.noaa.messageapi.interfaces;

import java.util.List;

/**
 * Responses are the processing center and result aggregation repository
 * for requests. When a request is submitted,
 * it immediately returns a response, which executes
 * any processing steps (validation, factoring, transformation, etc.)
 * in sequence, eventually yielding a set of returned data packets from
 * endpoint connections, where it combines them and sets a response
 * list of records, list of rejections, and changes the isComplete boolean
 * to true.
 * @author Ryan Berkheimer
 */
public interface IResponse {

    /**
     * Returns true or false, depending on if all processing
     * within the response is complete.
     */
    public boolean isComplete();

    /**
     * Returns the associated request that the response is
     * responsible for processing. The request is typically
     * deep-copied when submitted, so it will contain the exact
     * conditions it did at the time of calling submit.
     */
    public IRequest getRequest();

    /**
     * Returns the list of rejections as applied to the request that is
     * contained by the response.
     */
    public List<IRejection> getRejections();

    /**
     * Returns the list of records added to the response as a result
     * of any processing done within the associated request.
     */
    public List<IRecord> getRecords();

    /**
     * Sets the records in the response to the passed record list.
     * This replaces any existing records in the response.
     */
    public void setRecords(List<IRecord> records);

    /**
     * Sets the rejections in the response to the passed rejection list.
     * This replaces any existing rejections in the response.
     */
    public void setRejections(List<IRejection> rejections);

    /**
     * Sets the completion status of the response. This value should be set to
     * true when all request processing is complete, so the caller knows that
     * there are no more records or rejections coming through for the current
     * submission. 
     */
    public void setComplete(boolean isComplete);


}
