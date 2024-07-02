import { useEffect, useState } from 'react';
import { useNavigate, useParams } from 'react-router-dom';
import { Car } from '../../../models/car';
import { CarCard } from '../../../features/Display Cars/CarCard';

import './DisplayCarsPage.css';
import { Layout } from '../../../shared/components/layout/Layout';
import { getCarsCountByOwnerId, getPageOfCarsByOwnerId } from '../../../services/Cars Service/CarsService';
import { User } from '../../../models/user';
import LoadingPage from '../../Loading Page/LoadingPage';
import InfiniteScroll from 'react-infinite-scroll-component';
import { getDealerById } from '../../../services/Dealers Service/DealersService';
import DealerMap from '../../../features/Map/DealerMap';
import { getDealerLocation } from '../../../services/Location Service/LocationService';
import { Button } from '../../../shared/components/button/Button';
import QRCodeGenerator from '../../../features/QR Code Generation/QRCodeGenerator';
import ContactForm from '../../../features/Contact Form/ContactForm';

const degreeToRadians = (value: number) => (value * Math.PI) / 180;

/**
 * DisplayCarsPage
 * A component that displays a user's cars with infinite scroll functionality.
 *
 * Props: None
 *
 * Example:
 * <DisplayCarsPage />
 */
export default function DisplayCarsPage() {
    const [cars, setCars] = useState<Car[]>([]);

    const [isLoadingCars, setIsLoadingCars] = useState<boolean>(true);
    const [isLoadingUser, setIsLoadingUser] = useState<boolean>(true);
    const [carsTotal, setCarsTotal] = useState<number>(0);
    const [pageNumber, setPageNumber] = useState<number>(0);
    const [user, setUser] = useState<User>();
    const [latitude, setLatitude] = useState<number>();
    const [longitude, setLongitude] = useState<number>();
    const [distance, setDistance] = useState<number>();

    const navigate = useNavigate();

    const { userId } = useParams();
    if (userId === undefined) {
        navigate('/home');
        return;
    }

    const handleError = () => {
        navigate('/home');
        return;
    };

    const isLoggedIn = () => {
        return localStorage.getItem('authToken') != null;
    };

    const computeDistance = (userPosition: GeolocationPosition) => {
        // Further reference: https://en.wikipedia.org/wiki/Haversine_formula

        const userLatitude = degreeToRadians(userPosition.coords.latitude);
        const userLongitude = degreeToRadians(userPosition.coords.longitude);
        const dealerLatitude = degreeToRadians(latitude!);
        const dealerLongitude = degreeToRadians(longitude!);

        const deltaLatitude = dealerLatitude - userLatitude;
        const deltaLongitude = dealerLongitude - userLongitude;

        const a =
            Math.sin(deltaLatitude / 2) * Math.sin(deltaLatitude / 2) +
            Math.cos(userLatitude) * Math.cos(dealerLatitude) * Math.sin(deltaLongitude / 2) * Math.sin(deltaLongitude / 2);
        const c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));
        const R = 6371; // Earth's radius in kilometers
        const distance = R * c;

        setDistance(distance);
    };

    const fetchCars = () => {
        getPageOfCarsByOwnerId(parseInt(userId), pageNumber, 50)
            .then((response) => {
                setCars([...cars, ...response]);
                setPageNumber(pageNumber + 1);
            })
            .catch(handleError);
    };

    useEffect(() => {
        getPageOfCarsByOwnerId(parseInt(userId), pageNumber, 50)
            .then((response) => {
                setCars(response);
                setIsLoadingCars(false);
                setPageNumber(pageNumber + 1);
            })
            .catch(handleError);

        getCarsCountByOwnerId(parseInt(userId))
            .then((response) => {
                setCarsTotal(response);
            })
            .catch(handleError);

        getDealerById(userId)
            .then((response) => {
                setUser(response);
                setIsLoadingUser(false);
            })
            .catch(handleError);

        getDealerLocation(parseInt(userId)).then((response) => {
            setLatitude(response.data.latitude);
            setLongitude(response.data.longitude);
        });
    }, []);

    if (isLoadingCars || isLoadingUser) return <LoadingPage />;

    return (
        <Layout userId={parseInt(userId)}>
            <h1 data-testid='username'>{user?.getFirstName() + ' ' + user?.getLastName()}</h1>
            <h2>{carsTotal == 0 ? 'No cars available' : carsTotal === 1 ? 'One car available.' : `${carsTotal} cars available.`}</h2>

            <QRCodeGenerator />

            <div className='cars-list' id='scroll-div'>
                <InfiniteScroll
                    dataLength={cars.length}
                    next={fetchCars}
                    hasMore={carsTotal > cars.length}
                    loader={<h4>Loading...</h4>}
                    className='infinite-scroll-grid'
                    scrollableTarget='scroll-div'
                    height={600}
                >
                    {cars.map((car) => (
                        <CarCard
                            key={car.getId()}
                            givenCar={car}
                            readOnly={userId != localStorage.getItem('userId') && localStorage.getItem('userRole') != 'ADMIN'}
                        />
                    ))}
                </InfiniteScroll>

                {localStorage.getItem('userRole') != 'MANAGER' && latitude && longitude && (
                    <>
                        <div className='contact-wrapper'>Contact us</div>
                        <DealerMap latitude={latitude} longitude={longitude} />

                        <div className='distance-wrapper'>
                            {distance ? (
                                <div>You are {Math.round(distance)} km away.</div>
                            ) : (
                                <Button
                                    type='button'
                                    buttonMessage='Compute distance'
                                    className='distance-button'
                                    onClick={() => navigator.geolocation.getCurrentPosition(computeDistance)}
                                />
                            )}{' '}
                        </div>
                    </>
                )}

                {localStorage.getItem('userRole') != 'MANAGER' && isLoggedIn() && <ContactForm email={user!.getEmail()} />}
            </div>
        </Layout>
    );
}
