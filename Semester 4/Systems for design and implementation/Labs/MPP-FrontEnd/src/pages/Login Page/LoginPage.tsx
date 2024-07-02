import { LoginForm } from '../../features/Authentication/Login Form/LoginForm';
import { Layout } from '../../shared/components/layout/Layout';

import './LoginPage.css';
import { loginUser } from '../../services/Authentication Service/AuthenticationService';
import { useNavigate } from 'react-router-dom';
import { LoginResponseDTO } from '../../types/LoginResponseDTO.types';
import { useContext, useEffect, useState } from 'react';
import { ConnectionStatusContext } from '../../contexts/ConnectionStatusContext';
import Loading from 'react-loading';

export default function LoginPage() {
    const navigator = useNavigate();
    const [isLoading, setIsLoading] = useState<boolean>(false);
    const [errorMessage, setErrorMessage] = useState<string>();

    const connectionContext = useContext(ConnectionStatusContext);
    if (!connectionContext) return;

    const isLoggedIn = connectionContext.isLoggedIn;
    const setIsLoggedIn = connectionContext.setIsLoggedIn;

    const handleLogin = (email: string, password: string) => {
        setIsLoading(true);

        loginUser(email, password)
            .then((loginResponse: LoginResponseDTO) => {
                console.log(loginResponse.accessToken);
                localStorage.setItem('authToken', loginResponse.accessToken);
                localStorage.setItem('userId', loginResponse.userId.toString());
                localStorage.setItem('userRole', loginResponse.userRole);

                setIsLoggedIn(true);

                loginResponse.userRole === 'USER' ? navigator('/viewDealers') : navigator('/cars/' + loginResponse.userId);

                setIsLoading(false);
                setErrorMessage(undefined);
            })
            .catch((error) => {
                setErrorMessage((error as Error).message);
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
            <div className='login-wrapper' data-testid='login-wrapper'>
                <div className='login-welcome-message' data-testid='login-welcome-message'>
                    Welcome to TravelWheels
                </div>
                <div className='login-message'>Sign in to your account</div>

                <LoginForm handleLogin={handleLogin} />

                <div className='error-message' data-testid='error-message'>
                    {errorMessage && <div>{errorMessage}</div>}
                </div>
                <div className='login-loader-wrapper'>
                    {isLoading && <Loading type='spin' color='black' width={'30px'} height={'30px'} />}
                </div>
            </div>
        </Layout>
    );
}
