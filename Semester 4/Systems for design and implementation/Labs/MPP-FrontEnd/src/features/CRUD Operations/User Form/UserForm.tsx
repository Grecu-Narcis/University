import { UserFormType } from '../../../types/UserFormProps.types';
import { FormEntry } from './Form Entry/FormEntry';

import './UserForm.css';

function createFormEntries(props: UserFormType) {
    let formEntries = [
        // { label: 'ID', ref: props.idInput, placeHolder: 'ID', defaultValue: '', disabled: false },
        { label: 'First Name', ref: props.firstNameInput, placeHolder: 'First Name', defaultValue: '' },
        { label: 'Last Name', ref: props.lastNameInput, placeHolder: 'Last Name', defaultValue: '' },
        { label: 'URL', ref: props.urlInput, placeHolder: 'URL', defaultValue: '' },
        { label: 'Age', ref: props.ageInput, placeHolder: 'Age', defaultValue: '' },
    ];

    return formEntries;
}

/**
 * UserForm
 * A component that renders a user form based on the provided configuration.
 *
 * Props:
 * - props (UserFormType): An object containing configuration for the form.
 *   - props.firstNameInput: RefObject to the input element for the first name field.
 *   - props.lastNameInput: RefObject to the input element for the last name field.
 *   - props.urlInput: RefObject to the input element for the URL field.
 *   - props.ageInput: RefObject to the input element for the age field.
 *   - props.givenUser (optional): Optional User object representing the current user.
 *
 * Example Usage:
 * <UserForm
 *   firstNameInput={firstNameRef}
 *   lastNameInput={lastNameRef}
 *   urlInput={urlRef}
 *   ageInput={ageRef}
 *   givenUser={currentUser}
 * />
 */
export function UserForm(props: UserFormType) {
    const formEntries = createFormEntries(props);

    return (
        <div className='form-div' data-testid='user-form'>
            <form className='user-form'>
                {formEntries.map((entry) => (
                    <FormEntry
                        key={entry.label}
                        ref={entry.ref}
                        label={entry.placeHolder}
                        placeHolder={entry.placeHolder}
                        defaultValue={entry.defaultValue}
                    />
                ))}
            </form>
        </div>
    );
}
