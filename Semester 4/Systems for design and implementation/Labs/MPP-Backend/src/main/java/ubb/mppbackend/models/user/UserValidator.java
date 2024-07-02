package ubb.mppbackend.models.user;

import ubb.mppbackend.exceptions.UserValidatorException;

import java.util.*;

/**
 * Utility class for validating User objects.
 */
public class UserValidator {
    /**
     * Validates a User object to ensure it meets certain criteria.
     *
     * @param userToValidate  The User object to be validated.
     * @throws UserValidatorException  Thrown if the validation fails, containing a list of validation errors.
     */
    public static void validate(User userToValidate) throws UserValidatorException {
        List<String> errors = new ArrayList<>();

        if (userToValidate.getFirstName().length() < 3)
            errors.add("First name is too short");

        if (userToValidate.getLastName().length() < 3)
            errors.add("Last name is too short");

        if (!errors.isEmpty())
            throw new UserValidatorException(errors);
    }
}
