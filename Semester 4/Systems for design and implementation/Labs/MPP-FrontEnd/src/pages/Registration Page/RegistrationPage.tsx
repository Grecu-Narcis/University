import { Link, useNavigate } from 'react-router-dom';
import { RegistrationForm } from '../../features/Authentication/Register Form/RegistrationForm';
import { Layout } from '../../shared/components/layout/Layout';

import './RegistrationPage.css';
import { registerUser } from '../../services/Authentication Service/AuthenticationService';
import { useContext, useEffect, useState } from 'react';
import { ConnectionStatusContext } from '../../contexts/ConnectionStatusContext';
import Loading from 'react-loading';

export default function RegistrationPage() {
    const navigator = useNavigate();
    const [isLoading, setIsLoading] = useState<boolean>(false);

    const connectionContext = useContext(ConnectionStatusContext);

    if (!connectionContext) return;

    const isLoggedIn = connectionContext.isLoggedIn;

    const handleRegister = (firstName: string, lastName: string, email: string, password: string, userRole: string) => {
        setIsLoading(true);

        registerUser(firstName, lastName, email, password, userRole)
            .then(() => {
                setIsLoading(false);
                navigator('/login');
            })
            .catch(() => {
                setIsLoading(false);
            });
    };

    useEffect(() => {
        if (isLoggedIn) {
            navigator('/home');
            return;
        }
    }, []);

    return (
        <Layout>
            <div className='registration-wrapper' data-testid='registration-wrapper'>
                <div className='register-message' data-testid='register-message'>
                    Create a new account
                </div>
                <RegistrationForm handleRegister={handleRegister} />

                <div className='terms-message' data-testid='terms-message'>
                    By signing up, you agree to our Terms and Conditions
                </div>
                <Link to={'/login'} className='login-link'>
                    Already have an account? Login
                </Link>

                <div className='register-loader-wrapper'>
                    {isLoading && <Loading type='spin' color='black' width={'30px'} height={'30px'} />}
                </div>
            </div>
        </Layout>
    );
}
