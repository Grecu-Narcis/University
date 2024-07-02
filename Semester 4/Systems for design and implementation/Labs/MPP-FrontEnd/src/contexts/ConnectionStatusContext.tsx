import { createContext, useEffect, useState } from 'react';
import { ConnectionStatusProps } from '../types/ConnectionStatusProps.types';
import { addMissingUsers, checkServerStatus } from '../services/Users Service/UsersService';
import { UserDTO } from '../types/UserDTO.types';
import NotificationCard from '../features/Notification Card/NotificationCard';

export const ConnectionStatusContext = createContext<ConnectionStatusProps | null>(null);

/**
 * Provides a context to monitor connection status and server availability.
 */
function ConnectionStatusContextProvider({ children }: any) {
    const [isOnline, setIsOnline] = useState<boolean>(navigator.onLine);
    const [isServerOnline, setIsServerOnline] = useState<boolean>(true);
    const [isLoggedIn, setIsLoggedIn] = useState<boolean>(localStorage.getItem('authToken') !== null);

    const handleLogout = () => {
        setIsLoggedIn(false);
        localStorage.removeItem('userId');
        localStorage.removeItem('authToken');
        localStorage.removeItem('userRole');
        localStorage.removeItem('profileImage');
    };

    useEffect(() => {
        const connectionInterval = setInterval(() => {
            setIsOnline(navigator.onLine);
            checkServerStatus()
                .then((result) => {
                    setIsServerOnline(result);

                    const users: UserDTO[] = JSON.parse(localStorage.getItem('users')!);

                    if (result) localStorage.setItem('users', JSON.stringify([]));

                    if (isOnline && users.length > 0) {
                        addMissingUsers(users);
                    }
                })
                .catch(() => {
                    setIsServerOnline(false);
                });
        }, 2000);

        return () => clearInterval(connectionInterval);
    }, []);

    const connectionStatusContext = {
        isOnline,
        setIsOnline,
        isServerOnline,
        setIsServerOnline,
        isLoggedIn,
        setIsLoggedIn,
        handleLogout,
    };

    return (
        <ConnectionStatusContext.Provider value={connectionStatusContext}>
            {(!isOnline || !isServerOnline) && (
                <NotificationCard>{!isOnline ? 'Ooops... no internet connection!' : 'Ooops... the server is down!'}</NotificationCard>
            )}
            {children}
        </ConnectionStatusContext.Provider>
    );
}

export { ConnectionStatusContextProvider };
