import { Link } from 'react-router-dom';
import { Button } from '../../../shared/components/button/Button';
import { LoginFormProps } from '../../../types/LoginFormProps.types';
import { FormEntry } from '../../CRUD Operations/User Form/Form Entry/FormEntry';

import './LoginForm.css';
import { useRef } from 'react';

function getEmailAndPasswordFromInputs(emailInput: React.RefObject<HTMLInputElement>, passwordInput: React.RefObject<HTMLInputElement>) {
    if (!emailInput.current || !passwordInput.current) throw new Error('Input refs not defined!');

    return {
        email: emailInput.current.value,
        password: passwordInput.current.value,
    };
}

//TODO: make the form responsive!!

export function LoginForm({ handleLogin }: LoginFormProps) {
    const emailInput = useRef<HTMLInputElement>(null);
    const passwordInput = useRef<HTMLInputElement>(null);

    const handleOnClick = () => {
        try {
            const { email, password } = getEmailAndPasswordFromInputs(emailInput, passwordInput);

            handleLogin(email, password);
        } catch (e) {
            alert((e as Error).message);
        }
    };

    return (
        <>
            <form className='login-form'>
                <FormEntry label='Email' placeHolder='Email' ref={emailInput} />
                <FormEntry label='Password' placeHolder='Password' type='password' ref={passwordInput} />

                <div className='login-options'>
                    <Button type='button' buttonMessage='Login' margin='1rem 0' onClick={handleOnClick} />
                    <Link to='/register' className='register-link' data-testid='register-link'>
                        New to Rentify? Create an account.
                    </Link>
                </div>
            </form>
        </>
    );
}
