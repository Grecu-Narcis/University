import { forwardRef } from 'react';

import { FormEntryProps } from '../../../../types/FormEntryProps.types';

import './FormEntry.css';

const FormEntry = forwardRef<HTMLInputElement, FormEntryProps>((props, ref) => {
    return (
        <div className='form-entry' data-testid='form-entry'>
            <label className='form-label' htmlFor={props.label}>
                {props.label}
            </label>

            <input
                data-testid='form-entry-input'
                type={props.type ? props.type : 'text'}
                className='form-input'
                id={props.label}
                placeholder={props.placeHolder}
                ref={ref}
                defaultValue={props.defaultValue}
                disabled={props.disabled ? true : false}
            />
        </div>
    );
});

export { FormEntry };
