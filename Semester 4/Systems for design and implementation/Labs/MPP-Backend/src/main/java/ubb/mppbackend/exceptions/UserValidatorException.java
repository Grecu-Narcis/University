package ubb.mppbackend.exceptions;

import java.util.List;

/**
 * A custom exception class representing validation errors related to user data.
 * This exception is typically thrown when there are validation issues with user input.
 * Extends the standard Java {@link Exception} class.
 */
public class UserValidatorException extends Exception {
    /**
     * Constructs a new UserValidatorException with the specified list of validation errors.
     * The validation errors are joined together into a single detail message separated by commas.
     * @param errors The list of validation errors encountered.
     */
    public UserValidatorException(List<String> errors) {
        super(String.join(", ", errors));
    }
}
