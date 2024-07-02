import './App.css';
import { User } from './models/user';

import { APIProvider } from '@vis.gl/react-google-maps';
import { Routes, Route, BrowserRouter, Navigate } from 'react-router-dom';
import React, { Suspense, useEffect, useState } from 'react';
import LoadingPage from './pages/Loading Page/LoadingPage';
import { PagingContextProvider } from './contexts/PagingContext';
import { convertDtoToUser } from './services/Users Service/UsersService';
import SockJS from 'sockjs-client';
import Stomp from 'stompjs';
import { UserDTO } from './types/UserDTO.types';
import { ConnectionStatusContextProvider } from './contexts/ConnectionStatusContext';
import { endPointUrl } from './services/config';
import CompareCarsContextProvider from './contexts/CompareCarsContext';
import CompareCarsPage from './pages/Compare Cars Page/CompareCarsPage';

const RegistrationPage = React.lazy(() => import('./pages/Registration Page/RegistrationPage'));
const LoginPage = React.lazy(() => import('./pages/Login Page/LoginPage'));
const LandingPage = React.lazy(() => import('./pages/Landing Page/LandingPage'));
const DisplayCarsPage = React.lazy(() => import('./pages/Display Data Page/Display Cars For User Page/DisplayCarsPage'));
const CarDetailsPage = React.lazy(() => import('./pages/Car Details Page/CarFormPage'));
const DisplayDealersPage = React.lazy(() => import('./pages/Display Dealers Page/DisplayDealersPage'));
const AdminDashboardPage = React.lazy(() => import('./pages/Admin Dashboard Page/AdminDashboardPage'));
const ProfilePage = React.lazy(() => import('./pages/Profile Page/ProfilePage'));
const AddCarPage = React.lazy(() => import('./pages/Add Car Page/AddCarPage'));

const pageSize = 3;

document.title = 'TravelWheels';

function App() {
    const [users, setUsers] = useState<User[]>([]);

    const [currentUsers, setCurrentUsers] = useState<User[]>(users.slice(0, pageSize));
    const [currentPage, setCurrentPage] = useState<number>(1);

    useEffect(() => {
        if (!localStorage.getItem('users')) localStorage.setItem('users', JSON.stringify([]));
        // if (!localStorage.getItem('images')) localStorage.setItem('images', JSON.stringify([]));

        // getAllUsers().then((users) => {
        //     setUsers(users);
        //     setCurrentUsers(users.slice(0, pageSize));
        // });

        if (false) {
            const sock = new SockJS(endPointUrl + '/websocket');
            const stompClient = Stomp.over(sock);

            stompClient.connect({}, () => {
                stompClient.subscribe('/topic/users', (message) => {
                    const usersDTO: UserDTO[] = JSON.parse(message.body);
                    const usersReceived = usersDTO.map((userDTO) => convertDtoToUser(userDTO));

                    setUsers((prevState: User[]) => [...prevState, ...usersReceived]);
                });
            });
        }
    }, []);

    return (
        <APIProvider apiKey={import.meta.env.VITE_MAPS_KEY} onLoad={() => console.log('Maps API has loaded.')}>
            <ConnectionStatusContextProvider>
                <PagingContextProvider
                    pagingContext={{
                        currentUsers,
                        setCurrentUsers,
                        currentPage,
                        setCurrentPage,
                        pageSize: pageSize,
                    }}
                >
                    <BrowserRouter>
                        <CompareCarsContextProvider>
                            <Routes>
                                <Route
                                    path='/register'
                                    element={
                                        <Suspense fallback={<LoadingPage />}>
                                            <RegistrationPage />
                                        </Suspense>
                                    }
                                />
                                <Route
                                    path='/login'
                                    element={
                                        <Suspense fallback={<LoadingPage />}>
                                            <LoginPage />
                                        </Suspense>
                                    }
                                />

                                <Route
                                    path='/Home'
                                    element={
                                        <Suspense fallback={<LoadingPage />}>
                                            <LandingPage />
                                        </Suspense>
                                    }
                                />

                                <Route
                                    path='/cars/:userId'
                                    element={
                                        <Suspense fallback={<LoadingPage />}>
                                            <DisplayCarsPage />
                                        </Suspense>
                                    }
                                />

                                <Route
                                    path='/addCar'
                                    element={
                                        <Suspense fallback={<LoadingPage />}>
                                            <AddCarPage />
                                        </Suspense>
                                    }
                                />

                                <Route
                                    path='/viewCar/:carId'
                                    element={
                                        <Suspense fallback={<LoadingPage />}>
                                            <CarDetailsPage />
                                        </Suspense>
                                    }
                                />

                                <Route
                                    path='/viewDealers'
                                    element={
                                        <Suspense fallback={<LoadingPage />}>
                                            <DisplayDealersPage />
                                        </Suspense>
                                    }
                                />

                                <Route
                                    path='/dashboard'
                                    element={
                                        <Suspense fallback={<LoadingPage />}>
                                            <AdminDashboardPage />
                                        </Suspense>
                                    }
                                />

                                <Route
                                    path='/profile'
                                    element={
                                        <Suspense fallback={<LoadingPage />}>
                                            <ProfilePage />
                                        </Suspense>
                                    }
                                />

                                <Route path='/compare' element={<CompareCarsPage />} />
                                <Route path='*' element={<Navigate to={'/home'} />} />
                            </Routes>
                        </CompareCarsContextProvider>
                    </BrowserRouter>
                </PagingContextProvider>
            </ConnectionStatusContextProvider>
        </APIProvider>
    );
}

export default App;
