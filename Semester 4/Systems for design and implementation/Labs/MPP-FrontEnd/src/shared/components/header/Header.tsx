import { Link, useNavigate } from 'react-router-dom';

import './Header.css';
import { useContext, useEffect, useState } from 'react';
import { getImageByUserId } from '../../../services/Images Service/ImagesService';
import { ConnectionStatusContext } from '../../../contexts/ConnectionStatusContext';
import { Button } from '../button/Button';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faRightFromBracket } from '@fortawesome/free-solid-svg-icons';

const Header = () => {
    const [profileImage, setProfileImage] = useState<string>();
    const [userRole, setUserRole] = useState<string>();

    const connectionContext = useContext(ConnectionStatusContext);

    if (!connectionContext) return;

    const isLoggedIn = connectionContext.isLoggedIn;
    const handleLogout = connectionContext.handleLogout;

    const navigator = useNavigate();

    const handleLogoutClick = () => {
        handleLogout();
        navigator('/home');
    };

    useEffect(() => {
        if (!localStorage.getItem('userId')) return;
        const userId = parseInt(localStorage.getItem('userId')!);

        if (localStorage.getItem('userRole')) setUserRole(localStorage.getItem('userRole')!);

        const cachedProfileImage = localStorage.getItem('profileImage');

        if (cachedProfileImage) setProfileImage(cachedProfileImage);
        else if (userId)
            getImageByUserId(userId).then((response) => {
                setProfileImage(response);
                localStorage.setItem('profileImage', response);
            });
    }, []);

    return (
        <div className='header' data-testid='header-test-id'>
            <nav className='navbar'>
                <Link to={'/home'} className='title'>
                    TravelWheels
                </Link>
                <div className='links'>
                    <Link to={'/home'} className='link'>
                        Home
                    </Link>

                    <Link to={'/viewDealers'} className='link'>
                        View dealers
                    </Link>
                    {isLoggedIn ? (
                        <>
                            {userRole && userRole === 'MANAGER' && (
                                <>
                                    <Link to={'/cars/' + localStorage.getItem('userId')} className='link'>
                                        View cars
                                    </Link>

                                    <Link to={'/addCar'} className='link'>
                                        Add car
                                    </Link>
                                </>
                            )}

                            {userRole && userRole === 'ADMIN' && (
                                <Link to={'/dashboard'} className='link'>
                                    Dashboard
                                </Link>
                            )}

                            {profileImage && (
                                <Link to={'/profile'}>
                                    {' '}
                                    <img src={'data:image/jpeg;base64,' + profileImage} className='profile-image link' />{' '}
                                </Link>
                            )}
                            <FontAwesomeIcon icon={faRightFromBracket} className='logout-icon' onClick={handleLogoutClick} />
                        </>
                    ) : (
                        <>
                            <Link to={'/login'} className='login-button'>
                                <Button type='button' buttonMessage='Log in' margin='0' />
                            </Link>

                            <Link to={'/register'} className='logout-button'>
                                <Button type='button' buttonMessage='Sign up' margin='0' backgroundColor='#E5E7E9' textColor='black' />
                            </Link>
                        </>
                    )}
                </div>
            </nav>
        </div>
    );
};

export { Header };
