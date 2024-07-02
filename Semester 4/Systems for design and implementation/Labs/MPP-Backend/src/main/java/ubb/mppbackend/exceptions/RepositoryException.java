package ubb.mppbackend.exceptions;

/**
 * A custom exception class representing an error related to repository operations.
 * This exception is typically thrown when there is a problem with data access or persistence.
 * Extends the standard Java {@link Exception} class.
 */
public class RepositoryException extends Exception {
    /**
     * Constructs a new RepositoryException with the specified detail message.
     * The detail message is used to provide information about the exception.
     * @param message The detail message explaining the reason for the exception.
     */
    public RepositoryException(String message) {
        super(message);
    }
}
